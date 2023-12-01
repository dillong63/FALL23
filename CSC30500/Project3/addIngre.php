<?php
session_start();
$host = $_SESSION["host"];
$user = $_SESSION["user"];
$pass = $_SESSION["passw"];
$dbName = $user;

//connect
echo "Attempting to connect to DB server: $host ... <br>";
$conn = new mysqli($host, $user, $pass, $dbName);
if ($conn->connect_error)
        die("Could not connect:".mysqli_connect_error());
else{
        echo " connected!<br>";
}
// Create the procedure for adding an ingredient if it does not exist
$queryString = " CREATE PROCEDURE IF NOT EXISTS addStoreIngredient(IN Ing varCHAR(50), IN qty INT) " .
    " BEGIN " .
       " INSERT INTO Inventory (Ingredient, Quantity) ".
       " VALUES (Ing, qty) ".
        " ON DUPLICATE KEY UPDATE Quantity = Quantity + qty; " .
    "END";

if (!$conn->query($queryString)) {
    die("Error creating procedure: " . $conn->error);
}
// Call the above procedure
$stmt = $conn->prepare("CALL addStoreIngredient(?, ?)");

// Bind values
$stmt->bind_param("si",$iname, $iqty);
$iname = $_POST["iname"];
$iqty = (int)$_POST["iq"];

$stmt->execute();

echo "Table Updated <br>";
echo "To return to the previous page <a href='addIng.html'>click here</a> <br>";
echo "To return to the main menu <a href='main_menu.html'>click here</a> <br>";
conn->close();
?>