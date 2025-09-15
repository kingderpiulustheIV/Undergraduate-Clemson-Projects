-- ## Problem 2
-- 
-- Create the INVOICE table structure shown in the ProblemSet09 ERD:
-- - INV_NUM should store integer values. 
-- - INV_DATE should store date values. 
-- - INV_AMOUNT should support up to eight digits to the left of the decimal place and 
--   two digits to the right of the decimal place. 
-- - Use INV_NUM as the primary key.  
-- - Note that the CUST_NUM is the foreign key to CUSTOMER, so be certain to enforce 
--   referential integrity.
-- 

/* YOUR SOLUTION HERE */
CREATE TABLE INVOICE (
	INV_NUM INTEGER PRIMARY KEY,
	CUST_NUM INTEGER,
    INV_DATE DATE,
    INV_AMOUNT DECIMAL(10,2),
	CONSTRAINT CUST_NUM FOREIGN KEY (CUST_NUM) REFERENCES CUSTOMER(CUST_NUM)

);
