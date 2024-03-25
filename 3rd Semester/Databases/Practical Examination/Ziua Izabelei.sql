CREATE DATABASE Practical
GO

USE Practical
Go

DROP TABLE Guests
DROP TABLE Bands
DROP TABLE TentsCaterers
DROP TABLE Caterers
DROP TABLE Tents
GO

-- SELECT * FROM Guests
-- SELECT * FROM Tents
-- SELECT * FROM Bands
-- SELECT * FROM Caterers
-- SELECT * FROM TentsCaterers
-- GO

-- !!! = if you see this thing, these are mistakes i did and that were pointed to me during marking
-- Observation: add ids for all entities used
-- subject II

/*
Create a database for Ziua Izabelei
Important entities: Tents, Bands, Caterers, Guests
*/

-- 1. Write SQL Script to create the tables

-- A tent has a name and a color. A tent can serve food from multiple caterers. Tents name are unique.
CREATE TABLE Tents(
	TID INT PRIMARY KEY,
	TName VARCHAR(50) UNIQUE,
	TColor VARCHAR(50)
)

-- A caterer has a name and an address and a flag if it has a vegetarian menu. A caterer can provide food to multiple tents.
CREATE TABLE Caterers(
	CID INT PRIMARY KEY,
	CName VARCHAR(50),
	CAddr VARCHAR(50),
	Vegeterian BIT
)

CREATE TABLE TentsCaterers( -- !!!: i should make a candidate key, so i won't have the same pair (TID, CID) twice 
	TCID INT PRIMARY KEY,
	TID INT REFERENCES Tents(TID),
	CID INT REFERENCES Caterers(CID)
)

-- A band has a name, a music genre, the fee per show and can sing in only one tent. It also has the start and end time of the show (format HH:MM). A tent can however support multiple bands.
CREATE TABLE Bands(
	BID INT PRIMARY KEY,
	BName VARCHAR(50),
	BGenre VARCHAR(50),
	BFee INT,
	TID INT REFERENCES Tents(TID),
	BStart TIME,
	BEnd TIME
)

-- A guest has a name, a date of birth and is assigned to a tent.
CREATE TABLE Guests(
	GID INT PRIMARY KEY,
	GName VARCHAR(50),
	GDOB DATE,
	TID INT REFERENCES Tents(TID)
)
GO

INSERT INTO Tents
VALUES(1, 'abc', 'red')
INSERT INTO Tents
VALUES(2, 'def', 'blue')
INSERT INTO Caterers
VALUES(1, 'food1', 'here', 0)
INSERT INTO Caterers
VALUES(2, 'food2', 'here', 1)
INSERT INTO Caterers
VALUES(3, 'food3', 'here', 1)
INSERT INTO TentsCaterers
VALUES(1, 1, 1)
INSERT INTO TentsCaterers
VALUES(2, 1, 2)
INSERT INTO Bands
VALUES(1, 'aaa', 'metal', 100, 2, '18:50', '19:50')
INSERT INTO Bands
VALUES(2, 'def', 'rock', 100, 1, '18:50', '19:50')
INSERT INTO Guests
VALUES(1, 'alex', '09.09.2002', 2)
INSERT INTO Guests
VALUES(2, 'mihai', '09.09.2002', 1)
INSERT INTO Guests
VALUES(3, 'andrei', '09.09.2002', 1)
GO

-- 2. Create a procedure that receives two tents names N1 and N2. It moves all the guests and bands from tent N1 to N2.
-- It deletes all the relations between the caterers and the tent N1. Then it deletes tent N1.
-- *** observation: suppose tents N1 and N2 already exists, no need to verify

CREATE OR ALTER PROC uspReassignFromTent
(@N1 VARCHAR(50), @N2 VARCHAR(50))
AS
	DECLARE @N1ID INT = (SELECT TID FROM Tents WHERE TName = @N1) 
	DECLARE @N2ID INT = (SELECT TID FROM Tents WHERE TName = @N2) 
    UPDATE Guests
	SET TID = @N2ID
	WHERE TID = @N1ID
	UPDATE Bands
	SET TID = @N2ID
	WHERE TID = @N1ID
	DELETE FROM TentsCaterers
	WHERE TID = @N1ID
	DELETE FROM Tents
	WHERE TID = @N1ID

EXEC uspReassignFromTent 'abc', 'def'
GO

-- 3. Create a view that shows the names of the bands that sing in tents with more than 50 guests.

CREATE OR ALTER VIEW vBandsWithManyGuests AS
	SELECT Bands.BName, COUNT(*) GuestsNumber FROM Bands -- !!!: group after id and then find the name, maybe multiple bands have the same name even though they are different
	INNER JOIN Guests ON Guests.TID = Bands.TID
	GROUP BY Bands.BName
	HAVING COUNT(*) >= 50
GO

SELECT * FROM vBandsWithManyGuests
GO

-- 4. Create a function that receives T and a providesVegMenu bit. It then shows all the caterers names that provide food for 
-- at least T tents and does/doesn't have a vegetarian menu (depending on the bit).

CREATE OR ALTER FUNCTION ufCaterersWithGuestsAndMenu(@T INT, @providesVegMenu BIT)
RETURNS TABLE
RETURN
	SELECT Caterers.CName, COUNT(*) ProvidedTents FROM Caterers -- !!!: group after id and then find the name, maybe multiple caterers have the same name even though they are different
	INNER JOIN TentsCaterers ON TentsCaterers.CID = Caterers.CID
	WHERE Caterers.Vegeterian = @providesVegMenu
	GROUP BY Caterers.CName
	HAVING @T <= COUNT(*)
GO

SELECT * FROM ufCaterersWithGuestsAndMenu(0, 1)
GO


-- subject I

-- Table R has the structure: [ID, A, V, L, M, N, P]

CREATE TABLE R(
	ID INT PRIMARY KEY,
	A INT,
	V VARCHAR(100),
	L INT,
	M INT,
	N INT,
	P INT
)

-- Below are the rows inserted into the table:

INSERT INTO R
VALUES(1, 1, 'A-nceput de ieri sa cada', 2, 2, 1, 1)

INSERT INTO R
VALUES(2, 1, 'Cate-un fulg, acum a stat,', 1, 1, 2, 1)

INSERT INTO R
VALUES(3, 1, 'Norii s-au mai razbunat', 3, 4, 2, 2)

INSERT INTO R
VALUES(4, 2, 'Spre apus, dar stau gramada', 4, 3, 3, 1)

INSERT INTO R
VALUES(5, 2, 'Peste sat.', 6, 9, 3, 2)

INSERT INTO R
VALUES(6, 3, 'Nu e soare, dar e bine,', 5, 5, 3, 3)

INSERT INTO R
VALUES(7, 3, 'Si pe rau e numai fum.', 1, 6, 4, 1)

INSERT INTO R
VALUES(8, 3, 'Vantu-i linistit acum,', 2, 5, 4, 2)

INSERT INTO R
VALUES(9, 4, 'Dar navalnic vuiet vine', 3, 9, 4, 3)

INSERT INTO R
VALUES(10, 4, 'De pe drum.', 7, 5, 4, 4)

INSERT INTO R
VALUES(11, 4, 'Sunt copii. Cu multe sanii,', 3, 5, 5, 1)

INSERT INTO R
VALUES(12, 4, 'De pe coasta vin tipand', 2, 8, 5, 2)

INSERT INTO R
VALUES(13, 4, 'Si se-mping si sar razand;', 1, 6, 5, 3)

-- 1. Suppose the returned result are tuples of form <A, MaxL>
-- What happens after running the query?
/*
a. 4 tuples are shown
b. 3 tuples are shown
c. 2 tuples are shown
d. tuple <4, 7> is in the entry set
e. tuple <3, 1> is in the entry set
f. none of the above

Answers: c, d, e
*/

SELECT r1.A, MAX(r1.L) MaxL
FROM R r1
WHERE r1.V LIKE '_%pe%_'
GROUP BY r1.A
HAVING MAX(r1.L) >= ALL
(SELECT r2.L-6 FROM R r2)


-- 2. After running the query, how many rows are shown?
/*
a. 0
b. 1
c. 2
d. 3
e. 4
f. none of the above

Answers: e	
*/

SELECT t1.ID
FROM (SELECT r1.ID, r1.A, r1.V
	  FROM R r1 INNER JOIN R r2 ON r1.ID = r2.ID
	  WHERE r1.ID < 5) t1
	  LEFT JOIN (SELECT r3.ID, r3.A, r3.V
				FROM R r3
				WHERE r3.M < 5) t2 ON t1.ID = t2.ID

-- 3. We have the table DeleteLog[ID, FNDif], the function ufF1 and the trigger on R (suppose it's the only trigger)
-- After running the delete, how many entries will DeleteLog have?
/*
a. 0
b. 1
c. 2
d. 3
e. 4
f. none of the above

Answers: d
*/

CREATE TABLE DeleteLog(
	ID INT PRIMARY KEY,
	FnDif INT)
GO

CREATE OR ALTER FUNCTION ufF1(@Dif INT)
RETURNS INT
BEGIN
RETURN
(SELECT COUNT(*) FROM R WHERE A < @Dif)
END
GO

CREATE OR ALTER TRIGGER TrOnDelete
ON R FOR DELETE
AS
 INSERT DeleteLog(ID, FnDif)
 SELECT d.ID, dbo.ufF1(d.p - d.N)
 FROM deleted d
 WHERE d.N > d.P
GO

DELETE
FROM R
WHERE ID BETWEEN 11 AND 15

SELECT * FROM DeleteLog
SELECT * FROM R
