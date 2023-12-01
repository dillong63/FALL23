<?php
/*Dillon Geary 11/30 */
//start the session
session_start();

//store login vars in session var
$_SESSION["host"] = $_POST["host"];
$_SESSION["user"] = $_POST["user"];
$_SESSION["passw"] = $_POST["password"];

$host = $_SESSION["host"];
$user = $_SESSION["user"];
$pass = $_SESSION["passw"];
$dbName = $user;

//connect to the database
echo "Attempting to connect to DB server: $host ...";
$_SESSION["conn"] = new mysqli($host, $user, $pass, $dbName);
$conn = $_SESSION["conn"];
if ($conn->connect_error)
        die("Could not connect:".mysqli_connect_error());
else{
        echo " connected!<br>";
        echo "<a href='main_menu.html'>Click to continue</a>";}

//create recipe table
$queryString = "create table if not exists Recipes".
        " (RecipeName varchar(50), Ingredient varchar(50), Quantity integer, PRIMARY KEY(RecipeName, Ingredient))";
if (! $conn->query($queryString))
    die("Error creating table: " . $conn->error() );
//create inventory table
$queryString = "create table if not exists Inventory".
    " (Ingredient varchar(50), Quantity integer,Primary key(Ingredient))";
if (! $conn->query($queryString))
    die("Error creating table: " . $conn->error() );
conn->close();
?>