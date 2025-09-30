<?php
require 'db_connect.php'; // Connection to MariaDB

$stmt = $pdo->query("SELECT * FROM S");
echo "<h1>Suppliers</h1><table border='1'><tr><th>ID</th><th>Name</th><th>Status</th><th>City</th></tr>";
while ($row = $stmt->fetch()) {
    echo "<tr><td>{$row['S']}</td><td>{$row['SNAME']}</td><td>{$row['STATUS']}</td><td>{$row['CITY']}</td></tr>";
}
echo "</table>";
?>
