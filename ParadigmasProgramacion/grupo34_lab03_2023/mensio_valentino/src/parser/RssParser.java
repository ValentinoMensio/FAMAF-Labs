package parser;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import org.xml.sax.InputSource;
import java.io.StringReader;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import feed.*;

/* Esta clase implementa el parser de feed de tipo rss (xml)
 * https://www.tutorialspoint.com/java_xml/java_dom_parse_document.htm 
 * */

public class RssParser extends GeneralParser<Feed> {
    public static Document XMLParser(String s) {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            InputSource is = new InputSource(new StringReader(s));
            return builder.parse(is);
        }
        catch (Exception e){
            e.printStackTrace();
            return null;
        }
    }
    
    public Feed parse(String s){
        Document doc = XMLParser(s);
        NodeList nList = doc.getElementsByTagName("item");
        Feed feed = new Feed("");
        try {
            for (int i = 0; i < nList.getLength(); i++) {
                Node nNode = nList.item(i);
                Element eElement = (Element) nNode;

                String pubDate = eElement.getElementsByTagName("pubDate").item(0).getTextContent();
                SimpleDateFormat formato = new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss Z", Locale.ENGLISH);
                Date fecha = formato.parse(pubDate);

                Article article = new Article(
                        eElement.getElementsByTagName("title").item(0).getTextContent(),
                        eElement.getElementsByTagName("description").item(0).getTextContent(),
                        fecha,
                        eElement.getElementsByTagName("link").item(0).getTextContent());
                feed.addArticle(article);
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
        
        return feed;
    }    
}