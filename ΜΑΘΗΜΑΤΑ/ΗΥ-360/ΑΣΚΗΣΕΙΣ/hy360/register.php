<html>
<?php
session_start();
require_once('includes/functions.inc.php');
if (check_login_status() == true) 
{ 
              redirect('index.php'); 
}
?>
<head> 
  <meta http-equiv="Content-type" content="text/html;charset=utf-8" /> 
  <title>Only Books</title> 
  <link rel="stylesheet" type="text/css" href="css/register.css" /> 
  	<script type="text/javascript">
	function displayCredit()
	{
		document.getElementById("cardtext").innerHTML = "Credit Number/CSC:";
		document.forms["login-form"]["bank"].style.display = "none";
		document.forms["login-form"]["csc"].style.display = "inline";
		document.forms["login-form"]["credit"].style.display = "inline";
	}
	
	function displayBank()
	{
		document.getElementById("cardtext").innerHTML = "Bank Account:";
		document.forms["login-form"]["credit"].style.display = "none";
		document.forms["login-form"]["csc"].style.display = "none";
		document.forms["login-form"]["bank"].style.display = "inline";
	}
	function displayForm(option)
	{
		if (option=="retail")
		{
			displayCredit();
		}
		else
		{
			displayBank();
		}
	}
	</script>
</head> 
<body> 
  <form id="login-form" method="post" action="includes/register.inc.php"> 
    <fieldset> 
	  <h5> Register </h5>
      <p>Please enter your personal info.</p>
      <label for="username"> 
		Username:  <input type="text" name="username" id="username"/>  <br />
      </label> 
      <label for="password"> 
		Password:  <input type="password" name="password" id="password"/>  <br />
      </label> 
      <label for="email"> 
		Email: <input type="email" name="email" id="email"/>  <br />
      </label> 
      <label> 
		Full Name:  <input type="text" name="name" id="name"/> <br />
      </label> 
      <label for="phone"> 
		Phone Number:  <input type="phone" name="phone" id="phone"/>  <br />
      </label> 
	  <label for="address"> 
		Address:  <input type="address" name="address" id="address"/>  <br />
      </label>
	  <label  id="hidden">
		Type of customer: <br /> 
		<select name="customertype" onchange="displayForm(this.value)">
		  <option value="retail" id="retail">Retail</option>
		  <option value="reseller" id="retail">Reseller</option>
		</select>
	  </label>
	  <br /> <label id="cardtext">Credit Number/CSC:</label>
	  <label>
		<input type="bank" name="bank" id="bank"/> 
		<input size = "11" type="credit" name="credit" id="credit"/>
		<input size="1" maxlength="3" type="csc" name="csc" id="csc"/>  
	  </label>
	  <br /> 
	  <label for="submit"> 
        <input type="submit" name="submit" id="submit" value="Submit" /> 
      </label>
	  <label for "terms">
	  <small><br /><br />By clicking submit you agree to our <a href="terms.php">Terms of Service</a></small>
	  </label>
	  <label>
	  </label>
    </fieldset> 
  </form>
</body> 
<?php

if (isset($_SESSION['taken']))
{
	echo '<script> alert("Username taken")  </script>';
	unset($_SESSION['taken']);
	
}
?>
<html>