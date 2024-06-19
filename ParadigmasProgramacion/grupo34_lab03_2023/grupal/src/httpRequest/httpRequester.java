package httpRequest;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.Reader;
import java.net.HttpURLConnection;
import java.net.URL;

/* Esta clase se encarga de realizar efectivamente el pedido de feed al servidor de noticias
 * Leer sobre como hacer una http request en java
 * https://www.baeldung.com/java-http-request
 * */

public class httpRequester {
	
	public String getFeedRss(String urlFeed){
		StringBuffer content = new StringBuffer();
		try {
			URL url = new URL(urlFeed);
			
				HttpURLConnection con = (HttpURLConnection) url.openConnection();
				
					con.setRequestMethod("GET");
				int status = con.getResponseCode();
				Reader streamReader = null;
				if (status > 299) {
					streamReader = new InputStreamReader(con.getErrorStream());
				} else {
					streamReader = new InputStreamReader(con.getInputStream());
				}
				BufferedReader in = new BufferedReader(streamReader);
				String inputLine;
				while ((inputLine = in.readLine()) != null) {
					content.append(inputLine);
				}
				in.close();
				con.disconnect();
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return content.toString();
	}

	public String getFeedReedit(String urlFeed) {
		String feedReeditJson = null;
		return feedReeditJson;
	}
}
