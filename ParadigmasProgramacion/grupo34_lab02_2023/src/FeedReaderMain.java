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

public class FeedReaderMain {

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
			for (SingleSubscription s : subs.getSubscriptionsList()) {
				httpRequester hr = new httpRequester();

				if (s.getUrlType().contains("reddit")){
					System.out.println("Reddit no implementado");
				}else if (s.getUrlType().contains("rss")){
					int urlParamsSize = s.getUrlParamsSize();
					List<String> urlParams = new ArrayList<>(s.getUrlParams()); // Hace una copia de la lista existente
					for (int i = 0; i < urlParamsSize ; i++) {
						s.setUrlParams(urlParams.get(i));
						String feed = hr.getFeedRss(s.getFeedToRequest(i));
						RssParser rp = new RssParser();
						Feed f = rp.parse(feed);
						f.prettyPrint();
					}
				}
			}
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
			
			for (SingleSubscription s : subs.getSubscriptionsList()) {
				httpRequester hr = new httpRequester();
				if (s.getUrlType().contains("reddit")){
					System.out.println("Reddit no implementado");
				}else if (s.getUrlType().contains("rss")){
					int urlParamsSize = s.getUrlParamsSize();
					List<String> urlParams = new ArrayList<>(s.getUrlParams()); // Hace una copia de la lista existente
					
					Dictionary dict = new Dictionary();
					Map<String, String> dictionary = dict.info();
					
					for (int i = 0; i < urlParamsSize ; i++) {
						s.setUrlParams(urlParams.get(i));
						String feed = hr.getFeedRss(s.getFeedToRequest(i));
						RssParser rp = new RssParser();
						Feed f = rp.parse(feed);
						
						Map<String, NamedEntity> neTable = new HashMap<String, NamedEntity>();
						for (Article art : f.getArticleList()) {
							Heuristic h = new QuickHeuristic();
							for (String word : art.getText().split("[ .,]+")) {
								if (h.isEntity(word)) {
									String d = dictionary.get(word);
									NamedEntity ne;
									if (d != null) {
										String[] params = d.split(", ");
										String category = params[0];
										String theme = params[1];
										switch (category) {
											case "Person":
												String peid = params[2];
												ne = neTable.get(word);
												if (ne == null) {
													Person p = new Person(word, peid, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "LastName":
												String lncanonica = params[2];
												String lnorigen = params[3];
												ne = neTable.get(word);
												if (ne == null) {
													LastName p = new LastName(word, lncanonica, lnorigen, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "Name":
												params = dictionary.get(word).split(", ", 5);
												String nacanonica = params[2];
												String naorigen = params[3];
												String naalternatives =  params[4];
												ne = neTable.get(word);
												if (ne == null) {
													Name p = new Name(word, nacanonica, naorigen, naalternatives, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											
											case "Title":
												String ticanonica = params[2];
												String tiprofessional = params[3];
												ne = neTable.get(word);
												if (ne == null) {
													Title p = new Title(word, ticanonica, tiprofessional, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "Country":
												String copopulation = params[2];
												String colanguage = params[3];
												ne = neTable.get(word);
												if (ne == null) {
													Country p = new Country(word, copopulation, colanguage, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "City":
												String cicountry = params[2];
												String cicapital = params[3];
												String cipopulation = params[4];
												ne = neTable.get(word);
												if (ne == null) {
													City p = new City(word, cicountry, cicapital, cipopulation, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "Address":
												String adcity = params[2];
												ne = neTable.get(word);
												if (ne == null) {
													Address p = new Address(word, adcity, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "Organization":
												String orcanonica = params[2];
												String ormembers = params[3];
												String ortype = params[4];
												ne = neTable.get(word);
												if (ne == null) {
													Organization p = new Organization(word, orcanonica, ormembers, ortype, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "Product":
												String prcommercial = params[2];
												String prproducer = params[3];
												
												ne = neTable.get(word);
												if (ne == null) {
													Product p = new Product(word, prcommercial, prproducer, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "Event":
												String evcanonica = params[2];
												String evdate = params[3];
												String evrecurrent = params[4];
												
												ne = neTable.get(word);
												if (ne == null) {
													Event p = new Event(word, evcanonica, evdate, evrecurrent, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "Date":
												String daprecise = params[2];
												String dacanonica = params[3];
												ne = neTable.get(word);
												if (ne == null) {
													DateClass p = new DateClass(word, daprecise, dacanonica, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
											case "Other":
												String otcomentary= "";
												ne = neTable.get(word);
												if (ne == null) {
													Other p = new Other(word, otcomentary, theme);
													neTable.put(word, p);
												} else {
													ne.incFrequency();
												}
												break;
										}
									} else {
										ne = neTable.get(word);
										if (ne == null) {
											NamedEntity p = new NamedEntity(word, null, 1, null);
											neTable.put(word, p);
										} else {
											ne.incFrequency();
										}
									}
								}
							}
						}
						for (NamedEntity ne : neTable.values()) {
							System.out.println(ne.toString());
						}
					}
				}
			}
			
		}else {
			printHelp();
		}
	}

}
