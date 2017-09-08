<?php

session_start();
require_once('../includes/config.inc.php');
require_once('functions.inc.php');
$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
mysql_select_db("hy360", $con);
$username = $_SESSION['username'];
$section = $_POST['favorite'];
$result = mysql_query ( "INSERT INTO civilianfavourite (Username, Section) VALUES ('$username','$section')");

redirect('../civilian.php');


?>