USE kanybekovka;
SET hive.auto.convert.join=true;
SELECT http, SUM(males), SUM(females)
FROM (
   SELECT http_status as http, IF(sex='male', 1, 0) as males, IF(sex='female', 1, 0) as females
   FROM Logs LEFT JOIN Users on Users.ip = Logs.ip
) AS sol
GROUP BY http