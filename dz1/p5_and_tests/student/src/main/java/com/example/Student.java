package student.src.main.java.com.example;

import java.util.ArrayList;
// import java.util.Arrays;
import java.util.Stack;
import java.util.function.Predicate;

public class Student<T> {
    private String name;
    private ArrayList<T> grades;
    private Stack<Runnable> undoList;
    private Predicate<T> predicate;

    public String getName() { return new String(this.name); }

    public void setName(String name) {
      String tmp_name = new String(this.name);
      undoList.push(() -> {
        this.name = tmp_name;
        // undoList.pop();
      });
      this.name = name;
    }

    public void setGrade(T grade) throws IllegalArgumentException {
      if (!isValidGrade(grade)) {
        throw new IllegalArgumentException("Некорректная оценка!");
      }
      this.grades.add(grade);
      undoList.push(() -> {
        this.grades.remove(grades.size() - 1);
        // this.undoList.pop();
      });
    }

    public ArrayList<T> getGrades() {
      return new ArrayList<>(this.grades);
    }

    private void removeGrade(T grade,
        int index) throws IllegalArgumentException, IndexOutOfBoundsException {
      int counter = -1;
      if (index < 0 || index >= this.grades.size()) {
        throw new IndexOutOfBoundsException("Недопустимый индекс! ");
      }
      for (int i = this.grades.size() - 1; i >= 0; i -= 1) {
        if (this.grades.get(i) == grade) {
          ++counter;
        }
        if (counter == index) {
          this.grades.remove(i);
          int tmp_index = i;
          this.undoList.push(() -> {
            this.grades.add(tmp_index, grade);
            // this.undoList.pop();
          });
          return;
        }
      }
      if (counter < index) {
        throw new IllegalArgumentException("Have not this grade.\n");
      }
    }

    public void removeGrade(T grade) throws IllegalArgumentException, IndexOutOfBoundsException { removeGrade(grade, 0); }

    @Override
    public boolean equals(Object obj) {
      if (this == obj) return true;
      if (obj == null || getClass() != obj.getClass()) return false;
      Student<?> student = (Student<?>) obj;
      return name.equals(student.name) && grades.equals(student.grades);
    }

    @Override
    public String toString() {
      String res = "" + this.name + ": [";
      for (int i = 0; i < this.grades.size(); ++i) {
        res += this.grades.get(i).toString();
        if (i != this.grades.size() - 1) {
          res += ",";
        }
      }
      res += "]";
      return res;
    }

    public Student(String name) {
      this.name = name;
      this.grades = new ArrayList<>();
      this.undoList = new Stack<>();
    }

    public Student(String name, T[] grades) {
      this.name = name;
      this.grades = new ArrayList<>();
      this.undoList = new Stack<>();
      for (int i = 0; i < grades.length; ++i) {
        this.grades.add(grades[i]);
      }
    }

    public Student(String name, ArrayList<T> grades) {
      this.name = name;
      this.grades = new ArrayList<>();
      this.undoList = new Stack<>();
      for (int i = 0; i < grades.size(); ++i) {
        this.grades.add(grades.get(i));
      }
    }

    public Student(String name, Predicate<T> predicate) {
      this.name = name;
      this.grades = new ArrayList<>();
      this.undoList = new Stack<>();
      this.predicate = predicate;
    }

    public Student(String name, T[] grades, Predicate<T> predicate) {
      this.name = name;
      this.grades = new ArrayList<>();
      this.undoList = new Stack<>();
      this.predicate = predicate;
      for (int i = 0; i < grades.length; ++i) {
        if (isValidGrade(grades[i])) {
          this.grades.add(grades[i]);
        }
      }
    }

    public Student(String name, ArrayList<T> grades, Predicate<T> predicate) {
      this.name = name;
      this.grades = new ArrayList<>();
      this.undoList = new Stack<>();
      this.predicate = predicate;
      for (int i = 0; i < grades.size(); ++i) {
        if (isValidGrade(grades.get(i))) {
          this.grades.add(grades.get(i));
        }
      }
    }

    private boolean isValidGrade(T grade) {
      if (predicate instanceof Predicate) {
        return predicate.test(grade);
      } else {
        return true;
      }
    }  // проверка на корректность оценки

    public void undoLastAction() {
      if (!undoList.empty()) {
        this.undoList.peek().run();
        this.undoList.pop();
      }
    }

}