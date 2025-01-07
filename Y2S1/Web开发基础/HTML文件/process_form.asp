<%
Dim username
Dim score

' 获取表单数据
username = Request.Form("username")
score = Request.Form("score")


' 连接数据库
Dim conn
Set conn = Server.CreateObject("ADODB.Connection")
conn.Open "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\inetpub\wwwroot\MyWeb\score.mdb"

' 插入数据
Dim insertSQL
insertSQL = "INSERT INTO score (s_name, s_score) VALUES ('" & username & "', " & score & ")"
conn.Execute insertSQL

' 关闭数据库连接
conn.Close
Set conn = Nothing

%>
