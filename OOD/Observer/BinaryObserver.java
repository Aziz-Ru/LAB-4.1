package Observer;

public class BinaryObserver extends Observer {

  public BinaryObserver(Subject sub){
    this.subject = sub;
    this.subject.attach(this);
  }

  @Override
  public void updateState(int state) {
    System.out.println("Binary String: " + Integer.toBinaryString(state));
  }
  
}
