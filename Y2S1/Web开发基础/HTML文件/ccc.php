<!DOCTYPE html>
<html>
<head>
    <title>显示数据库数据</title>
</head>
<body>
asd
<?php
try {
    // 连接到MDB数据库
    $db = new PDO("odbc:Driver={Microsoft Access Driver (*.mdb)};Dbq=C:\Users\xChangx\OneDrive\Desktop\Chang\大学二年级第一学期\Web开发基础\HTML文件\数据库\SiteWeaver.mdb");
    
    // 设置错误模式为异常
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    
    // 执行查询
    $query = "SELECT * FROM 表1";
    $stmt = $db->query($query);
    
    // 获取查询结果
    $data = $stmt->fetchAll(PDO::FETCH_ASSOC);
    
    // 关闭数据库连接
    $db = null;
    
    // 显示数据
    echo "<table>";
    echo "<tr><th>ID</th><th>Name</th><th>Age</th></tr>";
    foreach ($data as $row) {
        echo "<tr>";
        echo "<td>" . $row['ID'] . "</td>";
        echo "<td>" . $row['Name'] . "</td>";
        echo "<td>" . $row['Age'] . "</td>";
        echo "</tr>";
    }
    echo "</table>";
} catch(PDOException $e) {
    echo "数据库连接失败：" . $e->getMessage();
}
?>

</body>
</html>
