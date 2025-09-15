-- ## Problem 3
-- 
-- Write a query to display the book number, title, and number of times each book has been 
-- checked out. Include books that have never been checked out. Sort the results in descending 
-- order by the number of times checked out and then by title.
-- 
-- +------------+-----------------------------------------------------------------------+---------------------+
-- |   BOOK_NUM | BOOK_TITLE                                                            |   Times Checked Out |
-- |------------+-----------------------------------------------------------------------+---------------------|
-- |       5236 | Database in the Cloud                                                 |                  12 |
-- |       5235 | Beginner's Guide to JAVA                                              |                   9 |
-- |       5240 | iOS Programming                                                       |                   7 |
-- |       5238 | Conceptual Programming                                                |                   6 |
-- |       5237 | Mastering the database environment                                    |                   5 |
-- |       5252 | Beyond the Database Veil                                              |                   4 |
-- |       5242 | C# in Middleware Deployment                                           |                   4 |
-- |       5246 | Capture the Cloud                                                     |                   4 |
-- |       5244 | Cloud-based Mobile Applications                                       |                   4 |
-- |       5254 | Coding Style for Maintenance                                          |                   4 |
-- |       5249 | Starlight Applications                                                |                   4 |
-- |       5248 | What You Always Wanted to Know About Database, But Were Afraid to Ask |                   3 |
-- |       5243 | DATABASES in Theory                                                   |                   2 |
-- |       5239 | J++ in Mobile Apps                                                    |                   0 |
-- |       5241 | JAVA First Steps                                                      |                   0 |
-- |       5250 | Reengineering the Middle Tier                                         |                   0 |
-- |       5247 | Shining Through the Cloud: Sun Programming                            |                   0 |
-- |       5245 | The Golden Road to Platform independence                              |                   0 |
-- |       5251 | Thoughts on Revitalizing Ruby                                         |                   0 |
-- |       5253 | Virtual Programming for Virtual Environments                          |                   0 |
-- +------------+-----------------------------------------------------------------------+---------------------+
-- 

/* YOUR SOLUTION HERE */
 SELECT b.BOOK_NUM,
       b.BOOK_TITLE,
       COUNT(c.BOOK_NUM) AS "Times Checked Out"
FROM BOOK b
LEFT JOIN CHECKOUT c ON b.BOOK_NUM = c.BOOK_NUM
GROUP BY b.BOOK_NUM, b.BOOK_TITLE
ORDER BY COUNT(c.BOOK_NUM) DESC, b.BOOK_TITLE;