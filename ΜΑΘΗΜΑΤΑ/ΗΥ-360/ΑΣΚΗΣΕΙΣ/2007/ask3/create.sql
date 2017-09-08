create table department (
dnumber integer,
dname varchar(20),
chairiid integer,
primary key (dnumber));

create table courses (
cnumber integer,
cname varchar(20),
credits integer,
dnumber integer,
primary key (cnumber));

create table instructor (
iid integer,
fname varchar(20),
lname varchar(20),
sex varchar(10),
bdate date,
dnumber integer,
salary integer,
primary key (iid));

create table teaches (
iid integer,
cnumber integer,
primary key (iid,cnumber));

create table student (
sid integer,
fname varchar(20),
lname varchar(20),
bdate date,
addr varchar(20),
sex varchar(10),
semester integer,
dnumber integer,
primary key (sid));

create table attends (
sid integer,
cnumber integer,
primary key (sid,cnumber));

