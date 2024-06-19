# Trabajo Práctico 3 - Mensio (individual)


## Índice
- [Instalar Spark](#pregunta1)
	- [Implementar Maven](#pregunta1a)
	- [Crear archivo pom.xml](#pregunta1b)
        - [Estructura básica de un archivo pom.xml](#pregunta1bstruct)
        - [Configurar plugins](#pregunta1bplugins)
        - [Configurar dependencias](#pregunta1bdependencias)
	- [Compilar](#pregunta1c)
- [Estructura de un programa Spark](#pregunta2)
- [Estructura de un programa de conteo de palabras con Spark](#pregunta3)
- [Adaptar el código del Laboratorio 2](#pregunta4)
- [Integración de estructura orientada a objetos y estructura funcional](#pregunta5)

<br><br><br>

**Respuesta de ChatGPT 3.5 y Copilot:**<br>

<div id='pregunta1'/> </div>

## ¿Cómo se instala Spark en una computadora personal?


Encontré un blog que recomienda utilizar Maven para gestionar las dependencias de Spark.

Apache Maven es una potente herramienta de gestión de proyectos que se utiliza para gestionar dependencias, como herramienta de compilación e incluso como herramienta de documentación. Es de código abierto y gratuita.<br><br>

<div id='pregunta1a'/> </div> 

### Instalación de Spark en Linux Mint utilizando Maven y un archivo `pom.xml`<br><br>

Para instalar Apache Spark en una computadora personal con Linux Mint y utilizar el archivo `pom.xml`, asumiremos que estás trabajando en un proyecto de Maven. A continuación, te proporcionaré los pasos generales para la instalación:

1. Verifica los requisitos previos:
   - Asegúrate de tener Java instalado en tu máquina. Spark requiere Java 8 o superior. Puedes verificar la versión de Java instalada utilizando el comando `java -version` en la terminal.
   - Asegúrate de tener Maven instalado en tu sistema. Puedes verificar la instalación de Maven con el comando `mvn -version`.

2. Descarga Spark:
   - Visita el [sitio web oficial de Apache Spark](https://spark.apache.org/downloads.html) y descarga la última versión estable de Spark en formato tarball (archivo `.tgz`).

3. Extrae el archivo tarball de Spark:
    - Abre la terminal y navega hasta la ubicación donde se descargó el archivo tarball de Spark.
    - Utiliza el siguiente comando para extraer el archivo:
    ```
    tar -xvf nombre_archivo.tgz
 	```

4. Configura el archivo `pom.xml`:
   - Abre el archivo `pom.xml` en tu editor de texto preferido.
   - Agrega la siguiente dependencia de Spark al archivo:
 	```xml
 	<dependency>
     	<groupId>org.apache.spark</groupId>
     	<artifactId>spark-core_2.12</artifactId>
     	<version>versión_de_spark</version>
 	</dependency>
 	```

 	Asegúrate de reemplazar `versión_de_spark` con la versión específica de Spark que descargaste.

5. Compila y construye el proyecto:
   - En la terminal, navega hasta la ubicación del proyecto que contiene el archivo `pom.xml`.
   - Ejecuta el siguiente comando para compilar y construir el proyecto:
 	```
 	mvn clean package
 	```

   Esto descargará automáticamente las dependencias necesarias, incluido Spark, y generará un archivo JAR para tu proyecto.

Con estos pasos, habrás instalado Spark en tu computadora personal con Linux Mint y configurado tu proyecto Maven para utilizarlo. Recuerda ajustar cualquier configuración adicional según las necesidades específicas de tu proyecto.

<br>

<div id='pregunta1b'/> </div>

### Creación de un archivo POM.xml para un proyecto Maven

<br>


Para crear un archivo `pom.xml` para un proyecto Maven, puedes seguir estos pasos:

1. Crea un nuevo directorio para tu proyecto:
   - Abre la terminal y navega hasta el directorio donde deseas crear tu proyecto Maven.
   - Ejecuta el siguiente comando para crear un nuevo directorio:
 	```
 	mkdir nombre_proyecto
 	```

2. Ingresa al directorio del proyecto:
   - Navega al directorio que acabas de crear:
 	```
 	cd nombre_proyecto
 	```

3. Inicializa el proyecto Maven:
   - Ejecuta el siguiente comando para inicializar un nuevo proyecto Maven en el directorio actual:
 	```
 	mvn archetype:generate -DgroupId=com.example -DartifactId=nombre_proyecto -DarchetypeArtifactId=maven-archetype-quickstart -DinteractiveMode=false
 	```

   Esto creará una estructura de proyecto Maven básica en el directorio `nombre_proyecto`, incluyendo el archivo `pom.xml`.

4. Abre el archivo `pom.xml` en tu editor de texto preferido:
   - Utiliza un editor de texto como nano, vim o cualquier otro de tu elección para abrir el archivo `pom.xml`.

5. Personaliza el archivo `pom.xml` según las necesidades de tu proyecto:
   - En el archivo `pom.xml`, puedes especificar información como el nombre del proyecto, la descripción, la versión, las dependencias, los complementos, etc. Consulta la documentación de Maven [aquí](https://maven.apache.org/guides/introduction/introduction-to-the-pom.html) para obtener más información sobre la estructura y los elementos del archivo `pom.xml`.
   - Asegúrate de proporcionar la configuración correcta para tu proyecto, incluidas las dependencias que necesites.

6. Guarda el archivo `pom.xml`.

Con estos pasos, habrás creado un archivo `pom.xml` básico para tu proyecto Maven. Puedes agregar y configurar las dependencias adicionales según las necesidades de tu proyecto antes de compilar y construir el proyecto con Maven.

<br>

<div id='pregunta1bstruct'/> </div>

### Estructura básica de un archivo POM.xml

<br>

Un archivo `pom.xml` es el archivo de configuración principal de Maven y define la estructura, las dependencias y las configuraciones de tu proyecto. A continuación, se muestra la estructura básica de un archivo `pom.xml`:

```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"
     	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
     	xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 https://maven.apache.org/xsd/maven-4.0.0.xsd">

	<!-- Información del proyecto -->
	<modelVersion>4.0.0</modelVersion>
	<groupId>com.example</groupId>
	<artifactId>nombre_proyecto</artifactId>
	<version>1.0.0</version>
	<name>Nombre del Proyecto</name>
	<description>Descripción del proyecto</description>

	<!-- Dependencias del proyecto -->
	<dependencies>
    	<!-- Aquí se agregan las dependencias del proyecto -->
    	<dependency>
        	<groupId>grupo_dependencia</groupId>
        	<artifactId>dependencia</artifactId>
        	<version>1.0.0</version>
    	</dependency>
	</dependencies>

	<!-- Configuraciones adicionales -->
	<build>
    	<!-- Aquí se pueden agregar configuraciones de compilación y construcción -->
	</build>

</project>
```

A continuación, se describen los elementos principales del archivo `pom.xml`:

- `<modelVersion>`: Especifica la versión del modelo de proyecto de Maven. Generalmente se establece en `4.0.0`.
- `<groupId>`: Define el identificador único del grupo para tu proyecto.
- `<artifactId>`: Define el identificador único del artefacto (proyecto)

 en el grupo.
- `<version>`: Especifica la versión del proyecto.
- `<name>`: Proporciona el nombre descriptivo del proyecto.
- `<description>`: Proporciona una descripción del proyecto.

Dentro del elemento `<dependencies>`, puedes agregar las dependencias de tu proyecto utilizando la etiqueta `<dependency>`. Esto incluye el `groupId`, `artifactId` y `version` de cada dependencia.

Además, puedes personalizar y agregar configuraciones adicionales dentro del elemento `<build>`, como opciones de compilación, directorios de recursos, complementos, entre otros.

Recuerda que esta es una estructura básica y que el archivo `pom.xml` puede contener muchos otros elementos y configuraciones adicionales según las necesidades de tu proyecto.

<br>

<div id='pregunta1bplugins'/> </div>

### ¿Qué plugins puedo utilizar en un archivo POM.xml y cómo se configuran?

<br>

En un archivo `pom.xml`, puedes configurar varios complementos (plugins) para realizar tareas específicas durante el ciclo de vida de construcción de tu proyecto. Aquí tienes algunos ejemplos de plugins comunes y cómo se configuran:

1. **maven-compiler-plugin**: Configura las opciones de compilación de Java para el proyecto.

Ejemplo de configuración:
```xml
<build>
	<plugins>
    	<plugin>
        	<groupId>org.apache.maven.plugins</groupId>
        	<artifactId>maven-compiler-plugin</artifactId>
        	<version>3.8.1</version>
        	<configuration>
            	<source>1.8</source>
            	<target>1.8</target>
        	</configuration>
    	</plugin>
	</plugins>
</build>
```
En este ejemplo, se especifica que se utilizará Java 1.8 como versión de origen y destino de compilación.

2. **maven-surefire-plugin**: Ejecuta pruebas unitarias durante la fase de pruebas del ciclo de vida del proyecto.

Ejemplo de configuración:
```xml
<build>
	<plugins>
    	<plugin>
        	<groupId>org.apache.maven.plugins</groupId>
        	<artifactId>maven-surefire-plugin</artifactId>
        	<version>3.0.0-M5</version>
        	<configuration>
            	<includes>
                	<include>**/*Test.java</include>
            	</includes>
        	</configuration>
    	</plugin>
	</plugins>
</build>
```
En este ejemplo, se configura el plugin para ejecutar las pruebas unitarias que coincidan con el patrón `**/*Test.java`.

3. **maven-jar-plugin**: Empaqueta el proyecto en un archivo JAR.

Ejemplo de configuración:
```xml
<build>
	<plugins>
    	<plugin>
        	<groupId>org.apache.maven.plugins</groupId>
        	<artifactId>maven-jar-plugin</artifactId>
        	<version>3.2.0</version>
        	<configuration>
            	<archive>
                	<manifest>
                    	<mainClass>com.example.MainClass</mainClass>
                	</manifest>
            	</archive>
        	</configuration>
    	</plugin>
	</plugins>
</build>
```
En este ejemplo, se configura el plugin para agregar una clase principal (`MainClass`) al archivo JAR generado.

Estos son solo ejemplos de plugins comunes, pero Maven ofrece una amplia gama de plugins para diversas tareas, como generar informes, empaquetar archivos adicionales, ejecutar análisis estáticos de código, entre otros.

Para configurar un plugin en el archivo `pom.xml`, debes agregarlo dentro del elemento `<plugins>` en la sección `<build>`. Puedes especificar el `groupId`, `artifactId` y `version` del plugin, así como cualquier configuración adicional dentro del elemento `<configuration>`.

Recuerda que los nombres de los plugins y las versiones pueden variar según los plugins que desees utilizar, por lo que es importante consultar la documentación oficial de cada plugin específico para obtener información detallada sobre su configuración.

<br>

<div id='pregunta1bdependencias'/> </div>

### ¿Cómo puedo configurar el complemento Maven Dependency Plugin para copiar las dependencias de mi proyecto a un directorio 'lib' durante la fase de procesamiento de recursos?

<br>

Para configurar el complemento Maven Dependency Plugin y copiar las dependencias de tu proyecto a un directorio específico, como 'lib', puedes seguir estos pasos:

1. Abre el archivo `pom.xml` de tu proyecto en un editor de texto.

2. Agrega la siguiente configuración dentro del elemento `<build>`:

```xml
<build>
	<plugins>
    	<plugin>
        	<groupId>org.apache.maven.plugins</groupId>
        	<artifactId>maven-dependency-plugin</artifactId>
        	<version>3.1.2</version>
        	<executions>
            	<execution>
                	<id>copy-dependencies</id>
                	<phase>package</phase>
                	<goals>
                    	<goal>copy-dependencies</goal>
                	</goals>
                	<configuration>
                    	<outputDirectory>${project.build.directory}/lib</outputDirectory>
                	</configuration>
            	</execution>
        	</executions>
    	</plugin>
	</plugins>
</build>
```

En esta configuración, hemos utilizado el complemento Maven Dependency Plugin y especificado la versión `3.1.2`. Dentro de `<executions>`, hemos definido una ejecución con el identificador `copy-dependencies`, que se ejecutará en la fase `package` del ciclo de vida de Maven.

Dentro de `<configuration>`, hemos establecido `<outputDirectory>` como `${project.build.directory}/lib`, lo que indica que las dependencias se copiarán al directorio `lib` dentro del directorio de construcción del proyecto.

3. Guarda el archivo `pom.xml`.

4. Ejecuta el comando Maven para construir y copiar las dependencias:

```bash
mvn package
```

Este comando compilará tu proyecto y copiará todas las dependencias en el directorio `lib` especificado.

Después de ejecutar el comando, podrás encontrar las dependencias en el directorio `lib` dentro del directorio de construcción de tu proyecto.

#Dado este archivo pom, cómo compilar java usando Maven como herramienta?

Para compilar un proyecto Java utilizando Maven y el archivo POM proporcionado, debes seguir los siguientes pasos:

1. Asegúrate de tener instalado Maven en tu sistema. Puedes verificarlo ejecutando el siguiente comando en la línea de comandos:

   ```bash
   mvn -v
   ```

   Si Maven está instalado, se mostrará la versión de Maven y otra información relacionada.

2. Abre una terminal o línea de comandos y navega hasta el directorio raíz del proyecto que contiene el archivo POM.xml.

3. Ejecuta el siguiente comando para compilar el proyecto:

   ```bash
   mvn clean package
   ```

   Esto iniciará el proceso de compilación utilizando Maven y ejecutará todas las fases necesarias, como la compilación de código fuente, la ejecución de pruebas y la creación del archivo JAR.

4. Una vez que el comando se complete sin errores, encontrarás el archivo JAR generado en la carpeta `target` del directorio raíz del proyecto. En este caso, el archivo se llamará `FeedReader-1.0.jar`.

Ahora has compilado exitosamente el proyecto Java utilizando Maven. Puedes ejecutar el archivo JAR resultante utilizando el siguiente comando:

```bash
java -jar target/FeedReader-1.0.jar
```

Asegúrate de ajustar el nombre del archivo JAR si difiere del mencionado anteriormente.

Recuerda que para compilar y ejecutar el proyecto, debes tener instalado Java Development Kit (JDK) en tu sistema y configurada la variable de entorno JAVA_HOME adecuadamente.

<br>

<div id='pregunta1c'/> </div>

### COMPILACIÓN

<br>

**Maven**
    
	sudo apt install maven
**Compilación**
    
	mvn clean package
**Ejecución con argumentos (sin datos de spark)**
    
	java -cp lib/*:target/FeedReader-1.0.jar FeedReaderMain -ne 2>/dev/null

<br><br>

<div id='pregunta2'/> </div>

## ¿Qué estructura tiene un programa en Spark?

<br>

En Spark, un programa generalmente sigue una estructura básica que consta de las siguientes partes:

1. Importación de bibliotecas: Al comienzo del programa, se importan las bibliotecas necesarias de Spark y otras dependencias específicas, como `pyspark` para Python o `sparklyr` para R.

2. Configuración de SparkContext: El SparkContext es el punto de entrada principal para interactuar con Spark. Aquí se configuran los parámetros de Spark, como el modo de ejecución local o en un clúster, la cantidad de recursos asignados, etc. En Python, esto se realiza mediante la creación de un objeto `SparkContext`.

3. Creación de un RDD o DataFrame: En Spark, los datos se representan como RDDs (Resilient Distributed Datasets) o DataFrames. En esta etapa, se crea un RDD o DataFrame a partir de una fuente de datos, como un archivo CSV, una base de datos o una API externa.

4. Transformaciones: Las transformaciones son operaciones que se aplican a los RDD o DataFrames para realizar cálculos o manipulaciones en los datos. Estas operaciones son perezosas (lazy), lo que significa que no se ejecutan inmediatamente, sino que se registran para su posterior evaluación. Algunas transformaciones comunes incluyen `map`, `filter`, `reduce`, `groupBy`, etc.

5. Acciones: Las acciones son operaciones que desencadenan la ejecución de las transformaciones y devuelven resultados o realizan ciertas acciones en los datos. Algunas acciones comunes incluyen `collect`, `count`, `take`, `save`, `show`, etc. Al ejecutar una acción, Spark planifica y optimiza las transformaciones anteriores y realiza los cálculos necesarios en los datos distribuidos.

6. Cierre de SparkContext: Al final del programa, se debe cerrar el SparkContext para liberar los recursos utilizados por Spark.

Es importante tener en cuenta que esta es una estructura generalizada y que la implementación exacta puede variar según el lenguaje de programación utilizado (Python, Scala, Java, etc.) y las características específicas del programa en Spark.

<br><br>

<div id='pregunta3'/> </div>

## ¿Qué estructura tiene un programa de conteo de palabras en diferentes documentos en Spark?

<br>

Un programa de conteo de palabras en diferentes documentos en Spark sigue una estructura similar a la mencionada anteriormente. A continuación, se muestra una estructura básica para un programa de conteo de palabras en Spark:

1. Importación de bibliotecas: Importa las bibliotecas necesarias de Spark y otras dependencias requeridas.

2. Configuración de SparkContext: Configura el entorno de Spark, como el modo de ejecución y los recursos asignados.

3. Creación de RDD o DataFrame: Crea un RDD o DataFrame a partir de los documentos de entrada. Puedes usar métodos como `textFile` para leer archivos de texto o cargar datos desde una base de datos, almacenamiento en la nube u otra fuente.

4. Transformaciones de limpieza y preparación de datos: Aplica transformaciones en el RDD o DataFrame para limpiar y preparar los datos. Esto puede incluir la eliminación de signos de puntuación, conversión a minúsculas, tokenización de palabras, etc.

5. Transformaciones de conteo de palabras: Aplica transformaciones para realizar el conteo de palabras. Puedes usar métodos como `flatMap` para dividir las líneas en palabras, `map` para asignar una ocurrencia de cada palabra y luego `reduceByKey` para sumar las ocurrencias de cada palabra.

6. Acciones para obtener resultados: Aplica acciones para obtener los resultados del conteo de palabras, como `collect` para obtener todas las palabras y sus conteos o `take` para obtener los primeros N resultados.

7. Manipulación y visualización de resultados: Puedes realizar operaciones adicionales en los resultados, como ordenar las palabras por su conteo, filtrar palabras específicas o generar una representación visual de los resultados.

8. Cierre de SparkContext: Cierra el SparkContext para liberar los recursos utilizados por Spark.

Es importante destacar que este es un esquema general y que la implementación exacta puede variar según el lenguaje de programación utilizado y los detalles específicos del programa en Spark.

<br><br>

<div id='pregunta4'/> </div>

## ¿Cómo adaptar el código del Laboratorio 2 a la estructura del programa objetivo en Spark?

<br>

**Respuestas de Copilot:**

<br>

**Sigo los pasos de la estructura del programa objetivo en Spark**
1. ### Importación de bibliotecas
	creo el archivo `pom.xml` con las dependencias necesarias

2.  ### Configuración de SparkContext
	```java
	SparkSession sparkSession = SparkSession.builder()
    	.appName("EntityRecognition")
    	.master("local[*]")
    	.getOrCreate();

	JavaSparkContext sparkContext = new JavaSparkContext(sparkSession.sparkContext());
	```

3. ### Creación de RDD o DataFrame:
	<br>

	**Itero sobre la lista de suscripciones**
	```java
	for (String subscription : subscriptions) {
	```

	<br>

	**Proceso la suscripción RSS**
	```java
	int urlParamsSize = s.getUrlParamsSize();
	List<String> urlParams = new ArrayList<>(s.getUrlParams());

	Dictionary dict = new Dictionary();
	Map<String, String> dictionary = dict.info();

	for (int i = 0; i < urlParamsSize; i++) {
	s.setUrlParams(urlParams.get(i));
	String feed = hr.getFeedRss(s.getFeedToRequest(i));
	// ...
	}
	```
   Se obtiene el tamaño de los parámetros de la URL de la suscripción y se crea una lista de parámetros. Luego se crea una instancia de `Dictionary` y se obtiene un mapa de información desde `dict.info()`. A continuación, se itera sobre los parámetros de la URL y se realiza lo siguiente:
   - Se establece el parámetro de URL actual en la suscripción (`s.setUrlParams(urlParams.get(i))`).
   - Se realiza una solicitud HTTP para obtener el feed RSS correspondiente (`hr.getFeedRss(s.getFeedToRequest(i))`).
   - Se analiza el feed RSS utilizando un `RssParser` y se obtiene un objeto `Feed` (`rp.parse(feed)`).

	<br>

	**Procesamiento de los artículos del feed RSS**
	```java
	JavaRDD<Article> articleRDD = sparkContext.parallelize(f.getArticleList());

	JavaRDD<String> namedEntitiesRDD = articleRDD.flatMap(article -> {
	// ...
	});
	```
	Se crea un `JavaRDD` llamado `articleRDD` a partir de la lista de artículos obtenida del feed RSS. Luego se crea otro `JavaRDD` llamado `namedEntitiesRDD` mediante la transformación de cada artículo en una lista de entidades nombradas.

4. **Transformaciones de conteo de palabras:**
	```java
	JavaPairRDD<String, Integer> wordCountRDD = namedEntitiesRDD
    	.mapToPair(namedEntity -> new Tuple2<>(namedEntity, 1))
    	.reduceByKey(Integer::sum);
	```

    Se crea un RDD llamado `wordCountRDD` en el cual se realiza un mapeo y una reducción en el `namedEntitiesRDD` para contar la frecuencia de cada entidad nombrada. Cada entidad se mapea a una tupla (entidad, 1), y luego luego se realiza una reducción por clave sumando los valores.

5. **Acciones para obtener resultados:**
    ```java
    for (Tuple2<String, Integer> wordCount : wordCounts) {
		String word = wordCount._1();
		int count = wordCount._2();
    ```

    Se recopilan los resultados del RDD `wordCountRDD` en una lista de tuplas llamada wordCounts y se recorre cada tupla `wordCount` en `wordCounts`. 

    Se extraen las palabras y el recuento de la tupla wordCount.
    
    Por ultimo se busca la palabra en el diccionario y se obtiene la información asociada a la palabra como en el laboratorio 2.

6. **Cierre de SparkContext**
	```java
	sparkContext.close();
    sparkSession.close();
	```

<br><br>

<div id='pregunta5'/> </div>

## ¿Cómo se integra una estructura orientada a objetos con la estructura funcional de map-reduce?

<br>

La integración de una estructura orientada a objetos con la estructura funcional de map-reduce se puede lograr mediante el uso de conceptos como la programación funcional y la programación orientada a objetos (POO) en conjunto. A continuación, se presentan algunas formas de lograr esta integración:

1. Utilización de funciones como parámetros: En muchos lenguajes de programación modernos, las funciones son ciudadanos de primera clase, lo que significa que se pueden pasar como parámetros a otras funciones. Puedes aprovechar esta característica para utilizar funciones como el mapeo (`map`) y la reducción (`reduce`) en combinación con objetos y métodos orientados a objetos.

2. Implementación de interfaces funcionales: En lenguajes que admiten interfaces funcionales, como Java 8 y versiones posteriores, puedes definir interfaces funcionales que representen operaciones como el mapeo y la reducción. Luego, puedes implementar estas interfaces utilizando clases y objetos orientados a objetos. Esto te permite utilizar objetos que cumplen con una interfaz funcional en funciones de mapeo y reducción.

3. Uso de lambdas o funciones anónimas: Las lambdas o funciones anónimas son una forma concisa de definir funciones en línea. Puedes utilizar lambdas para encapsular lógica funcional y combinarla con objetos y métodos orientados a objetos. Por ejemplo, puedes pasar una lambda como argumento a una función de mapeo o reducción que acepta una función como parámetro.

4. Patrones de diseño combinados: Puedes combinar patrones de diseño orientados a objetos con conceptos de programación funcional para lograr una integración más completa. Por ejemplo, puedes utilizar el patrón de diseño Strategy para encapsular diferentes algoritmos de mapeo o reducción en clases separadas y permitir que los objetos seleccionen el algoritmo adecuado en tiempo de ejecución.

En general, la integración de una estructura orientada a objetos con la estructura funcional de map-reduce requiere un enfoque cuidadoso en el diseño y la implementación del programa. Es esencial comprender los principios tanto de la programación orientada a objetos como de la programación funcional y buscar formas de combinarlos de manera efectiva para lograr el resultado deseado.
