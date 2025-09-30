<?php
require 'db_connect.php';

$stmt = $pdo->query("SELECT * FROM P");
echo "<h1>Parts</h1><table border='1'><tr><th>ID</th><th>Name</th><th>Color</th><th>Weight</th></tr>";
while ($row = $stmt->fetch()) {
    echo "<tr><td>{$row['P']}</td><td>{$row['PNAME']}</td><td>{$row['COLOR']}</td><td>{$row['WEIGHT']}</td></tr>";
}
echo "</table>";
?>
