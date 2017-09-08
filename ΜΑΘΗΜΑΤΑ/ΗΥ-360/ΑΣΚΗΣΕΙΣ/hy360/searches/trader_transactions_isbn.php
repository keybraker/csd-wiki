<?php
session_start();
echo "Result:";
echo " <br> <br> ";
require_once('../includes/config.inc.php');
$username = $_SESSION['username'];
$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
mysql_select_db("hy360", $con);
$isbn = $_POST['sisbn'];
$result = mysql_query("

SELECT *
    FROM (
    SELECT Username, Name, ISBN, Title, Type, Writers, Cost, Amount, TransactionDate, Cost*Amount
    FROM transactionoftrader
    NATURAL JOIN book
    NATURAL JOIN customer
    ) AS joined
WHERE joined.Username = '$username'  AND ISBN = $isbn


");
echo "<table border='1'>
<tr>
<th>Username</th>
<th>Name</th>
<th>ISBN</th>
<th>Book</th>
<th>Genre</th>
<th>Author</th>
<th>Cost</th>
<th>Amount</th>
<th>Date</th>
<th>Final Cost</th>
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
	echo "<td>" . $row[7] . "</td>";
	echo "<td>" . $row[8] . "</td>";
	echo "<td>" . $row[9] . "</td>";
	echo "</tr>";
}
echo "</table>";


?>