-- ## Problem 6
-- 
-- Write a query to display the patron ID, first and last name of all patrons who have never 
-- checked out any book. Sort the result by patron last name and then first name.
-- 
-- +----------+-------------+-------------+
-- |   PAT_ID | PAT_FNAME   | PAT_LNAME   |
-- |----------+-------------+-------------|
-- |     1166 | Vera        | Alvarado    |
-- |     1180 | Nadine      | Blair       |
-- |     1238 | Erika       | Bowen       |
-- |     1208 | Ollie       | Cantrell    |
-- |     1227 | Alicia      | Dickson     |
-- |     1205 | Claire      | Gomez       |
-- |     1239 | Elton       | Irwin       |
-- |     1240 | Jan         | Joyce       |
-- |     1243 | Roberto     | Kennedy     |
-- |     1242 | Mario       | King        |
-- |     1237 | Brandi      | Larson      |
-- |     1167 | Alan        | Martin      |
-- |     1182 | Jamal       | Melendez    |
-- |     1201 | Shelby      | Noble       |
-- |     1244 | Leon        | Richmond    |
-- |     1200 | Lorenzo     | Torres      |
-- |     1241 | Irene       | West        |
-- +----------+-------------+-------------+
-- 

/* YOUR SOLUTION HERE */
SELECT p.PAT_ID,
       p.PAT_FNAME,
       p.PAT_LNAME
FROM PATRON p
LEFT JOIN CHECKOUT c ON p.PAT_ID = c.PAT_ID
WHERE c.PAT_ID IS NULL
ORDER BY p.PAT_LNAME, p.PAT_FNAME;
