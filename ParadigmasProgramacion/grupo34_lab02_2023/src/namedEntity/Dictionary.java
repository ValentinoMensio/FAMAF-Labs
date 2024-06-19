package namedEntity;

import java.util.Map;
import java.util.HashMap;

public class Dictionary {
	private Map<String, String> d = new HashMap<String, String>() {{
			put("Messi", "LastName, Futbol, Lionel Messi, Argentina");
			put("Argentina", "Country, null, 45810000, Español");
			put("Córdoba", "City, null, Argentina, Córdoba, 4000000");
			put("Beijing", "Country, tema generico, 21540000, China");
			put("will", "Other, will, grande will");
			put("Tesla", "Organization, null, Tesla Inc., 45000, Automotora");
			put("Yaccarino", "LastName, null, Linda Yaccarino, USA");
			put("Google", "Organization, null, Google LLC, 178000, Tecnologia");
			put("Washington", "City, null, USA, Olympia, 7700000");
			put("Twitter", "Organization, null, Twitter Inc., 7500, Redes Sociales");
			put("2013", "Date, null, null, 2013");
			put("Disney+", "Organization, cultura, Disney Plus, -, Streaming");
			put("Elon", "Name, otros, Elon Musk, Sudáfrica, null");
			put("Indiana", "City, otros, USA, Indianápolis, 6785000");
			put("Logan", "Other, Cine, Pelicula de 2017");
			put("Musk", "LastName, otros, Elon Musk, Sudáfrica");
			put("Cuba", "Country, otros, 11000000, Español");

		}};
	
	public Map<String, String> info(){
		return this.d;
	}
}
