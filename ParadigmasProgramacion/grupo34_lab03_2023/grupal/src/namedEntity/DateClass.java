package namedEntity;

public class DateClass extends NamedEntity {
    String canonicalName;
    String precise;

    public DateClass (String name, String canonicalName, String precise, String theme) {
        super(name, "Date", 1, theme);
        this.canonicalName = canonicalName;
        this.precise = precise;
    }

    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", canonical=" + canonicalName + ", precise=" + precise + "]";
    }
}
