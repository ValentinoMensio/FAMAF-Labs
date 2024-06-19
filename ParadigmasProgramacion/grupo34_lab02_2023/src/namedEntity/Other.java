package namedEntity;

public class Other extends NamedEntity {
    String comentary;

    public Other(String name, String comentary, String theme) {
        super(name, "Other", 1, theme);
        this.comentary = comentary;
    }

    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", commentary=" + comentary + "]";
    }
}
