<?php
require_once('config.inc.php');
require_once('functions.inc.php');

session_start();

	if ($_SESSION['logged_in'] == false) redirect('../index.php');
	$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
	mysql_select_db("hy360", $con);
	$username = $_SESSION['username'];
	$isbn = $_POST['isbn'];
	if ($_POST['stock']=="") redirect('../trader.php');
	$howmany = $_POST['stock'];
	$result = mysql_query(" SELECT MoneyAvailable FROM traderaccount WHERE Username = '$username'");
	$row = mysql_fetch_array($result);
	$money_available = $row[0];
	$find_stock = mysql_query(" SELECT Stock FROM book WHERE ISBN = '$isbn'");
	if (mysql_num_rows($find_stock) >0)
	{
		$row2 = mysql_fetch_array($find_stock);
		$stock_available = $row2[0];
		if ($howmany <= $stock_available)
		{
			$find_cost = mysql_query(" SELECT Cost FROM book WHERE ISBN = '$isbn'");
			$row3 = mysql_fetch_array($find_cost);
			$cost = $row3[0];
				$check = mysql_query(" SELECT MoneyOwns FROM traderaccount WHERE Username = '$username'");
				$row = mysql_fetch_array($check);
				$money_owns = $row[0];
				//$money_owns = $money_owns + (($cost*$howmany)-$money_available);
				$money_owns = $money_owns + (($cost*$howmany));
				//$money_available = 0;
				$stock_available = $stock_available - $howmany;
				//$update = mysql_query("UPDATE traderaccount SET MoneyAvailable = '$money_available' WHERE username = '$username'");
				$update = mysql_query("UPDATE traderaccount SET MoneyOwns = '$money_owns' WHERE username = '$username'");
				$update = mysql_query("UPDATE book SET Stock = Stock - '$howmany' WHERE ISBN = '$isbn'");
				$insert = mysql_query ("INSERT transactionoftrader (Username,ISBN,TransactionDate,Amount) VALUES ('$username','$isbn',CURDATE(),'$howmany')");
				redirect("../trader.php");
			//}
		}
		else
		{
			echo "Not enough stock";
		}
	}
	else
	{
		echo "isbn not found";
	}
?>