<?php
// Database connection details
$dsn = 'mysql:host=courses;dbname=z1930118';
$username = 'z1930118';
$password = '2003Jul17';

try {
    // Create a PDO instance
    $pdo = new PDO($dsn, $username, $password);

    // Set error mode to exception for better debugging
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    // Optional: set fetch mode to associative array
    $pdo->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
} catch (PDOException $e) {
    // Handle connection errors
    die("Database connection failed: " . $e->getMessage());
}
?>
