package parser;

import java.io.FileReader;
import java.io.IOException;
import org.json.*;
import subscription.*;

/*
 * Esta clase implementa el parser del  archivo de suscripcion (json)
 * Leer https://www.w3docs.com/snippets/java/how-to-parse-json-in-java.html
 * */

public class SubscriptionParser extends GeneralParser<Subscription> {
    FileReader reader;
	
     @Override
     public Subscription parse(String s) {
        try {
            reader = new FileReader(s); 
        }
        catch (IOException e) {
            System.out.println(e);
        }
        
        JSONArray arr = new JSONArray(new JSONTokener(reader));
        Subscription subs = new Subscription("");
        for (int i = 0; i < arr.length(); i++) {
       	 JSONObject obj = arr.getJSONObject(i);
       	 SingleSubscription sub = new SingleSubscription(obj.getString("url"), null, obj.getString("urlType"));
       	 JSONArray params = obj.getJSONArray("urlParams");
       	 for (int j = 0; j < params.length(); j++) {
       		 sub.setUrlParams(params.getString(j));
       	 }
       	 subs.addSingleSubscription(sub);
        }
        return subs;
     }
 }