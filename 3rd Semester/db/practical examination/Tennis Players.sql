create database sub2
GO

use sub2
GO

drop table Registration
drop table Player
drop table Championship
drop table Locations
drop table ChampionshipType
GO

create table ChampionshipType(
    id int not null primary key,
    name varchar(50),
    description varchar(100)
)
GO

create table Locations(
    id int not null,
    primary key (id),
    country varchar(50),
    city varchar(50)
)
go

create table Championship(
    id int not null primary key,
    name varchar(50) unique not null,
    description varchar(100) CONSTRAINT chk_description CHECK (description <> ''),
    type int foreign key references ChampionshipType(id),
    location int foreign key references Locations(id),
)
go

create table Player(
    pid int not null primary key,
    name varchar(50),
    surname varchar(50),
    gender varchar(10),
    dob date
)
go

create table Registration(
    pid int not null,
    cid int not null,
    primary key (pid, cid),
    foreign key (pid) references Player(pid),
    foreign key (cid) references Championship(id),
    winprize int,
    CONSTRAINT chk_winprize CHECK (winprize >= 0)
)
go

-- insert data

insert into ChampionshipType (id, name, description)
values
    (1, 'Grand Slam', 'Most important tennis tournaments'),
    (2, 'WTA 500', 'More like a warm-up for Grand Slams'),
    (3, 'WTA 1000', 'Second Most important tennis tournaments');


insert into Locations (id, country, city)
values 
    (1, 'United States', 'New York'),
    (2, 'England', 'London'),
    (3, 'Spain', 'Barcelona');

insert into Championship (id, name, description, type, location)
values 
    (101, 'US Open', 'One of the 4 grand slams', 1, 1),
    (102, 'Indian Wells', 'Considere the fifth grand slam', 3, 1),
    (103, 'Romania Bucharest Open', 'First Championship held in Romania', 3, 3);

insert into Player (pid, name, surname, gender, dob)
values 
    (1001, 'Rafael', 'Nadal', 'Male', '1990-05-15'),
    (1002, 'Simona', 'Halep', 'Female', '1988-09-20'),
    (1003, 'Serena', 'Williams', 'Male', '1995-02-10');

insert into Registration (pid, cid, winprize)
values 
    (1001, 101, 5000),
    (1002, 102, 0),
    (1003, 103, 2500);
go

-- implement a stored procedure that receives a championship, a player and a prize, and adds the player to the championship
-- if the player is already registered, the procedure should update the prize

drop procedure addPlayerToChampionship
go

create procedure addPlayerToChampionship
    @championship int,
    @player int,
    @prize int
as
begin
    if exists (select * from Registration where pid = @player and cid = @championship)
        update Registration set winprize = @prize where pid = @player and cid = @championship
    else
        insert into Registration values (@player, @championship, @prize)
end
go

exec addPlayerToChampionship 101, 1001, 10000
exec addPlayerToChampionship 102, 1001, 10000
exec addPlayerToChampionship 103, 1001, 10000
exec addPlayerToChampionship 101, 1002, 750
exec addPlayerToChampionship 102, 1002, 272
exec addPlayerToChampionship 103, 1002, 1912
exec addPlayerToChampionship 102, 1002, 5000
exec addPlayerToChampionship 102, 1003, 5000

select * from Registration
go

-- create a view that shows the names of the players that have participated to all championships
create or alter view PlayersInAllChampionships as
select P.pid, P.name, P.surname
from Player P 
where not exists (
    select C.id
    from Championship C
    where not exists (
        select R.pid
        from Registration R
        where R.pid = P.pid and R.cid = C.id
    )
);
go

select * from PlayersInAllChampionships
go
-- implement a function that lists the name of the championships in which are registered no more than m players,
-- where m >= 1 is a parameter of the function
create or alter function ChampionshipsWithMPlayers (@m int)
returns table
as
return (
    select C.name
    from Championship C
    where (
        select count(*)
        from Registration R
        where R.cid = C.id
    ) <= @m
);
go

select * from ChampionshipsWithMPlayers(2)