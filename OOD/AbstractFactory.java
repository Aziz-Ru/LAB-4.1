public class AbstractFactory {
  
  public static void main(String[] args) {
      AbstractFactoryDemo shapeFactory = FactoryProducer.getFactory(false);
      Shape shape1 = shapeFactory.getShape("RECTANGLE");
      shape1.draw();
  
      AbstractFactoryDemo roundedShapeFactory = FactoryProducer.getFactory(true);
      Shape shape2 = roundedShapeFactory.getShape("RECTANGLE");
      shape2.draw();
      
      Shape shape3 = roundedShapeFactory.getShape("SQUARE");
      shape3.draw();
    }
}

class FactoryProducer {
   public static AbstractFactoryDemo getFactory(boolean rounded){   
      if(rounded){
         return new RoundedShapeFactory();         
      }else{
         return new ShapeFactory();
      }
   }
}


abstract class AbstractFactoryDemo {
   abstract Shape getShape(String shapeType) ;
}

 class ShapeFactory extends AbstractFactoryDemo {
   @Override
   public Shape getShape(String shapeType){    
      if(shapeType.equalsIgnoreCase("RECTANGLE")){
         return new Rectangle();         
      }else if(shapeType.equalsIgnoreCase("SQUARE")){
         return new Square();
      }	 
      return null;
   }
}
class RoundedShapeFactory extends AbstractFactoryDemo {
   @Override
   public Shape getShape(String shapeType){    
      if(shapeType.equalsIgnoreCase("RECTANGLE")){
         return new RoundedRectangle();         
      }else if(shapeType.equalsIgnoreCase("SQUARE")){
         return new RoundedShape();
      }	 
      return null;
   }
}








interface Shape{
  void draw();
}

class  Rectangle implements Shape {

  @Override
  public void draw() {
    System.out.println("Inside Rectangle::draw() method.");
  }

  
}
class RoundedRectangle implements Shape {

  @Override
  public void draw() {
    System.out.println("Inside RoundedRectangle::draw() method.");
  }

  
}

class Square implements Shape {

  @Override
  public void draw() {
    System.out.println("Inside Square::draw() method.");
  }

  
}

class RoundedShape implements Shape {

  @Override
  public void draw() {
    System.out.println("Inside RoundedSquare::draw() method.");
  }

  
}
