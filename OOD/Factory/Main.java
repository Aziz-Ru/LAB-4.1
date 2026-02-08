package Factory;

public class Main {
  
  public static void main(String[] args) {
    
    AbstractFactory shapeFactory = FactoryProducer.geFactory(false);
    Shape shape1 = shapeFactory.getShape("rectangle");
    shape1.draw();
    Shape shape2 = shapeFactory.getShape("square");
    shape2.draw();
    AbstractFactory roundedShapeFactory = FactoryProducer.geFactory(true);
    Shape shape3 = roundedShapeFactory.getShape("rectangle");
    shape3.draw();
    Shape shape4 = roundedShapeFactory.getShape("square");
    shape4.draw();
  }
}
