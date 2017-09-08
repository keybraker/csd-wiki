<?php
require_once('config.inc.php');
require_once('functions.inc.php');

session_start();

	if ($_SESSION['logged_in'] == false) redirect('../index.php');
	$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
	mysql_select_db("hy360", $con);
	$username = $_SESSION['username'];
	$isbn = $_POST['risbn'];
	if ($_POST['rstock']=="") redirect('../trader.php');
	$howmany = $_POST['rstock'];
	$result = mysql_query(" SELECT MoneyAvailable FROM civilianaccount WHERE Username = '$username'");
	$row = mysql_fetch_array($result);
	$money_available = $row[0];
	$check_isbn = mysql_query(" SELECT ISBN FROM book WHERE ISBN = '$isbn'");
	$check =  mysql_query("
	
	SELECT grouped.sum FROM
	(
		SELECT joined.Username, SUM(joined.Amount) AS sum FROM 
		(
			SELECT Username, Cost, Amount, ISBN
			FROM transactionofcivilian
			NATURAL JOIN book
		) AS joined
		WHERE Username = '$username'  AND ISBN = $isbn
		GROUP BY joined.Username
	)AS grouped
	
	");
	$row = mysql_fetch_array($check);
	$num_bought = $row[0];
	if (mysql_num_rows($check_isbn)>0)
	{
		if ($num_bought >= $howmany)
		{
			$update = mysql_query(" UPDATE Book SET Stock = Stock + $howmany WHERE ISBN = $isbn");
			$paid = mysql_query("SELECT Cost FROM book WHERE ISBN=$isbn");
			$row=mysql_fetch_array($paid);
			$paid = $row[0] * $howmany;
			$money_available = $money_available + $paid;
			$update = mysql_query("UPDATE civilianaccount SET MoneyAvailable = '$money_available' WHERE username = '$username'");				
			$howmany = -1 * $howmany;
			$insert = mysql_query("INSERT transactionofcivilian(Username, ISBN, TransactionDate, Amount) VALUES('$username',$isbn,CURDATE(),$howmany)");
			redirect("../trader.php");
		}
		else
		{
			echo "You didnt buy all those to return them :O";
		}
	}
	else
	{
		echo "isbn not found";
	}
?>