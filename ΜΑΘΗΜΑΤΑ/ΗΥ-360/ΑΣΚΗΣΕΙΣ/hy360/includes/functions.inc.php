<?php

/**
*
* Important Application files
* Project hy360
* 
* @file /include/functions.inc.php
*
*/
 
/** Redirects to specified page */
function redirect($page)
{
	header('Location: ' . $page);
	exit();
}

/** Check login status */
function check_login_status()
{
	if(isset($_SESSION['logged_in']))
	{
		return $_SESSION['logged_in'];
	}
	return false;
}	

?>