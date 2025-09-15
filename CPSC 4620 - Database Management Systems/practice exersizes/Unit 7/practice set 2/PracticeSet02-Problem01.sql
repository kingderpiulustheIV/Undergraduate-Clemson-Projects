-- ## Problem 1:
-- 
-- The local authorities require all the guest information, such as their first and last 
-- name and their stay start and end dates, without checking the existence of reservation data.
-- 
-- +----------------+---------------+---------------+-------------+
-- | GuestFirstName | GuestLastName | StayStartDate | StayEndDate |
-- +----------------+---------------+---------------+-------------+
-- |    Clinton     |    Castro     |  2024-09-10   | 2024-09-15  |
-- |    Clinton     |    Castro     |  2024-04-10   | 2024-04-15  |
-- |     Kobie      |    Burris     |  2024-09-10   | 2024-09-15  |
-- |     Kobie      |    Burris     |  2024-04-10   | 2024-04-15  |
-- |     Erika      |   Tomlinson   |  2024-09-10   | 2024-09-15  |
-- |     Erika      |   Tomlinson   |  2024-06-30   | 2024-07-10  |
-- |     Erika      |   Tomlinson   |  2024-04-10   | 2024-04-15  |
-- |     Aubrey     |   Carpenter   |  2024-08-01   | 2024-09-01  |
-- |      Amy       |     Tapia     |  2024-06-30   | 2024-07-10  |
-- |     Kaine      |    Harwood    |  2024-06-30   | 2024-07-10  |
-- |     Ronald     |     Oneil     |  2024-09-10   | 2024-09-15  |
-- |     Ronald     |     Oneil     |  2024-04-10   | 2024-04-15  |
-- |     Manuel     |    Gibson     |               |             |
-- |      Jada      |     Swan      |               |             |
-- |     Bryce      |    Thorpe     |  2024-08-01   | 2024-09-01  |
-- |      Jada      |     Swan      |               |             |
-- |     Ronald     |     Oneil     |               |             |
-- +----------------+---------------+---------------+-------------+

/* YOUR SOLUTION HERE */
SELECT g.GuestFirstName, g.GuestLastName, s.StayStartDate, s.StayEndDate
FROM GUEST g
LEFT JOIN STAY s ON g.GuestID = s.GuestID
