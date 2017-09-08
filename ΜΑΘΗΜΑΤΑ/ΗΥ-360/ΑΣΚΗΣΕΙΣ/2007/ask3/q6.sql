select distinct sid
from attends
where not exists
	(select *
	from department
	where dname='Biologia' and not exists
		(select *
		from courses
		where courses.cnumber=attends.cnumber and
		      courses.dnumber=department.dnumber));
