<html>
<head>
<link rel="stylesheet" type="text/css" href="css/civilian.css" /> 
</head>
<?php 
session_start();   
require_once('includes/functions.inc.php'); 
require_once('includes/config.inc.php');   
if (check_login_status() == false) 
{ 
              redirect('login.php'); 
}
if ($_SESSION['type'] != 'civilian') redirect('index.php');
?>
<fieldset id="f1">
<form action="includes/civdelacc.inc.php" method="post" align="right">
<input type="submit" name="submit" id="submit" value="Delete Account" /> 
<button type="button" align="left" onClick="window.location='includes/logout.inc.php'">Logout</button> 
</form>
<?php
echo "Welcome " . $_SESSION['username'];
$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
mysql_select_db("hy360", $con);
$username = $_SESSION['username'];
$result = mysql_query(" SELECT MoneyAvailable FROM civilianaccount WHERE Username = '$username'");
$row = mysql_fetch_array($result);
echo ".Your current amount is: ";
echo $row[0];
$result2 = mysql_query(" SELECT * FROM civilianfavourite WHERE Username = '$username'");
if (mysql_num_rows($result2))
{
	echo " Your current favorites are: ";
	while ($row = mysql_fetch_array($result2)) echo $row[1] . " ";
}
else echo " You have no favorites";
?>
<br /> <br /> 
<a href="goodclients.php">Good Clients</a>
<a href="badclients.php">Bad Clients</a> <br />  <br /> 
<fieldset>
<legend> Profile/Account </legend>
Our genre list: Mystery ,Horror, Fiction, Action, Thriller, Humor, Romance.
<form action="includes/add_favorite.inc.php" method="post">
<input type="text" name="favorite" id="favorite" size="10" /> 
<input type="submit" name="submit" id="submit" value="Add Favorite" /> 
</form>
<form action="includes/rmv_favorite.inc.php" method="post">
<input type="text" name="dfavorite" id="dfavorite" size="10" /> 
<input type="submit" name="submit" id="submit" value="Remove Favorite" /> 
</form>
<br /> 
<form action="includes/civaddmoney.inc.php" method="post">
Euro:<input type="text" name="money" id="money" size="10" /> 
<input type="submit" name="submit" id="submit" value="Add Money" /> 
</form>
<form action="includes/civbuybook.inc.php" method="post">
ISBN:<input type="text" name="isbn" id="isbn" size="10" /> 
How many:<input type="text" name="stock" id="stock" size="1" /> 
<input type="submit" name="submit" id="submit" value="Buy Books" /> 
</form>
<form action="includes/civretbook.inc.php" method="post">
ISBN:<input type="text" name="risbn" id="risbn" size="10" /> 
How many:<input type="text" name="rstock" id="rstock" size="1" /> 
<input type="submit" name="submit" id="submit" value="Return Books" /> 
</form>
<br />
</fieldset>
<fieldset>
<legend> Search Box </legend>
<form action="searches/civilian_transactions_date.php" method="post">
Get transactions by date, from:<input type="text" name="from" id="from" size="10" /> 
to:<input type="text" name="to" id="to" size="10" /> (Format of date is: YYYY-MM-DD)
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/civilian_transactions_isbn.php" method="post">
Get transactions by isbn <input type="text" name="sisbn" id="sisbn" size="10" /> 
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/civilian_transactions_cost.php" method="post">
Get transactions by cost,  bigger than:<input type="text" name="bigger" id="bigger" size="10" /> 
smaller than:<input type="text" name="smaller" id="smaller" size="10" /> 
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/civilian_transactions_genre.php" method="post">
Get transactions by genre <input type="text" name="genre" id="genre" size="10" /> 
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/civilian_transactions_author.php" method="post">
Get transactions by author <input type="text" name="author" id="author" size="10" /> 
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/civilian_transactions_num.php" method="post">
Get transactions by number purchased <input type="text" name="num" id="num" size="10" /> 
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/book_name.php" method="post">
Get book by name <input type="text" name="bname" id="bname" size="10" /> 
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/book_author.php" method="post">
Get book by author <input type="text" name="bauthor" id="bauthor" size="10" /> 
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/book_genre.php" method="post">
Get book by genre <input type="text" name="bgenre" id="bgenre" size="10" /> 
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/book_cost.php" method="post">
Get book by cost,  bigger than:<input type="text" name="bbigger" id="bbigger" size="10" /> 
smaller than:<input type="text" name="bsmaller" id="bsmaller" size="10" /> 
<input type="submit" name="submit" id="submit" value="Go" /> 
</form>
<form action="searches/book_fav.php" method="post">
Get all your favorites<input type="submit" name="submit" id="submit" value="Go">
</form>
</fieldset>
<fieldset>
<legend> Our Books </legend>
	<?php
	require_once('includes/config.inc.php');
	$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
	mysql_select_db("hy360", $con);
	$result = mysql_query("SELECT * FROM book");
	echo "<table border='1'>
	<tr>
	<th>Isbn</th>
	<th>Title</th>
	<th>Author</th>
	<th>Cost</th>
	<th>Publish Date</th>
	<th>Genre</th>
	<th>Stock</th>
	</tr>";
	while ($row = mysql_fetch_array($result))
	{
		echo "<tr>";
		echo "<td>" . $row[0] . "</td>";
		echo "<td>" . $row[1] . "</td>";
		echo "<td>" . $row[2] . "</td>";
		echo "<td>" . $row[3] . "</td>";
		echo "<td>" . $row[4] . "</td>";
		echo "<td>" . $row[5] . "</td>";
		echo "<td>" . $row[6] . "</td>";
		echo "</tr>";
	}
	echo "</table>";
	?>
</fieldset>
</fieldset>
</html>
<br />