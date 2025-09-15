-- ## Task 1:
-- 
-- The Finance team wants to calculate a VAT (8%) on the amount of the stay reservations in the
-- database. However, the team wants to calculate the VAT after the discounts are applied on the 
-- prices. In addition, it is important to remember if there is no discount/offers, then the 
-- value is NULL in the TRAVELS table. Create a procedure called VATCalculator to 
-- calculate the VAT amount and return with the corresponding travel ID. In addition, execute the 
-- procedure to account for NULL values and send the respective result to the team. The VAT 
-- value should be rounded to 2 decimals.
-- 
-- Remember we need to redefine the MYSQL delimiter (;) when creating the procedure. 
-- This will prevent the commands from executing separately.
-- 
DELIMITER $$
CREATE PROCEDURE VATCalculator()
	BEGIN
		DECLARE VAT_PERCENTAGE FLOAT DEFAULT 0.08;
		SELECT TRAVEL_ID, ROUND(TRAVEL_PRICE * (1- IFNULL(TRAVEL_DISCOUNT, 0)) * VAT_PERCENTAGE,2) AS VAT  FROM TRAVELS;
	END;
$$
DELIMITER ;
CALL VATCalculator();

-- ## Task 2:
-- 
-- The Driver Relationship team wants to arrange workshops and education materials to the 
-- drivers. However, the team wants to create clusters of the drivers based on their experience 
-- in InstantRide. To collect these detail, you will need to create a SQL function called
-- DRIVER_STATUS to determine the level of the driver as follows:
-- 
-- - MASTER more than 4 travels
-- - PRO more than 2 travels
-- - ROOKIE 2 or less travels
-- 
-- In addition, run the function to verify it works as expected and send them back the 
-- driver levels.
-- 
DELIMITER $$
CREATE FUNCTION DRIVER_STATUS(
    id INT
) 
RETURNS VARCHAR(20)
DETERMINISTIC
BEGIN
    DECLARE driverLevel VARCHAR(20);
    DECLARE travelCount INT;
    SET travelCount = (SELECT COUNT(TRAVEL_ID) FROM TRAVELS WHERE DRIVER_ID=id GROUP BY DRIVER_ID);
    
    IF ( travelCount > 4) THEN
        SET driverLevel = 'MASTER';
    ELSEIF (travelCount > 2) THEN
        SET driverLevel = 'PRO';
    ELSE
        SET driverLevel = 'ROOKIE';
    END IF;
    RETURN (driverLevel);
END;
$$
DELIMITER ;


SELECT 
    DRIVER_ID, DRIVER_STATUS(DRIVER_ID)
FROM
    DRIVERS;
	
-- ## Task 3:
-- 
-- The Marketing team wants to collect emails of the users on InstantRide. However, the team 
-- needs a SQL statement to execute inside their programming environment. You need to create a
-- statement that they can easily run the EXECUTE command to return a single column table 
-- containing the USER_EMAIL addresses.
-- 
SET @UserEmailCollector:='SELECT USER_EMAIL FROM USERS';
PREPARE Statement FROM @UserEmailCollector;
EXECUTE Statement;

-- ## Task 4:
-- 
-- The Development team of InstantRide wants to ensure that all email data of the users are 
-- uppercase.  Otherwise, their login system could have problems finding the users. Therefore, 
-- they want you to ensure that each email in the table will always be uppercase after a new 
-- user is added. 
-- 
-- Create a TRIGGER called email_insert that will SET new email addresses to uppercase and 
-- run before new emails are added to the USERS table.
-- 
CREATE TRIGGER  email_insert
	BEFORE INSERT ON USERS FOR EACH ROW 
		SET NEW.USER_EMAIL = UPPER(NEW.USER_EMAIL);
	
INSERT  INTO USERS VALUES ('9000', 'Test1', 'Test1', 'upper@mail.com');

SELECT * FROM USERS WHERE USER_ID = '9000';

-- ## Task 5:
-- 
-- The Developers team also wants you to ensure that emails are converted to uppercase after an 
-- update operation. Currently, new insertions are guaranteed to have uppercase emails, but 
-- there is no such guarantee for legacy emails. Therefore, the team wants to ensure that emails 
-- are being retained in a uppercase irrespective of any changes in the database. 
-- 
-- Create a new TRIGGER called email_update for the USERS table that runs before an 
-- UPDATE operation.
-- 
CREATE TRIGGER  email_update
	BEFORE UPDATE ON USERS FOR EACH ROW 
		SET NEW.USER_EMAIL = UPPER(NEW.USER_EMAIL);

UPDATE USERS
	SET USER_EMAIL = 'isItUpper@mail.com'
	WHERE USER_ID = '9000';
		
SELECT * FROM USERS WHERE USER_ID = '9000';

-- ## Task 6:
-- 
-- The Marketing team of InstantRide wants to create mailing lists for the users. However, they 
-- need a single string which consists of all emails of the users combined (delimited) with a
--  “;”. You need to create a procedure called EmailList which uses a CURSOR that iteratively 
-- collects the email addresses in the USERS table and appends them to the string value. 
-- 
-- In addition, run the procedure and return back them the email list.
-- 
DELIMITER $$ 
CREATE PROCEDURE EmailList (
        INOUT emailAddresses varchar(10000)
)
BEGIN
    DECLARE finished INTEGER DEFAULT 0;
    DECLARE emailAddress varchar(100) DEFAULT "";

    DECLARE cursorEmail CURSOR FOR SELECT USER_EMAIL FROM USERS;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET finished = 1;
 
    OPEN cursorEmail;
    collect: LOOP
        FETCH cursorEmail INTO emailAddress;
        IF finished = 1 THEN 
            LEAVE collect;
        END IF;
        SET emailAddresses = CONCAT(emailAddresses,emailAddress,';');
    END LOOP collect;
    CLOSE cursorEmail;
 
END;
$$
DELIMITER ;

SET @userEmailList = ""; 
CALL EmailList(@userEmailList);
SELECT @userEmailList;


