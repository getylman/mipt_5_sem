// package sem_5.java.dz2;

public class MyClass {
  private int value = 1;

    @Cache
    public int getValue() {
        return value;
    }

    @Setter
    public void setValue(int value) {
        this.value = value;
    }
}
