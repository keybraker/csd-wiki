select distinct fname, lname
from instructor i, teaches t1, teaches t2
where t1.iid=i.iid and t2.iid=i.iid and
	t1.cnumber!=t2.cnumber and 
	i.iid not in
		(select iid 
		from teaches
		where cnumber not in (t1.cnumber,t2.cnumber));
