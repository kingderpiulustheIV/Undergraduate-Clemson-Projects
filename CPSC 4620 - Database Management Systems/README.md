# CPSC 4620 - Database Management Systems

## Course Description
Comprehensive course covering database design, implementation, and management. Topics include relational database theory, SQL programming, database normalization, transaction management, and database application development. Students learn to design efficient database schemas and implement database-driven applications using SQL and Java.

## Learning Objectives
- Master SQL query language (DDL, DML, DCL)
- Design normalized relational database schemas
- Understand database normalization (1NF, 2NF, 3NF, BCNF)
- Implement complex queries with joins, subqueries, and aggregations
- Develop database-driven applications using JDBC
- Learn transaction management and concurrency control
- Understand database indexing and optimization
- Apply Entity-Relationship (ER) modeling
- Practice database security and access control

## Projects and Exercises

### Class Exercises
- **Class Exercise 1**: Basic SQL queries and table creation
- **Class Exercise 2**: Joins and multi-table queries
- **Class Exercise 3**: Aggregate functions and grouping
- **Class Exercise 4**: Advanced SQL concepts and subqueries

### Practice Exercises
Extensive practice sets covering all database concepts:
- **Unit 7 Practice Sets**: Advanced query writing and optimization
- **Unit 8 Practice Sets**: Transactions, views, and stored procedures
- Problem sets with 11+ problems each covering various SQL topics

### Major Projects

#### Project Part 1: Database Design
ER diagram creation and schema design for a pizza ordering system. Includes:
- Entity-Relationship modeling
- Schema normalization
- Table design and relationships

#### Project Part 2: SQL Implementation
Implementation of the database schema using SQL:
- DDL statements for table creation
- Data population scripts
- Complex query development
- View and index creation

#### Project Part 3: Java Implementation
Full database application using Java and JDBC:
- **DBNinja.java**: Main application controller
- **Order Management**: DineinOrder, PickupOrder, DeliveryOrder classes
- **Data Models**: Pizza, Topping, Customer, Discount classes
- **Database Connectivity**: DBConnector class for connection management
- **Menu System**: Interactive menu interface
- Complete CRUD operations implementation

### Database Tester Application
Helper application for testing database connections and operations:
- **DBTesterApp.java**: Testing framework
- **DBUtil.java**: Utility functions
- **Product.java**: Sample data model
- Connection validation and query testing

## Technology Stack

### Database Management System
- **MySQL/MariaDB**: Primary relational database system
- Support for standard SQL syntax
- Transaction support and ACID properties

### Programming Language
- **Java**: Database application development
- **JDBC (Java Database Connectivity)**: Database access API

### SQL Topics Covered
- Data Definition Language (DDL)
- Data Manipulation Language (DML)
- Data Control Language (DCL)
- Complex JOIN operations
- Subqueries and nested queries
- Aggregate functions (COUNT, SUM, AVG, etc.)
- GROUP BY and HAVING clauses
- Views and indexes
- Stored procedures
- Transactions and triggers

### Development Tools
- MySQL Workbench or similar database IDE
- Java Development Kit (JDK 8+)
- JDBC MySQL Connector driver
- SQL script files (.sql)
- Command-line database clients

### Database Concepts
- Relational Model
- Entity-Relationship (ER) Diagrams
- Normalization Theory
- Functional Dependencies
- Transaction Management
- Concurrency Control
- Database Indexes
- Query Optimization

### Project Architecture
- **Three-tier architecture**: Presentation, Business Logic, Data Access
- Object-oriented design for database entities
- Connection pooling and resource management
- Error handling and exceptions

## Setup and Requirements

### Software Requirements
- MySQL Server 5.7+ or MariaDB
- Java JDK 8 or later
- MySQL JDBC Connector (mysql-connector-java)
- Database IDE (MySQL Workbench, DBeaver, or similar)
- SQL script execution capability

### Database Setup
1. Install MySQL/MariaDB server
2. Create database and user accounts
3. Execute schema creation scripts
4. Populate with initial data
5. Configure JDBC connection parameters

### Java Application Setup
1. Java JDK installed and configured
2. JDBC driver in classpath
3. Database connection credentials configured
4. Compile and run Java applications

### Development Environment
- IDE (Eclipse, IntelliJ IDEA, or VS Code)
- SQL client for database interaction
- Version control (Git)
- Windows 10 x86-64

## Work Type
This class includes **individual exercises and assignments** working with SQL and Java.

## Key Topics Covered
- Relational Database Design
- SQL Query Language (DDL, DML, DCL)
- Database Normalization (1NF through BCNF)
- Entity-Relationship Modeling
- JDBC Programming
- Transaction Management
- Query Optimization
- Database Security
- Multi-user Concurrency
- Application-Database Integration

## Project Domain
The main project implements a **Pizza Ordering System** database with:
- Customer management
- Order processing (dine-in, pickup, delivery)
- Menu and topping management
- Discount and pricing systems
- Order history and reporting
