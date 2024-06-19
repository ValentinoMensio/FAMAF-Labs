package namedEntity;

public class Address extends NamedEntity {
    String city;

    public Address(String name, String city, String theme) {
        super(name, "Place", 1, theme);
        this.city = city;
    }

    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", city=" + city + "]";
    }
}