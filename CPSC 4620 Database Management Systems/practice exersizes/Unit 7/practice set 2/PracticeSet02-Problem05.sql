-- ## Problem 5
-- 
-- During the guest user analysis, developers realized there could be duplicate users in the 
-- system. Check for the guests with the same name but different GuestIDs to check whether 
-- they are duplicate or not.
-- 
-- +---------+----------------+---------------+-------------------+--------------+
-- | GuestID | GuestFirstName | GuestLastName |    GuestEmail     | DUP Guest ID |
-- +---------+----------------+---------------+-------------------+--------------+
-- |   12    |     Ronald     |     Oneil     | r.oneil@tmail.com |      7       |
-- |   11    |      Jada      |     Swan      | j.swan@tmail.com  |      9       |
-- |    9    |      Jada      |     Swan      | j.swan@xmail.com  |      11      |
-- |    7    |     Ronald     |     Oneil     | r.oneil@xmail.com |      12      |
-- +---------+----------------+---------------+-------------------+--------------+

/* YOUR SOLUTION HERE */
SELECT g.GuestID, g.GuestFirstName, g.GuestLastName, g.GuestEmail, d.GuestID AS "DUP Guest ID"
FROM GUEST g
JOIN GUEST d ON g.GuestFirstName = d.GuestFirstName AND g.GuestLastName = d.GuestLastName AND g.GuestID != d.GuestID
