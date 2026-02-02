package Filter;

import java.util.ArrayList;

public class MaleCriteria implements Criteria {

  @Override
  public ArrayList<Person> meetCriteria(ArrayList<Person> persons) {
    ArrayList<Person> malePerson = new ArrayList<Person>();
    for (Person p: persons){
      if(p.getGender().equalsIgnoreCase("male")){
        malePerson.add(p);
      }
    }
    return malePerson;
  }
  
}
