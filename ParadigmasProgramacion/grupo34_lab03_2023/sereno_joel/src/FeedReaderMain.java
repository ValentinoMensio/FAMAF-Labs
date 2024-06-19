import java.util.*;

import feed.Article;
import feed.Feed;
import httpRequest.httpRequester;
import namedEntity.*;
import namedEntity.Dictionary;
import namedEntity.heuristic.*;
import org.apache.spark.api.java.JavaPairRDD;
import parser.RssParser;
import parser.SubscriptionParser;
import scala.Tuple2;
import scala.reflect.internal.JavaAccFlags;
import subscription.SingleSubscription;
import subscription.Subscription;

import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.SparkConf;

public class FeedReaderMain {
	static final SparkConf conf = new SparkConf().setAppName("reader").setMaster("local[*]");
	static final JavaSparkContext sc = new JavaSparkContext(conf);
	private static void printHelp(){
		System.out.println("Please, call this program in correct way: FeedReader [-ne]");
	}
	
	public static void main(String[] args) {
		System.out.println("************* FeedReader version 1.0 *************");
		if (args.length == 0) {
			
			/*
			Leer el archivo de suscription por defecto;
			Llamar al httpRequester para obtenr el feed del servidor
			Llamar al Parser especifico para extrar los datos necesarios por la aplicacion 
			Llamar al constructor de Feed
			LLamar al prettyPrint del Feed para ver los articulos del feed en forma legible y amigable para el usuario
			*/
			//Leer el archivo de suscription por defecto;
			SubscriptionParser sp = new SubscriptionParser();
			Subscription subs = sp.parse("config/subscriptions.json");
			

			
			//Llamar al httpRequester para obtenr el feed del servidor
			
			List<SingleSubscription> subsList = subs.getSubscriptionsList();
			JavaRDD<SingleSubscription> distSubs = sc.parallelize(subsList);
			// solo filtramos las del tipo RSS ya que el parser para las de tipo Reddit no esta implementado
			JavaRDD<List<String>> subsUrls = distSubs.filter(s -> s.getUrlType().contains("rss")).map(s -> {
																											int listSize = s.getUrlParamsSize();
																											List<String> list = new ArrayList<String>(listSize);
																											for (int i = 0; i < listSize; i++) {
																												list.add(s.getFeedToRequest(i));
																											}
																											return list;
																										});
			List<String> urls = subsUrls.reduce((a, b) -> {a.addAll(b); return a;});
			JavaRDD<Feed> feeds = sc.parallelize(urls).map(url -> {httpRequester hr = new httpRequester(); return hr.getFeedRss(url);}).map(text -> {RssParser rp = new RssParser(); return rp.parse(text);});
			feeds.foreach(feed -> feed.prettyPrint());
			
			//Llamar al Parser especifico para extrar los datos necesarios por la aplicacion
			//Llamar al constructor de Feed
			
		} else if (args.length == 1){
			System.out.println("************* Datos Heuristica *************");
			/*
			Leer el archivo de suscription por defecto;
			Llamar al httpRequester para obtenr el feed del servidor
			Llamar al Parser especifico para extrar los datos necesarios por la aplicacion 
			Llamar al constructor de Feed
			Llamar a la heuristica para que compute las entidades nombradas de cada articulos del feed
			LLamar al prettyPrint de la tabla de entidades nombradas del feed.
			 */
			
			SubscriptionParser sp = new SubscriptionParser();
			Subscription subs = sp.parse("config/subscriptions.json");

			//Llamar al httpRequester para obtenr el feed del servidor

			List<SingleSubscription> subsList = subs.getSubscriptionsList();
			JavaRDD<SingleSubscription> distSubs = sc.parallelize(subsList);
			JavaRDD<List<String>> subsUrls = distSubs.filter(s -> s.getUrlType().contains("rss")).map(s -> {
				int listSize = s.getUrlParamsSize();
				List<String> list = new ArrayList<String>(listSize);
				for (int i = 0; i < listSize; i++) {
					list.add(s.getFeedToRequest(i));
				}
				return list;
			});
			List<String> urls = subsUrls.reduce((a, b) -> {a.addAll(b); return a;});
			List<Feed> feeds = sc.parallelize(urls).map(url -> {httpRequester hr = new httpRequester(); return hr.getFeedRss(url);}).map(text -> {RssParser rp = new RssParser(); return rp.parse(text);}).collect();
			Dictionary dict = new Dictionary();
			Map<String, String> dictionary = dict.info();
			JavaPairRDD<String, Integer> counts = sc.emptyRDD().mapToPair(s -> new scala.Tuple2<>("", 0));
			for (Feed feed : feeds) {
				List<Article> articles = feed.getArticleList();
				for (Article article : articles) {
					String text = article.getText();
					counts = counts.union(sc.parallelize(Arrays.asList(text.split("[ .,]+"))).mapToPair(word -> new Tuple2<>(word, 1)));
				}
			}
			counts.reduceByKey((a, b) -> a + b).filter(t -> new QuickHeuristic().isEntity(t._1()));
			JavaPairRDD<String, NamedEntity> neTable = counts.keys().zip(counts.map(t -> {
				String key = t._1();
				Integer value = t._2();
				String d = dictionary.get(key);
				NamedEntity ne = null;
				if (d != null) {
					String[] params = d.split(", ");
					String category = params[0];
					String theme = params[1];
					switch (category) {
						case "Person":
							String peid = params[2];
							ne = new Person(key, peid, theme);
							break;
						case "LastName":
							String lncanonica = params[2];
							String lnorigen = params[3];
							ne = new LastName(key, lncanonica, lnorigen, theme);
							break;
						case "Name":
							params = dictionary.get(key).split(", ", 5);
							String nacanonica = params[2];
							String naorigen = params[3];
							String naalternatives = params[4];
							ne = new Name(key, nacanonica, naorigen, naalternatives, theme);
							break;
						case "Title":
							String ticanonica = params[2];
							String tiprofessional = params[3];
							ne = new Title(key, ticanonica, tiprofessional, theme);
							break;
						case "Country":
							String copopulation = params[2];
							String colanguage = params[3];
							ne = new Country(key, copopulation, colanguage, theme);
							break;
						case "City":
							String cicountry = params[2];
							String cicapital = params[3];
							String cipopulation = params[4];
							ne = new City(key, cicountry, cicapital, cipopulation, theme);
							break;
						case "Address":
							String adcity = params[2];
							ne = new Address(key, adcity, theme);
							break;
						case "Organization":
							String orcanonica = params[2];
							String ormembers = params[3];
							String ortype = params[4];
							ne = new Organization(key, orcanonica, ormembers, ortype, theme);
							break;
						case "Product":
							String prcommercial = params[2];
							String prproducer = params[3];
							ne = new Product(key, prcommercial, prproducer, theme);
							break;
						case "Event":
							String evcanonica = params[2];
							String evdate = params[3];
							String evrecurrent = params[4];
							ne = new Event(key, evcanonica, evdate, evrecurrent, theme);
							break;
						case "Date":
							String daprecise = params[2];
							String dacanonica = params[3];
							ne = new DateClass(key, daprecise, dacanonica, theme);
							break;
						case "Other":
							String otcomentary = "";
							ne = new Other(key, otcomentary, theme);
							break;
					}
					ne.setFrequency(value);
				} else {
					ne = new NamedEntity(key, null, value, null);
				}
				return ne;
			}));
			neTable.foreach(ne -> System.out.println(ne.toString()));
		}else {
			printHelp();
		}
		sc.close();
	}

}
