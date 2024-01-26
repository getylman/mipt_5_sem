// package sem_5.java.dz2;

public class MyClass3 {
  private Integer value;

  @Cache
  public Integer getValue() {
      return value;
  }
  @Setter
  public void setValue(Integer value) {
      this.value = value;
  }
}
