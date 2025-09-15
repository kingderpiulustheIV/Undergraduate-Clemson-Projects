-- ## Problem 5
-- 
-- Enable auto increment on the primary key in the CUSTOMER table.
-- The values should start with 2000.
-- 

/* YOUR SOLUTION HERE */
SET FOREIGN_KEY_CHECKS = 0;

ALTER TABLE CUSTOMER 
MODIFY CUST_NUM INTEGER AUTO_INCREMENT;

ALTER TABLE CUSTOMER AUTO_INCREMENT = 2000;

SET FOREIGN_KEY_CHECKS = 1;