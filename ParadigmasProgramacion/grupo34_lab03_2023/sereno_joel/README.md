# Laboratorio 3:
***
## Programación asistida para Frameworks sobre Cálculo Distribuido
### Etapa Individual: Sereno Joel
***

### ¿Cómo se instala Spark en una computadora personal?
Para instalar Spark en nuestra computadora, en mi caso voy a usar
Intellij IDEA como IDE para programar, por lo que vamos a la documentación
oficial de Spark que contiene una sección con "Useful Developer Tools"
en [https://spark.apache.org/developer-tools.html](https://spark.apache.org/developer-tools.html)
donde indica como instalar Spark en este IDE, y dice lo siguiente:
> To create a Spark project for IntelliJ:
> * Download IntelliJ and install the [Scala plug-in for IntelliJ](https://confluence.jetbrains.com/display/SCA/Scala+Plugin+for+IntelliJ+IDEA).
> * Go to File -> Import Project, locate the spark source directory, and select “Maven Project”.
> * In the Import wizard, it’s fine to leave settings at their default. However it is usually
useful to enable “Import Maven projects automatically”, since changes to the project structure
will automatically update the IntelliJ project.
> * As documented in Building Spark, some build configurations require specific profiles to be enabled.
The same profiles that are enabled with -P[profile name] above may be enabled on the Profiles screen in
the Import wizard. For example, if developing for Hadoop 2.7 with YARN support, enable profiles yarn and
hadoop-2.7. These selections can be changed later by accessing the “Maven Projects” tool window from the
View menu, and expanding the Profiles section.

Luego añadimos la dependencia a Maven en nuestro proyecto con la siguiente información:
> groupId: org.apache.spark  
> artifactId: spark-core_2.12  
> version: 3.4.0

Y así de fácil tenemos instalado Spark en nuestra computadora.

### ¿Qué estructura tiene un programa en Spark?
Spark ofrece una [guía](https://spark.apache.org/docs/latest/rdd-programming-guide.html) para programar
con Spark en la cuál se comenta el funcionamiento del Framework y dice que:
> At a high level, every Spark application consists of a driver program that runs the user’s main
function and executes various parallel operations on a cluster. The main abstraction Spark provides
is a resilient distributed dataset (RDD), which is a collection of elements partitioned across the
nodes of the cluster that can be operated on in parallel.

Es decir, Spark puede procesar varios elementos de estos RDD paralelamente en nuestra computadora,
o incluso en varias.

### ¿Qué estructura tiene un programa de conteo de palabras en diferentes documentos en Spark?
Spark también ofrece una [página(https://spark.apache.org/examples.html)] con ejemplos de programas,
en este caso un programa de conteo de palabras en Spark se vería de la siguiente forma:
~~~
JavaRDD<String> textFile = sc.textFile("hdfs://...");
JavaPairRDD<String, Integer> counts = textFile
.flatMap(s -> Arrays.asList(s.split(" ")).iterator())
.mapToPair(word -> new Tuple2<>(word, 1))
.reduceByKey((a, b) -> a + b);
counts.saveAsTextFile("hdfs://...");
~~~

### ¿Cómo adaptar el código del Laboratorio 2 a la estructura del programa objetivo en Spark?
Para adaptar el código del Laboratorio 2 a la estructura de Spark, lo más conveniente es aprovechar
el procesamiento en paralelo que ofrece el Framework, por lo que procesaremos las subscripciones en paralelo:
~~~
List<SingleSubscription> subsList = subs.getSubscriptionsList();
JavaRDD<SingleSubscription> distSubs = sc.parallelize(subsList);
~~~
Ahora cada elemento del RDD *distSubs* es una SingleSubscription y puede ser trabajada por separado
de las otras, de esta forma extraemos las urls necesarias para obtener los feeds de cada subscription
y procesamos cada una por separado para obtener los feeds e imprimirlos por pantalla:
~~~
JavaRDD<Feed> feeds = sc.parallelize(urls).[...]
feeds.foreach(feed -> feed.prettyPrint());
~~~
En el caso del conteo de Entidades Nombradas procedemos de igual manera solo que esta vez en lugar de
imprimir los feeds contamos en cada uno de ellos la cantidad de Entidades Nombradas.  
Para ello obtenemos el texto de cada artículo de cada feed:
~~~
for (Feed feed : feeds) {
    List<Article> articles = feed.getArticleList();
    for (Article article : articles) {
        String text = article.getText();
        [...]
~~~
y contamos como en el ejemplo anterior de conteo de palabras, además iremos aplicando la función *union* que
une dos RDD:
~~~
        [...]
        counts = counts.union(sc.parallelize(Arrays.asList(text.split("[ .,]+"))).mapToPair(word -> new Tuple2<>(word, 1)));
    }
}
~~~
De esta forma counts tiene tuplas con todas las palabras de todos los articulos de todos los feeds, cada una con un 1.  
Ahora simplemente agrupamos todas las keys iguales entre si y sumamos sus valores con *reduceByKey, asi estaremos
contando la cantidad de ocurrencias de cada palabra.  
Y filtramos aquellas palabras que si son entidades nombradas según la heurística con *filter*.
~~~
counts.reduceByKey((a, b) -> a + b).filter(t -> new QuickHeuristic().isEntity(t._1()));
~~~
Finalmente creamos la tabla de entidades nombradas de manera similar al Laboratorio 2 para asi poder imprimir los
resultados en pantalla.

### ¿Cómo se integra una estructura orientada a objetos con la estructura funcional de map-reduce?
La estructura funcional de map-reduce permite aplicar a los elementos del RDD, que no son mas que objetos
en Java, funciones que los convierten en otros objetos con map y luego hacer que el RDD devuelva algún resultado
(también un objeto) por medio de reduce.