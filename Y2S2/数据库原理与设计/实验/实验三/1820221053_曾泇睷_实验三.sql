use sales

SELECT * FROM customer
WHERE 顾客编号 IN(
        SELECT 顾客编号 FROM orders
        WHERE 订单编号 IN(
            SELECT 订单编号 FROM lineitem
            WHERE 零件编号 IN(
                SELECT 零件编号 FROM part
                WHERE 制造商 = '徐州市泰力公司矿山设备四厂' && 零件名称 = '活塞式减压阀')));

SELECT * FROM customer
WHERE 顾客编号 NOT IN(
        SELECT 顾客编号 FROM orders
        WHERE 订单编号 IN(
            SELECT 订单编号 FROM lineitem
            WHERE 零件编号 IN(
                SELECT 零件编号 FROM part
                WHERE 制造商 = '徐州市泰力公司矿山设备四厂' && 零件名称 = '活塞式减压阀')));

SELECT * FROM customer
WHERE 国籍编号 IN(
    SELECT 国家编号 FROM nation
    WHERE 国家名称 = '中国'
    ) AND 顾客编号 IN(
        SELECT 顾客编号 FROM orders
        GROUP BY 顾客编号 HAVING AVG(订单总金额) > 500
    );

SELECT * FROM part
WHERE 零件编号 IN(
        SELECT 零件编号 FROM lineitem
        WHERE 订单编号 IN(
            SELECT 订单编号 FROM orders
            WHERE 顾客编号 IN(
                SELECT 顾客编号 FROM customer
                WHERE 姓名 = '薜融'
            ) AND 顾客编号 NOT IN(
                SELECT 顾客编号 FROM customer
                WHERE 姓名 = '宣荣揣'
            )
        )
    );

CREATE TRIGGER after_insert
AFTER INSERT ON lineitem
FOR EACH ROW
BEGIN
    DECLARE retail_price DECIMAL(10,2);
    DECLARE new_amount DECIMAL(10,2);
    SELECT 零件售价 INTO retail_price FROM part WHERE part.零件编号= new.零件编号;
    SET new_amount = retail_price * new.数量 * (1-new.折扣);
    UPDATE orders SET 订单总金额 = (订单总金额 + new_amount) WHERE 订单编号 = new.订单编号;
END;

INSERT INTO lineitem VALUES (4995, 4577, 22419, 1, 0, 0.5518992);


CREATE TRIGGER before_update_quantity
BEFORE UPDATE ON lineitem
FOR EACH ROW
BEGIN
    DECLARE available_qty INT;

    SELECT 可用数量 INTO available_qty
    FROM partsupp
    WHERE 零件编号 = NEW.零件编号 AND 供应商编号 = NEW.供应商编号;

    IF NEW.数量 > available_qty THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = '可用数量不足，无法更新订单明细中的数量';
    END IF;
END;

UPDATE lineitem SET 数量 = 304
WHERE 订单编号 = 4998 AND 零件编号 = 4577 AND 供应商编号 = 22419;