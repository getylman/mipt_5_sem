// package sem_5.java.dz2;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class Utils {
    public static <T> T cache(T obj) throws Exception {
        Class<?> clazz = obj.getClass();
        Map<Method, Object> cache = new HashMap<>();
        Object proxy;
        try {
            proxy = java.lang.reflect.Proxy.newProxyInstance(clazz.getClassLoader(), clazz.getInterfaces(),
                    (proxyObj, method, args) -> {
                        if (method.isAnnotationPresent(Cache.class)) {
                            if (!cache.containsKey(method)) {
                                cache.put(method, method.invoke(obj, args));
                            } else {
                                Object cachedResult = cache.get(method);
                                if (isStateChanged(obj, cachedResult)) {
                                    Object newResult = method.invoke(obj, args);
                                    cache.put(method, newResult);
                                    return newResult;
                                } else {
                                    return cachedResult;
                                }
                            }
                        } else {
                            return method.invoke(obj, args);
                        }
                        return null;
                    });
        } catch (Exception e) {
            // Обработка исключения
            throw new Exception("Ошибка при создании прокси-объекта: " + e.getMessage(), e);
        }
        return (T)proxy;
    }

    private static boolean isStateChanged(Object obj, Object cachedResult) throws Exception {
        for (Method method : obj.getClass().getDeclaredMethods()) {
            try {
                if (method.isAnnotationPresent(Cache.class)) {
                    if (method.getName().equals("equals") || method.getName().equals("hashCode")) {
                        continue;
                    }
                    if (method.isAnnotationPresent(Setter.class)) {
                        method.setAccessible(true);
                        Object newResult = method.invoke(obj, cachedResult);  // тк этот метод может потенциально пробросить исключение
                        if (!Objects.equals(newResult, cachedResult)) {
                            return true;
                        }
                    }
                }
            } catch (Exception e) {
                // Обработка исключения
                throw new Exception("Ошибка при вызове метода: " + e.getMessage(), e);
            }
        }
        return false;
    }
}
