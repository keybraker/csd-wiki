select iid
from instructor
where salary in
	(select max(salary)
	from instructor
	where salary < (select max(salary) from instructor));
