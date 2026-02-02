package COR;

public class  ConsoleLogger extends AbstractLogger {

  ConsoleLogger(int level){
    this.level=level;
  }

  @Override
  void write(String message) {
    System.out.println("Standard Console::Logger: " + message);
  }
  
}
