package namedEntity;

public class City extends NamedEntity {
    String country;
    String capital;
    String population;

    public City(String name, String country, String capital, String population, String theme) {
        super(name, "Place", 1, theme);
        this.country = country;
        this.population = population;
    }
    
    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", country=" + country + ", capital=" + capital + ", population=" + population + "]";
    }
}
