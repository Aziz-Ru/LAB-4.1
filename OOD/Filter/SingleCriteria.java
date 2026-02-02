package Filter;

import java.util.ArrayList;

public class SingleCriteria implements Criteria {

  @Override
  public ArrayList<Person> meetCriteria(ArrayList<Person> person) {
    ArrayList<Person> singlePerson = new ArrayList<Person>();
    
    for (Person p: person){
      if(p.getMaritalStatus().equalsIgnoreCase("single")){
        singlePerson.add(p);  
      }
    }

    return singlePerson;
  }
  
}
