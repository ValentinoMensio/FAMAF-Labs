package namedEntity;

public class LastName extends NamedEntity{
    String canonicalName;
    String origin;

    public LastName(String name, String canonicalName, String origin, String theme) {
        super(name, "Person", 1, theme);
        this.canonicalName = canonicalName;
        this.origin = origin;
    }

    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", canonical=" + canonicalName + ", origin=" + origin + "]";
    }
}
