<?php
require_once('config.inc.php');
require_once('functions.inc.php');
$mysqli = @new mysqli(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD,DB_DATABASE);
if (mysqli_connect_errno())
{
	printf("Unable to connect to database %s", mysqli_connect_error());
	exit();
}
$isbn = $_POST['isbn'];
$title = $_POST['title'];
$author = $_POST['author'];
$cost = $_POST['cost'];
$date = $_POST['date'];
$type = $_POST['genre'];
$stock = $_POST['stock'];

$check_isbn = "SELECT * FROM book WHERE ISBN='$isbn'";
$registered = $mysqli->query($check_isbn);
if (is_object($registered) && $registered->num_rows == 1)
{
	$update = "UPDATE book SET Stock = Stock + '$stock' WHERE ISBN = '$isbn'";
	$mysqli->query($update);
}
else
{
	$insert = "INSERT INTO book (ISBN, Title, Writers, Cost, PublishDate, Type, Stock)
					   VALUES ('$isbn','$title','$author','$cost','$date','$type','$stock')";
	$mysqli->query($insert);
}

redirect("../admin.php");
?>