-- ## Problem 1:
-- 
-- The House Development team wants to ensure that the default price of the extras should be 0
-- instead of NULL. Their calculation system doesn't work when NULL values are returned. 
-- You need to modify the ExtraPrice column in the EXTRA table so that the value 
-- defaults to zero.
-- 

/* YOUR SOLUTION HERE */
ALTER TABLE EXTRA
ALTER COLUMN ExtraPrice SET DEFAULT 0;

