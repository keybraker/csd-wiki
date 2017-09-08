<?php
require_once('config.inc.php');
require_once('functions.inc.php');
session_start();
$username = $_SESSION['username'];
$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
mysql_select_db("hy360", $con);
$check = mysql_query(" SELECT MoneyOwns FROM traderaccount WHERE Username = '$username'");
$row = mysql_fetch_array($check);
$money_owns = $row[0];
if ($money_owns ==0)
{
	$delete = " DELETE FROM traderaccount WHERE Username = '$username'";
	$mysqli->query($delete);
	$delete = " DELETE FROM trader WHERE Username = '$username'";
	$mysqli->query($delete);
	$delete = " DELETE FROM customer WHERE Username = '$username'";
	$mysqli->query($delete);
	unset($_SESSION['logged_in']); 
	unset($_SESSION['username']); 
	unset($_SESSION['type']);
}
else
{
	"You cant delete your account while you owe us money...WTF is wrong with you?";
}
?>