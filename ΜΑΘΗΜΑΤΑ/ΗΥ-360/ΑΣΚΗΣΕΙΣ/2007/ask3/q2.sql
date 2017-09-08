(select cnumber
from instructor i, teaches t
where i.iid=t.iid and lname='Papadopoulos')
union
(select cnumber 
from student s, attends a
where s.sid=a.sid and lname='Papadopoulos');
