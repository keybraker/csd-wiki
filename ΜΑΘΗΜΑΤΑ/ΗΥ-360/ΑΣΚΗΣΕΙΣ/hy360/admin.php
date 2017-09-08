<html>
<?php
session_start();
require_once('includes/functions.inc.php');
if (check_login_status() == true) 
{ 
	if ($_SESSION['username'] != 'admin') redirect('index');
}
else
{
	redirect('login.php');
}
?>
<head>
<link rel="stylesheet" type="text/css" href="css/admin.css" /> 
</head>
<body>
<fieldset>
	<legend> Administrator's Panel </legend>
	<br /> <br /> <br />
	<form action="includes/addbook.inc.php" method="post">
	<a href="goodclients.php">Good Clients</a>
	<a href="badclients.php">Bad Clients</a> <br />
	ISBN: <input type="text" name="isbn" id="isbn" size="6" />
	Title:<input type="text" name="title" id="title" size="6" />
	Author:<input type="text" name="author" id="author" size="6" />
	Cost:<input type="text" name="cost" id="cost" size="1" />
	Publish Date:<input type="text" name="date" id="date" size="4" />
	Genre:<input type="text" name="genre" id="genre" size="5" />
	Stock:<input type="text" name="stock" id="stock" size="2" /> <br />
	<input type="submit" name="submit" id="submit" value="Add Book" /> 
	</form>
	<form action="includes/rmvbook.inc.php" method="post">
	ISBN:<input type="text" name="isbn" id="isbn" size="10" /> <br />
	<input type="submit" name="submit" id="submit" value="Remove Book" /> 
	</form>
	<button type="button" onClick="window.location='includes/award.inc.php'">Award best Trader</button> <br />  <br />
	<button type="button" onClick="window.location='includes/logout.inc.php'">Logout</button>
	<br /> <br /> 
	<h2><u>List of Books</u></h2>
	<br /> <br />
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
</body>
</html>