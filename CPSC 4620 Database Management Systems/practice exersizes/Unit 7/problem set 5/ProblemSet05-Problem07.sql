-- ## Problem 7
-- 
-- Write a query to display the patron ID, last name, number of times that patron has ever 
-- checked out a book, and the number of different books the patron has ever checked out. 
-- 
-- For example, if a given patron has checked out the same book twice, that would count as two
-- checkouts but only one book. Limit the results to only patrons who have made at least three
-- checkouts. 
-- 
-- Sort the results in descending order by number of books, then in descending order by 
-- number of checkouts, and then in ascending order by patron ID.
-- 
-- +----------+-------------+-----------------+-----------------------+
-- |   PAT_ID | PAT_LNAME   |   NUM CHECKOUTS |   NUM DIFFERENT BOOKS |
-- |----------+-------------+-----------------+-----------------------|
-- |     1161 | Koch        |               3 |                     3 |
-- |     1165 | Baldwin     |               3 |                     3 |
-- |     1181 | Horne       |               3 |                     3 |
-- |     1185 | Yang        |               3 |                     3 |
-- |     1210 | Cooley      |               3 |                     3 |
-- |     1229 | Burke       |               3 |                     3 |
-- |     1160 | carter      |               3 |                     2 |
-- |     1171 | Marsh       |               3 |                     2 |
-- |     1172 | Miles       |               3 |                     2 |
-- |     1207 | Ramos       |               3 |                     2 |
-- |     1209 | Mathis      |               3 |                     2 |
-- |     1183 | Hughes      |               3 |                     1 |
-- +----------+-------------+-----------------+-----------------------+
-- 

/* YOUR SOLUTION HERE */
SELECT p.PAT_ID,
       p.PAT_LNAME,
       COUNT(c.CHECK_NUM) AS "NUM CHECKOUTS",
       COUNT(DISTINCT c.BOOK_NUM) AS "NUM DIFFERENT BOOKS"
FROM PATRON p
JOIN CHECKOUT c ON p.PAT_ID = c.PAT_ID
GROUP BY p.PAT_ID, p.PAT_LNAME
HAVING COUNT(c.CHECK_NUM) >= 3
ORDER BY COUNT(DISTINCT c.BOOK_NUM) DESC, COUNT(c.CHECK_NUM) DESC, p.PAT_ID ASC;