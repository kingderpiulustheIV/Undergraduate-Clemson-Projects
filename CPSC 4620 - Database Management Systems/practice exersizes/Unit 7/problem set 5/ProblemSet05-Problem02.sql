-- ## Problem 2
-- 
-- Write a query to display the book number, title, author last name, author first name,
-- patron ID, last name, and patron type for all books currently checked out to a patron. 
-- Sort the results by book title.
-- 
-- +------------+-----------------------------+------------+------------+----------+-------------+------------+
-- |   BOOK_NUM | BOOK_TITLE                  | AU_LNAME   | AU_FNAME   |   PAT_ID | PAT_LNAME   | PAT_TYPE   |
-- |------------+-----------------------------+------------+------------+----------+-------------+------------|
-- |       5252 | Beyond the Database Veil    | Chiang     | Xia        |     1229 | Burke       | Student    |
-- |       5242 | C# in Middleware Deployment | Aggerwal   | Manish     |     1228 | Goodman     | Student    |
-- |       5246 | Capture the Cloud           | Bruer      | Hugo       |     1172 | Miles       | STUDENT    |
-- |       5238 | Conceptual Programming      | Palca      | Julia      |     1229 | Burke       | Student    |
-- |       5240 | iOS Programming             | Beatney    | Rachel     |     1212 | McClain     | Student    |
-- |       5249 | Starlight Applications      | Chiang     | Xia        |     1207 | Ramos       | Student    |
-- +------------+-----------------------------+------------+------------+----------+-------------+------------+
-- -- 

/* YOUR SOLUTION HERE */
SELECT b.BOOK_NUM,
       b.BOOK_TITLE,
       a.AU_LNAME,
       a.AU_FNAME,
       p.PAT_ID,
       p.PAT_LNAME,
       p.PAT_TYPE
FROM BOOK b
JOIN WRITES w ON b.BOOK_NUM = w.BOOK_NUM
JOIN AUTHOR a ON w.AU_ID = a.AU_ID
JOIN CHECKOUT c ON b.BOOK_NUM = c.BOOK_NUM
JOIN PATRON p ON c.PAT_ID = p.PAT_ID
WHERE c.CHECK_IN_DATE IS NULL
ORDER BY b.BOOK_TITLE;