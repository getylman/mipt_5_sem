package student.src.test.java.com.example;

import student.src.main.java.com.example.Student;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions;

import java.beans.Transient;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.function.Predicate;

public class StudentTest {
  @Test
  public void testInitWithName() {
    Student<Integer> student = new Student<>("Vasya Pupkin");
    assertEquals("Vasya Pupkin", student.getName());
  }
  @Test
  public void testInitWithNameGradesArray() {
    Integer[] grades = new Integer[] { 3, 4, 2 };
    Student<Integer> student = new Student<>("Vasya Pupkin", grades);
    assertEquals("Vasya Pupkin", student.getName());
    assertTrue(student.getGrades().equals(new ArrayList<>(Arrays.asList(grades))));
  }
  @Test
  public void testInitWithNameGradesArrayList() {
    ArrayList<Integer> grades = new ArrayList<>(Arrays.asList(new Integer[] {2, 3, 4}));
    Student<Integer> student = new Student<>("Vasya Pupkin", grades);
    assertEquals("Vasya Pupkin", student.getName());
    assertTrue(student.getGrades().equals(grades));
  }
  @Test
  public void testInitWithNamePredicate() {
    Student<Integer> student = new Student<>("Vasya Pupkin", p -> p >= 1 && p <= 5);
    assertEquals("Vasya Pupkin", student.getName());
    try {
      student.setGrade(1);
    } catch (IllegalArgumentException e) {
      // ...
    }
    assertEquals(1, student.getGrades().size());
    try {
      student.setGrade(6);
    } catch (IllegalArgumentException e) {
      // ...
    }
    assertEquals(1, student.getGrades().size());
  }
  @Test
  public void testInitWithNameArrayPredicate() {
    Predicate<Integer> predicate = p -> p >= 1 && p <= 5;
    Integer[] grades = new Integer[] { 3, 4, 2, 6, 2 };
    Student<Integer> student = new Student<>("Vasya Pupkin", grades, predicate);
    assertEquals("Vasya Pupkin", student.getName());
    ArrayList<Integer> test_grades = new ArrayList<>();
    for (int i = 0; i < grades.length; ++i) {
      if (predicate.test(grades[i])) {
        test_grades.add(grades[i]);
      }
    }
    assertTrue(student.getGrades().equals(new ArrayList<>(Arrays.asList(test_grades))));
  }
  @Test
  public void testInitWithNameArrayListPredicate() {
    Predicate<Integer> predicate = p -> p >= 1 && p <= 5;
    ArrayList<Integer> grades = new ArrayList<>(Arrays.asList(new Integer[] {2, 3, 4, 6, 2}));
    Student<Integer> student = new Student<>("Vasya Pupkin", grades, predicate);
    assertEquals("Vasya Pupkin", student.getName());
    ArrayList<Integer> test_grades = new ArrayList<>();
    for (int i = 0; i < grades.size(); ++i) {
      if (predicate.test(grades.get(i))) {
        test_grades.add(grades.get(i));
      }
    }
    assertTrue(student.getGrades().equals(test_grades));
  }
  @Test
  public void testGetName() {
    Student<Integer> student = new Student<>("Vasya Pupkin");
    assertEquals("Vasya Pupkin", student.getName());
  }
  @Test
  public void testSetName() {
    Student<Integer> student = new Student<>("Vasya Pupkin");
    student.setName("A");
    assertEquals("A", student.getName());
  }
  @Test
  public void testGetGrade() {
    Student<Integer> student = new Student<>("Vasya Pupkin");
    ArrayList<Integer> grades = new ArrayList<>();
    for (int i = 0; i < 10; ++i) {
      student.setGrade(i);
      grades.add(i);
    }
    assertTrue(grades.equals(student.getGrades()));
  }

  @Test
  public void testSetInvalidGrade() {
    Student<Integer> student = new Student<>("Vasya Pupkin", p -> p >= 1 && p <= 5);
    String last_stage = student.toString();
    try {
      student.setGrade(6);
    } catch (IllegalArgumentException e) {
      assertEquals(last_stage, student.toString());
    }
  }

  @Test
  public void testSetValidGrade() {
    ArrayList<Integer> last_stage_list = student.getGrades();
    for (int i = 1; i <= 5; ++i) {
      last_stage_list.add(i);
      student.setGrade(i);
    }
    assertEquals(last_stage_list, student.getGrades());
  }
  @Test
  public void testToString() {
    ArrayList<Integer> grades = new ArrayList<>(Arrays.asList(new Integer[] { 2, 3, 4 }));
    Student<Integer> student = new Student<>("Vasya Pupkin", grades);
    assertEquals("Vasya Pupkin: [2,3,4]", student.toString());
  }
  @Test
  public void testEquals() {
    Predicate<Integer> predicate1 = p -> p >= 1 && p <= 5;
    Integer[] grades1 = new Integer[] { 3, 4, 2, 6, 2 };
    String name1 = "Lupa";
    Predicate<Integer> predicate2 = p -> p >= 1 && p <= 5;
    Integer[] grades2 = new Integer[] { 3, 4, 2, 2 };
    String name2 = "Lupa";
    Predicate<Integer> predicate3 = p -> p >= 1 && p <= 5;
    Integer[] grades3 = new Integer[] { 3, 4, 2, 2 };
    String name3 = "Pupa";
    Predicate<Integer> predicate4 = p -> p >= 1 && p <= 5;
    Integer[] grades4 = new Integer[] { 3, 2, 4, 2, 0};
    String name4 = "Lupa";
    Predicate<Integer> predicate5 = p -> p >= -1 && p <= 5;
    Integer[] grades5 = new Integer[] { 3, 4, 2, 2, 0};
    String name5 = "Lupa";
    Student<Integer> student1 = new Student<>(name1, grades1, predicate1);
    Student<Integer> student2 = new Student<>(name2, grades2, predicate2);
    Student<Integer> student3 = new Student<>(name3, grades3, predicate3);
    Student<Integer> student4 = new Student<>(name4, grades4, predicate4);
    Student<Integer> student5 = new Student<>(name5, grades5, predicate5);
    assertFalse(student1.equals(student5));
    assertFalse(student1.equals(student4));
    assertFalse(student1.equals(student3));
    assertTrue(student1.equals(student2));
    assertFalse(student3.equals(student5));
  }
  @Test
  public void testRemoveGrade() {
    Predicate<Integer> predicate1 = p -> p >= 1 && p <= 5;
    Integer[] grades1 = new Integer[] { 3, 4, 2, 6, 2 };
    String name1 = "Vasya Pupkin";
    ArrayList<Integer> test_grades = new ArrayList<>(Arrays.asList(new Integer[] { 3, 2, 2 }));
    Student<Integer> student1 = new Student<>(name1, grades1, predicate1);
    student1.removeGrade(4);
    assertTrue(test_grades, student1.getGrades());
  }
  @Test
  public void testUndoLastAction() {
    Predicate<Integer> predicate1 = p -> p >= 1 && p <= 5;
    Integer[] grades1 = new Integer[] { 3, 4, 2, 6, 2 };
    String name1 = "Vasya Pupkin";
    Student<Integer> student1 = new Student<>(name1, grades1, predicate1);
    Student<Integer> student2 = new Student<>(name1, grades1, predicate1);
    student1.setName("Lupa");
    student1.setGrade(5);
    student1.removeGrade(3);
    for (int i = 0; i < 3; ++i) {
      student1.undoLastAction();
    }
    assertTrue(student1.equals(student2));
  }
}
