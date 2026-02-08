package Factory;

public class ShapeFactory extends AbstractFactory {
  public Shape getShape(String shapeType){
    if(shapeType.equalsIgnoreCase("square")){
      return new Square();
    }
    else if(shapeType.equalsIgnoreCase("rectangle")){
      return new Rectangle();
    }
    return null;
  }
}
