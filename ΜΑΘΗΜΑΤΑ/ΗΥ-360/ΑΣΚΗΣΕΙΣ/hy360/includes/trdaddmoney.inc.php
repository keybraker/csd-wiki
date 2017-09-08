<?php
require_once('config.inc.php');
require_once('functions.inc.php');

session_start();

if ($_SESSION['logged_in'] == false)
	redirect('../index.php');

	$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
	mysql_select_db("hy360", $con);
	$username = $_SESSION['username'];
	$money = $_POST['money'];
	$check = mysql_query("SELECT MoneyOwns FROM traderaccount WHERE Username = '$username'");
	$row = mysql_fetch_array($check);
	$money_owns = $row[0];
	if ($money_owns == 0)
	{
		$update = "UPDATE traderaccount SET MoneyAvailable = MoneyAvailable + '$money' WHERE username = '$username'";
		mysql_query($update);
	}
	else
	{
		if ($money_owns >= $money)
		{
			$money_owns = $money_owns - $money;
			$update = "UPDATE traderaccount SET MoneyOwns = $money_owns WHERE username = '$username'";
			mysql_query($update);
		}
		else
		{
			$money = $money - $money_owns;
			$money_owns = 0;
			$update = "UPDATE traderaccount SET MoneyOwns = $money_owns WHERE username = '$username'";
			mysql_query($update);
			$update = "UPDATE traderaccount SET MoneyAvailable = MoneyAvailable + '$money' WHERE username = '$username'";
			mysql_query($update);
		}
	}
	redirect('../trader.php');
?>