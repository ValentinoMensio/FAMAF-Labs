# Punto estrella - Laboratorio 0

## Enunciado

Opcionalmente, y con la posibilidad de que se otorguen puntos extras en la evaluación parcial, se pide investigar qué mecanismos permiten funcionar a nombres de dominio como:
http://中文.tw/
https://💩.la
Ayuda: investigue sobre el término “encoding”.

## URL Encodign

La codificación de URL, también conocida como codificación porcentual, es un mecanismo utilizado para reemplazar caracteres dentro de una URL convirtiéndolos en un formato estandarizado que pueda ser transmitido a través de Internet.

### Percent encoding

Las URL solo pueden contener un conjunto limitado de caracteres definidos por el conjunto de caracteres ASCII, que incluye caracteres alfanuméricos junto con algunos caracteres especiales. Sin embargo, muchos caracteres, incluidos los no alfanuméricos como espacios, signos de puntuación y caracteres no ASCII no están permitidos en las URL.

La codificación de URL resuelve este problema representando un otcteto de caracteres fuera del conjunto de caracteres permitidos en un formato que puede ser transmitido de manera segura dentro de una URL. Funciona reemplazando cada carácter no estándar con un '%' seguido de un valor hexadecimal de dos dígitos que representa el carácter en el conjunto de caracteres ASCII.

Por ejemplo:
-   El espacio (' ') se convierte en '%20'.
-   El ampersand ('&') se convierte en '%26'.
-   El signo de interrogación ('?') se convierte en '%3F'.
-   El signo más ('+') se convierte en '%2B'.

 

### Caracteres UTF-8

Para codificar un caracter UTF-8 utilizando percent encoding, se deben seguir los siguientes pasos:

1.  Convertir la cadena de caracteres en una secuencia de bytes utilizando la codificación UTF-8.
2.  Convertir cada byte que no sea una letra o dígito ASCII al formato %HH, donde HH es el valor hexadecimal del byte.

### Ejemplo:

El emoji 💩, que tiene un valor Unicode de U+1F4A9, se representa en UTF-8 como la secuencia de bytes `0xF0 0x9F 0x92 0xA9`. Luego, cada byte se convierte en percent encoding: `%F0%9F%92%A9`.


