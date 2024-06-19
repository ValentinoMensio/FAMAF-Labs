#!/usr/bin/env python
# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Revisión 2014 Carlos Bederián
# Revisión 2011 Nicolás Wolovick
# Copyright 2008-2010 Natalia Bidart y Daniel Moisset
# $Id: server.py 656 2013-03-18 23:49:11Z bc $

import optparse
import socket
import select
from connection_PE import Connection
from constants import *
import threading


class Server(object):
    """
    El servidor, que crea y atiende el socket en la dirección y puerto
    especificados donde se reciben nuevas conexiones de clientes.
    """

    def __init__(self, addr=DEFAULT_ADDR, port=DEFAULT_PORT,
                 directory=DEFAULT_DIR):
        print("Serving %s on %s:%s." % (directory, addr, port))
        # FALTA: Crear socket del servidor, configurarlo, asignarlo
        # a una dirección y puerto, etc.

        # Crear socket del servidor
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Configurar socket del servidor
        self.server_socket.bind((addr, port))
        # Permitir una conexión a la vez
        self.server_socket.listen(5)
        # Guarda el directorio compartido
        self.directory = directory

        # Crear el objeto poll
        self.poll_object = select.poll()
        # Registrar el socket del servidor en el objeto poll
        self.poll_object.register(self.server_socket.fileno(), select.POLLIN)
        # Diccionario de conexiones (almacena las conexiones activas)
        self.connections = {}

    def serve(self):
        """
        Atiende conexiones de clientes entrantes utilizando poll.
        """
        while True:
            # Esperar por eventos en los sockets registrados
            events = self.poll_object.poll()
            for fileno, event in events:
                # Si el evento se origina en el socket del servidor indica que hay una nueva conexión.
                if fileno == self.server_socket.fileno():
                    # Aceptar una conexión del cliente
                    client_socket, client_address = self.server_socket.accept()
                    print("Connection from %s:%s" % client_address)
                    # Crear una nueva conexión para el cliente
                    conn = Connection(client_socket, self.directory)
                    # Registrar el socket del cliente en el objeto poll
                    self.poll_object.register(
                        client_socket.fileno(), select.POLLIN)
                    # Guardar la conexión en el diccionario
                    self.connections[client_socket.fileno()] = conn
                # Si el evento es de lectura indica que es un socket de un cliente existente
                elif event & select.POLLIN:
                    # Recuperamos la conexión del diccionario
                    conn = self.connections[fileno]
                    # Si la conexión existe indica que es
                    if conn:
                        conn.handle()
                    # Si la conexión no existe indica que se cerró (quit)
                    if not conn.connected:
                        # Si no hay conexión, se cierra el socket
                        self.poll_object.unregister(fileno)
                        del self.connections[fileno]
                        print("Connection closed")


def main():
    """Parsea los argumentos y lanza el server"""

    parser = optparse.OptionParser()
    parser.add_option(
        "-p", "--port",
        help="Número de puerto TCP donde escuchar", default=DEFAULT_PORT)
    parser.add_option(
        "-a", "--address",
        help="Dirección donde escuchar", default=DEFAULT_ADDR)
    parser.add_option(
        "-d", "--datadir",
        help="Directorio compartido", default=DEFAULT_DIR)

    options, args = parser.parse_args()
    if len(args) > 0:
        parser.print_help()
        sys.exit(1)
    try:
        port = int(options.port)
    except ValueError:
        sys.stderr.write(
            "Numero de puerto invalido: %s\n" % repr(options.port))
        parser.print_help()
        sys.exit(1)

    server = Server(options.address, port, options.datadir)
    server.serve()


if __name__ == '__main__':
    main()
