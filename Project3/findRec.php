<?php
session_start();
$host = $_SESSION["host"];
$user = $_SESSION["user"];
$pass = $_SESSION["passw"];
$dbName = $user;

// connect
echo "Attempting to connect to DB server: $host ... <br>";
$conn = new mysqli($host, $user, $pass, $dbName);
if ($conn->connect_error) {
    die("Could not connect: " . $conn->connect_error);
} else {
    echo " connected!<br>";
}

// Create the procedure list all the recipes
$queryString = "CREATE PROCEDURE IF NOT EXISTS listRec(IN RecN VARCHAR(50)) " .
    "BEGIN " .
    "   SELECT Ingredient, Quantity FROM Recipes WHERE RecipeName = RecN; " .
    "END";
if (!$conn->query($queryString)) {
    die("Error creating procedure: " . $conn->error);
}

// Call the above procedure
$stmt = $conn->prepare("CALL listRec(?)");
// Bind values
$stmt->bind_param("s", $rnam);

$rnam = $_POST["rname"];

$stmt->execute();

$stmt->bind_result($ing, $qty);

echo "<table border=1>";
echo "<tr> <th>Ingredient</th> <th>QTY</th> </tr>";

while ($stmt->fetch()) {
    echo "<tr> <td>" . $ing . "</td>" .
        "<td>" . $qty . "</td></tr>";
}
echo "</table>";

echo "To return to the previous page <a href='listRec.html'>click here</a> <br>";
echo "To return to the main menu <a href='main_menu.html'>click here</a> <br>";
$conn->close();
?>