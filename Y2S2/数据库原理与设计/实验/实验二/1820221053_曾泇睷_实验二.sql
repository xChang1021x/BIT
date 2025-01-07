use sales

SELECT 供应商名称, 供应商地址, 供应商电话 FROM supplier

SELECT * FROM orders
WHERE YEAR(订单日期) = 2014 and MONTH(订单日期) >= 1 and MONTH(订单日期) <= 10 and 订单总金额 > 1000

SELECT customer.顾客编号, customer.姓名, orders.订单总金额
FROM customer LEFT OUTER JOIN orders ON orders.顾客编号 = customer.顾客编号

SELECT customer.顾客编号, customer.姓名
FROM customer LEFT OUTER JOIN orders ON orders.顾客编号 = customer.顾客编号
WHERE 订单总金额 > 1000

SELECT 供应商编号, 供应商名称, 供应商地址
FROM supplier
WHERE 国家编号 IN
    (SELECT 国家编号
    FROM supplier
    WHERE 供应商名称 = '金仓集团')

SELECT 零件名称, 制造商, 零件售价, 供应价格
FROM part INNER JOIN partsupp ON part.零件编号 = partsupp.零件编号
WHERE 供应价格 > 零件售价

SELECT orders.订单编号, 订单总金额, 零件编号
FROM customer INNER JOIN orders ON orders.顾客编号 = customer.顾客编号 INNER JOIN lineitem ON orders.订单编号 = lineitem.订单编号
WHERE 姓名 IN
    (SELECT 姓名
     FROM customer
     WHERE 姓名 = '阿波罗')
