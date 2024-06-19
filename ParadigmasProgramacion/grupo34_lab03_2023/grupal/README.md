# Laboratorio 3:
***
## Programación asistida para Frameworks sobre Cálculo Distribuido
### Etapa Grupal:
***

### Ventajas y desventajas de cada implementacion

**Ventajas**

- **Mensio:** 
    * El uso de Maven para gestionar las dependencias del proyecto (Spark, Json)
    * Código simple y organizado

- **Sereno:**
    * Punto estrella: la obtención de feeds también se hace con Spark y RDDs
    * Cumple con lo pedido por el enunciado
    
 **Desventajas**
 
- **Mensio:**
    * Mala interpretacion del enunciado, la implementación solo cuenta las ocurrencias de las entidades nombradas de cada Feed por separado y no la encontrada en toda la coleccion de Documentos.

- **Sereno:**
    * La forma de instalar Spark solo servía para el entorno de desarrollo IntelliJ IDEA
    * Código confuso y desorganizado, sin comentarios sobre que hace cada parte del código
     
### Elección
Elegimos la implementación de Sereno principalmente porque la implementación de Mensio a la hora de contar la cantidad de ocurrencias de las entidades nombradas no sumaba la cantidad para los distintos feeds, si no que trabajaba con cada feed de forma independiente. Ademas por el añadido de la obtencion de feed con Spark y RDDs.

Pero implementamos el uso de Maven para gestionar las dependencias del proyecto, tal como en la implementación de Mensio, ya que es facil de utilizar y es más general.

### Funcionalidad
Para recuperar documentos por palabras clave se debe correr el programa con el argumento -search seguido de la palabra que se quiere buscar:

<br>
    ```cmd
    java -cp lib/*:target/FeedReader-1.0.jar FeedReaderMain -search (palabra) 2>/dev/null
    ```
<br>

Luego el programa se encarga de buscar en los documentos dicha palabra y contar sus ocurrencias en cada uno de ellos por medio de un índice invertido, para esto cambiamos en FeedReaderMain el RDD que contaba las palabras por uno que cuenta según el feed:

* Primero a cada palabra de todos los feeds los agrupamos con un HashMap que contiene el sitio en el que se encontraba la palabra y un 1:
    <br>
    ```java
    for (Feed feed : feeds) {
        List<Article> articles = feed.getArticleList();
        for (Article article : articles) {
            String text = article.getText();
            countsPerFeed = countsPerFeed.union(sc.parallelize(Arrays.asList(text.split("[ .,]+"))).mapToPair(word -> new Tuple2<>(word, new HashMap<String, Integer>() {{ put(feed.getSiteName(), 1);}})));
        }
    }
    ```
    <br>
* Luego usamos reduceByKey para agrupar todas las palabras que se repiten y juntamos sus respectivos HashMaps sumando los 1s, de esta forma cada elemento del RDD contendrá una palabra distinta y su cantidad de ocurrencias por cada feed:
    <br>
    ```java
    countsPerFeed = countsPerFeed.reduceByKey((a, b) ->{    Set<String> keys = b.keySet();
                                                            for(String key : keys) {
                                                                a.merge(key, b.get(key), Integer::sum);
                                                            }
                                                            return a;
                                                        });
    ```
    <br>
* Hacemos un map con las entradas del RDD y buscamos la palabra que se ingreso para obtener el HashMap que contaba las ocurrencias y lo convertimos en una lista:
    <br>
    ```java
    Map<String, Map<String, Integer>> countsMap = countsPerFeed.collectAsMap();
    List<Map.Entry<String, Integer>> entryList = new ArrayList<>(countsMap.get(args[1]).entrySet());
    ```
    <br>
* Odenamos la lista de mayor a menor utilizando un comparador personalizado, `Collections.sort()`, que compara los valores `Integer` calculados anteriormente en los HashMaps: 

    ```java
    Collections.sort(entryList, new Comparator<Map.Entry<String, Integer>>() {
        public int compare(Map.Entry<String, Integer> entry1, Map.Entry<String, Integer> entry2) {
            // Ordenar de mayor a menor (invierte el orden para ordenar de menor a mayor)
            return entry2.getValue().compareTo(entry1.getValue());
        }
    });
    ```
    <br>
    
* Y por último imprimimos la lista `entryList`, que contiene para cada sitio, la cantidad de ocurrencias de la palabra buscada en orden:
    
    <br>
    ```java
    for (Map.Entry<String, Integer> entry : entryList) {
        System.out.printf("%s: %s\n", entry.getKey(), entry.getValue());
    }
    ```
    <br>
Para escribir el código nos basamos en la API de Spark y HashMap de Java con ayuda de chatGPT para solucionar los errores que nos ibamos encontrando.

### Comentario aparte
En el lab2 nos falto agregar la obtencion del titulo de cada feed, en particular faltaba agregar ese título a los feeds en el RssParser, por lo que tuvimos que ponerlo para que funcione nuestra implementación actual:
    <br>
    ```java
    Feed feed = new Feed(doc.getElementsByTagName("title").item(0).getTextContent());
    ```
    <br>
Además modificamos ligeramente la parte encargada de contar las entidades nombradas para que se adapte a esta nueva implementación:
    <br>
    ```java
    JavaPairRDD<String, Integer> counts = countsPerFeed.filter(t -> new QuickHeuristic().isEntity(t._1())).mapValues(hm -> {
                            int total = 0; 
                            for(int val : hm.values()){ 
                                total += val;
                            } 
                            return total;
                        });
    ```
    <br>
Aprovechamos que habíamos contado la cantidad de ocurrencias para cada palabra para cada feed y simplemente filtramos las entidades nombradas y sumamos el total de ocurrencias.