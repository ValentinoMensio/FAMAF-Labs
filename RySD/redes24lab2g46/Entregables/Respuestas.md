⦁ ¿Qué estrategias existen para poder implementar este mismo servidor pero con capacidad de atender múltiples clientes simultáneamente? Investigue y responda brevemente qué cambios serían necesarios en el diseño del código.

Uso de subprocesos (threads): Cada vez que se establece una conexión con un cliente, el servidor crea un nuevo hilo para manejar esa conexión, permitiendo así manejar múltiples clientes simultáneamente.

Uso de procesos (multiprocesamiento): Similar al uso de subprocesos, pero en lugar de subprocesos, se crean procesos separados para manejar cada conexión de cliente. Esto puede ser útil para evitar problemas de concurrencia asociados con los subprocesos en algunos lenguajes de programación.

Modelo asíncrono: En lugar de utilizar subprocesos o procesos separados, el servidor utiliza operaciones de entrada/salida asíncronas para manejar múltiples conexiones de cliente de manera eficiente.

En el lab 2 ya implementamos threads y modelo asincrono con poll.

Para implementar multiprocesamiento, en vez de crear un nuevo hilo para cada conexion entrante, se crearian procesos separados para manejar cada conexion.

Ademas los procesos necesitarán comunicarse entre sí y con el proceso principal (servidor) para compartir información sobre las conexiones, datos compartidos. Esto podría hacerse mediante mecanismos de comunicación interprocesos (IPC) como pipes, colas (queues).

Ademas se debe garantizar que estos recursos sean gestionados de manera segura para evitar condiciones de carrera o problemas de concurrencia. Esto puede requerir el uso de mecanismos de sincronización como semáforos o bloqueos.

Ademas debemos gestionar la finalización de los procesos hijos para evitar recursos no utilizados y posibles fugas de memoria.


⦁ Pruebe ejecutar el servidor en una máquina del laboratorio, mientras utiliza el cliente desde otra, hacia la ip de la máquina servidor. ¿Qué diferencia hay si se corre el servidor desde la IP “localhost”, “127.0.0.1” o la ip “0.0.0.0”?

 Si ejecutamos el servidor desde "localhost" o "127.0.0.1", solo podremos conectar al cliente desde la misma máquina. Pero si ejecutamos el servidor desde "0.0.0.0", podremos conectar al cliente desde cualquier dispositivo en la red local.