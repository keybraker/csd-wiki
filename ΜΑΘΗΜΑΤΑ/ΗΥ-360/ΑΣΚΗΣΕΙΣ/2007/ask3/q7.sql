select distinct fname, lname
from instructor i, department d, teaches t1, teaches t2
where d.chairiid=i.iid and
	t1.iid=i.iid and t2.iid=i.iid and t1.cnumber!=t2.cnumber;
