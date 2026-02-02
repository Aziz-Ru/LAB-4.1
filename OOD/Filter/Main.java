package Filter;

import java.util.ArrayList;

public class Main {
  public static void main(String[] args) {
    ArrayList<Person> persons = new ArrayList<Person>();
    persons.add(new Person("Robert","Male","Single"));
    persons.add(new Person("John","Male","Married"));
    persons.add(new Person("Laura","Female","Married"));
    persons.add(new Person("Diana","Female","Single"));
    persons.add(new Person("Mike","Male","Single"));
    persons.add(new Person("Bobby","Male","Single"));

    Criteria male = new MaleCriteria();
    Criteria female = new FemaleCriteria();
    Criteria single = new SingleCriteria();
    Criteria married = new MarriedCriteria();
    System.out.println("Males: ");

    printPersons(male.meetCriteria(persons));
    System.out.println("\nFemales: ");
    printPersons(female.meetCriteria(persons));
    System.out.println("\nSingle Person: ");
    printPersons(single.meetCriteria(male.meetCriteria(persons)));
    System.out.println("\nMarried Person: ");
    printPersons(married.meetCriteria(female.meetCriteria(persons)));

  
  }

  public static void printPersons(ArrayList<Person> persons){
    for (Person p: persons){
      System.out.println("Person : [ Name : " + p.getName() 
         +", Gender : " + p.getGender()
         +", Marital Status : " + p.getMaritalStatus()
         +" ]");
    }
  }
}
