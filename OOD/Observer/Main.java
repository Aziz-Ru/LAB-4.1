package Observer;

public class Main {
  
   public static void main(String[] args){
    Subject sub = new Subject();
    new HexObserver(sub);
    new BinaryObserver(sub);
    
    sub.setState(100);
    System.out.println("-------------------");
    sub.setState(50);
    
  }
}
