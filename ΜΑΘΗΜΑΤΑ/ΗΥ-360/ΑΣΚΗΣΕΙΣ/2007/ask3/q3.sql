(select i.fname, i.lname, c.cname
from instructor i, courses c, teaches t
where i.iid=t.iid and c.cnumber=t.cnumber)
union
(select i.fname, i.lname, null
from instructor i
where i.iid not in
	(select distinct iid 
	from teaches));
