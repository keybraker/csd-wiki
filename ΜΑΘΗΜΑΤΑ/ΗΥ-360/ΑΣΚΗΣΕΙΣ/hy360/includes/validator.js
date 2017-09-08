function validateForm()
{
	var y=document.forms["login-form"]["username"].value;
	if (y==null || y=="")
	{
		  alert("Username name must be filled out");
		  return false;
	}
	var x=document.forms["login-form"]["password"].value;
	if (x==null || x=="")
	{
		  alert("Password name must be filled out");
		  return false;
	}
}