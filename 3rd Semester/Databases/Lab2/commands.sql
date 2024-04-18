DELETE FROM timedSolution;
DELETE FROM Session;
DELETE FROM Cube;
DELETE FROM isTrainerOf;
DELETE FROM Trainer;
DELETE FROM Person;
DELETE FROM Club;
DELETE FROM CubeType;
DELETE FROM Contest;
DELETE FROM Organization;
GO

select * from Organization;
select * from Contest


-- Inserting 20 rows for Organization table
INSERT INTO Organization
VALUES
    (1, 'Org1', 'Romania', '1995-04-04'),
    (2, 'Org2', 'USA', '1980-12-12'),
    (3, 'Org3', 'Australia', '1990-10-17'),
    (4, 'Org4', 'China', '2000-01-01'),
    (5, 'Org5', 'Hungary', '1975-04-23'),
    (6, 'Org6', 'Brazil', '1988-08-08'),
    (7, 'Org7', 'France', '1999-03-15'),
    (8, 'Org8', 'Canada', '2005-05-20'),
    (9, 'Org9', 'Japan', '1998-09-09'),
    (10, 'Org10', 'Germany', '2001-11-11'),
    (11, 'Org11', 'South Korea', '1985-03-21'),
    (12, 'Org12', 'Italy', '1996-06-26'),
    (13, 'Org13', 'Spain', '1982-07-07'),
    (14, 'Org14', 'Mexico', '1977-08-17'),
    (15, 'Org15', 'Argentina', '1992-02-28'),
    (16, 'Org16', 'Russia', '2003-12-31'),
    (17, 'Org17', 'India', '1987-05-05'),
    (18, 'Org18', 'United Kingdom', '1994-01-15'),
    (19, 'Org19', 'Sweden', '1989-10-30'),
    (20, 'Org20', 'Norway', '1979-11-19');

-- Inserting contests ensuring each organization has at least 5 contests
INSERT INTO Contest
VALUES
    ('Romanian Masters', '2017-09-14', '2017-09-16', 1),
    ('USA Winter Session', '2015-02-01', '2015-02-02', 2),
    ('Australian Open', '2016-10-23', '2016-10-25', 3),
    ('Wuhan Gathering', '2017-04-02', '2017-04-04', 4),
    ('Brazilian Championship', '2019-07-10', '2019-07-12', 6),
    ('French Open', '2020-04-05', '2020-04-07', 7),
    ('Canadian Nationals', '2018-09-18', '2018-09-20', 8),
    ('Romanian Masters 2', '2018-09-14', '2018-09-16', 1),
    ('USA Winter Session 2', '2016-02-01', '2016-02-02', 2),
    ('Australian Open 2', '2017-10-23', '2017-10-25', 3),
    ('Wuhan Gathering 2', '2018-04-02', '2018-04-04', 4),
    ('Brazilian Championship 2', '2020-07-10', '2020-07-12', 6),
    ('French Open 2', '2021-04-05', '2021-04-07', 7),
    ('Canadian Nationals 2', '2019-09-18', '2019-09-20', 8),
    ('Romanian Masters 3', '2019-09-14', '2019-09-16', 1),
    ('USA Winter Session 3', '2017-02-01', '2017-02-02', 2),
    ('Australian Open 3', '2018-10-23', '2018-10-25', 3),
    ('Wuhan Gathering 3', '2019-04-02', '2019-04-04', 4),
    ('Brazilian Championship 3', '2021-07-10', '2021-07-12', 6),
    ('French Open 3', '2022-04-05', '2022-04-07', 7);


INSERT INTO CubeType
VALUES
    (1, '3x3', 'Cube', 'The most popular cube'),
    (2, '4x4', 'Cube', 'A face has 4x4 stickers'),
    (3, '2x2', 'Cube', 'The smallest cube available'),
    (4, 'Pyraminx', 'Regular Tetrahedron', 'A tetrahedron with 4 faces'),
    (5, 'Megaminx', 'Dodecahedron', 'A puzzle with 12 faces'),
    (6, '5x5', 'Cube', 'A larger cube with 5x5 stickers'),
    (7, 'Skewb', 'Pyramid', 'A pyramid-shaped puzzle'),
    (8, 'Square-1', 'Square', 'A cube that can change shape');

INSERT INTO Club
VALUES
    (1, 'Club1', 'Romania'),
    (2, 'Club2', 'USA'),
    (3, 'Club3', 'USA'),
    (4, 'Club4', 'China'),
    (5, 'Club5', 'Hungary'),
    (6, 'Club6', 'Brazil'),
    (7, 'Club7', 'France'),
    (8, 'Club8', 'Canada');

INSERT INTO Person
VALUES
    (1, 'Person 1 First Name', 'Person 1 Last Name', '1997-04-04', 'Romania', 3),
    (2, 'Person 2 First Name', 'Person 2 Last Name', '1987-12-12', 'USA', 2),
    (3, 'Person 3 First Name', 'Person 3 Last Name', '2000-04-19', 'Australia', 1),
    (4, 'Person 4 First Name', 'Person 4 Last Name', '1999-01-01', 'China', 4),
    (5, 'Person 5 First Name', 'Person 5 Last Name', '1994-04-23', 'India', 5),
    (6, 'Person 6 First Name', 'Person 6 Last Name', '1985-08-08', 'Brazil', 6),
    (7, 'Person 7 First Name', 'Person 7 Last Name', '1992-03-15', 'France', 7),
    (8, 'Person 8 First Name', 'Person 8 Last Name', '2000-05-20', 'Canada', 8),
    (9, 'Person 9 First Name', 'Person 9 Last Name', '2000-05-20', 'Canada', 1),
    (10, 'Person 10 First Name', 'Person 10 Last Name', '1993-05-20', 'Canada', 1),
    (11, 'Person 11 First Name', 'Person 11 Last Name', '1996-05-20', 'Canada', 1);



INSERT INTO Trainer
VALUES
    (1, 'Trainer 1 First Name', 'Trainer 1 Last Name', '1978-04-04', 3, 72),
    (2, 'Trainer 2 First Name', 'Trainer 2 Last Name', '1980-12-12', 2, 89),
    (3, 'Trainer 3 First Name', 'Trainer 3 Last Name', '1979-06-03', 2, 82),
    (4, 'Trainer 4 First Name', 'Trainer 4 Last Name', '1985-03-24', 4, 91),
    (5, 'Trainer 5 First Name', 'Trainer 5 Last Name', '1982-04-23', 5, 78),
    (6, 'Trainer 6 First Name', 'Trainer 6 Last Name', '1982-08-08', 6, 85),
    (8, 'Trainer 8 First Name', 'Trainer 8 Last Name', '1988-05-20', 8, 93);

INSERT INTO isTrainerOf
VALUES
    (1, 1),
    (2, 2),
    (1, 3),
    (4, 5),
    (5, 4),
    (6, 6),
    (8, 8);

INSERT INTO Cube
VALUES
    (1, 1, 3, 'Manufacturer 1', 'Model 1', 'Black'),
    (2, 1, 5, 'Manufacturer 1', 'Model 2', 'White'),
    (3, 2, 2, 'Manufacturer 3', 'Model 3', 'Stickerless'),
    (4, 2, 3, 'Manufacturer 4', 'Model 4', 'Stickerless'),
    (5, 3, 3, 'Manufacturer 5', 'Model 5', 'Black'),
    (6, 1, 4, 'Manufacturer 1', 'Model 2', 'Stickerless'),
    (7, 3, 6, 'Manufacturer 2', 'Model 6', 'Black'),
    (8, 4, 7, 'Manufacturer 3', 'Model 7', 'Stickerless'),
    (9, 5, 8, 'Manufacturer 4', 'Model 8', 'White');

INSERT INTO Session
VALUES
    (1, 2, 1, '2017-09-15 10:00:00', '2017-09-15 12:00:00', 'R''U''R''U2D''R''D2L2FD'),
    (2, 1, 1, '2015-02-01 12:00:00', '2015-02-01 13:00:00', 'FU2D''L''FUR''U2LR'),
    (3, 3, 1, '2016-10-23 11:00:00', '2016-10-23 13:00:00', 'R''U''R''U2D''R''D2L2FD'),
    (4, 4, 1, '2017-04-02 17:00:00', '2017-04-02 20:00:00', 'FU2D''L''FUR''U2LR'),
    (5, 4, 1, '2018-06-12 13:00:00', '2018-06-12 16:00:00', 'R''U''R''U2D''R''D2L2FD'),
    (6, 4, 1, '2019-07-11 14:00:00', '2019-07-11 16:00:00', 'L''U''B''U''D2B''U''F2'),
    (7, 6, 2, '2020-04-06 10:00:00', '2020-04-06 12:30:00', 'R''D''F''U''R2D''F''U''F2'),
    (8, 7, 3, '2018-09-19 13:00:00', '2018-09-19 15:30:00', 'B''L''D''B''L2D''R''D2');

INSERT INTO timedSolution
VALUES
    (1, 1, 2, 4.67, 0),
    (2, 1, 2, 5.67, 0),
    (3, 2, 1, 5.27, NULL),
    (4, 3, 1, 4.87, 1),
    (5, 4, 3, 24.82, 0),
    (6, 6, 6, 10.23, 0),
    (7, 7, 7, 28.91, NULL),
    (8, 8, 8, 15.76, 1),
    (9, 4, 1, 4.27, NULL),
    (10, 4, 3, 4.27, 0);
GO

UPDATE Person
SET ClubID = 1
WHERE Country = 'Romania'
    or Country = 'Australia';
GO

UPDATE Cube
SET Options = 'Stickerless'
WHERE Manufacturer = 'Manufacturer 1';
GO

UPDATE Trainer
SET Experience = 96
WHERE Experience
BETWEEN 83 AND 90
GO

-- -- DELETE all the timed solutions that have their dnf null
-- DELETE FROM timedSolution
-- WHERE dnf IS NULL;

-- -- DELETE all the trainers with an experience lower than 75
-- DELETE FROM isTrainerOf
-- WHERE TId < 75;

-- DELETE FROM Trainer
-- WHERE Experience < 75;


-- DELETE FROM Session WHERE StartTime LIKE '2017%';
-- DELETE FROM Cube WHERE Manufacturer = 'Manufacturer 1';
-- GO

-- -- -- a) 2 queries with the union operation; use UNION [ALL] and OR;
-- find the number of persons that are from Romania or have a stickerless cube
    SELECT Person.P
    FROM Person
    WHERE Person.Country = 'Romania'
UNION
    SELECT Cube.PId
    FROM Cube
    WHERE Cube.Options = 'Stickerless';

-- select all the clubs that are from USA or have trainers that have more than 80 experience
    SELECT Club.ClubId
    FROM Club
    WHERE Club.Country = 'USA'
UNION ALL
    SELECT Trainer.TId
    FROM Trainer
    WHERE Trainer.Experience > 80;

-- b. 2 queries with the intersection operation; use INTERSECT and IN;
-- select all the persons that have a cube that is stickerless and a cube that is black
    SELECT Person.PId
    FROM Person,
        Cube
    WHERE Person.PId = Cube.PId
        AND Cube.Options = 'Stickerless'
INTERSECT
    SELECT Person.PId
    FROM Person,
        Cube
    WHERE Person.PId = Cube.PId
        AND Cube.Options = 'Black';

-- select all the contests that have a session that started in 2018 and a session that started in 2019
    SELECT Contest.CId
    FROM Contest
    WHERE Contest.CId IN (
                         SELECT Session.CId
    FROM Session
    WHERE DATEPART(YEAR, Session.StartTime) = 2018
                     )
INTERSECT
    SELECT Contest.CId
    FROM Contest
    WHERE Contest.CId IN (
                         SELECT Session.CId
    FROM Session
    WHERE DATEPART(YEAR, Session.StartTime) = 2019
                     );

-- c. 2 queries with the difference operation; use EXCEPT and NOT IN;
-- select all the cube types except the ones for which at least a stickerless cube exists
    SELECT CubeType.CubeTypeId
    FROM CubeType
EXCEPT
    SELECT CubeType.CubeTypeId
    FROM CubeType,
        Cube
    WHERE CubeType.CubeTypeId = Cube.CubeTypeId
        AND Cube.Options = 'Stickerless';

-- select all the cube types that do not have a timed solution
SELECT CubeType.CubeTypeId
FROM CubeType
WHERE CubeType.CubeTypeId NOT IN (
                                     SELECT Cube.CubeTypeId
FROM Cube,
    timedSolution
WHERE Cube.CubeId = timedSolution.CubeId
                                 );


-- d) 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

-- select all the clubs that have persons who own 3x3 cubes
SELECT DISTINCT
    C.ClubId
FROM Club C
    INNER JOIN Person P
    ON C.ClubID = P.ClubID
    INNER JOIN Cube Cb
    ON P.PId = Cb.PId
    INNER JOIN CubeType Cbt
    ON Cb.CubeTypeId = Cbt.CubeTypeId
WHERE Cbt.Name = '3x3';
GO

-- inner join of trainers and the timed solutions of their trainees
SELECT isTrainerOf.TId,
    timedSolution.Time
FROM isTrainerOf
    INNER JOIN Person
    ON isTrainerOf.PId = Person.PId
    INNER JOIN Cube
    ON Person.PId = Cube.PId
    INNER JOIN timedSolution
    ON Cube.CubeId = timedSolution.CubeId
GO


-- select all the cubes for which we do not know if a solution was DNF or not
SELECT DISTINCT
    Cb.CubeId
FROM Cube Cb
    LEFT JOIN timedSolution ts
    ON Cb.CubeId = ts.CubeId
WHERE ts.DNF is NULL
GO

-- right join of cubes and their timed solutions
SELECT ts.Time,
    Cb.CubeId
FROM timedSolution ts
    RIGHT JOIN Cube Cb
    ON ts.CubeId = Cb.CubeId
GO

-- see which person can be trained by which trainer, and viceversa. They have to be in the same club
SELECT P.PId,
    T.TId
FROM Person P
    FULL JOIN Trainer T
    ON P.ClubId = T.ClubId
GO

-- e) 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery must include a subquery in its own WHERE clause;
-- select all the persons that have a cube that is stickerless and a cube that is black
SELECT Person.PId
FROM Person
WHERE Person.PId IN (
                        SELECT Cube.PId
    FROM Cube
    WHERE Cube.Options = 'Stickerless'
                    )
    AND Person.PId IN (
                            SELECT Cube.PId
    FROM Cube
    WHERE Cube.Options = 'Black'
                        );
GO

-- select all the cubes that have a timed solution below 5 seconds or above 20 seconds
SELECT COUNT(*)
FROM Cube
WHERE Cube.CubeId IN (
                         SELECT timedSolution.CubeId
    FROM timedSolution
    WHERE timedSolution.Time < 5
                     )
    OR Cube.CubeId IN (
                            SELECT timedSolution.CubeId
    FROM timedSolution
    WHERE timedSolution.Time > 20
                        );
GO

-- f) 2 queries with the EXISTS operator and a subquery in the WHERE clause, use TOP;

-- find the number of trainers that have at least one person in their club
SELECT COUNT(*)
FROM Trainer
WHERE EXISTS
(
    SELECT TOP 1
    Person.PId
FROM Person
WHERE Person.ClubId = Trainer.ClubId
);
GO

-- select all the persons that have at least one cube that is stickerless
SELECT Person.PId
FROM Person
WHERE EXISTS
(
    SELECT TOP 1
    Cube.PId
FROM Cube
WHERE Cube.PId = Person.PId
    AND Cube.Options = 'Stickerless'
);
GO

-- g. 2 queries with a subquery in the FROM clause;                         

-- select all the persons that have a trainer with experience between 75 and 90
SELECT Person.PId
FROM Person,
    (
    SELECT Trainer.TId
    FROM Trainer
    WHERE Trainer.Experience
    BETWEEN 75 AND 90
) AS ExperiencedTrainers
    INNER JOIN isTrainerOf
    ON ExperiencedTrainers.TId = isTrainerOf.TId
WHERE Person.PId = isTrainerOf.PId;
GO

-- select all persons that have a 3x3 cube and a 4x4 cube
SELECT DISTINCT
    Person.PId
FROM
    (
    SELECT Cube.PId
    FROM Cube,
        CubeType
    WHERE Cube.CubeTypeId = CubeType.CubeTypeId
        AND CubeType.Name = '3x3'
) AS ThreeCubes ,
    Person
WHERE Person.PId = ThreeCubes.PId
    AND Person.PId IN (
                            SELECT Cube.PId
    FROM Cube,
        CubeType
    WHERE Cube.CubeTypeId = CubeType.CubeTypeId
        AND CubeType.Name = '4x4'
                        );
GO

-- h) 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause; 
-- use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

-- select all the clubs that have at least 3 persons
SELECT Person.ClubId
FROM Person
GROUP BY Person.ClubId
HAVING COUNT(*) >= 3
GO

-- select all the clubs that have sum of the experience of their trainers greater than 150
SELECT Club.ClubId
FROM Club
    INNER JOIN Trainer
    ON Club.ClubId = Trainer.ClubId
GROUP BY Club.ClubId
HAVING SUM(Trainer.Experience) > 150;
GO

-- select all the cubes that have at least one timed solution under 5 seconds done on a stickerless cube
SELECT timedSolution.CubeId
FROM timedSolution
GROUP BY timedSolution.CubeId
HAVING MIN(timedSolution.Time) < 5
    AND timedSolution.CubeId IN (
                                       SELECT Cube.CubeId
    FROM Cube
    WHERE Cube.Options = 'Stickerless'
                                   )
GO


-- select all the contests that have at least 2 sessions with 3 timed solutions each
SELECT Session.CId
FROM Session
GROUP BY Session.CId
HAVING COUNT(*) >= 2
    AND Session.CId IN (
                              SELECT timedSolution.SID
    FROM timedSolution
    GROUP BY timedSolution.SId
    HAVING COUNT(*) >= 3
                          );
GO

-- i) 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); 
-- rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.

-- find the number of persons that have a cube that is stickerless
SELECT COUNT(*)
FROM Person
WHERE Person.PId=ANY
(
    SELECT Cube.PId
FROM Cube
WHERE Cube.Options = 'Stickerless'
);
--- WHERE Person.PId IN (SELECT Cube.PId FROM Cube WHERE Cube.Options = 'Stickerless');
GO

-- select all the sessions that have all their timed solutions not DNF
SELECT Session.SId
FROM Session
WHERE Session.SId<>ALL
(
    SELECT timedSolution.SId
FROM timedSolution
WHERE timedSolution.DNF = 1
    or timedSolution.DNF is NULL
);
--- WHERE Session.SId NOT IN (SELECT timedSolution.SId FROM timedSolution WHERE timedSolution.DNF = 1);
GO

-- select the cube that has the maximum number of timed solutions
SELECT Cube.CubeId
FROM Cube
WHERE Cube.CubeId=ANY
(
    SELECT TOP 1
    c1.CubeId
FROM Cube c1,
    timedSolution
WHERE c1.CubeId = timedSolution.CubeId
GROUP BY c1.CubeId
ORDER BY COUNT(*) DESC
);
GO
-- rewrite the query using aggregator operator
-- SELECT TOP 1 timedSolution.CubeId
-- FROM timedSolution
-- GROUP BY timedSolution.CubeId
-- ORDER BY COUNT(*) DESC;
-- GO

-- select the contest that have the minimum number of sessions
SELECT Contest.CId
FROM Contest
WHERE Contest.CId=ANY
(
    SELECT TOP 1
    c1.CId
FROM Contest c1,
    Session
WHERE c1.CId = Session.CId
GROUP BY c1.CId
ORDER BY COUNT(*) ASC
);
GO

-- rewrite the query using aggregator operator
-- SELECT TOP 1 Session.CId
-- FROM Session
-- GROUP BY Session.CId
-- ORDER BY COUNT(*) ASC;
-- GO