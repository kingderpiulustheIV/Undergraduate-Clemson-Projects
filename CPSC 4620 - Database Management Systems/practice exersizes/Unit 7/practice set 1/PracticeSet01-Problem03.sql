-- ## Problem 3:
-- 
-- The InstantStay Finance team requires the actual prices for the stays in the system. 
-- 
-- Calculate the actual price using the price and discount amount from the corresponding tables. 
-- (HINT: don't worry if your calculations have too many decimal points)
-- 
-- +--------+--------------------+
-- | StayID |    Actual Price    |
-- +--------+--------------------+
-- |   1    |       110.0        |
-- |   2    |       110.0        |
-- |   3    |       110.0        |
-- |   4    |       110.0        |
-- |   5    | 116.9999998062849  |
-- |   6    | 118.99999916553497 |
-- |   7    |       -120.5       |
-- |   8    | 127.49999910593033 |
-- |   9    | 127.99999952316284 |
-- |   10   | 99.99999962747097  |
-- |   11   | 87.49999850988388  |
-- |   12   |  -91.174998447299  |
-- |   13   |       200.0        |
-- +--------+--------------------+


SELECT StayID, StayPrice * (1 - StayDiscount) AS "Actual Price"
FROM STAY;