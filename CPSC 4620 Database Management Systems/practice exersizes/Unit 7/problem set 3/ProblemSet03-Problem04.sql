-- ## Problem 4
-- 
-- Write a query to display the book number, book title, and subject for every book sorted by 
-- book number. (20 rows)
-- 
-- +------------+-----------------------------------------------------------------------+-------------------+
-- |   BOOK_NUM | TITLE                                                                 | Subject of Book   |
-- |------------+-----------------------------------------------------------------------+-------------------|
-- |       5235 | Beginner's Guide to JAVA                                              | Programming       |
-- |       5236 | Database in the Cloud                                                 | Cloud             |
-- |       5237 | Mastering the database environment                                    | Database          |
-- |       5238 | Conceptual Programming                                                | Programming       |
-- |       5239 | J++ in Mobile Apps                                                    | Programming       |
-- |       5240 | iOS Programming                                                       | Programming       |
-- |       5241 | JAVA First Steps                                                      | Programming       |
-- |       5242 | C# in Middleware Deployment                                           | Middleware        |
-- |       5243 | DATABASES in Theory                                                   | Database          |
-- |       5244 | Cloud-based Mobile Applications                                       | Cloud             |
-- |       5245 | The Golden Road to Platform independence                              | Middleware        |
-- |       5246 | Capture the Cloud                                                     | Cloud             |
-- |       5247 | Shining Through the Cloud: Sun Programming                            | Programming       |
-- |       5248 | What You Always Wanted to Know About Database, But Were Afraid to Ask | Database          |
-- |       5249 | Starlight Applications                                                | Cloud             |
-- |       5250 | Reengineering the Middle Tier                                         | Middleware        |
-- |       5251 | Thoughts on Revitalizing Ruby                                         | Programming       |
-- |       5252 | Beyond the Database Veil                                              | Database          |
-- |       5253 | Virtual Programming for Virtual Environments                          | Programming       |
-- |       5254 | Coding Style for Maintenance                                          | Programming       |
-- +------------+-----------------------------------------------------------------------+-------------------+
-- 

/* YOUR SOLUTION HERE */
SELECT BOOK_NUM, 
	BOOK_TITLE AS TITLE,  
    BOOK_SUBJECT AS 'Subject of Book'
FROM BOOK
ORDER BY BOOK_NUM ASC;
