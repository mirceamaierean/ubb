use Seminar6
go

-- stored procedure

create or alter proc uspUpdateStationOnRoute(@rname varchar(50), @sname varchar(50), @arrival time, @departure time)
as 
    declare @rid int = (select id from Routes where name = @rname),
        @sid int = (select id from Stations where name = @sname)

    if @rid is null
        begin
            raiserror('Route %s does not exist', 16, 1, @rname)
            return
        end

    if @sid is null
        begin
            raiserror('Station %s does not exist', 16, 1, @sname)
            return
        end

    if exists (select * from RoutesStations where routeId = @rid and stationId = @sid)
        update RoutesStations
        set arrivalTime = @arrival, departureTime = @departure
        where routeId = @rid and stationId = @sid
    else
        insert RoutesStations(routeId, stationId, arrivalTime, departureTime)
        values (@rid, @sid, @arrival, @departure)
go

insert TrainTypes values(1, 'tt1', 'tt1desc')
insert Trains values(1, 't1', 1), (2, 't2', 1), (3, 't3', 1)
insert Routes values(1, 'r1', 1), (2, 'r2', 2), (3, 'r3', 3)
insert Stations values(1, 's1'), (2, 's2'), (3, 's3')
go

SELECT * FROM TrainTypes
SELECT * FROM Trains
SELECT * FROM Routes
SELECT * FROM Stations
SELECT * FROM RoutesStations
go

exec uspUpdateStationOnRoute 'r1', 's1', '10:00', '10:10'
exec uspUpdateStationOnRoute 'r1', 's2', '10:00', '10:10'
exec uspUpdateStationOnRoute 'r1', 's3', '10:40', '10:50'
exec uspUpdateStationOnRoute 'r2', 's1', '11:00', '11:10'
exec uspUpdateStationOnRoute 'r2', 's2', '11:20', '11:30'
exec uspUpdateStationOnRoute 'r2', 's3', '11:40', '11:50'
exec uspUpdateStationOnRoute 'r3', 's1', '12:00', '12:10'

drop view if exists vRoutesWithAllStations
go

create view vRoutesWithAllStations
as
select r.name
from Routes r
where not exists (select id from Stations s
                    except
                    select stationId from RoutesStations rs where rs.routeId = r.id)
go
select * from vRoutesWithAllStations

create function ufFilterStationsByNumberOfRoutes(@n int)
returns table
return
select s.name
from Stations s
Where s.id in 
(select rs.stationId
    from RoutesStations rs
    group by rs.stationId
    having count(*) > @n)
go

select * from ufFilterStationsByNumberOfRoutes(2)
select * from ufFilterStationsByNumberOfRoutes(1)