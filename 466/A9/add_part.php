<?php
require 'db_connect.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $id = $_POST['id'];
    $name = $_POST['name'];
    $color = $_POST['color'];
    $weight = $_POST['weight'];

    $stmt = $pdo->prepare("INSERT INTO P (P, PNAME, COLOR, WEIGHT) VALUES (?, ?, ?, ?)");
    $stmt->execute([$id, $name, $color, $weight]);

    echo "<p>Part $id added successfully!</p>";
}
?>

<form method="POST">
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
