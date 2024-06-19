# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Copyright 2014 Carlos Bederián
# $Id: connection.py 455 2011-05-01 00:32:09Z carlos $

import socket
import re
import os
import select
from constants import *
from base64 import b64encode, b64decode


class Connection(object):
    """
    Conexión punto a punto entre el servidor y un cliente.
    Se encarga de satisfacer los pedidos del cliente hasta que termina la conexión.
    """

    def __init__(self, socket, directory):
        self.socket = socket
        self.connected = True
        self.directory = directory
        self.buffer = ''
        if not os.path.exists(self.directory):
            os.makedirs(self.directory)

    def handle(self):
        """
        Atiende eventos de la conexión hasta que termina.
        """
        try:
            while self.connected:
                # Verifica si hay sockets para leer en la conexión
                ready_to_read, _, _ = select.select([self.socket], [], [], 0.1)
                # Si hay sockets para leer en la conexión los procesa
                if self.socket in ready_to_read:
                    data = self.socket.recv(4096).decode("utf-8")
                    if not data:
                        self.socket.close()
                        break
                    self.buffer += data
                    self._process_buffer()
                # Si no hay sockets para leer en la conexión sale del bucle
                else:
                    break
            if not self.connected:
                self._close_connection()
        except Exception as e:
            self._close_connection()

    def _process_buffer(self):
        """
        Procesa el buffer de la conexión, buscando comandos completos.
        """
        eol_index = self.buffer.find(EOL)
        while eol_index != -1:
            line = self.buffer[:eol_index]
            self.process_command(line)
            self.buffer = self.buffer[eol_index + len(EOL):]
            eol_index = self.buffer.find(EOL)

    def process_command(self, data):
        """
        Procesa un comando recibido del cliente.
        """
        command_parts = data.split()
        command_name = command_parts[0]

        if re.findall(r"\n(?!\r)", data):
            self._send_response(status_format(BAD_EOL))
            self.connected = False
            return
        try:
            handlers = {
                "quit": self._handle_quit,
                "get_file_listing": self._handle_get_file_listing,
                "get_metadata": self._handle_get_metadata,
                "get_slice": self._handle_get_slice
            }
            handler = handlers.get(
                command_name, lambda x: status_format(INVALID_COMMAND))
            self._send_response(handler(command_parts))
        except Exception as e:
            self._send_response(status_format(INTERNAL_ERROR))

    def _handle_quit(self, command_parts):
        """
        Prepara la desconexión del cliente.
        """
        if len(command_parts) == 1:
            self.connected = False
            return status_format(CODE_OK)
        else:
            return status_format(INVALID_ARGUMENTS)

    def _handle_get_file_listing(self, command_parts):
        """
        Lista todos los archivos del directorio.
        """
        if len(command_parts) == 1:
            response = status_format(CODE_OK)
            files = [f for f in os.listdir(self.directory) if os.path.isfile(
                os.path.join(self.directory, f))]
            for file in files:
                response += f"{file}{EOL}"
            response += f"{EOL}"
        else:
            response = status_format(INVALID_ARGUMENTS)

        return response

    def _handle_get_metadata(self, command_parts):
        """
        Devuelve el tamaño en bytes de un archivo.
        """
        if len(command_parts) == 2:
            file_name = command_parts[1]
            file = os.path.join(self.directory, file_name)
            if os.path.exists(file):
                response = status_format(CODE_OK)
                response += f"{os.path.getsize(file)}{EOL}"
            else:
                response = status_format(FILE_NOT_FOUND)
        else:
            response = status_format(INVALID_ARGUMENTS)

        return response

    def _handle_get_slice(self, command_parts):
        """
        Devuelve un fragmento de texto de un archivo expresado en base64.
        """
        if len(command_parts) == 4 and command_parts[2].isdigit() and command_parts[3].isdigit():
            offset = int(command_parts[2])
            size = int(command_parts[3])
            file_path = os.path.join(self.directory, command_parts[1])

            if not os.path.exists(file_path):
                return status_format(FILE_NOT_FOUND)

            with open(file_path, "rb") as file:
                file_data = file.read()

            file_size = os.path.getsize(file_path)
            if offset > file_size or offset < 0 or size > file_size - offset:
                return status_format(BAD_OFFSET)

            file_data = file_data[offset: offset + size]
            encoded_data = b64encode(file_data)

            response = status_format(CODE_OK)
            response += f"{encoded_data.decode('utf-8')}{EOL}"
        else:
            response = status_format(INVALID_ARGUMENTS)

        return response

    def _close_connection(self):
        """
        Cierra la conexión con el cliente.
        """
        self.socket.close()

    def _send_response(self, response):
        """
        Envía una respuesta al cliente.
        """
        self.socket.send(response.encode("utf-8"))
