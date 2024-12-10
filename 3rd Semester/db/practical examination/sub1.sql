USE Practical
GO

drop table sub1
go

CREATE TABLE sub1
(
    fk1 INT NOT NULL,
    fk2 INT NOT NULL,
    PRIMARY KEY (fk1, fk2),
    c1 VARCHAR(100),
    c2 VARCHAR(100),
    c3 int,
    c4 int,
    c5 VARCHAR(10)
)
go

insert into sub1 values (3, 2, 'samsung elecctronics', 'semiconductors', 120, 100, 'ss')
insert into sub1 values (1, 3, 'apple', 'computer hardware', 50, 50, 'cd')
insert into sub1 values (2, 1, 'microsoft', 'software', 80, 30, 'ef')

select c2, sum(c3) totalc3, avg(c3)
from sub1
where c3 > 50 or c4 < 50
group by c2
having sum(c3) > 80

select *
from
    (select fk1, fk2, c3
    from sub1
    where fkk1 < fk2) r1
    left JOIN
    (select fk1, fk2, c2, c5
    from sub1
    where c4 <= 50 and c5 like '%Q') r2 on r1.fk1 = r2.fk1 and r1.fk2 = r2.fk2

