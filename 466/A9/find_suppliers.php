<?php
require 'db_connect.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $part_id = $_POST['part_id'];
    $stmt = $pdo->prepare("SELECT S.S, S.SNAME, SP.QTY FROM S JOIN SP ON S.S = SP.S WHERE SP.P = ?");
    $stmt->execute([$part_id]);

    echo "<h1>Suppliers for Part $part_id</h1><table border='1'><tr><th>ID</th><th>Name</th><th>Quantity</th></tr>";
    while ($row = $stmt->fetch()) {
        echo "<tr><td>{$row['S']}</td><td>{$row['SNAME']}</td><td>{$row['QTY']}</td></tr>";
    }
    echo "</table>";
}
?>

<form method="POST">
    <label for="part_id">Part ID:</label>
    <input type="text" name="part_id" required>
    <button type="submit">Find Suppliers</button>
</form>
