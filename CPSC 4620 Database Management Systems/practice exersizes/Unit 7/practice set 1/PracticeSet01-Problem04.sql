-- ## Problem 4:
-- 
-- The InstantStay Finance team indicates that the retrieved data is not suitable for 
-- making payments as currency. 
-- 
-- You need to round up the actual prices to have only 2 decimals (at most).
-- 
-- +--------+----------------------+
-- | StayID | Actual Price Rounded |
-- +--------+----------------------+
-- |   1    |        110.0         |
-- |   2    |        110.0         |
-- |   3    |        110.0         |
-- |   4    |        110.0         |
-- |   5    |        117.0         |
-- |   6    |        119.0         |
-- |   7    |        -120.5        |
-- |   8    |        127.5         |
-- |   9    |        128.0         |
-- |   10   |        100.0         |
-- |   11   |         87.5         |
-- |   12   |        -91.17        |
-- |   13   |        200.0         |
-- +--------+----------------------+

/* YOUR SOLUTION HERE */
SELECT StayID, Round((StayPrice * (1 - StayDiscount)),2) AS "Actual Price Rounded"
FROM STAY;