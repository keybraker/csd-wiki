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
  <link rel="stylesheet" type="text/css" href="css/login.css" /> 
  <script src="includes/validator.js" type="text/javascript"></script>
</head> 
<body> 
  <form id="login-form" method="post" action="includes/login.inc.php" onsubmit="return validateForm();"> 
    <fieldset> 
      <p><strong>Please enter your username and password to access your account.</strong></p>
      <label for="username"> 
        <input type="text" name="username" id="username" />Username: 
      </label> 
      <label for="password"> 
        <input type="password" name="password" id="password" />Password: 
      </label> 
      <label for="submit"> 
        <input type="submit" name="submit" id="submit" value="Login" /> 
      </label>
	  <label for ="register">
	  New member? Register <a href="register.php">here</a>
	  </label>
    </fieldset> 
  </form>
</body> 
</html> 

