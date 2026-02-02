
public class Singleton {

  public static void main(String[] args) {
    SingletoneObject obj1 = SingletoneObject.getInstance();
    SingletoneObject obj2 = SingletoneObject.getInstance();
    if (obj1 == obj2) {
      System.out.println("Same Instance");
    } else {
      System.out.println("Different Instance");
    }
  }
}

class SingletoneObject {
  private static SingletoneObject intance = new SingletoneObject();
  private SingletoneObject() {}
  public static SingletoneObject getInstance() {
    return intance;
  }
}

