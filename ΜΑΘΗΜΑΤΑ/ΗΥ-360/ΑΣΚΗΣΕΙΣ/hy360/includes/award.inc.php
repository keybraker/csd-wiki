<?php

require_once('config.inc.php');
require_once('functions.inc.php');
$con = mysql_connect(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD);
mysql_select_db("hy360", $con);
$result = mysql_query("

SELECT grouped.Username,grouped.sum FROM
(
SELECT joined.Username, SUM( joined.Cost * joined.Amount ) AS sum FROM (

SELECT Username, Cost, Amount, TransactionDate
FROM transactionoftrader
NATURAL JOIN book
) AS joined
WHERE (SELECT MONTH(TransactionDate)  ) = (SELECT MONTH (CURDATE() ) )
GROUP BY joined.Username
) AS grouped ORDER BY grouped.sum DESC


");
$row = mysql_fetch_array($result);
$topuser = $row[0];
$result = mysql_query(" UPDATE trader  SET DiscountPercent = 0 WHERE DiscountPercent = 5 ");
$result = mysql_query(" UPDATE trader  SET DiscountPercent = 5 WHERE Username = '$topuser' ");
$result = mysql_query(" UPDATE traderaccount SET MoneyOwns = MoneyOwns - MoneyOwns*0.05");
redirect('../admin.php');


?>