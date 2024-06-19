package namedEntity;

public class Name extends NamedEntity{
    String canonicalName;
    String origin;
    String alternateForms;

    public Name(String name, String canonicalName, String origin, String alternateForms, String theme) {
        super(name, "Person", 1, theme);
        this.canonicalName = canonicalName;
        this.origin = origin;
        this.alternateForms = alternateForms;
    }

    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", canonical=" + canonicalName + ", origin=" + origin + ", alternate forms=" + "]";
    }
}
