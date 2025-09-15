-- ## Problem 5:
-- 
-- The InstantStay Owner Relationships team wants to send thank you notes to the owners joined in 
-- the last year and are still in the InstantStay system. 
-- 
-- Collect all the information about who owners joined in the last year and are still active in 
-- the system.
-- 
-- 
-- +---------+----------------+---------------+--------------------+---------------+--------------+
-- | OwnerID | OwnerFirstName | OwnerLastName |     OwnerEmail     | OwnerJoinDate | OwnerEndDate |
-- +---------+----------------+---------------+--------------------+---------------+--------------+
-- |    1    |      Kaya      |     Logan     | k.logan@xmail.com  |  2024-03-08   |              |
-- |    2    |      Ruth      |     Gibbs     | r.gibbs@xmail.com  |  2024-06-26   |              |
-- |    3    |    Alberto     |     Burke     | a.burke@xmail.com  |  2024-08-02   |              |
-- |    4    |    Kristen     |     Jones     | k.jones@xmail.com  |  2024-08-08   |              |
-- |    5    |      Alec      |    Webber     | a.webber@xmail.com |  2024-09-17   |              |
-- +---------+----------------+---------------+--------------------+---------------+--------------+

/* YOUR SOLUTION HERE */
SELECT *
FROM OWNER
WHERE (OwnerJoinDate >= DATE_ADD(current_date(),  interval - 1 year))
AND OwnerEndDate IS NULL;

