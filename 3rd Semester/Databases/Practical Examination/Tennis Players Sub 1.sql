CREATE DATABASE PracticalExam
go

drop table sub1
go

create table sub1
(
    cid int not null,
    pid int not null,
    primary key (cid, pid),
    cname varchar(50),
    pname varchar(50),
    startdate date,
    enddate date,
    fieldtype int,
    country varchar(100),
    city varchar(100)
)
go

insert into sub1 values (1, 1, 'Roland Garros', 'Simona Halep', '2020-06-22', '2020-06-30', 2, 'China', 'Beijing')
insert into sub1 values (1, 2, 'WTA', 'Rafael Nadal', '2020-09-30', '2020-10-11', 1, 'Slovenia', 'Ljubljana')
insert into sub1 values (1, 3, 'Australian Open', 'Serena Williams', '2020-09-01', '2020-09-16', 3, 'Italy', 'Florence')
insert into sub1 values (2, 2, 'US Open', 'Naomi Osaka', '2020-01-05', '2020-01-12', 2, 'New York', 'New York')
insert into sub1 values (2, 3, 'US Open', 'Asleigh Barty', '2020-06-06', '2020-06-30', 1, 'California', 'Los Angeles')
insert into sub1 values (2, 4, 'Wimbledon', 'Alexander Zverev', '2020-10-15', '2020-11-02', 4, 'France', 'Lion')
insert into sub1 values (3, 3, 'WTA', 'Serena Williams', '2020-02-02', '2020-02-14', 4, 'Great Britain', 'Cambridge')
insert into sub1 values (4, 5, 'Roland Garros', 'Alexander Zverev', '2020-05-01', '2020-05-16', 5, 'Japan', 'Osaka')
insert into sub1 values (4, 6, 'French Open', 'Sofia Kenin', '2020-09-09', '2020-09-19', 2, 'France', 'Marseille')
insert into sub1 values (5, 6, 'Australian Open', 'Maria Sharapova', '2020-04-04', '2020-04-22', 1, 'Australia', 'Melbourne')
insert into sub1 values (5, 7, 'French Open', 'Naomi Osaka', '2020-08-08', '2020-08-17', 2, 'France', 'Nice')
insert into sub1 values (6, 4, 'Wimbledon', 'Maria Sharapova', '2020-02-20', '2020-03-09', 4, 'Austria', 'Linz')
insert into sub1 values (6, 8, 'US Open', 'Steffi Graf', '2020-07-07', '2020-07-25', 2, 'Florida', 'Miami')
insert into sub1 values (6, 9, 'Roland Garros', 'Simona Halep', '2020-10-20', '2020-10-30', 1, 'France', 'Paris')

select cname, COUNT(fieldtype) countFieldType, sum(fieldtype) sumFieldType
from sub1
where month(startdate) > 5 or cname like '%e%'
group by cname
having count(city)< 3

select *FROM
(select cid, pid, pname, city from sub1
where pname like '%s%') p1
inner join (select cid, pid, enddate, country from sub1
where day(enddate) BETWEEN 1 and 15) p2
on p1.cid = p2.cid and p1.pid = p2.pid
where country like '%a%'
go

create or alter trigger tr
on sub1
for update AS
declare @no INT = 0
select @no = sum(d.fieldtype - i.fieldtype)
from deleted d inner join inserted i
on d.cid = i.cid and d.pid = i.pid
where d.fieldtype <= i.fieldtype
print @no
go

update sub1
set fieldtype = 5
where cname like '%n%'