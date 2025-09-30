<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Parts and Suppliers</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin-bottom: 20px;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 8px;
        }
        th {
            background-color: #f4f4f4;
        }
        form {
            margin-bottom: 20px;
        }
    </style>
</head>
<body>
    <?php
    $dsn = 'mysql:host=localhost;dbname=z1930118';
    $username = 'your_username';
    $password = 'your_password';
    try {
        $pdo = new PDO($dsn, $username, $password);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    } catch (PDOException $e) {
        die("Connection failed: " . $e->getMessage());
    }

    // Show all suppliers
    echo "<h2>All Suppliers</h2>";
    $stmt = $pdo->query("SELECT * FROM S");
    echo "<table><tr><th>ID</th><th>Name</th><th>City</th></tr>";
    while ($row = $stmt->fetch()) {
        echo "<tr><td>{$row['supplier_id']}</td><td>{$row['name']}</td><td>{$row['city']}</td></tr>";
    }
    echo "</table>";

    // Show all parts
    echo "<h2>All Parts</h2>";
    $stmt = $pdo->query("SELECT * FROM P");
    echo "<table><tr><th>ID</th><th>Name</th><th>Color</th></tr>";
    while ($row = $stmt->fetch()) {
        echo "<tr><td>{$row['part_id']}</td><td>{$row['name']}</td><td>{$row['color']}</td></tr>";
    }
    echo "</table>";

    // Form to find suppliers of a part
    echo "<h2>Find Suppliers of a Part</h2>";
    echo '<form method="POST">
            <label for="part">Part:</label>
            <select name="part" id="part">';
    $stmt = $pdo->query("SELECT * FROM P");
    while ($row = $stmt->fetch()) {
        echo "<option value='{$row['part_id']}'>{$row['name']}</option>";
    }
    echo '</select>
          <button type="submit" name="find_suppliers">Find Suppliers</button>
          </form>';

    if (isset($_POST['find_suppliers'])) {
        $part_id = $_POST['part'];
        $stmt = $pdo->prepare("SELECT S.name, S.city, SP.quantity FROM S JOIN SP ON S.supplier_id = SP.supplier_id WHERE SP.part_id = ?");
        $stmt->execute([$part_id]);
        echo "<table><tr><th>Supplier</th><th>City</th><th>Quantity</th></tr>";
        while ($row = $stmt->fetch()) {
            echo "<tr><td>{$row['name']}</td><td>{$row['city']}</td><td>{$row['quantity']}</td></tr>";
        }
        echo "</table>";
    }

    // Additional forms for other functionalities (buy parts, add new part, etc.) follow a similar pattern...
    ?>
</body>
</html>
