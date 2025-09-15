-- ## Task 1:
-- 
-- The Car Maintenance team wanted to ensure that the default price of the maintenance actions 
-- should not be empty and 0 instead if not specified. Alter the MAINTENANCE_TYPES table 
-- created in _Chapter 8, Activity 1_ to set the default MAINTENANCE_PRICE to 0.
-- 
ALTER TABLE MAINTENANCE_TYPES
	ALTER COLUMN MAINTENANCE_PRICE SET DEFAULT 0;

-- ## Task 2:
-- 
-- The Driver Relationship team wants to ensure that the all driving license IDs in the active 
-- drivers table have the length of 7. Alter the ACTIVE_DRIVERS table created previously
-- to check the length of the DRIVER_DRIVING_LICENSE_ID.
-- 
ALTER TABLE ACTIVE_DRIVERS ADD CHECK (LENGTH(DRIVER_DRIVING_LICENSE_ID) = 7);

-- ## Task 3:
-- 
-- The Car Maintenance team wants to insert and store the following maintenance types to the
-- MAINTENANCE_TYPES table:
-- 
-- ID: 1 
-- Description: Tire Change 
-- Price: 50 
-- 
-- ID: 2
-- Description: Oil Change 
-- Price: 45 
-- 
-- ID: 3
-- Description: Full Cleaning
-- Price: 100 
-- 
-- ID: 4
-- Description: Gas Pump Change
-- Price: 145
-- 
INSERT INTO MAINTENANCE_TYPES VALUES (1, 'Tire Change', 50);
INSERT INTO MAINTENANCE_TYPES VALUES (2, 'Oil Change', 45);
INSERT INTO MAINTENANCE_TYPES VALUES (3, 'Full Cleaning', 100); 
INSERT INTO MAINTENANCE_TYPES VALUES (4, 'Gas Pump Change', 145);

-- ## Task 4:
-- 
-- The Car Maintenance team wants to add new maintenance tasks into the system. The team has
-- determined that there should be Tire Change (ID: 1) task for every car with the model year
-- 2021 in InstantRide. Due date of this maintenance tasks is 31 December, 2022 
-- Insert the rows into the MAINTENANCES table for every car built in 2021 and send the
-- data back to the team.
-- 

INSERT INTO MAINTENANCES(CAR_ID, MAINTENANCE_TYPE_ID, MAINTENANCE_DUE) 
	SELECT CAR_ID, '1', '2022-12-31' FROM CARS WHERE CAR_YEAR = '2021';

-- ## Task 5:
-- 
-- The Driver Relationship team realized that there is no need for DRIVER_DRIVING_LICENSE_CHECKED
-- field in the active drivers table. Since all the drivers are already active in InstantRide, 
-- their driving licenses should be checked regularly. The team wanted you to remove the field 
-- from the table.
-- 
ALTER TABLE ACTIVE_DRIVERS DROP COLUMN DRIVER_DRIVING_LICENSE_CHECKED;

-- ## Task 6:
-- 
-- The Car Maintenance team wants to update the price of Oil Change to 75.In addition, they 
-- will no longer provide or require a _Gas Pump Change_ in the future and there is no need to 
-- keep the maintenance item in the database. Update the cost of the oil change and remove the 
-- gas pump change option from the MAINTENANCE_TYPES table.
-- 
SET SQL_SAFE_UPDATES = 0;
UPDATE MAINTENANCE_TYPES 
SET 
    MAINTENANCE_PRICE = 75
WHERE
    MAINTENANCE_TYPE_DESCRIPTION = 'Oil Change';
DELETE FROM MAINTENANCE_TYPES 
WHERE
    MAINTENANCE_TYPE_DESCRIPTION = 'Gas Pump Change';
SET SQL_SAFE_UPDATES = 1;
