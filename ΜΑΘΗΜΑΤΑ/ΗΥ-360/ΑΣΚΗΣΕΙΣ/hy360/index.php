<?php 
session_start();   
require_once('includes/functions.inc.php'); 
  
if (check_login_status() == false) 
{ 
              redirect('login.php'); 
}
if ($_SESSION['username'] == 'admin') redirect('admin.php');
if ($_SESSION['type'] == 'civilian') redirect ('civilian.php');
if ($_SESSION['type'] == 'trader') redirect ('trader.php');
echo "Welcome ".$_SESSION['username'];
 
?> 
<html> 
	<head> 
		<meta http-equiv="Content-type" content="text/html;charset=utf-8" /> 
		<title>Only Books</title> 
	</head> 
	<body> 
		<p>You are currently logged in. You may log out using the button below.</p> 
		<p><a href="includes/logout.inc.php">Log Out</a></p> 
	</body> 
</html> 
