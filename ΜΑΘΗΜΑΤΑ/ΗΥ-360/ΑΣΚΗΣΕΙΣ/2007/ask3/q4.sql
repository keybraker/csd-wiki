select distinct fname, lname
from student
where sid not in
	(select sid 
	from attends
	where cnumber in (555,777));
