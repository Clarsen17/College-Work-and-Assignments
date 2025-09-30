<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CSCI 466 Assignment 8 - Collen Larsen, z1930118</title>
</head>
<body>
    <h1>CSCI 466 Assignment 8</h1>
    <?php
    function generateDropdown($name) {
        echo "<select name='$name'>";
        for ($i = 0; $i <= 9; $i++) {
            echo "<option value='$i'>$i</option>";
        }
        echo "</select>";
    }

    if ($_SERVER["REQUEST_METHOD"] === "POST") {
        $word = $_POST['word'] ?? null;
        $count = $_POST['count'] ?? null;
        $listtype = $_POST['listtype'] ?? null;
        $numstart = $_POST['numstart'] ?? null;
        $numstep = $_POST['numstep'] ?? null;
        $numnums = $_POST['numnums'] ?? null;

        echo "<hr>";

        // Validate and display list
        if (preg_match('/^\w+$/', $word) && ctype_digit($count) && ($listtype === "ordered" || $listtype === "unordered")) {
            $count = (int)$count;
            echo $listtype === "ordered" ? "<ol>" : "<ul>";
            for ($i = 0; $i < $count; $i++) {
                echo "<li>$word</li>";
            }
            echo $listtype === "ordered" ? "</ol>" : "</ul>";
        } else {
            echo "<p>List display parameters not received.</p>";
        }

        // Validate and display multiplication table
        if (ctype_digit($numstart) && ctype_digit($numstep) && ctype_digit($numnums)) {
            $numstart = (int)$numstart;
            $numstep = (int)$numstep;
            $numnums = (int)$numnums;

            echo "<table border='1'>";
            echo "<tr><th></th>";
            for ($col = 0; $col < $numnums; $col++) {
                $header = $numstart + $col * $numstep;
                echo "<th>$header</th>";
            }
            echo "</tr>";

            for ($row = 0; $row < $numnums; $row++) {
                $rowHeader = $numstart + $row * $numstep;
                echo "<tr><th>$rowHeader</th>";
                for ($col = 0; $col < $numnums; $col++) {
                    $colHeader = $numstart + $col * $numstep;
                    echo "<td>" . ($rowHeader * $colHeader) . "</td>";
                }
                echo "</tr>";
            }
            echo "</table>";
        } else {
            echo "<p>Multiplication parameters not received.</p>";
        }
    }
    ?>

    <hr>
    <form method="POST" action="">
        <label>Word: <input type="text" name="word"></label><br>
        <label>Count: <input type="text" name="count"></label><br>
        <label>List Type:</label>
        <label><input type="radio" name="listtype" value="ordered"> Ordered</label>
        <label><input type="radio" name="listtype" value="unordered"> Unordered</label><br>
        <label>Start Number:</label>
        <?php generateDropdown("numstart"); ?><br>
        <label>Step:</label>
        <?php generateDropdown("numstep"); ?><br>
        <label>Number of Rows/Columns:</label>
        <?php generateDropdown("numnums"); ?><br>
        <button type="submit">LET’S GOOOO</button>
    </form>
</body>
</html>