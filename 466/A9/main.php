<?php
require 'db_connect.php';

function showSuppliers($pdo) {
    $stmt = $pdo->query("SELECT * FROM S");
    echo "<table><tr><th>ID</th><th>Name</th><th>Status</th><th>City</th></tr>";
    while ($row = $stmt->fetch()) {
        echo "<tr><td>{$row['S']}</td><td>{$row['SNAME']}</td><td>{$row['STATUS']}</td><td>{$row['CITY']}</td></tr>";
    }
    echo "</table>";
}

function showParts($pdo) {
    $stmt = $pdo->query("SELECT * FROM P");
    echo "<table><tr><th>ID</th><th>Name</th><th>Color</th><th>Weight</th></tr>";
    while ($row = $stmt->fetch()) {
        echo "<tr><td>{$row['P']}</td><td>{$row['PNAME']}</td><td>{$row['COLOR']}</td><td>{$row['WEIGHT']}</td></tr>";
    }
    echo "</table>";
}

function findSuppliersForPart($pdo, $part_id) {
    $stmt = $pdo->prepare("SELECT S.S, S.SNAME, SP.QTY FROM S JOIN SP ON S.S = SP.S WHERE SP.P = ?");
    $stmt->execute([$part_id]);
    echo "<table><tr><th>ID</th><th>Name</th><th>Quantity</th></tr>";
    while ($row = $stmt->fetch()) {
        echo "<tr><td>{$row['S']}</td><td>{$row['SNAME']}</td><td>{$row['QTY']}</td></tr>";
    }
    echo "</table>";
}

function addPart($pdo, $id, $name, $color, $weight) {
    $stmt = $pdo->prepare("INSERT INTO P (P, PNAME, COLOR, WEIGHT) VALUES (?, ?, ?, ?)");
    $stmt->execute([$id, $name, $color, $weight]);
    echo "<p style='color:green; text-align:center;'>Part $id added successfully!</p>";
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $action = $_POST['action'];
    switch ($action) {
        case 'show_suppliers': showSuppliers($pdo); break;
        case 'show_parts': showParts($pdo); break;
        case 'find_suppliers': findSuppliersForPart($pdo, $_POST['part_id']); break;
        case 'add_part': addPart($pdo, $_POST['id'], $_POST['name'], $_POST['color'], $_POST['weight']); break;
        default: echo "<p style='color:red; text-align:center;'>Invalid action!</p>";
    }
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Parts & Suppliers Management</title>
    <link rel="stylesheet" type="text/css" href="parts_style.css">
</head>
<body>
    <h1>Parts & Suppliers Management</h1>
    <div class="container">
        <form method="POST">
            <input type="hidden" name="action" value="show_suppliers">
            <button type="submit">Show Suppliers</button>
        </form>

        <form method="POST">
            <input type="hidden" name="action" value="show_parts">
            <button type="submit">Show Parts</button>
        </form>

        <form method="POST">
            <input type="hidden" name="action" value="find_suppliers">
            <label for="part_id">Part ID:</label>
            <input type="text" name="part_id" required>
            <button type="submit">Find Suppliers</button>
        </form>

        <form method="POST">
            <input type="hidden" name="action" value="add_part">
            <label for="id">Part ID:</label>
            <input type="text" name="id" required>
            <label for="name">Part Name:</label>
            <input type="text" name="name" required>
            <label for="color">Color:</label>
            <input type="text" name="color" required>
            <label for="weight">Weight:</label>
            <input type="number" name="weight" required>
            <button type="submit">Add Part</button>
        </form>
    </div>
</body>
</html>
