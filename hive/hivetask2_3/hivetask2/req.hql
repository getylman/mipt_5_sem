-- Adding necessary JAR files
ADD JAR /opt/cloudera/parcels/CDH/lib/hive/lib/hive-contrib.jar;

-- Using the database
USE kanybekovka;

-- Selecting the internet and the count of info from the Logs table

SELECT internet, COUNT(info) AS amount
FROM (
	SELECT SPLIT(info, ' ')[0] AS internet, info
	FROM Logs
) AS sub_query 

-- Browse DESC

GROUP BY internet
ORDER BY amount DESC;
