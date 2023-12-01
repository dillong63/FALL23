<?php
//Dillon Geary
session_start();
$host = $_SESSION["host"];
$user = $_SESSION["user"];
$pass = $_SESSION["passw"];
$dbName = $user;

// connect
echo "Attempting to connect to DB server: $host ... <br>";
$conn = new mysqli($host, $user, $pass, $dbName);
if ($conn->connect_error)
        die("Could not connect:".mysqli_connect_error());
else{
        echo " connected!<br>";
}
// Create the procedure for looking if there are enought ingre
$queryString = "CREATE PROCEDURE IF NOT EXISTS lookRec(IN RecN VARCHAR(50)) " .
    "BEGIN " .
       "SELECT * FROM Recipes, Inventory WHERE RecipeName = RecN AND Inventory.Quantity<Recipes.Quantity AND Inventory.Ingredient=Recipes.Ingredient; " .
    "END";

if (!$conn->query($queryString)) {
    die("Error creating procedure: " . $conn->error);
}
//build procedure for changing inventory
$queryString = "CREATE PROCEDURE IF NOT EXISTS buyRec(IN RecN VARCHAR(50)) " .
    "BEGIN " .
       " UPDATE Inventory, Recipes " .
       " SET Inventory.Quantity = Inventory.Quantity -Recipes.Quantity " .
       " WHERE Recipes.RecipeName = RecN AND Inventory.Ingredient = Recipes.Ingredient; " .
    "END";


if (!$conn->query($queryString)) {
    die("Error creating procedure: " . $conn->error);
}
// Call the above procedure
$stmt = $conn->prepare("CALL lookRec(?)");

// Bind values
$stmt->bind_param("s", $rname);

$rname = $_POST["rname"];

$stmt->execute();
if (!$stmt->fetch()) {
    $stmt->close();
    // If there are enough ingredients, execute the second procedure
    $stmt = $conn->prepare("CALL buyRec(?)");
    $stmt->bind_param("s", $recname);
    $recname = $_POST["rname"];
    // Use the same parameter value
    $stmt->execute();
    $stmt->close();
    echo "Table Updated <br>";
} else {
    echo "Not enough ingredients.";
}

echo "To return to the previous page <a href='buyRec.html'>click here</a> <br>";
echo "To return to the main menu <a href='main_menu.html'>click here</a> <br>";
$conn->close();
?>