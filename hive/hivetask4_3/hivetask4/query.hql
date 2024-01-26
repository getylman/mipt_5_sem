ADD JAR /opt/cloudera/parcels/CDH/lib/hive/lib/hive-contrib.jar;
ADD JAR /opt/cloudera/parcels/CDH/lib/hive/lib/hive-serde.jar;
ADD FILE ./udf.py;
USE kidunst;
SELECT TRANSFORM(age)
USING 'python3 udf.py' AS megabyte
FROM Users 
LIMIT 10
