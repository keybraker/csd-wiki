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
$delete = "DELETE FROM book WHERE ISBN='$isbn'";
$mysqli->query($delete);
redirect("../admin.php");

?>