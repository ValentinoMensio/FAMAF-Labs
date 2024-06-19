package namedEntity;

public class Organization extends NamedEntity {
    String canonicalName;
    String membeString;
    String type;

    public Organization(String name, String canonicalName, String membeString, String type, String theme) {
        super(name, "Organization", 1, theme);
        this.canonicalName = canonicalName;
        this.membeString = membeString;
        this.type = type;
    }
    
    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", canonical=" + canonicalName + ", members=" + membeString + ", type=" + type + "]";
    }
}