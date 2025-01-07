CREATE DATABASE TPCH;

use sales

create table region
(
    地区编号 int         null,
    地区名称 varchar(45) null,
    备注     varchar(45) null
);

create table Nation
(
    国家编号 int         null,
    国家名称 varchar(45) null,
    地区编号 int null,
    备注 varchar(45) null
);

create table Supplier
(
    供应商编号 int null,
    供应商名称 varchar(45) null,
    供应商地址 varchar(45) null,
    国家编号 int null,
    供应商电话 varchar(45) null
);

create table Part
(
    零件编号 int null,
    零件名称 varchar(45) null,
    制造商 varchar(45) null,
    尺寸 varchar(45) null,
    零件售价 int null
);

create table PartSupp
(
    零件编号 int null,
    供应商编号 int null,
    可用数量 int null,
    供应价格 int null
);

create table Customer
(
    顾客编号 int null,
    姓名 varchar(45) null,
    国籍编号 int null
);

create table Orders
(
    订单编号 int null,
    顾客编号 int null,
    订单日期 varchar(45) null,
    订单总金额 int null
);

create table Lineitem
(
    订单编号 int null,
    零件编号 int null,
    供应商编号 int null,
    数量 int null,
    退货标记 varchar(10) null,
    折扣 float null
);



