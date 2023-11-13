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

INSERT INTO Organization VALUES (1, 'Org1', 'Romania', '1995-04-04'), 
                                (2, 'Org2', 'USA', '1980-12-12'),
                                (3, 'Org3', 'Australia', '1990-10-17'),
                                (4, 'Org4', 'China', '2000-01-01'), 
                                (5, 'Org5', 'Hungary', '1975-04-23'),
                                (6, 'Org6', 'Brazil', '1988-08-08'),
                                (7, 'Org7', 'France', '1999-03-15'),
                                (8, 'Org8', 'Canada', '2005-05-20');

INSERT INTO Contest VALUES  (1, 'Romanian Masters', '2017-09-14', '2017-09-16', 1),
                            (2, 'USA Winter Session', '2015-02-01', '2015-02-02', 2),
                            (3, 'Australian Open', '2016-10-23', '2016-10-25', 3),
                            (4, 'Wuhan Gathering', '2017-04-02', '2017-04-04', 4),
                            (5, 'Brazilian Championship', '2019-07-10', '2019-07-12', 6),
                            (6, 'French Open', '2020-04-05', '2020-04-07', 7),
                            (7, 'Canadian Nationals', '2018-09-18', '2018-09-20', 8);

INSERT INTO CubeType VALUES (1, '3x3', 'Cube', 'The most popular cube'),
                            (2, '4x4', 'Cube', 'A face has 4x4 stickers'),
                            (3, '2x2', 'Cube', 'The smallest cube available'),
                            (4, 'Pyraminx', 'Regular Tetrahedron', 'A tetrahedron with 4 faces'),
                            (5, 'Megaminx', 'Dodecahedron', 'A puzzle with 12 faces'),
                            (6, '5x5', 'Cube', 'A larger cube with 5x5 stickers'),
                            (7, 'Skewb', 'Pyramid', 'A pyramid-shaped puzzle'),
                            (8, 'Square-1', 'Square', 'A cube that can change shape');

INSERT INTO Club VALUES (1, 'Club1', 'Romania'),
                        (2, 'Club2', 'USA'),
                        (3, 'Club3', 'USA'),
                        (4, 'Club4', 'China'),
                        (5, 'Club5', 'Hungary'),
                        (6, 'Club6', 'Brazil'),
                        (7, 'Club7', 'France'),
                        (8, 'Club8', 'Canada');

INSERT INTO Person VALUES(1, 'Person 1 First Name', 'Person 1 Last Name', '1997-04-04', 'Romania', 3),
                         (2, 'Person 2 First Name', 'Person 2 Last Name', '1987-12-12', 'USA', 2),
                         (3, 'Person 3 First Name', 'Person 3 Last Name', '2000-04-19', 'Australia', 1),
                         (4, 'Person 4 First Name', 'Person 4 Last Name', '1999-01-01', 'China', 4);
INSERT INTO Person VALUES(5, 'Person 5 First Name', 'Person 5 Last Name', '1994-04-23', 'India', 5);
INSERT INTO Person VALUES(6, 'Person 6 First Name', 'Person 6 Last Name', '1985-08-08', 'Brazil', 6);
INSERT INTO Person VALUES(7, 'Person 7 First Name', 'Person 7 Last Name', '1992-03-15', 'France', 7);
INSERT INTO Person VALUES(8, 'Person 8 First Name', 'Person 8 Last Name', '2000-05-20', 'Canada', 8);

INSERT INTO Trainer VALUES(1, 'Trainer 1 First Name', 'Trainer 1 Last Name', '1978-04-04', 3, 72);
INSERT INTO Trainer VALUES(2, 'Trainer 2 First Name', 'Trainer 2 Last Name', '1980-12-12', 2, 89);
INSERT INTO Trainer VALUES(3, 'Trainer 3 First Name', 'Trainer 3 Last Name', '1979-06-03', 1, 82);
INSERT INTO Trainer VALUES(4, 'Trainer 4 First Name', 'Trainer 4 Last Name', '1985-03-24', 4, 91);
INSERT INTO Trainer VALUES(5, 'Trainer 5 First Name', 'Trainer 5 Last Name', '1982-04-23', 5, 78);
INSERT INTO Trainer VALUES(6, 'Trainer 6 First Name', 'Trainer 6 Last Name', '1982-08-08', 6, 85);
INSERT INTO Trainer VALUES(7, 'Trainer 7 First Name', 'Trainer 7 Last Name', '1990-03-15', 7, 76);
INSERT INTO Trainer VALUES(8, 'Trainer 8 First Name', 'Trainer 8 Last Name', '1988-05-20', 8, 93);

INSERT INTO isTrainerOf VALUES(1, 1);
INSERT INTO isTrainerOf VALUES(2, 2);
INSERT INTO isTrainerOf VALUES(1, 3);
INSERT INTO isTrainerOf VALUES(4, 5);
INSERT INTO isTrainerOf VALUES(5, 4);
INSERT INTO isTrainerOf VALUES(6, 6);
INSERT INTO isTrainerOf VALUES(7, 7);
INSERT INTO isTrainerOf VALUES(8, 8);

INSERT INTO Cube VALUES(1, 1, 3, 'Manufacturer 1', 'Model 1', 'Black');
INSERT INTO Cube VALUES(2, 1, 5, 'Manufacturer 1', 'Model 2', 'White');
INSERT INTO Cube VALUES(3, 2, 2, 'Manufacturer 3', 'Model 3', 'Stickerless');
INSERT INTO Cube VALUES(4, 2, 3, 'Manufacturer 4', 'Model 4', 'Stickerless');
INSERT INTO Cube VALUES(5, 3, 3, 'Manufacturer 5', 'Model 5', 'Black');
INSERT INTO Cube VALUES(6, 1, 4, 'Manufacturer 1', 'Model 2', 'Stickerless');
INSERT INTO Cube VALUES(7, 3, 6, 'Manufacturer 2', 'Model 6', 'Blue');
INSERT INTO Cube VALUES(8, 4, 7, 'Manufacturer 3', 'Model 7', 'Stickerless');
INSERT INTO Cube VALUES(9, 5, 8, 'Manufacturer 4', 'Model 8', 'White');

INSERT INTO Session VALUES(1, 2, 1, '2017-09-15 10:00:00', '2017-09-15 12:00:00', 'R''U''R''U2D''R''D2L2FD');
INSERT INTO Session VALUES(2, 1, 1, '2015-02-01 12:00:00', '2015-02-01 13:00:00', 'FU2D''L''FUR''U2LR');
INSERT INTO Session VALUES(3, 3, 1, '2016-10-23 11:00:00', '2016-10-23 13:00:00', 'R''U''R''U2D''R''D2L2FD');
INSERT INTO Session VALUES(4, 4, 1, '2017-04-02 17:00:00', '2017-04-02 20:00:00', 'FU2D''L''FUR''U2LR');
INSERT INTO Session VALUES(5, 4, 1, '2018-06-12 13:00:00', '2018-06-12 16:00:00', 'R''U''R''U2D''R''D2L2FD');
INSERT INTO Session VALUES(6, 4, 1, '2019-07-11 14:00:00', '2019-07-11 16:00:00', 'L''U''B''U''D2B''U''F2');
INSERT INTO Session VALUES(7, 6, 2, '2020-04-06 10:00:00', '2020-04-06 12:30:00', 'R''D''F''U''R2D''F''U''F2');
INSERT INTO Session VALUES(8, 7, 3, '2018-09-19 13:00:00', '2018-09-19 15:30:00', 'B''L''D''B''L2D''R''D2');

INSERT INTO timedSolution VALUES(1, 2, 4.67, 0);
INSERT INTO timedSolution VALUES(2, 1, 5.27, NULL);
INSERT INTO timedSolution VALUES(3, 1, 4.87, 1);
INSERT INTO timedSolution VALUES(4, 3, 24.82, 0);
INSERT INTO timedSolution VALUES(5, 5, 18.54, 1);
INSERT INTO timedSolution VALUES(6, 6, 10.23, 0);
INSERT INTO timedSolution VALUES(7, 7, 28.91, NULL);
INSERT INTO timedSolution VALUES(8, 8, 15.76, 1);


UPDATE Person SET ClubID = 1 WHERE Country = 'Romania' or Country = 'Australia';
UPDATE Cube SET Options = 'Stickerless' WHERE Manufacturer = 'Manufacturer 1';
UPDATE Trainer SET Experience = 96 WHERE Experience > 83;
GO

-- DELETE FROM Session WHERE StartTime LIKE '2017%';
-- DELETE FROM Cube WHERE Manufacturer = 'Manufacturer 1';
-- GO

-- -- -- a) 2 queries with the union operation; use UNION [ALL] and OR;
-- select all the speedcubers that are from Romania or have a Stickerless cube
SELECT Person.PId
FROM Person
WHERE Person.Country = 'Romania'
UNION
SELECT Cube.PId
FROM Cube
WHERE Cube.Options = 'Stickerless';

-- select all the club that are from USA or has trainers that have more than 80 experience
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
FROM Person, Cube
WHERE Person.PId = Cube.PId AND Cube.Options = 'Stickerless'
INTERSECT
SELECT Person.PId
FROM Person, Cube
WHERE Person.PId = Cube.PId AND Cube.Options = 'Black';

-- select all the contests that have a session that started in 2018 and a session that started in 2019
SELECT Contest.CId
FROM Contest
WHERE Contest.CId IN (SELECT Session.CId FROM Session WHERE DATEPART(YEAR, Session.StartTime) = 2018)
INTERSECT
SELECT Contest.CId
FROM Contest
WHERE Contest.CId IN (SELECT Session.CId FROM Session WHERE DATEPART(YEAR, Session.StartTime) = 2019);

-- c. 2 queries with the difference operation; use EXCEPT and NOT IN;


-- d) 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

-- select all the clubs that have persons who own 3x3 cubes
SELECT C.ClubId, P.PId
FROM Club C
INNER JOIN Person P ON C.ClubID = P.ClubID
INNER JOIN Cube Cb ON P.PId = Cb.PId
INNER JOIN CubeType Cbt ON Cb.CubeTypeId = Cbt.CubeTypeId
WHERE Cbt.Name = '3x3';
GO

-- select all the cubes for which we do not know if a solution was DNF or not
SELECT Cb.CubeId, ts.Time
FROM Cube Cb
LEFT JOIN timedSolution ts ON Cb.CubeId = ts.CubeId
WHERE ts.DNF is NULL

-- select all the trainers that currently have no persons
SELECT t.TId
FROM isTrainerOf ito
RIGHT JOIN Trainer t ON ito.TId = t.TId
WHERE ito.TId is NULL
GO

-- select all the traitors. I mean trainers. I mean trainers that have persons from other clubs
SELECT t.TId, p.PId, t.ClubId, p.ClubId
FROM Trainer t
FULL JOIN isTrainerOf ito ON t.TId = ito.TId
FULL JOIN Person p ON ito.PId = p.PId
WHERE t.ClubId != p.ClubId