<?php
require_once('config.inc.php');
require_once('functions.inc.php');

session_start();

if ($_SESSION['logged_in'] == false)
	redirect('../index.php');

	$mysqli = @new mysqli(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD,DB_DATABASE);
	if (mysqli_connect_errno())
	{
		printf("Unable to connect to database %s", mysqli_connect_error());
		exit();
	}
	$username = $_SESSION['username'];
	$money = $_POST['money'];
	$update = "UPDATE civilianaccount SET MoneyAvailable = MoneyAvailable + '$money' WHERE username = '$username'";
	$mysqli->query($update);
	redirect('../civilian.php');
?>