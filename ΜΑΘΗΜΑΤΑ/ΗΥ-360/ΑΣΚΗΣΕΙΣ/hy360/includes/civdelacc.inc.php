<?php
require_once('config.inc.php');
require_once('functions.inc.php');
session_start();
$mysqli = @new mysqli(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD,DB_DATABASE);
if (mysqli_connect_errno())
{
	printf("Unable to connect to database %s", mysqli_connect_error());
	exit();
}
$username = $_SESSION['username'];
$delete = " DELETE FROM civilianaccount WHERE Username = '$username'";
$mysqli->query($delete);
$delete = " DELETE FROM civilianprofile WHERE Username = '$username'";
$mysqli->query($delete);
$delete = " DELETE FROM civilian WHERE Username = '$username'";
$mysqli->query($delete);
$delete = " DELETE FROM customer WHERE Username = '$username'";
$mysqli->query($delete);
unset($_SESSION['logged_in']); 
unset($_SESSION['username']); 
unset($_SESSION['type']);
echo "Your account has been deleted, GTFO";
?>