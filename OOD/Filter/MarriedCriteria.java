package Filter;

import java.util.ArrayList;

public class MarriedCriteria implements Criteria{

  @Override
  public ArrayList<Person> meetCriteria(ArrayList<Person> person) {
    ArrayList<Person> marriedPerson = new ArrayList<Person>();
    for (Person p: person){
      if(p.getMaritalStatus().equalsIgnoreCase("married")){
        marriedPerson.add(p);  
      }
    }
    return marriedPerson;
  }
  
}
