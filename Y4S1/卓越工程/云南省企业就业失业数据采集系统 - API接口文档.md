# 云南省企业就业失业数据采集系统 - API接口文档

## 基础响应

| 参数   | 说明         | 类型   |
| ------ | ------------ | ------ |
| status | 状态名称     | String |
| code   | 相应状态码   | int    |
| info   | 响应状态信息 | String |
| data   | 返回的数据   | object |
> 返回示例
>
> ```json
> {
> 	"status": "success",
> 	"code": 200,
> 	"info": "请求成功",
> 	"data": null
> }
> ```


# 企业级

## 一、备案信息相关接口

### 1.1 提交备案信息

- **请求方法**：POST
- **请求路径**：/api/profile/submit
- **功能描述**：企业提交备案信息，提交后状态转为待审核，待审核期间不可修改
- **请求头**：无特殊请求头

**请求参数（Body）**

| 参数名         | 类型         | 是否必填 | 说明                                                         |
| :------------- | :----------- | :------- | :----------------------------------------------------------- |
| region_code    | VARCHAR(12)  | 是       | 所属地区，系统根据登录账号自动填充，用户不可修改             |
| org_code       | VARCHAR(18)  | 是       | 统一社会信用代码，18位字母数字，唯一                         |
| company_name   | VARCHAR(255) | 是       | 企业名称，可输入中文、英文                                   |
| company_type   | ENUM         | 是       | 企业性质，两级联动下拉选择                                   |
| industry_code  | ENUM         | 是       | 所属行业，两级联动下拉选择                                   |
| main_business  | TEXT         | 是       | 主要经营业务，两级联动下拉选择，无对应选项可在其他栏填写     |
| contact_person | VARCHAR(50)  | 是       | 联系人，可输入中文、英文                                     |
| address        | VARCHAR(500) | 是       | 详细联系地址，需先通过三级联动选择省/市/县，再填写街道门牌号 |
| postal_code    | VARCHAR(6)   | 是       | 邮政编码，6位数字                                            |
| contact_phone  | VARCHAR(20)  | 是       | 联系电话，唯一，需以+86开头，支持手机号或固话格式            |
| fax_number     | VARCHAR(20)  | 否       | 传真，支持"区号-座机"格式                                    |
| email          | VARCHAR(100) | 否       | 电子邮箱，需符合标准Email格式                                |

**响应参数（data字段）**

| 参数名      | 类型     | 说明                           |
| :---------- | :------- | :----------------------------- |
| profile_id  | BIGINT   | 备案信息ID                     |
| status      | INT      | 备案状态（待审核=0，已通过=1） |
| submit_time | DATETIME | 提交时间                       |

**成功响应示例**

```
{
	"status": "success",
	"code": 200,
	"info": "备案信息提交成功，等待审核",
	"data": {
		"profile_id": 10001,
		"status": 0,
		"submit_time": "2025-01-15T10:30:00+08:00"
	}
}
```



**错误响应示例**

```
{
	"status": "fail",
	"code": 400,
	"info": "统一社会信用代码已被注册",
	"data": null
}
```



**错误码说明**

| 错误码     | 说明                             |
| :--------- | :------------------------------- |
| E-PROF-001 | 统一社会信用代码已存在           |
| E-PROF-002 | 联系电话已被注册                 |
| E-PROF-003 | 电子邮箱格式不正确或已被注册     |
| E-PROF-004 | 缺少必填字段或字段格式不符合要求 |

### 1.2 获取备案信息

- **请求方法**：GET
- **请求路径**：/api/profile
- **功能描述**：已登录企业获取自身备案信息
- **请求头**：Authorization: Bearer {token}（用户登录令牌）
- **请求参数（Query）**：无

**响应参数（data字段）**

| 参数名         | 类型         | 说明                                               |
| :------------- | :----------- | :------------------------------------------------- |
| id             | BIGINT       | 内部主键                                           |
| region_code    | VARCHAR(12)  | 所属地区                                           |
| org_code       | VARCHAR(18)  | 统一社会信用代码                                   |
| company_name   | VARCHAR(255) | 企业名称                                           |
| company_type   | ENUM         | 企业性质                                           |
| industry_code  | ENUM         | 所属行业                                           |
| main_business  | TEXT         | 主要经营业务                                       |
| contact_person | VARCHAR(50)  | 联系人                                             |
| address        | VARCHAR(500) | 详细联系地址                                       |
| postal_code    | VARCHAR(6)   | 邮政编码                                           |
| contact_phone  | VARCHAR(20)  | 联系电话                                           |
| fax_number     | VARCHAR(20)  | 传真（可选）                                       |
| email          | VARCHAR(100) | 电子邮箱（可选）                                   |
| status         | INT          | 备案状态（待审核=0，已通过=1，已暂停=2，已注销=3） |
| created_at     | DATETIME     | 创建时间                                           |
| updated_at     | DATETIME     | 更新时间                                           |

**成功响应示例**

```
{
	"status": "success",
	"code": 200,
	"info": "备案信息获取成功",
	"data": {
		"id": 10001,
		"region_code": "530000",
		"org_code": "91530000MA6K3H9X7C",
		"company_name": "云南XX科技有限公司",
		"company_type": "私营有限责任公司",
		"industry_code": "I. 信息传输、软件和信息技术服务业",
		"main_business": "软件开发、信息技术咨询",
		"contact_person": "张XX",
		"address": "云南省昆明市五华区XX街道XX号",
		"postal_code": "650000",
		"contact_phone": "+8613800138000",
		"fax_number": "0871-65123456",
		"email": "zhang@xxcompany.com",
		"status": 1,
		"created_at": "2025-01-10T09:00:00+08:00",
		"updated_at": "2025-01-10T09:00:00+08:00"
	}
}
```



**错误响应示例**

```
{
	"status": "fail",
	"code": 401,
	"info": "用户未登录",
	"data": null
}
```



**错误码说明**

| 错误码     | 说明               |
| :--------- | :----------------- |
| E-PROF-005 | 用户未登录         |
| E-PROF-006 | 企业未提交备案信息 |

### 1.3 修改备案信息

- **请求方法**：PUT
- **请求路径**：/api/profile/update
- **功能描述**：已备案企业修改自身备案信息，修改后状态重置为待审核
- **请求头**：Authorization: Bearer {token}
- **请求参数（Body）**：同提交备案信息接口（除region_code不可修改外）

**响应参数（data字段）**

| 参数名      | 类型     | 说明                         |
| :---------- | :------- | :--------------------------- |
| profile_id  | BIGINT   | 备案信息ID                   |
| status      | INT      | 更新后的备案状态（待审核=0） |
| update_time | DATETIME | 更新时间                     |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "备案信息修改成功，等待审核",
	"data": {
		"profile_id": 10001,
		"status": 0,
		"update_time": "2025-01-16T14:20:00+08:00"
	}
}
```



**错误响应示例**



```
{
	"status": "fail",
	"code": 403,
	"info": "备案信息处于待审核状态，不可修改",
	"data": null
}
```



**错误码说明**

| 错误码     | 说明                             |
| :--------- | :------------------------------- |
| E-PROF-007 | 备案信息处于待审核状态，禁止修改 |
| E-PROF-008 | 企业备案已被暂停或注销，无法修改 |

### 1.4 获取备案审核状态

- **请求方法**：GET
- **请求路径**：/api/profile/check-status
- **功能描述**：企业查询自身备案信息的审核状态
- **请求头**：Authorization: Bearer {token}
- **请求参数（Query）**：无

**响应参数（data字段）**

| 参数名        | 类型     | 说明                                               |
| :------------ | :------- | :------------------------------------------------- |
| status        | INT      | 备案状态（待审核=0，已通过=1，已暂停=2，已注销=3） |
| check_opinion | String   | 审核意见（仅审核不通过时返回）                     |
| check_time    | DATETIME | 审核时间（仅审核完成后返回）                       |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "审核状态查询成功",
	"data": {
		"status": 1,
		"check_opinion": "审核通过",
		"check_time": "2025-01-12T15:30:00+08:00"
	}
}
```



## 二、数据填报相关接口

### 2.1 获取当期填报窗口信息

- **请求方法**：GET
- **请求路径**：/api/reporting/windows/current
- **功能描述**：返回企业当期填报的开放时间（T0）、截止时间（T1）及是否可提交状态
- **请求头**：Authorization: Bearer {token}
- **请求参数（Query）**：无

**响应参数（data字段）**

| 参数名  | 类型     | 说明                        |
| :------ | :------- | :-------------------------- |
| t0      | DATETIME | 填报开放时间                |
| t1      | DATETIME | 填报截止时间                |
| is_open | BOOLEAN  | 是否可提交（t0 ≤ now < t1） |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "填报窗口信息获取成功",
	"data": {
		"t0": "2025-01-01T00:00:00+08:00",
		"t1": "2025-01-15T23:59:59+08:00",
		"is_open": true
	}
}
```



### 2.2 获取当期报表

- **请求方法**：GET
- **请求路径**：/api/reports/{period}
- **功能描述**：获取指定报送期的报表信息，若无则由服务端在T0时间自动生成
- **请求头**：Authorization: Bearer {token}

**路径参数**

| 参数名 | 类型   | 是否必填 | 说明                  |
| :----- | :----- | :------- | :-------------------- |
| period | String | 是       | 报送期，格式为YYYY-MM |

**响应参数（data字段）**

| 参数名                | 类型        | 说明                                                         |
| :-------------------- | :---------- | :----------------------------------------------------------- |
| id                    | BIGINT      | 报表ID                                                       |
| enterprise_id         | BIGINT      | 企业ID                                                       |
| reporting_period      | DATE        | 报送期（YYYY-MM）                                            |
| status                | VARCHAR(25) | 报表状态（待填报/草稿/待市级审核/市级驳回/待省级审核/省级驳回/已被省级修正/已归档/省级修正后归档） |
| version               | INT         | 版本号，默认1，被驳回后重新提交自动+1                        |
| initial_employees     | INT         | 建档期就业人数                                               |
| current_employees     | INT         | 调查期就业人数                                               |
| reduction_type_code   | INT         | 就业人数减少类型代码（可空，仅人数减少时必填）               |
| primary_reason_code   | INT         | 主要原因代码（可空，仅人数减少时必填）                       |
| primary_reason_desc   | TEXT        | 主要原因说明（可空，选"其他"时必填）                         |
| secondary_reason_code | INT         | 次要原因代码（可空）                                         |
| secondary_reason_desc | TEXT        | 次要原因说明（可空，选"其他"时必填）                         |
| tertiary_reason_code  | INT         | 第三原因代码（可空）                                         |
| tertiary_reason_desc  | TEXT        | 第三原因说明（可空，选"其他"时必填）                         |
| other_reason_desc     | TEXT        | 其他原因（可空）                                             |
| submitted_at          | DATETIME    | 提交时间（可空）                                             |
| updated_at            | DATETIME    | 最后更新时间                                                 |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "报表获取成功",
	"data": {
		"id": 20001,
		"enterprise_id": 10001,
		"reporting_period": "2025-01",
		"status": "待填报",
		"version": 1,
		"initial_employees": 120,
		"current_employees": 120,
		"reduction_type_code": null,
		"primary_reason_code": null,
		"primary_reason_desc": null,
		"secondary_reason_code": null,
		"secondary_reason_desc": null,
		"tertiary_reason_code": null,
		"tertiary_reason_desc": null,
		"other_reason_desc": null,
		"submitted_at": null,
		"updated_at": "2025-01-01T00:00:00+08:00"
	}
}
```



**错误响应示例**



```
{
	"status": "fail",
	"code": 403,
	"info": "企业未备案，无法获取报表",
	"data": null
}
```



**错误码说明**

| 错误码     | 说明                   |
| :--------- | :--------------------- |
| E-PERM-001 | 企业未备案，无填报权限 |
| E-REPT-001 | 报送期格式不正确       |

### 2.3 暂存报表草稿

- **请求方法**：PUT
- **请求路径**：/api/reports/{period}/draft
- **功能描述**：暂存当前填写的报表数据，仅进行基础校验，报表状态更新为草稿
- **请求头**：Authorization: Bearer {token}
- **路径参数**：同获取当期报表接口的period参数

**请求参数（Body）**

| 参数名                | 类型 | 是否必填 | 说明                                        |
| :-------------------- | :--- | :------- | :------------------------------------------ |
| initial_employees     | INT  | 是       | 建档期就业人数，非负整数                    |
| current_employees     | INT  | 是       | 调查期就业人数，非负整数                    |
| reduction_type_code   | INT  | 否       | 就业人数减少类型代码（仅人数减少时必填）    |
| primary_reason_code   | INT  | 否       | 主要原因代码（仅人数减少时必填）            |
| primary_reason_desc   | TEXT | 否       | 主要原因说明（选"其他"时必填，长度5-200字） |
| secondary_reason_code | INT  | 否       | 次要原因代码（不可与主要原因重复）          |
| secondary_reason_desc | TEXT | 否       | 次要原因说明（选"其他"时必填，长度5-200字） |
| tertiary_reason_code  | INT  | 否       | 第三原因代码（不可与主要、次要原因重复）    |
| tertiary_reason_desc  | TEXT | 否       | 第三原因说明（选"其他"时必填，长度5-200字） |
| other_reason_desc     | TEXT | 否       | 其他原因                                    |

**响应参数（data字段）**

| 参数名      | 类型        | 说明             |
| :---------- | :---------- | :--------------- |
| report_id   | BIGINT      | 报表ID           |
| status      | VARCHAR(25) | 报表状态（草稿） |
| update_time | DATETIME    | 暂存时间         |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "报表草稿暂存成功",
	"data": {
		"report_id": 20001,
		"status": "草稿",
		"update_time": "2025-01-10T11:20:00+08:00"
	}
}
```



**错误码说明**

| 错误码     | 说明                                           |
| :--------- | :--------------------------------------------- |
| E-REPT-002 | 人数字段为负数或非整数                         |
| E-REPT-003 | 原因代码重复或选择无效                         |
| E-REPT-004 | 选择"其他"原因但未填写说明或说明长度不符合要求 |

### 2.4 提交报表

- **请求方法**：POST
- **请求路径**：/api/reports/{period}/submit
- **功能描述**：提交报表进行审核，执行严格校验，通过后状态转为待市级审核
- **请求头**：
  - Authorization: Bearer {token}
  - Idempotency-Key: {唯一标识}（用于幂等控制）
- **路径参数**：同获取当期报表接口的period参数
- **请求参数（Body）**：同暂存报表草稿接口的请求参数

**响应参数（data字段）**

| 参数名      | 类型        | 说明                   |
| :---------- | :---------- | :--------------------- |
| report_id   | BIGINT      | 报表ID                 |
| status      | VARCHAR(25) | 报表状态（待市级审核） |
| version     | INT         | 报表版本号             |
| submit_time | DATETIME    | 提交时间               |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "报表提交成功，等待市级审核",
	"data": {
		"report_id": 20001,
		"status": "待市级审核",
		"version": 1,
		"submit_time": "2025-01-15T10:00:00+08:00"
	}
}
```



**错误响应示例**



```
{
	"status": "fail",
	"code": 400,
	"info": "就业人数减少但未选择减少类型",
	"data": null
}
```



**错误码说明**

| 错误码      | 说明                               |
| :---------- | :--------------------------------- |
| E-WIN-001   | 不在填报时间窗口内，禁止提交       |
| E-RED-001   | 就业人数减少但未选择减少类型       |
| E-RSN-001   | 就业人数减少但未选择主要原因       |
| E-RSN-003   | 次要原因与主要原因重复             |
| E-RSN-005   | 第三原因与主要/次要原因重复        |
| E-IDEMP-001 | 提交幂等冲突，重复提交同一版本报表 |

### 2.5 获取减少类型字典

- **请求方法**：GET
- **请求路径**：/api/dicts/reduction-types
- **功能描述**：获取就业人数减少类型的下拉字典数据
- **请求头**：Authorization: Bearer {token}
- **请求参数（Query）**：无

**响应参数（data字段）**

| 参数名    | 类型    | 说明         |
| :-------- | :------ | :----------- |
| code      | INT     | 减少类型代码 |
| name      | String  | 减少类型名称 |
| is_active | BOOLEAN | 是否启用     |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "减少类型字典获取成功",
	"data": [
		{
			"code": 1,
			"name": "关闭破产",
			"is_active": true
		},
		{
			"code": 2,
			"name": "停业整顿",
			"is_active": true
		},
		{
			"code": 10,
			"name": "其他",
			"is_active": true
		}
	]
}
```



### 2.6 获取原因字典

- **请求方法**：GET
- **请求路径**：/api/dicts/reasons
- **功能描述**：根据减少类型过滤获取对应的原因下拉字典数据
- **请求头**：Authorization: Bearer {token}

**请求参数（Query）**

| 参数名 | 类型 | 是否必填 | 说明                       |
| :----- | :--- | :------- | :------------------------- |
| type   | INT  | 是       | 减少类型代码，用于过滤原因 |

**响应参数（data字段）**

| 参数名              | 类型    | 说明               |
| :------------------ | :------ | :----------------- |
| code                | INT     | 原因代码           |
| name                | String  | 原因名称           |
| is_active           | BOOLEAN | 是否启用           |
| reduction_type_code | INT     | 关联的减少类型代码 |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "原因字典获取成功",
	"data": [
		{
			"code": 101,
			"name": "市场需求萎缩",
			"is_active": true,
			"reduction_type_code": 2
		},
		{
			"code": 102,
			"name": "资金链断裂",
			"is_active": true,
			"reduction_type_code": 2
		},
		{
			"code": 999,
			"name": "其他",
			"is_active": true,
			"reduction_type_code": 2
		}
	]
}
```



## 三、数据查询相关接口

### 3.1 查询报表列表

- **请求方法**：GET
- **请求路径**：/api/reports
- **功能描述**：按条件分页检索当前企业的报表列表（只读）
- **请求头**：Authorization: Bearer {token}

**请求参数（Query）**

| 参数名         | 类型     | 是否必填 | 说明                                                      |
| :------------- | :------- | :------- | :-------------------------------------------------------- |
| period_from    | String   | 否       | 报送期起始，格式YYYY-MM                                   |
| period_to      | String   | 否       | 报送期结束，格式YYYY-MM（含当月）                         |
| status         | String[] | 否       | 报表状态，可多选，取值与报表状态枚举一致                  |
| has_reduction  | BOOLEAN  | 否       | 是否就业人数减少（current_employees < initial_employees） |
| version_op     | ENUM     | 否       | 版本号操作符（eq=等于，gte=大于等于，lte=小于等于）       |
| version_val    | INT      | 否       | 版本号值，需与version_op配合使用                          |
| submitted_from | datetime | 否       | 提交时间起始，格式为ISO8601（含时区）                     |
| submitted_to   | datetime | 否       | 提交时间结束，格式为ISO8601（含时区）                     |
| q              | String   | 否       | 关键字，模糊匹配驳回意见、主要原因说明等字段              |
| page           | INT      | 否       | 页码，默认1                                               |
| page_size      | INT      | 否       | 每页条数，默认20，最大100                                 |
| sort           | String   | 否       | 排序规则，默认"-reporting_period,-version"（-表示倒序）   |

**响应参数（data字段）**

| 参数名                  | 类型     | 说明           |
| :---------------------- | :------- | :------------- |
| items                   | Array    | 报表列表数据   |
| items.reporting_period  | String   | 报送期         |
| items.status            | String   | 报表状态       |
| items.version           | INT      | 版本号         |
| items.initial_employees | INT      | 建档期就业人数 |
| items.current_employees | INT      | 调查期就业人数 |
| items.has_reduction     | BOOLEAN  | 是否人数减少   |
| items.submitted_at      | DATETIME | 提交时间       |
| items.updated_at        | DATETIME | 最后更新时间   |
| page                    | INT      | 当前页码       |
| page_size               | INT      | 每页条数       |
| total                   | INT      | 总记录数       |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "报表列表查询成功",
	"data": {
		"items": [
			{
				"reporting_period": "2025-01",
				"status": "待市级审核",
				"version": 2,
				"initial_employees": 120,
				"current_employees": 100,
				"has_reduction": true,
				"submitted_at": "2025-01-15T09:15:00+08:00",
				"updated_at": "2025-01-15T09:15:10+08:00"
			}
		],
		"page": 1,
		"page_size": 20,
		"total": 8
	}
}
```



**错误码说明**

| 错误码      | 说明                                           |
| :---------- | :--------------------------------------------- |
| E-PARAM-001 | 查询条件非法（日期格式错误、版本区间不合法等） |
| E-PERM-002  | 越权访问其他企业数据                           |

### 3.2 获取报送期详情（最新版）

- **请求方法**：GET
- **请求路径**：/api/reports/{period}
- **功能描述**：查看指定报送期的最新有效版本报表详情（只读）
- **请求头**：Authorization: Bearer {token}
- **路径参数**：同获取当期报表接口的period参数
- **响应参数（data字段）**：同获取当期报表接口的响应参数
- **成功响应示例**：同获取当期报表接口的成功响应示例
- **错误码说明**：同查询报表列表接口的错误码说明

### 3.3 获取指定版本详情

- **请求方法**：GET
- **请求路径**：/api/reports/{period}/versions/{version}
- **功能描述**：查看指定报送期、指定版本的报表详情，包含状态时间线与驳回意见
- **请求头**：Authorization: Bearer {token}

**路径参数**

| 参数名  | 类型   | 是否必填 | 说明                  |
| :------ | :----- | :------- | :-------------------- |
| period  | String | 是       | 报送期，格式为YYYY-MM |
| version | INT    | 是       | 报表版本号            |

**响应参数（data字段）**

| 参数名                | 类型     | 说明                         |
| :-------------------- | :------- | :--------------------------- |
| reporting_period      | String   | 报送期                       |
| status                | String   | 报表状态                     |
| version               | INT      | 版本号                       |
| initial_employees     | INT      | 建档期就业人数               |
| current_employees     | INT      | 调查期就业人数               |
| reduction_type_code   | INT      | 就业人数减少类型代码（可空） |
| primary_reason_code   | INT      | 主要原因代码（可空）         |
| primary_reason_desc   | TEXT     | 主要原因说明（可空）         |
| secondary_reason_code | INT      | 次要原因代码（可空）         |
| secondary_reason_desc | TEXT     | 次要原因说明（可空）         |
| tertiary_reason_code  | INT      | 第三原因代码（可空）         |
| tertiary_reason_desc  | TEXT     | 第三原因说明（可空）         |
| other_reason_desc     | TEXT     | 其他原因（可空）             |
| submitted_at          | DATETIME | 提交时间（可空）             |
| updated_at            | DATETIME | 最后更新时间                 |
| timeline              | Array    | 状态时间线                   |
| timeline.status       | String   | 节点状态                     |
| timeline.operator     | String   | 操作者（管理员姓名或系统）   |
| timeline.operate_time | DATETIME | 操作时间                     |
| timeline.opinion      | String   | 备注/驳回意见（可空）        |

**成功响应示例**



```
{
	"status": "success",
	"code": 200,
	"info": "指定版本报表详情获取成功",
	"data": {
		"reporting_period": "2025-01",
		"status": "市级驳回",
		"version": 1,
		"initial_employees": 120,
		"current_employees": 100,
		"reduction_type_code": 2,
		"primary_reason_code": 101,
		"primary_reason_desc": "市场需求持续萎缩，订单量下降30%",
		"secondary_reason_code": null,
		"secondary_reason_desc": null,
		"tertiary_reason_code": null,
		"tertiary_reason_desc": null,
		"other_reason_desc": null,
		"submitted_at": "2025-01-15T09:15:00+08:00",
		"updated_at": "2025-01-16T14:30:00+08:00",
		"timeline": [
			{
				"status": "待填报",
				"operator": "系统",
				"operate_time": "2025-01-01T00:00:00+08:00",
				"opinion": "系统自动生成报表"
			},
			{
				"status": "待市级审核",
				"operator": "张XX",
				"operate_time": "2025-01-15T09:15:00+08:00",
				"opinion": "企业提交报表"
			},
			{
				"status": "市级驳回",
				"operator": "李XX（市级管理员）",
				"operate_time": "2025-01-16T14:30:00+08:00",
				"opinion": "请补充次要原因说明"
			}
		]
	}
}
```



**错误响应示例**



```
{
	"status": "fail",
	"code": 404,
	"info": "指定报送期或版本的报表不存在",
	"data": null
}
```



**错误码说明**

| 错误码     | 说明                         |
| :--------- | :--------------------------- |
| E-REPT-005 | 指定报送期或版本的报表不存在 |
| E-PERM-002 | 越权访问其他企业的报表数据   |

### 3.4 导出报表（企业端禁用）

- **请求方法**：GET
- **请求路径**：/api/reports/export
- **功能描述**：企业端禁止导出报表，访问此接口返回403
- **请求头**：Authorization: Bearer {token}
- **请求参数（Query）**：无

**错误响应示例**



```
{
	"status": "fail",
	"code": 403,
	"info": "企业端禁止导出报表",
	"data": null
}
```



**错误码说明**

| 错误码    | 说明               |
| :-------- | :----------------- |
| E-EXP-001 | 企业端禁止导出报表 |

## 四、公共错误码说明

| 错误码 | 说明                     |
| :----- | :----------------------- |
| 401    | 用户未登录或登录令牌失效 |
| 403    | 无权限访问该接口         |
| 404    | 请求的资源不存在         |
| 400    | 请求参数错误或格式不合法 |
| 500    | 服务器内部错误           |

## 五、字典接口

### 5.1 获取地区字典

- **请求方法**：GET
- **请求路径**：/api/dicts/regions
- **功能描述**：获取云南省市级地区字典
- **请求头**：Authorization: Bearer {token}

**响应参数（data字段）**

json

```
{
	"status": "success",
	"code": 200,
	"info": "地区字典获取成功",
	"data": [
		{
			"code": 1,
			"name": "昆明市",
			"type": "地级市"
		},
		{
			"code": 16,
			"name": "西双版纳傣族自治州",
			"type": "自治州"
		}
	]
}
```



### 5.2 获取企业性质字典

- **请求方法**：GET
- **请求路径**：/api/dicts/company-natures
- **功能描述**：获取企业性质字典
- **请求头**：Authorization: Bearer {token}

**响应参数（data字段）**

json

```
{
	"status": "success",
	"code": 200,
	"info": "企业性质字典获取成功",
	"data": [
		{
			"code": 1,
			"name": "中央直属国有企业",
			"category": "国有企业"
		},
		{
			"code": 7,
			"name": "私营有限责任公司",
			"category": "私营企业"
		}
	]
}
```



### 5.3 获取行业字典

- **请求方法**：GET
- **请求路径**：/api/dicts/industries
- **功能描述**：获取企业所属行业字典
- **请求头**：Authorization: Bearer {token}

**响应参数（data字段）**

```
{
	"status": "success",
	"code": 200,
	"info": "行业字典获取成功",
	"data": [
		{
			"code": 1,
			"name": "农业",
			"category": "A. 农、林、牧、渔业"
		},
		{
			"code": 65,
			"name": "软件和信息技术服务业",
			"category": "I. 信息传输、软件和信息技术服务业"
		}
	]
}
```
