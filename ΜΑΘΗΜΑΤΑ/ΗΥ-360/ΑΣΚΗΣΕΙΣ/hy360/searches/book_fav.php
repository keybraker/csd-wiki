<?php
session_start();
require_once('../includes/config.inc.php');
$username = $_SESSION['username'];
$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
mysql_select_db("hy360", $con);
$result = mysql_query("

SELECT * FROM
(
SELECT * FROM `civilianfavourite` NATURAL JOIN book  WHERE Username='$username'
) AS first
WHERE first.Type=first.Section

");
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
	echo "<td>" . $row[2] . "</td>";
	echo "<td>" . $row[3] . "</td>";
	echo "<td>" . $row[4] . "</td>";
	echo "<td>" . $row[5] . "</td>";
	echo "<td>" . $row[6] . "</td>";
	echo "<td>" . $row[7] . "</td>";
	echo "<td>" . $row[8] . "</td>";
	echo "</tr>";
}
echo "</table>";
?>