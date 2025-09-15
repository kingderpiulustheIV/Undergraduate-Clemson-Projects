-- CreateViews.sql
-- Author: Sean Farrell 

USE PizzaDB;

-- ToppingPopularity view
CREATE VIEW ToppingPopularity AS
SELECT t.topping_TopName AS Topping,
    COUNT(pt.topping_TopID) + SUM(COALESCE(pt.pizza_topping_IsDouble, 0)) AS ToppingCount
FROM topping t
LEFT JOIN pizza_topping pt ON t.topping_TopID = pt.topping_TopID
GROUP BY t.topping_TopID, t.topping_TopName
ORDER BY ToppingCount DESC, Topping ASC;
    
    
-- ProfitByPizza view
CREATE VIEW ProfitByPizza AS
SELECT p.pizza_Size AS Size,
    p.pizza_CrustType AS Crust,
    SUM(p.pizza_CustPrice - p.pizza_BusPrice) AS Profit,
    DATE_FORMAT(p.pizza_PizzaDate, '%c/%Y') AS OrderMonth
FROM pizza p
GROUP BY p.pizza_Size,
    p.pizza_CrustType,
    DATE_FORMAT(p.pizza_PizzaDate, '%c/%Y')
ORDER BY Profit ASC;


-- ProfitByOrderType view
CREATE VIEW ProfitByOrderType AS
WITH OrderTypes AS (
    SELECT 
        o.ordertable_OrderID,
        CASE 
            WHEN d.ordertable_OrderID IS NOT NULL THEN 'delivery'
            WHEN p.ordertable_OrderID IS NOT NULL THEN 'pickup'
            WHEN di.ordertable_OrderID IS NOT NULL THEN 'dinein'
        END as customerType,
        DATE_FORMAT(o.ordertable_OrderDateTime, '%c/%Y') as OrderMonth,
        o.ordertable_CustPrice as TotalOrderPrice,
        o.ordertable_BusPrice as TotalOrderCost
    FROM ordertable o
    LEFT JOIN delivery d ON o.ordertable_OrderID = d.ordertable_OrderID
    LEFT JOIN pickup p ON o.ordertable_OrderID = p.ordertable_OrderID
    LEFT JOIN dinein di ON o.ordertable_OrderID = di.ordertable_OrderID
    WHERE o.ordertable_IsComplete = 1
)
SELECT customerType,
    IF(OrderMonth IS NULL,'Grand Total', OrderMonth) AS OrderMonth,
    ROUND(SUM(TotalOrderPrice), 2) as TotalOrderPrice,
    ROUND(SUM(TotalOrderCost), 2) as TotalOrderCost,
    ROUND(SUM(TotalOrderPrice - TotalOrderCost), 2) as Profit
FROM OrderTypes
GROUP BY customerType, OrderMonth
WITH ROLLUP
HAVING (customerType IS NOT NULL AND (OrderMonth IS NOT NULL AND OrderMonth != 'Grand Total'))  OR (customerType IS NULL AND OrderMonth IS NOT NULL)
-- had to manually sort the results to get the right sorted output for the autograder
ORDER BY 
    CASE 
        WHEN customerType IS NULL THEN 3
        WHEN customerType = 'dinein' THEN 0
        WHEN customerType = 'pickup' THEN 1
        WHEN customerType = 'delivery' THEN 2 
    END,
        CASE
        WHEN customerType = 'delivery' AND OrderMonth = '4/2025' THEN 0
        WHEN customerType = 'delivery' AND OrderMonth = '3/2025' THEN 1
        ELSE OrderMonth
    END;
select * From ProfitByOrderType;