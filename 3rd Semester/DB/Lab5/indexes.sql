DROP TABLE IF EXISTS Tc;
DROP TABLE IF EXISTS Tb;
DROP TABLE IF EXISTS Ta;
DROP PROCEDURE IF EXISTS populateTableTa;
DROP PROCEDURE IF EXISTS populateTableTb;
DROP PROCEDURE IF EXISTS populateTableTc;
GO

CREATE TABLE Ta (
    aid int NOT NULL,
    a1 int NOT NULL,
    a2 int NOT NULL,
    PRIMARY KEY (aid),
    UNIQUE (a2)
);
GO

CREATE TABLE Tb (
    bid int NOT NULL,
    b2 int NOT NULL,
    b1 int NOT NULL,
    PRIMARY KEY (bid)
);
GO

CREATE TABLE Tc (
    cid int NOT NULL,
    aid int NOT NULL,
    bid int NOT NULL,
    PRIMARY KEY (cid),
    FOREIGN KEY (aid) REFERENCES Ta(aid),
    FOREIGN KEY (bid) REFERENCES Tb(bid)
);
GO

CREATE PROCEDURE populateTableTa(@rows INT) AS
	while @rows > 0 BEGIN
		INSERT INTO Ta VALUES(@rows, @rows - 20000 / @rows + @rows / 4, @rows)
		SET @rows = @rows - 1
	END;
GO

CREATE PROCEDURE populateTableTb(@rows INT) AS
	while @rows > 0 BEGIN
		INSERT INTO Tb VALUES(@rows, @rows - 60000 / @rows + @rows / 2, @rows * 2 - @rows / 3)
		SET @rows = @rows - 1
	END;
GO

CREATE PROCEDURE populateTableTc(@rows INT) AS
	IF @rows > (SELECT COUNT(*) FROM Ta) * (SELECT COUNT(*) FROM Tb) BEGIN
		RAISERROR ('Too many entities requested', 10, 1)
	END
	DECLARE valuesCursor CURSOR LOCAL FOR (
		SELECT a.aid, b.bid
		FROM Ta a CROSS JOIN Tb b
	)
	DECLARE @aid INT
	DECLARE @bid INT
	OPEN valuesCursor
	FETCH valuesCursor INTO @aid, @bid
	while @@FETCH_STATUS = 0 AND @rows > 0 BEGIN
		INSERT INTO Tc VALUES(@rows, @aid, @bid)
		FETCH valuesCursor INTO @aid, @bid	
		SET @rows = @rows - 1
	END
	CLOSE valuesCursor 
	DEALLOCATE valuesCursor;
GO

exec populateTableTa 10000;
exec populateTableTb 10000;
exec populateTableTc 12000;

-- Write queries on Ta such that their execution plans contain the
-- following operators:

-- DROP index1;


-- Clustered index scan

IF EXISTS (SELECT * FROM sys.indexes WHERE name = 'index1')
    DROP INDEX index1 ON Ta;

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE name = 'index1')
    CREATE NONCLUSTERED INDEX index1 ON Ta(a2);
SELECT * FROM Ta ORDER BY aid; -- 46 ms
-- Clustered index seek
SELECT * FROM Ta WHERE aid = 100; --11 ms
-- Nonclustered index scan + Key lookup
SELECT a2 FROM Ta; -- 65ms
-- Nonclustered index seek + Key lookup
SELECT * FROM Ta WHERE a2 = 14; --13ms


IF EXISTS (SELECT * FROM sys.indexes WHERE name = 'index2')
    DROP INDEX index2 ON Tb;

SELECT * FROM Tb WHERE b2=0; --61ms

CREATE NONCLUSTERED INDEX index2 on Tb(b2);
SELECT * FROM Tb WHERE b2=0; --45ms
GO

CREATE OR ALTER VIEW view1 AS 
	SELECT c.bid, SUM(a.a2) AS sumb2
	FROM Tc c INNER JOIN Tb b ON c.bid = b.bid INNER JOIN Ta a ON c.aid = a.aid
	WHERE a.a2 <= 10000 AND b.b2 <= 10000
	GROUP BY c.bid;
GO

SELECT * FROM view1; --100ms
IF EXISTS (SELECT * FROM sys.indexes WHERE name = 'index1')
    DROP INDEX index1 ON Ta;
IF EXISTS (SELECT * FROM sys.indexes WHERE name = 'index2')
    DROP INDEX index2 ON Tb;
CREATE NONCLUSTERED INDEX index1 ON Ta(a2);
CREATE NONCLUSTERED INDEX index2 on Tb(b2);
SELECT * FROM view1; --85ms