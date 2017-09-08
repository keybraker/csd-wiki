<?php 
session_start(); 
require_once('functions.inc.php'); 
if (check_login_status() == false) 
{ 
    redirect('login.php'); 
} 
else 
{ 
    unset($_SESSION['logged_in']); 
	unset($_SESSION['username']); 
	session_destroy(); 
} 
?> 
<html> 
	<head> 
		<meta http-equiv="Content-type" content="text/html;charset=utf-8" /> 
		<title>Only Books</title> 
	</head> 
	<body> 
		<h1>Logged Out</h1> 
		<meta HTTP-EQUIV="REFRESH" content="5; ../index.php">
		<p>You have successfully logged out.You will now be redirected or click back to <a href="../login.php">login</a> screen.</p> 
	</body> 
</html> 
