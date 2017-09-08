<?php

echo "These are our good clients";
echo " <br> <br> ";
require_once('includes/config.inc.php');
$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
mysql_select_db("hy360", $con);
$result = mysql_query("SELECT Username FROM traderaccount WHERE MoneyOwns = 0");
echo "<table border='1'>
<tr>
<th>Username</th>
</tr>";
while ($row = mysql_fetch_array($result))
{
	echo "<tr>";
	echo "<td>" . $row[0] . "</td>";
	echo "</tr>";
}
echo "</table>";


?>