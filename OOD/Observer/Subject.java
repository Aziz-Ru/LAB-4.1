package Observer;

import java.util.ArrayList;
import java.util.List;

public class Subject {

  List<Observer> observers = new ArrayList<Observer>();
  int state;

  void setState(int state){
    this.state = state;
    notifyObservers();    
  }

  int getState(){
    return state;
  }
  
 
  public void attach(Observer obs) {
    observers.add(obs);
  }


  public void detach(Observer obs) {
    observers.remove(obs);
  }

 
  public void notifyObservers() {
    for(Observer obs:observers){
      obs.updateState(this.state);
    }
  }
  
  
  
}
