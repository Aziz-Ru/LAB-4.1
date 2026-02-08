package Factory;

public class FactoryProducer {

  public static AbstractFactory geFactory(boolean rounded){
    if(rounded){
      return new RoundedShapeFactory();
    }else{
      return new ShapeFactory();
    }
  }
  
}
