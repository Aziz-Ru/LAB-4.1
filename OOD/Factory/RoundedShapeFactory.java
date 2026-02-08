package Factory;

public class RoundedShapeFactory extends AbstractFactory {
  
  public Shape getShape(String shapeType){
    if(shapeType.equalsIgnoreCase("square")){
      return new RoundedSquare();
    }
    else if(shapeType.equalsIgnoreCase("rectangle")){
      return new RoundedRectangle();
    }
    return null;
  
}

}
