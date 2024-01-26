// package sem_5.java.dz2;
import java.lang.reflect.InvocationTargetException;


public class Main {
    public static void main(String[] args) {
        try {
            // Тест 1: создание кеширующего прокси для объекта класса MyClass
            MyClass obj = new MyClass();
            MyClass cachedObj = Utils.cache(obj);
            System.out.println(cachedObj.getValue()); // Ожидаемый результат: 1
            System.out.println(cachedObj.getValue()); // Ожидаемый результат: 1
            cachedObj.setValue(2);
            System.out.println(cachedObj.getValue()); // Ожидаемый результат: 2
            System.out.println(cachedObj.getValue()); // Ожидаемый результат: 2

            // Тест 2: обработка исключения InstantiationException
            TestClass testObj = new TestClass();
            try {
                TestClass cachedTestObj = Utils.cache(testObj);
            } catch (Exception e) {
                System.out.println(e.getMessage()); // Ожидаемый результат: Ошибка при создании прокси-объекта: java.lang.InstantiationException: TestClass
            }

            // Тест 3: обработка исключения IllegalAccessException
            TestClass2 testObj2 = new TestClass2();
            try {
                TestClass2 cachedTestObj2 = Utils.cache(testObj2);
                cachedTestObj2.getValue();
            } catch (Exception e) {
                System.out.println(e.getMessage()); // Ожидаемый результат: Ошибка при вызове метода: java.lang.IllegalAccessException: Class Main can not access a member of class TestClass2 with modifiers "private"
            }

            // Тест 4: кеширование метода с несколькими параметрами
            MyClass2 obj2 = new MyClass2();
            MyClass2 cachedObj2 = Utils.cache(obj2);
            System.out.println(cachedObj2.sum(1, 2)); // Ожидаемый результат: 3
            System.out.println(cachedObj2.sum(1, 2)); // Ожидаемый результат: 3
            System.out.println(cachedObj2.sum(2, 3)); // Ожидаемый результат: 5
            System.out.println(cachedObj2.sum(2, 3)); // Ожидаемый результат: 5

            // Тест 5: кеширование метода с возвращаемым значением null
            MyClass3 obj3 = new MyClass3();
            MyClass3 cachedObj3 = Utils.cache(obj3);
            System.out.println(cachedObj3.getValue()); // Ожидаемый результат: null
            System.out.println(cachedObj3.getValue()); // Ожидаемый результат: null
            cachedObj3.setValue(1);
            System.out.println(cachedObj3.getValue()); // Ожидаемый результат: 1
            System.out.println(cachedObj3.getValue()); // Ожидаемый результат: 1
            cachedObj3.setValue(null);
            System.out.println(cachedObj3.getValue()); // Ожидаемый результат: null
            System.out.println(cachedObj3.getValue()); // Ожидаемый результат: null

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}