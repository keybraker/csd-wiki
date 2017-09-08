<?php

require_once('config.inc.php');
require_once('functions.inc.php');

session_start();

if ($_SESSION['logged_in'] == true)
{
	redirect('../index.php');
}
else
{
	if((!isset($_POST['username'])) || (!isset($_POST['password'])) || 
	    (!ctype_alnum($_POST['username'])))
	{
		redirect('../login.php');
	}
	
	$mysqli = @new mysqli(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD,DB_DATABASE);
	
	if (mysqli_connect_errno())
	{
		printf("Unable to connect to database %s", mysqli_connect_error());
		exit();
	}
	
	$username = $mysqli->real_escape_string($_POST['username']);
	$password = $mysqli->real_escape_string($_POST['password']);
	$sql = "SELECT * FROM customer WHERE Username='$username' AND Password='" . md5($password) . "'";
	$result = $mysqli->query($sql);
	
	if(is_object($result) && $result->num_rows == 1)
	{
		$_SESSION['logged_in'] = true;
		$_SESSION['username'] = $username;
		if ($username == 'admin') redirect('../admin.php');
		$sql = "SELECT * FROM civilian WHERE Username='$username'";
		$result = $mysqli->query($sql);
		if(is_object($result) && $result->num_rows == 1)
		{
			$_SESSION['type'] = 'civilian';
			redirect('../index.php');
		}
		else
		{
			$sql = "SELECT * FROM trader WHERE Username='$username'";
			$result = $mysqli->query($sql);
			if(is_object($result) && $result->num_rows == 1)
			{
				$_SESSION['type'] = 'trader';
				redirect('../index.php');
			}
			else echo "fatal error!!!";
		}
	}
	else
	{
		redirect('../login.php');
	}
}

?>