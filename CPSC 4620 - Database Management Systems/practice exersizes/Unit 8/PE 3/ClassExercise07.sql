-- ## Task 1:
-- 
-- The Car Maintenance team wants to add new maintenance tasks to the MAINTENANCES table created previously.  However, the team also wants to insert the tasks in a batch into the database. 
-- In other words, they want to insert the rows all together without inserting one-by-one. 
-- Therefore, you will need to create a script to add the following tasks and ensure that 
-- they are added together:
-- 
-- - Car ID: 1001, Maintenance Type: 2, Due: 2022-06-01
-- - Car ID: 1003, Maintenance Type: 2, Due: 2022-06-01
-- 
SET AUTOCOMMIT = OFF;
START TRANSACTION;
INSERT INTO MAINTENANCES VALUES ('1001','2', '2022-06-01');
INSERT INTO MAINTENANCES VALUES ('1003','2','2022-06-01');
COMMIT;
SET AUTOCOMMIT = ON;

-- ## Task 2:
-- 
-- The Car Maintenance team wants to add the Tire Change (ID: 1) maintenance task for all cars  
-- with the due date of 1 September, 2024. However, the team also wants to know that if an error 
-- occurs during the updates and will rollback to their previous state. 
-- Create a script for them to first add all tasks and then rollback the changes.
-- 
SET AUTOCOMMIT = OFF;
START TRANSACTION;
INSERT INTO MAINTENANCES(CAR_ID, MAINTENANCE_TYPE_ID, MAINTENANCE_DUE) SELECT CAR_ID, '1', '2024-09-01'
FROM CARS;
ROLLBACK;
SET AUTOCOMMIT = ON;

-- ## Task 3:
-- 
-- The Driver Relationship considered that working on both DRIVERS and ACTIVE_DRIVERS tables 
-- is difficult and too much work. Therefore, the team wants you to remove the table for the 
-- active drivers.
-- 
DROP TABLE ACTIVE_DRIVERS;

-- ## Task 4:
-- 
-- The Driver Relationship team wants to work with the active drivers using a VIEW constructed
-- on the DRIVERS table. By creating the VIEW the team wants to eliminate extra work to keep 
-- both tables up-to-date. Create a VIEW named ACTIVE_DRIVERS for the drivers that has at 
-- least one travel in InstantStay.
-- 
CREATE VIEW ACTIVE_DRIVERS AS
    SELECT 
        DRIVER_ID,
        DRIVER_FIRST_NAME,
        DRIVER_LAST_NAME,
        DRIVER_DRIVING_LICENSE_ID,
        DRIVER_RATING
    FROM
        DRIVERS
    WHERE
        DRIVER_ID IN (SELECT DISTINCT DRIVER_ID FROM TRAVELS);
				
-- ## Task 5:
-- 
-- The Driver Relationship team wants to update the driving license id of an active driver:
-- 
-- - Driver ID: 2003, New Driving License ID: 1735488
-- 
-- In addition, the team wants to do the update over the ACTIVE_DRIVERS VIEW 
-- and also want to see the actual change in the DRIVERS table.
-- 
UPDATE ACTIVE_DRIVERS 
SET 
    DRIVER_DRIVING_LICENSE_ID = 1735488
WHERE
    DRIVER_ID = '2003';

SELECT 
    *
FROM
    DRIVERS
WHERE
    DRIVER_ID = '2003';
	
-- ## Task 6:
-- 
-- The Driver Relationship team realized that maintaining driver IDs is difficult and requested 
-- an automatic way of incrementing the value when a new driver is added. You need to make the 
-- changes on the table to automatically increment the DRIVER_ID. After the change, you need 
-- to insert the following driver:
-- 
-- * First Name: Nursin
-- * Last Name: Yilmaz
-- * Driving License ID: 4141447 
-- * Start Date: 2021-12-28
-- * Driving License Checked: True
-- * Rating: 4.0
-- 
-- NOTE:  Because the DRIVER_ID is a Foreign key in the TRAVELS table, it is not a simple task
-- to change the type of the DRIVER_ID field.  This command alone does not work:
-- 
-- ALTER TABLE DRIVERS 
-- 	CHANGE DRIVER_ID DRIVER_ID INT AUTO_INCREMENT;
-- 
-- We must modify both the DRIVERS and TRAVELS tables:

ALTER TABLE TRAVELS DROP CONSTRAINT DRIVERID;

ALTER TABLE TRAVELS 
	CHANGE DRIVER_ID DRIVER_ID INT;

ALTER TABLE DRIVERS 
	CHANGE DRIVER_ID DRIVER_ID INT AUTO_INCREMENT;
    
ALTER TABLE TRAVELS 
	ADD FOREIGN KEY (DRIVER_ID) REFERENCES DRIVERS(DRIVER_ID);

INSERT INTO DRIVERS(DRIVER_FIRST_NAME, DRIVER_LAST_NAME, DRIVER_DRIVING_LICENSE_ID ,DRIVER_START_DATE, DRIVER_DRIVING_LICENSE_CHECKED, DRIVER_RATING) 
	VALUES('Nursin', 'Yilmaz','4141447','2021-12-28',TRUE, 4.0);


SELECT *
FROM DRIVERS;


