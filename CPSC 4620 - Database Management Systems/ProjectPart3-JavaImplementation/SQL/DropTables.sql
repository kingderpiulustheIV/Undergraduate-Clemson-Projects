-- DropTables.sql
-- Author: Sean Farrell

USE PizzaDB;

-- Drop views first
DROP VIEW IF EXISTS ToppingPopularity;
DROP VIEW IF EXISTS ProfitByPizza;
DROP VIEW IF EXISTS ProfitByOrderType;

-- Drop tables in reverse order of creation (due to foreign key constraints)
DROP TABLE IF EXISTS order_discount;
DROP TABLE IF EXISTS pizza_discount;
DROP TABLE IF EXISTS pizza_topping;
DROP TABLE IF EXISTS pizza;
DROP TABLE IF EXISTS pickup;
DROP TABLE IF EXISTS delivery;
DROP TABLE IF EXISTS dinein;
DROP TABLE IF EXISTS ordertable;
DROP TABLE IF EXISTS customer;
DROP TABLE IF EXISTS baseprice;
DROP TABLE IF EXISTS discount;
DROP TABLE IF EXISTS topping;


-- Drop the schema
DROP SCHEMA IF EXISTS PizzaDB;