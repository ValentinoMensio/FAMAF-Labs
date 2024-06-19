package namedEntity;

public class Event extends NamedEntity {
    String canonicalName;
    String date;
    String recurrence;

    public Event(String name, String canonicalName, String date, String recurrence, String theme) {
        super(name, "Event", 1, theme);
        this.canonicalName = canonicalName;
        this.date = date;
        this.recurrence = recurrence;
    }

    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", canonical=" + canonicalName + ", date=" + date + ", recurrence=" + recurrence + "]";
    }
}
