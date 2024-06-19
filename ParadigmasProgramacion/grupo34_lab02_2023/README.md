# Laboratorio 2:
## Programación orientada a objetos
***

### Integrantes:
* Valentino Mensio
* Joel Sereno

**Funcionalidad Codigo**
El primer paso en el proceso de creación del lector de noticias es el diseño de un archivo en formato .json que permita al usuario configurar los distintos sitios y tópicos a los cuales desea acceder para obtener noticias. Este archivo tendrá una estructura en la que se especificarán los diferentes sitios web de noticias, cada uno con su respectivo nombre y una lista de tópicos.

Una vez que el usuario ha definido la configuración del lector de noticias, el programa se encarga de acceder a cada uno de los sitios y tópicos especificados en el archivo .json y extraer la información de las noticias disponibles. Esta información se presenta al usuario en forma de feeds de noticias legibles y amigables.

Además de mostrar las noticias, el lector de noticias cuenta con una funcionalidad adicional para computar heurísticamente las entidades nombradas más mencionadas en la lista de feeds. Para ello, se utiliza un algoritmo de procesamiento de lenguaje natural que identifica las entidades nombradas (como nombres de personas, lugares, organizaciones, etc.) en los titulares y contenido de las noticias y las cuenta para determinar las más mencionadas.

Esta funcionalidad permite al usuario tener una visión general de las noticias más relevantes y los temas más importantes en los diferentes tópicos y sitios web que ha seleccionado, sin tener que leer todas las noticias en detalle. De esta manera, el lector de noticias proporciona una manera eficiente y conveniente para estar al día con las últimas noticias y tendencias en los temas que le interesan al usuario.

**Anotaciones**
*GeneralParser*
definimos un método abstracto *parse* que toma una cadena de texto como argumento y devuelve un objeto del tipo T. Este método *parse* es abstracto, lo que significa que no se proporciona una implementación en esta clase, sino que se deja a las subclases concretas proporcionar una implementación.

*RssParser*
Esta clase hereda de *GeneralParser* y define el método *parse* que toma una cadena de texto en formato XML y devuelve un objeto del tipo *Feed*.

*SubscriptionParser*
Implementa el parser para un archivo de suscripción en formato JSON. La clase SubscriptionParser extiende la clase abstracta GeneralParser y proporciona una implementación específica del método parse que convierte una ruta JSON en un objeto de tipo Subscription.

*namedEntity* 
Una entidad nombrada es un objeto que contiene un nombre, un recuento de ocurrencias, una categoría y un tema. Estas entidades nombradas son identificadas mediante una técnica heurística. Una vez identificadas, se buscan en nuestro diccionario para clasificarlas en una categoría y un tema específico.
Ademas cada categoria tiene datos adicionales propios.

*Falta Implementar*
Entendemos que el objetivo es crear dos jerarquias para namedEntitys (categoria y tema). Para esto como java no permite herencia multiple, se podria crear dos interfaces (ICategoria e ITema). luego podria implementar cada interfaz en la clase namedEntity. De esta manera se podria crear una jerarquia de herencia para cada interfaz.
