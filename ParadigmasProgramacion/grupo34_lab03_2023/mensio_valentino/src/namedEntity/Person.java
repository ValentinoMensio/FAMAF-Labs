package namedEntity;

public class Person extends NamedEntity {
   	String id;
    
    public Person(String name, String id, String theme) {
        super(name, "Person", 1, theme);
        this.id = id;
    }

    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", id=" + id + "]";
    }

}
