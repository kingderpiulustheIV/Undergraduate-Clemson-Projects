-- ## Problem 18
-- 
-- Write a query to display the patron ID, book number, patron first name and last name, and 
-- book title for all currently checked out books. (Remember to use the redundant relationship
-- described in the assignment instructions for current checkouts.) 
-- 
-- Sort the output by patron last name and book title.
-- 
-- +----------+------------+-------------+-------------+-----------------------------+
-- |   PAT_ID |   BOOK_NUM | PAT_FNAME   | PAT_LNAME   | BOOK_TITLE                  |
-- |----------+------------+-------------+-------------+-----------------------------|
-- |     1229 |       5252 | Gerald      | Burke       | Beyond the Database Veil    |
-- |     1229 |       5238 | Gerald      | Burke       | Conceptual Programming      |
-- |     1228 |       5242 | Homer       | Goodman     | C# in Middleware Deployment |
-- |     1212 |       5240 | Iva         | McClain     | iOS Programming             |
-- |     1172 |       5246 | Tony        | Miles       | Capture the Cloud           |
-- |     1207 |       5249 | Iva         | Ramos       | Starlight Applications      |
-- +----------+------------+-------------+-------------+-----------------------------+

/* YOUR SOLUTION HERE */
SELECT p.PAT_ID,
       c.BOOK_NUM,
       p.PAT_FNAME,
       p.PAT_LNAME,
       b.BOOK_TITLE
FROM PATRON p
JOIN CHECKOUT c ON p.PAT_ID = c.PAT_ID
JOIN BOOK b ON c.BOOK_NUM = b.BOOK_NUM
WHERE c.CHECK_IN_DATE IS NULL
ORDER BY p.PAT_LNAME, b.BOOK_TITLE;
