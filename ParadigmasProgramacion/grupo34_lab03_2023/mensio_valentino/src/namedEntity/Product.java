package namedEntity;

public class Product extends NamedEntity {
    String brand;
    String productor;

    public Product(String name, String brand, String productor, String theme) {
        super(name, "Product", 1, theme);
        this.brand = brand;
        this.productor = productor;
    }
    
    @Override
    public String toString() {
        return "ObjectNamedEntity [name=" + name + ", frequency=" + frequency + ", category=" + category + ", theme=" + theme + ", brand=" + brand + ", productor=" + productor + "]";
    }
}