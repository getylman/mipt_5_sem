package student.src.main.java.com.example;
import java.util.Scanner;

public class StudentInteraction {
  public StudentInteraction() {}

  public void makeInteraction() {
    Student<Integer> student = null;
    Scanner scanner = new Scanner(System.in);
    while (true) {
      getHat();
      int choice = scanner.nextInt();
      switch (choice) {
        case 0:
          scanner.close();
          return;
        case 1:
          System.out.print("Enter student name: ");
          String name = scanner.next();
          student = new Student<Integer>(name);
          System.out.print("Создан Студент " + student.getName());
          break;
        case 2:
          if (student != null) {
            System.out.print("Enter grade: ");
            int grade = scanner.nextInt();
            try {
              student.setGrade(grade);
            } catch (IllegalArgumentException e) {
              System.out.print(e.getMessage());
            }
          } else {
            System.out.println("Create a student first!");
          }
          break;
        case 3:
          if (student != null) {
            System.out.print("Enter grade to remove: ");
            int gradeToRemove = scanner.nextInt();
            try {
              student.removeGrade(gradeToRemove);
            } catch (IllegalArgumentException e) {
              System.out.print(e.getMessage());
            } catch (IndexOutOfBoundsException e) {
              System.out.print(e.getMessage());
            }
          } else {
            System.out.println("Create a student first!");
          }
          break;
        case 4:
          if (student != null) {
            System.out.println(student.toString());
          } else {
            System.out.println("Create a student first!");
          }
          break;
        case 5:
          if (student != null) {
            student.undoLastAction();
          } else {
            System.out.println("Create a student first!");
          }
          break;
        default:
          System.out.println("Invalid choice!");
      }
    }
  }

  public void getHat() {
    System.out.println(
        "\nMenu:\n" + "1. Create Student\n" + "2. Add Grade\n" + "3. Remove Last Grade\n" + "4. Print Student Inf\n"
            + "5. Undo Last Actiono\n" + "0. Exit");
    System.out.print("Enter your choice: ");
  }
}
