/*
 Navicat Premium Dump SQL

 Source Server         : conn
 Source Server Type    : MySQL
 Source Server Version : 80041 (8.0.41)
 Source Host           : localhost:3306
 Source Schema         : yunnan_system

 Target Server Type    : MySQL
 Target Server Version : 80041 (8.0.41)
 File Encoding         : 65001

 Date: 21/10/2025 22:17:19
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for account_info
-- ----------------------------
DROP TABLE IF EXISTS `account_info`;
CREATE TABLE `account_info`  (
  `username` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '用户名',
  `password` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '密码',
  `type` int NULL DEFAULT NULL COMMENT '账号类型: 1-企业账号 2-市账号',
  `enterprise_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '企业ID',
  `city_code` int NULL DEFAULT NULL COMMENT '市编码',
  `last_login_time` datetime NULL DEFAULT NULL COMMENT '最后登陆时间',
  `status` int NULL DEFAULT NULL COMMENT '状态: 0-正常 1-停用',
  `created_at` datetime NULL DEFAULT NULL COMMENT '账号创建时间',
  PRIMARY KEY (`username`) USING BTREE,
  INDEX `idx_account_type`(`type` ASC) USING BTREE,
  INDEX `idx_account_enterprise_id`(`enterprise_id` ASC) USING BTREE,
  INDEX `idx_account_city_code`(`city_code` ASC) USING BTREE,
  INDEX `idx_account_status`(`status` ASC) USING BTREE,
  INDEX `idx_account_last_login_time`(`last_login_time` ASC) USING BTREE,
  CONSTRAINT `fk_account_enterprise` FOREIGN KEY (`enterprise_id`) REFERENCES `enterprise_info` (`enterprise_id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '账号信息表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for enterprise_info
-- ----------------------------
DROP TABLE IF EXISTS `enterprise_info`;
CREATE TABLE `enterprise_info`  (
  `enterprise_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '企业ID',
  `org_code` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '组织机构代码',
  `name_zh` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '企业名称中文',
  `name_en` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '企业名称英文',
  `region` int NULL DEFAULT NULL COMMENT '所属地区',
  `nature` int NULL DEFAULT NULL COMMENT '所属性质',
  `industry` int NULL DEFAULT NULL COMMENT '所属行业',
  `industry_desc` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '主要经营业务详情',
  `contact_name_zh` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '联系人中文名',
  `contact_name_en` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '联系人英文名',
  `address` varchar(500) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '联系人地址',
  `postal_code` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '邮政编码',
  `phone_num` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '联系电话',
  `fax_num` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '传真号',
  `email` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '邮箱',
  `status` int NULL DEFAULT NULL COMMENT '状态: 0-创建未备案 1-已备案未审核 2-已退回 3-正常(已备案已审核) 4-倒闭',
  `created_at` datetime NULL DEFAULT NULL COMMENT '企业创建时间',
  `updated_at` datetime NULL DEFAULT NULL COMMENT '企业信息修改时间',
  PRIMARY KEY (`enterprise_id`) USING BTREE,
  INDEX `idx_enterprise_region`(`region` ASC) USING BTREE,
  INDEX `idx_enterprise_nature`(`nature` ASC) USING BTREE,
  INDEX `idx_enterprise_industry`(`industry` ASC) USING BTREE,
  INDEX `idx_enterprise_status`(`status` ASC) USING BTREE,
  INDEX `idx_enterprise_create_time`(`created_at` ASC) USING BTREE,
  INDEX `idx_enterprise_org_code`(`org_code` ASC) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '企业信息表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for enterprise_report_info
-- ----------------------------
DROP TABLE IF EXISTS `enterprise_report_info`;
CREATE TABLE `enterprise_report_info`  (
  `enterprise_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '企业ID',
  `period_id` int NOT NULL COMMENT '调查期ID',
  `report_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '数据填报ID',
  `old_report_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '旧数据填报ID',
  `reason_return` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退回原因',
  `status` int NULL DEFAULT NULL COMMENT '状态: -1-未填报 0-已暂存 1-待市级审核 2-待省级审核 3-审核通过 4-已归档 5-驳回',
  `period_start_time` datetime NULL DEFAULT NULL COMMENT '上报填报开始时间',
  `period_end_time` datetime NULL DEFAULT NULL COMMENT '上报填报结束时间',
  `created_at` datetime NULL DEFAULT NULL COMMENT '创建时间',
  `updated_at` datetime NULL DEFAULT NULL COMMENT '更新时间',
  `enterprise_nature` int NULL DEFAULT NULL COMMENT '企业所属性质',
  `enterprise_industry` int NULL DEFAULT NULL COMMENT '企业所属行业',
  `enterprise_region` int NULL DEFAULT NULL COMMENT '企业所属地区',
  PRIMARY KEY (`enterprise_id`, `period_id`, `report_id`) USING BTREE,
  INDEX `idx_enterprise_report_period`(`period_id` ASC) USING BTREE,
  INDEX `idx_enterprise_report_report_id`(`report_id` ASC) USING BTREE,
  INDEX `idx_enterprise_report_status`(`status` ASC) USING BTREE,
  INDEX `idx_enterprise_report_create_time`(`created_at` ASC) USING BTREE,
  INDEX `idx_enterprise_report_update_time`(`updated_at` ASC) USING BTREE,
  INDEX `idx_enterprise_report_nature`(`enterprise_nature` ASC) USING BTREE,
  INDEX `idx_enterprise_report_industry`(`enterprise_industry` ASC) USING BTREE,
  INDEX `idx_enterprise_report_region`(`enterprise_region` ASC) USING BTREE,
  INDEX `idx_enterprise_report_old_report_id`(`old_report_id` ASC) USING BTREE,
  CONSTRAINT `fk_enterprise_report_enterprise` FOREIGN KEY (`enterprise_id`) REFERENCES `enterprise_info` (`enterprise_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_enterprise_report_old_report` FOREIGN KEY (`old_report_id`) REFERENCES `report_info` (`report_id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `fk_enterprise_report_period` FOREIGN KEY (`period_id`) REFERENCES `period_info` (`period_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_enterprise_report_report` FOREIGN KEY (`report_id`) REFERENCES `report_info` (`report_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '企业上报信息表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for log_info
-- ----------------------------
DROP TABLE IF EXISTS `log_info`;
CREATE TABLE `log_info`  (
  `log_id` bigint NOT NULL AUTO_INCREMENT COMMENT '日志ID',
  `username` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '操作用户名',
  `user_type` int NULL DEFAULT NULL COMMENT '用户类型: 1-企业账号 2-市账号 3-省账号',
  `enterprise_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '企业ID',
  `operation_module` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '操作模块',
  `operation_desc` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '操作描述',
  `request_url` varchar(500) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '请求URL',
  `request_method` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '请求方法',
  `request_params` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '请求参数',
  `response_status` int NULL DEFAULT NULL COMMENT '响应状态',
  `execution_time` bigint NULL DEFAULT NULL COMMENT '执行时间(毫秒)',
  `error_message` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '错误信息',
  `operation_time` datetime NULL DEFAULT CURRENT_TIMESTAMP COMMENT '操作时间',
  PRIMARY KEY (`log_id`) USING BTREE,
  INDEX `idx_log_username`(`username` ASC) USING BTREE,
  INDEX `idx_log_operation_time`(`operation_time` ASC) USING BTREE,
  INDEX `idx_log_enterprise_id`(`enterprise_id` ASC) USING BTREE,
  INDEX `idx_log_module`(`operation_module` ASC) USING BTREE,
  CONSTRAINT `fk_log_account` FOREIGN KEY (`username`) REFERENCES `account_info` (`username`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_log_enterprise` FOREIGN KEY (`enterprise_id`) REFERENCES `enterprise_info` (`enterprise_id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '操作日志表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for notice_info
-- ----------------------------
DROP TABLE IF EXISTS `notice_info`;
CREATE TABLE `notice_info`  (
  `notice_id` bigint NOT NULL AUTO_INCREMENT COMMENT '通知ID',
  `title` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '通知标题',
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '通知内容',
  `attachment` varchar(500) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '附件路径',
  `attachment_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '附件原名',
  `is_important` int NULL DEFAULT 0 COMMENT '是否重要消息: 0-普通 1-重要',
  `notice_status` int NULL DEFAULT 1 COMMENT '消息状态: 1-全部人可见 2-企业可见 3-市可见 4-省可见',
  `publisher` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '发布人',
  `publish_time` datetime NULL DEFAULT CURRENT_TIMESTAMP COMMENT '发布时间',
  `start_time` datetime NULL DEFAULT NULL COMMENT '生效开始时间',
  `end_time` datetime NULL DEFAULT NULL COMMENT '生效结束时间',
  `read_count` int NULL DEFAULT 0 COMMENT '阅读次数',
  `status` int NULL DEFAULT 1 COMMENT '状态: 0-删除 1-正常 2-草稿',
  `created_at` datetime NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
  `updated_at` datetime NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
  PRIMARY KEY (`notice_id`) USING BTREE,
  INDEX `idx_notice_important`(`is_important` ASC) USING BTREE,
  INDEX `idx_notice_status`(`notice_status` ASC) USING BTREE,
  INDEX `idx_notice_publish_time`(`publish_time` ASC) USING BTREE,
  INDEX `idx_notice_publisher`(`publisher` ASC) USING BTREE,
  INDEX `idx_notice_start_end_time`(`start_time` ASC, `end_time` ASC) USING BTREE,
  INDEX `idx_notice_create_time`(`created_at` ASC) USING BTREE,
  CONSTRAINT `fk_notice_publisher` FOREIGN KEY (`publisher`) REFERENCES `account_info` (`username`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '通知消息表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for notice_read_info
-- ----------------------------
DROP TABLE IF EXISTS `notice_read_info`;
CREATE TABLE `notice_read_info`  (
  `id` bigint NOT NULL AUTO_INCREMENT COMMENT '记录ID',
  `notice_id` bigint NOT NULL COMMENT '通知ID',
  `username` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '阅读用户',
  `read_time` datetime NULL DEFAULT CURRENT_TIMESTAMP COMMENT '阅读时间',
  `enterprise_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '企业ID',
  `user_type` int NULL DEFAULT NULL COMMENT '用户类型',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `uk_notice_user`(`notice_id` ASC, `username` ASC) USING BTREE,
  INDEX `idx_notice_read_time`(`read_time` ASC) USING BTREE,
  INDEX `idx_notice_read_user`(`username` ASC) USING BTREE,
  INDEX `idx_notice_read_enterprise`(`enterprise_id` ASC) USING BTREE,
  CONSTRAINT `fk_notice_read_account` FOREIGN KEY (`username`) REFERENCES `account_info` (`username`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `fk_notice_read_enterprise` FOREIGN KEY (`enterprise_id`) REFERENCES `enterprise_info` (`enterprise_id`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `fk_notice_read_notice` FOREIGN KEY (`notice_id`) REFERENCES `notice_info` (`notice_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '通知阅读记录表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for period_info
-- ----------------------------
DROP TABLE IF EXISTS `period_info`;
CREATE TABLE `period_info`  (
  `period_id` int NOT NULL COMMENT '调查期ID(月)(时间戳)',
  `enterprise_count` int NULL DEFAULT NULL COMMENT '此调查期之前的企业总数',
  PRIMARY KEY (`period_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '调查期信息表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for report_info
-- ----------------------------
DROP TABLE IF EXISTS `report_info`;
CREATE TABLE `report_info`  (
  `report_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '数据填报ID',
  `construction_count` int NULL DEFAULT NULL COMMENT '建档期就业人数',
  `investigation_count` int NULL DEFAULT NULL COMMENT '调查期就业人数',
  `reduction_type` int NULL DEFAULT NULL COMMENT '就业人数减少类型',
  `reason1` int NULL DEFAULT NULL COMMENT '减少原因类型1',
  `reason1_desc` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '减少原因说明1',
  `reason2` int NULL DEFAULT NULL COMMENT '减少原因类型2',
  `reason2_desc` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '减少原因说明2',
  `reason3` int NULL DEFAULT NULL COMMENT '减少原因类型3',
  `reason3_desc` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '减少原因说明3',
  `other_reason` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '其他原因',
  PRIMARY KEY (`report_id`) USING BTREE,
  INDEX `idx_report_reduction_type`(`reduction_type` ASC) USING BTREE,
  INDEX `idx_report_reason1`(`reason1` ASC) USING BTREE,
  INDEX `idx_report_reason2`(`reason2` ASC) USING BTREE,
  INDEX `idx_report_reason3`(`reason3` ASC) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '数据填报信息表' ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
