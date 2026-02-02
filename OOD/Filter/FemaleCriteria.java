package Filter;

import java.util.ArrayList;


public class FemaleCriteria implements Criteria{

  @Override
  public ArrayList<Person> meetCriteria(ArrayList<Person> person) {
    
    ArrayList<Person> femalePerson = new ArrayList<Person>();
    for (Person p: person){
      if(p.getGender().equalsIgnoreCase("female")){
        femalePerson.add(p);  
      }
    }
    return femalePerson;
  }
  
}
