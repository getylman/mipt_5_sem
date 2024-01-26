ADD JAR /opt/cloudera/parcels/CDH/lib/hive/lib/hive-contrib.jar;

USE kanybekovka;

SELECT internet, COUNT(info) AS amount
FROM (
	SELECT SPLIT(info, ' ')[0] AS internet, info
	FROM Logs
) AS sub_query

GROUP BY internet
ORDER BY amount DESC;
