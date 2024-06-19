package namedEntity;

public class Country extends NamedEntity {
    String population;
    String language;

    public Country(String name, String population, String language, String theme) {
        super(name, "Place", 1, theme);
        this.population = population;
        this.language = language;
    }

    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", population=" + population + ", language=" + language+ "]";
    }
}