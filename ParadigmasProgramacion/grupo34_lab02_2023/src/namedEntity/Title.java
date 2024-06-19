package namedEntity;

public class Title extends NamedEntity {
    String canonicalName;
    String professional;

    public Title(String name, String canonicalName, String professional, String theme) {
        super(name, "Title", 1, theme);
        this.canonicalName = canonicalName;
        this.professional = professional;
    }

    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", canonical=" + canonicalName + ", professional=" + professional + "]";
    }
}
