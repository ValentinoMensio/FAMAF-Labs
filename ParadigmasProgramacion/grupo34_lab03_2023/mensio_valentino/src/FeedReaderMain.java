import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import feed.Article;
import feed.Feed;
import httpRequest.httpRequester;
import namedEntity.*;
import namedEntity.heuristic.*;
import parser.RssParser;
import parser.SubscriptionParser;
import subscription.SingleSubscription;
import subscription.Subscription;

import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.SparkConf;
import org.apache.spark.sql.SparkSession;

import java.util.Collections;

import scala.Tuple2;

public class FeedReaderMain {

	private static void printHelp(){
		System.out.println("Please, call this program in correct way: FeedReader [-ne]");
	}
	
	public static void main(String[] args) {
		System.out.println("************* FeedReader version 1.0 *************");
		System.out.println("************* Feeds *************");
		if (args.length == 0) {

			// Leer el archivo de suscripción por defecto
			SubscriptionParser sp = new SubscriptionParser();
			Subscription subs = sp.parse("config/subscriptions.json");
	
			// Procesar cada suscripción
			subs.getSubscriptionsList().forEach(subscription -> {
				// Crear el contexto de Spark
				SparkSession sparkSession = SparkSession.builder()
					.appName("EntityRecognition")
					.master("local[*]")
					.getOrCreate();

				JavaSparkContext sparkContext = new JavaSparkContext(sparkSession.sparkContext());

	
				httpRequester hr = new httpRequester();
	
				if (subscription.getUrlType().contains("reddit")) {
					System.out.println("Reddit no implementado");
				} else if (subscription.getUrlType().contains("rss")) {
					int urlParamsSize = subscription.getUrlParamsSize();
					List<String> urlParams = new ArrayList<>(subscription.getUrlParams());
	
					for (int i = 0; i < urlParamsSize; i++) {
						subscription.setUrlParams(urlParams.get(i));
						String feed = hr.getFeedRss(subscription.getFeedToRequest(i));
	
						// Crear un RDD con los feeds
						JavaRDD<String> feedRDD = sparkContext.parallelize(Collections.singletonList(feed));
	
						// Realizar el mapeo y parseo de los feeds utilizando el RssParser
						JavaRDD<Feed> parsedFeedRDD = feedRDD.map(feedContent -> {
							RssParser rp = new RssParser();
							return rp.parse(feedContent);
						});
	
						// Imprimir los feeds procesados
						parsedFeedRDD.foreach(Feed::prettyPrint);
					}
				}
	
				// Detener el contexto de Spark
				sparkContext.stop();
			});
			
		} else if (args.length == 1){
			System.out.println("************* Datos Heuristica *************");
			// Crear el contexto de Spark
			SparkSession sparkSession = SparkSession.builder()
				.appName("EntityRecognition")
				.master("local[*]")
				.getOrCreate();

			JavaSparkContext sparkContext = new JavaSparkContext(sparkSession.sparkContext());

			// Leer el archivo de suscripciones
			SubscriptionParser sp = new SubscriptionParser();
			Subscription subs = sp.parse("config/subscriptions.json");

			for (SingleSubscription s : subs.getSubscriptionsList()) {
				httpRequester hr = new httpRequester();
				if (s.getUrlType().contains("reddit")) {
					System.out.println("Reddit no implementado");
				} else if (s.getUrlType().contains("rss")) {
					int urlParamsSize = s.getUrlParamsSize();
					List<String> urlParams = new ArrayList<>(s.getUrlParams());

					Dictionary dict = new Dictionary();
					Map<String, String> dictionary = dict.info();

					for (int i = 0; i < urlParamsSize; i++) {
						s.setUrlParams(urlParams.get(i));
						String feed = hr.getFeedRss(s.getFeedToRequest(i));
						RssParser rp = new RssParser();
						Feed f = rp.parse(feed);

						// Convertir el feed a RDD
						JavaRDD<Article> articleRDD = sparkContext.parallelize(f.getArticleList());

						// Extraer las entidades nombradas de cada artículo
						JavaRDD<String> namedEntitiesRDD = articleRDD.flatMap(article -> {
							List<String> namedEntities = new ArrayList<>();
							Heuristic h = new QuickHeuristic();
							for (String word : article.getText().split("[ .,]+")) {
								if (h.isEntity(word)) {
									namedEntities.add(word);
								}
							}
							return namedEntities.iterator();
						});

						// Contar la frecuencia de cada entidad nombrada
						JavaPairRDD<String, Integer> wordCountRDD = namedEntitiesRDD
								.mapToPair(namedEntity -> new Tuple2<>(namedEntity, 1))
								.reduceByKey(Integer::sum);

						// Recopilar los resultados en una lista
						List<Tuple2<String, Integer>> wordCounts = wordCountRDD.collect();

						for (Tuple2<String, Integer> wordCount : wordCounts) {
							String word = wordCount._1();
							int count = wordCount._2();

							String d = dictionary.get(word);
							NamedEntity ne = null;
							if (d != null) {
								String[] params = d.split(", ");
								String category = params[0];
								String theme = params[1];
								switch (category) {
									case "Person":
										String peid = params[2];
										ne = new Person(word, peid, theme);
										break;

									case "LastName":
										String lncanonica = params[2];
										String lnorigen = params[3];
										ne = new LastName(word, lncanonica, lnorigen, theme);
										break;

									case "Name":
										params = dictionary.get(word).split(", ", 5);
										String nacanonica = params[2];
										String naorigen = params[3];
										String naalternatives =  params[4];
										ne = new Name(word, nacanonica, naorigen, naalternatives, theme);
										break;
									
									case "Title":
										String ticanonica = params[2];
										String tiprofessional = params[3];
										ne = new Title(word, ticanonica, tiprofessional, theme);
										break;

									case "Country":
										String copopulation = params[2];
										String colanguage = params[3];
										ne = new Country(word, copopulation, colanguage, theme);
										break;
									case "City":
										String cicountry = params[2];
										String cicapital = params[3];
										String cipopulation = params[4];
										ne = new City(word, cicountry, cicapital, cipopulation, theme);
										break;

									case "Address":
										String adcity = params[2];
										ne = new Address(word, adcity, theme);
										break;

									case "Organization":
										String orcanonica = params[2];
										String ormembers = params[3];
										String ortype = params[4];
										ne = new Organization(word, orcanonica, ormembers, ortype, theme);
										break;

									case "Product":
										String prcommercial = params[2];
										String prproducer = params[3];
										ne = new Product(word, prcommercial, prproducer, theme);
										break;

									case "Event":
										String evcanonica = params[2];
										String evdate = params[3];
										String evrecurrent = params[4];
										ne = new Event(word, evcanonica, evdate, evrecurrent, theme);
										break;

									case "Date":
										String daprecise = params[2];
										String dacanonica = params[3];
										ne = new DateClass(word, daprecise, dacanonica, theme);
										break;

									case "Other":
										String otcomentary= "";
										ne = new Other(word, otcomentary, theme);
										break;
								}
								
							} else {
								ne = new NamedEntity(word, null, count, null);
							}
							System.out.println(ne.toString());
						}
					}
				}
			}

			// Detener el contexto de Spark
			sparkContext.close();
			sparkSession.close();

			
		}else {
			printHelp();
		}
	}

}
