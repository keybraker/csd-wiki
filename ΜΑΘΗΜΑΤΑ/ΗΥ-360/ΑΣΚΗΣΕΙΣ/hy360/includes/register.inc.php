<?php
session_start();
require_once('config.inc.php');
require_once('functions.inc.php');
if (check_login_status() == true) 
{ 
              redirect('index.php'); 
} 
else
{
	$mysqli = @new mysqli(DB_HOSTNAME,DB_USERNAME,DB_PASSWORD,DB_DATABASE);
	
	if (mysqli_connect_errno())
	{
		printf("Unable to connect to database %s", mysqli_connect_error());
		exit();
	}
	
	$username = $mysqli->real_escape_string($_POST['username']);
	$password = $mysqli->real_escape_string($_POST['password']);
	$pass = md5($password);
	$email = $mysqli->real_escape_string($_POST['email']);
	$name = $mysqli->real_escape_string($_POST['name']);
	$address = $mysqli->real_escape_string($_POST['address']);
	$phone = $mysqli->real_escape_string($_POST['phone']);
	
	//echo $username . $password . $email . $name . $address . $phone;
	$check_user = "SELECT * FROM customer WHERE username='$username'";
	$registered = $mysqli->query($check_user);
	if (is_object($registered) && $registered->num_rows == 1)
	{
		$_SESSION['taken'] = true;
		redirect('../register.php');
	}
	else
	{
		$insert_user="INSERT INTO customer (Username, Password , Name, Email, Address, PhoneNumber) 
								   VALUES ('$username', '$pass', '$name','$email','$address','$phone' )";
		$result = $mysqli->query($insert_user);
		
		$customer_type = $_POST['customertype'];
		
		if ($customer_type == "retail") //idiwths
		{
			$number = $_POST['credit'];
			$csc = $_POST['csc'];
			$insert_user = "INSERT INTO civilian (Username,CreditCardNum,CreditCardCSC)
										  VALUES ('$username' , '$number' , '$csc' )";
			$mysqli->query($insert_user);
			
			$insert_account = "INSERT INTO civilianaccount (Username,MoneyAvailable)
													VALUES ('$username',0)";
			$insert_profile = "INSERT INTO civilianprofile (Username) VALUES ('$username')";
			$mysqli->query($insert_account);	
			$mysqli->query($insert_profile);
		}	
		else //emporos
		{
			$bank_number = $_POST['bank'];
			$insert_user = "INSERT INTO trader (Username,BankAccount,DiscountPercent)
										VALUES ('$username','$bank_number',0)";
			$mysqli->query($insert_user);
			
			$insert_account = "INSERT INTO traderaccount (Username,MoneyAvailable,MoneyOwns)
													VALUES ('$username',0,0)";
			$mysqli->query($insert_account);
		}
		
		if($result)
		{ 
			echo '<meta HTTP-EQUIV="REFRESH" content="5; ../index.php">'; 
			echo "<h2> $username </h2>" .'<p> you have successfully registered.
				  You will now be redirected or click back to 
				  <a href="../login.php">login</a> screen.</p>'; 
		}
		else
		{ 
			echo "error in registration".mysql_error();
		}	
	}
}
?>