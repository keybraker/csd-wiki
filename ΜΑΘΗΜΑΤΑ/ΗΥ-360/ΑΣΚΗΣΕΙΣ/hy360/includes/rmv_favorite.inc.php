<?php

session_start();
require_once('../includes/config.inc.php');
require_once('functions.inc.php');
$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
mysql_select_db("hy360", $con);
$username = $_SESSION['username'];
$section = $_POST['dfavorite'];
$result = mysql_query ( "DELETE FROM civilianfavourite WHERE Section='$section' AND Username='$username'");

redirect('../civilian.php');


?>