package Observer;

public class HexObserver extends Observer {

 public HexObserver(Subject sub){
    this.subject = sub;
    this.subject.attach(this);
  }

  @Override
  public void updateState(int state) {
    System.out.println("Hex String: " + Integer.toHexString(state));
  }
  
}
