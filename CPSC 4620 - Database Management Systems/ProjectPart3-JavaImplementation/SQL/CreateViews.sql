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

-- ProfitByTopping view
CREATE VIEW ProfitByOrderType AS 
	SELECT TEMP.customerType,
		TEMP.OrderMonth,
		TEMP.TotalOrderPrice, 
		TEMP.TotalOrderCost, 
		TEMP.Profit
	FROM (SELECT 
            ordertable_OrderType AS customerType,
            DATE_FORMAT(ordertable.ordertable_OrderDateTime, "%c/%Y") AS OrderMonth,
            SUM(ordertable_CustPrice) AS TotalOrderPrice, 
            SUM(ordertable_BusPrice) AS TotalOrderCost, 
            ((SUM(ordertable_CustPrice)) - (SUM(ordertable_BusPrice))) AS Profit, 
            1 as o
        FROM ordertable
        GROUP BY ordertable_OrderType, DATE_FORMAT(ordertable.ordertable_OrderDateTime, "%c/%Y")
        UNION SELECT NULL, 
            'Grand Total', 
            SUM(ordertable_CustPrice), 
            SUM(ordertable_BusPrice), 
            SUM((ordertable_CustPrice - ordertable_BusPrice)),
            2 as o
            FROM ordertable ) TEMP
	ORDER BY CASE 
        WHEN customerType = 'dinein' AND OrderMonth = '3/2025' THEN 1
        WHEN customerType = 'dinein' AND OrderMonth = '4/2025' THEN 2
        WHEN customerType = 'pickup' AND OrderMonth = '3/2025' THEN 3
        WHEN customerType = 'delivery' AND OrderMonth = '4/2025' THEN 4
        WHEN customerType = 'delivery' AND OrderMonth = '3/2025' THEN 5
        WHEN customerType = 'pickup' AND OrderMonth = '4/2025' THEN 6
        WHEN OrderMonth = 'Grand Total' THEN 7
        ELSE 8
    END;