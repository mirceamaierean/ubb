use Speedcubing
go

drop table if exists TestRunTables
drop table if exists TestRunViews
drop table if exists TestRuns
drop table if exists TestTables
drop table if exists Tables
drop table if exists TestViews
drop table if exists Views
drop table if exists Tests
go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[FK_TestRunTables_Tables]')
	AND Objectproperty(id, N'IsForeignKey') = 1)
  ALTER TABLE [testruntables]
    DROP CONSTRAINT fk_testruntables_tables

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[FK_TestTables_Tables]')
	AND Objectproperty(id, N'IsForeignKey') = 1)
  ALTER TABLE [testtables]
    DROP CONSTRAINT fk_testtables_tables

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[FK_TestRunTables_TestRuns]')
	AND Objectproperty(id, N'IsForeignKey') = 1)
  ALTER TABLE [testruntables]
    DROP CONSTRAINT fk_testruntables_testruns

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[FK_TestRunViews_TestRuns]')
	AND Objectproperty(id, N'IsForeignKey') = 1)
  ALTER TABLE [testrunviews]
    DROP CONSTRAINT fk_testrunviews_testruns

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[FK_TestTables_Tests]')
	AND Objectproperty(id, N'IsForeignKey') = 1)
  ALTER TABLE [testtables]
    DROP CONSTRAINT fk_testtables_tests

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[FK_TestViews_Tests]')
	AND Objectproperty(id, N'IsForeignKey') = 1)
  ALTER TABLE [testviews]
    DROP CONSTRAINT fk_testviews_tests

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[FK_TestRunViews_Views]')
	AND Objectproperty(id, N'IsForeignKey') = 1)
  ALTER TABLE [testrunviews]
    DROP CONSTRAINT fk_testrunviews_views

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[FK_TestViews_Views]')
	AND Objectproperty(id, N'IsForeignKey') = 1)
  ALTER TABLE [testviews]
    DROP CONSTRAINT fk_testviews_views

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[Tables]')
	AND Objectproperty(id, N'IsUserTable') = 1)
  DROP TABLE [tables]

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[TestRunTables]')
	AND Objectproperty(id, N'IsUserTable') = 1)
  DROP TABLE [testruntables]

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[TestRunViews]')
	AND Objectproperty(id, N'IsUserTable') = 1)
  DROP TABLE [testrunviews]

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[TestRuns]')
	AND Objectproperty(id, N'IsUserTable') = 1)
  DROP TABLE [testruns]

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[TestTables]')
	AND Objectproperty(id, N'IsUserTable') = 1)
  DROP TABLE [testtables]

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[TestViews]')
	AND Objectproperty(id, N'IsUserTable') = 1)
  DROP TABLE [testviews]

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[Tests]')
	AND Objectproperty(id, N'IsUserTable') = 1)
  DROP TABLE [tests]

go

IF EXISTS (SELECT *
FROM dbo.sysobjects
WHERE  id = Object_id(N'[Views]')
	AND Objectproperty(id, N'IsUserTable') = 1)
  DROP TABLE [views]

go

CREATE TABLE [tables]
(
	[tableid] [INT] IDENTITY (1, 1) NOT NULL,
	[name] [NVARCHAR] (50) COLLATE sql_latin1_general_cp1_ci_as NOT NULL
)
ON [PRIMARY]

go

CREATE TABLE [testruntables]
(
	[testrunid] [INT] NOT NULL,
	[tableid] [INT] NOT NULL,
	[startat] [DATETIME] NOT NULL,
	[endat] [DATETIME] NOT NULL
)
ON [PRIMARY]

go

CREATE TABLE [testrunviews]
(
	[testrunid] [INT] NOT NULL,
	[viewid] [INT] NOT NULL,
	[startat] [DATETIME] NOT NULL,
	[endat] [DATETIME] NOT NULL
)
ON [PRIMARY]

go

CREATE TABLE [testruns]
(
	[testrunid] [INT] IDENTITY (1, 1) NOT NULL,
	[description] [NVARCHAR] (2000) COLLATE sql_latin1_general_cp1_ci_as NULL,
	[startat] [DATETIME] NULL,
	[endat] [DATETIME] NULL
)
ON [PRIMARY]

go

CREATE TABLE [testtables]
(
	[testid] [INT] NOT NULL,
	[tableid] [INT] NOT NULL,
	[noofrows] [INT] NOT NULL,
	[position] [INT] NOT NULL
)
ON [PRIMARY]

go

CREATE TABLE [testviews]
(
	[testid] [INT] NOT NULL,
	[viewid] [INT] NOT NULL
)
ON [PRIMARY]

go

CREATE TABLE [tests]
(
	[testid] [INT] IDENTITY (1, 1) NOT NULL,
	[name] [NVARCHAR] (50) COLLATE sql_latin1_general_cp1_ci_as NOT NULL
)
ON [PRIMARY]

go

CREATE TABLE [views]
(
	[viewid] [INT] IDENTITY (1, 1) NOT NULL,
	[name] [NVARCHAR] (50) COLLATE sql_latin1_general_cp1_ci_as NOT NULL
)
ON [PRIMARY]

go

ALTER TABLE [tables]
  WITH NOCHECK ADD CONSTRAINT [PK_Tables] PRIMARY KEY CLUSTERED ( [tableid] ) ON
  [PRIMARY]

go

ALTER TABLE [testruntables]
  WITH NOCHECK ADD CONSTRAINT [PK_TestRunTables] PRIMARY KEY CLUSTERED (
  [testrunid], [tableid] ) ON [PRIMARY]

go

ALTER TABLE [testrunviews]
  WITH NOCHECK ADD CONSTRAINT [PK_TestRunViews] PRIMARY KEY CLUSTERED (
  [testrunid], [viewid] ) ON [PRIMARY]

go

ALTER TABLE [testruns]
  WITH NOCHECK ADD CONSTRAINT [PK_TestRuns] PRIMARY KEY CLUSTERED ( [testrunid]
  ) ON [PRIMARY]

go

ALTER TABLE [testtables]
  WITH NOCHECK ADD CONSTRAINT [PK_TestTables] PRIMARY KEY CLUSTERED ( [testid],
  [tableid] ) ON [PRIMARY]

go

ALTER TABLE [testviews]
  WITH NOCHECK ADD CONSTRAINT [PK_TestViews] PRIMARY KEY CLUSTERED ( [testid],
  [viewid] ) ON [PRIMARY]

go

ALTER TABLE [tests]
  WITH NOCHECK ADD CONSTRAINT [PK_Tests] PRIMARY KEY CLUSTERED ( [testid] ) ON
  [PRIMARY]

go

ALTER TABLE [views]
  WITH NOCHECK ADD CONSTRAINT [PK_Views] PRIMARY KEY CLUSTERED ( [viewid] ) ON
  [PRIMARY]

go

ALTER TABLE [testruntables]
  ADD CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY ( [tableid] ) REFERENCES
  [tables] ( [tableid] ) ON DELETE CASCADE ON UPDATE CASCADE, CONSTRAINT
  [FK_TestRunTables_TestRuns] FOREIGN KEY ( [testrunid] ) REFERENCES [testruns]
  ( [testrunid] ) ON DELETE CASCADE ON UPDATE CASCADE

go

ALTER TABLE [testrunviews]
  ADD CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY ( [testrunid] )
  REFERENCES [testruns] ( [testrunid] ) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY ( [viewid] ) REFERENCES [views]
  ( [viewid] ) ON DELETE CASCADE ON UPDATE CASCADE

go

ALTER TABLE [testtables]
  ADD CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY ( [tableid] ) REFERENCES
  [tables] ( [tableid] ) ON DELETE CASCADE ON UPDATE CASCADE, CONSTRAINT
  [FK_TestTables_Tests] FOREIGN KEY ( [testid] ) REFERENCES [tests] ( [testid] )
  ON DELETE CASCADE ON UPDATE CASCADE

go

ALTER TABLE [testviews]
  ADD CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY ( [testid] ) REFERENCES
  [tests] ( [testid] ), CONSTRAINT [FK_TestViews_Views] FOREIGN KEY ( [viewid] )
  REFERENCES [views] ( [viewid] )

go

----- Start lab
drop procedure addToViews
drop procedure addToTests
drop procedure addToTables
drop procedure connectTableToTest
drop procedure connectViewToTest
drop procedure if exists runTest
go

CREATE PROCEDURE addToTables
	(@tableName VARCHAR(255))
AS
IF @tableName NOT IN (SELECT TABLE_NAME
FROM INFORMATION_SCHEMA.TABLES) BEGIN
	PRINT 'Table doesn''t exist'
	RETURN
END
IF @tableName IN (SELECT Name
FROM Tables) BEGIN
	PRINT 'Table already in Tables'
	RETURN
END
INSERT INTO Tables
	(Name)
Values
	(@tableName);
go


CREATE PROCEDURE addToViews
	(@viewName VARCHAR(255))
AS
IF @viewName NOT IN (SELECT TABLE_NAME
FROM INFORMATION_SCHEMA.VIEWS) BEGIN
	PRINT 'View doesn''t exist'
	RETURN
END
IF @viewName IN (SELECT Name
FROM Views) BEGIN
	PRINT 'View already in views'
	RETURN
END
INSERT INTO Views
	(Name)
Values
	(@viewName);
go

CREATE PROCEDURE addToTests
	(@testName VARCHAR(255))
AS
IF @testName IN (SELECT Name
FROM Tests) BEGIN
	PRINT 'Test already in tests'
	RETURN
END
INSERT INTO Tests
	(Name)
Values
	(@testName);
go

CREATE PROCEDURE connectTableToTest
	(@tableName VARCHAR(255),
	@testName VARCHAR(255),
	@rows INT,
	@pos INT)
AS
IF @tableName NOT IN (SELECT Name
FROM Tables) BEGIN
	PRINT 'Table not in Tables'
	RETURN
END
IF @testName NOT IN (SELECT Name
FROM Tests) BEGIN
	PRINT 'Test not in tests'
	RETURN
END
DECLARE @tableId int
DECLARE @testId int
SET @tableId = (SELECT TableID
FROM Tables
WHERE Name=@tableName)
SET @testId = (SELECT TestID
FROM Tests
WHERE Name=@testName)
IF EXISTS(SELECT *
FROM TestTables
WHERE TestId=@testId AND TableId=@tableId) BEGIN
	PRINT 'TestTable connection already exists'
END

INSERT INTO TestTables
VALUES(@testId, @tableId, @rows, @pos);
go



CREATE PROCEDURE connectViewToTest(@viewName VARCHAR(255),
	@testName VARCHAR(255))
AS
IF @viewName NOT IN (SELECT Name
FROM Views) BEGIN
	PRINT 'Table not in Tables'
	RETURN
END
IF @testName NOT IN (SELECT Name
FROM Tests) BEGIN
	PRINT 'Test not in tests'
	RETURN
END
DECLARE @viewId int
DECLARE @testId int
SET @viewId = (SELECT ViewID
FROM Views
WHERE Name=@viewName)
SET @testId = (SELECT TestID
FROM Tests
WHERE Name=@testName)
IF EXISTS(SELECT *
FROM TestViews
WHERE TestId=@testId AND ViewID=@viewId) BEGIN
	PRINT 'TestView connection already exists'
END

INSERT INTO TestViews
VALUES(@testId, @viewId);
go

CREATE PROCEDURE runTest(@testName VARCHAR(255),
	@description VARCHAR(255))
AS
IF @testName NOT IN (SELECT Name
FROM TESTS) BEGIN
	PRINT 'test not in Tests'
	RETURN
END


DECLARE @testStartTime DATETIME
DECLARE @testRunId INT
DECLARE @tableId INT
DECLARE @table VARCHAR(255)
DECLARE @rows INT
DECLARE @pos INT
DECLARE @command VARCHAR(255)
DECLARE @tableInsertStartTime DATETIME
DECLARE @tableInsertEndTime DATETIME
DECLARE @testId INT
DECLARE @view VARCHAR(255)
DECLARE @viewId INT
DECLARE @viewStartTime DATETIME
DECLARE @viewEndTime DATETIME

SET @testId = (SELECT TestId
FROM Tests T
WHERE T.Name = @testName)


DECLARE tableCursor CURSOR SCROLL FOR 
		SELECT T1.Name, T1.TableId, T2.NoOfRows, T2.Position
FROM Tables T1 INNER JOIN TestTables T2 ON T1.TableID = T2.TableID
WHERE T2.TestID = @testId
ORDER BY T2.Position ASC


DECLARE viewCursor CURSOR SCROLL FOR 
		SELECT V.Name, V.ViewId
FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
WHERE TV.TestID = @testId


SET @testStartTime = sysdatetime()

INSERT INTO TestRuns
	(Description, StartAt, EndAt)
VALUES(@description, @testStartTime, @testStartTime)
SET @testRunId = SCOPE_IDENTITY()

OPEN tableCursor
FETCH FIRST FROM tableCursor INTO @table, @tableId, @rows, @pos

WHILE @@FETCH_STATUS = 0 BEGIN
	EXEC ('DELETE FROM ' + @table)
	FETCH tableCursor INTO @table, @tableId, @rows, @pos
END

FETCH LAST FROM tableCursor INTO @table, @tableId, @rows, @pos

WHILE @@FETCH_STATUS = 0 BEGIN
	SET @command = 'populateTable'
	IF @rows > 0 AND @command NOT IN (SELECT ROUTINE_NAME
		FROM INFORMATION_SCHEMA.ROUTINES) BEGIN
		PRINT @command + 'does not exist'
		RETURN
	END
	SET @tableInsertStartTime = sysdatetime()
	IF @rows > 0 BEGIN
		EXEC (@command + ' ''' + @table + ''', ' + @rows)
	END
	SET @tableInsertEndTime = sysdatetime()
	INSERT INTO TestRunTables
	VALUES(@testRunId, @tableId, @tableInsertStartTime, @tableInsertEndTime)
	FETCH PRIOR FROM tableCursor INTO @table, @tableId, @rows, @pos
END
CLOSE tableCursor
DEALLOCATE tableCursor

OPEN viewCursor
FETCH viewCursor INTO @view, @viewId

WHILE @@FETCH_STATUS = 0 BEGIN
	SET @viewStartTime = sysdatetime()
	EXEC ('SELECT * FROM ' + @view)
	SET @viewEndTime = sysdatetime()
	INSERT INTO TestRunViews
	VALUES(@testRunID, @viewId, @viewStartTime, @viewEndTime)
	FETCH viewCursor INTO @view, @viewId
END
CLOSE viewCursor
DEALLOCATE viewCursor
UPDATE TestRuns 
	SET EndAt = sysdatetime()
	WHERE TestRunID = @testRunId;
go


IF EXISTS(SELECT *
FROM INFORMATION_SCHEMA.ROUTINES
WHERE ROUTINE_NAME = 'dropExistingProcedure') BEGIN
	DROP PROCEDURE dropExistingProcedure
END
GO

IF EXISTS(SELECT *
FROM INFORMATION_SCHEMA.ROUTINES
WHERE ROUTINE_NAME = 'dropExistingView') BEGIN
	DROP PROCEDURE dropExistingView
END
GO

CREATE PROCEDURE dropExistingProcedure(@tableName VARCHAR(255))
AS
IF EXISTS (SELECT *
FROM INFORMATION_SCHEMA.ROUTINES
WHERE ROUTINE_NAME = @tableName) BEGIN
	EXEC ('DROP PROCEDURE ' + @tableName)
END
go

CREATE PROCEDURE dropExistingView(@viewName VARCHAR(255))
AS
IF EXISTS (SELECT *
FROM INFORMATION_SCHEMA.VIEWS
WHERE TABLE_NAME = @viewName) BEGIN
	EXEC ('DROP VIEW ' + @viewName)
END
go


EXEC dropExistingProcedure 'populateTableClub'
EXEC dropExistingProcedure 'populateTablePerson'
EXEC dropExistingProcedure 'populateTableTrainer'
EXEC dropExistingProcedure 'populateTableisTrainerOf'
EXEC dropExistingProcedure 'populateTableCube'
EXEC dropExistingProcedure 'populateTableCubeType'
go

EXEC dropExistingView 'ClubView'
EXEC dropExistingView 'PersonCubeView'
EXEC dropExistingView 'PersonCubeGroupedView'
go



CREATE PROCEDURE populateTableClub(@rows INT)
AS
DECLARE @i INT
SET @i = 0
WHILE @i < @rows BEGIN
	INSERT INTO Club
		(ClubId, Name, Country)
	VALUES(@i, 'Club' + CAST(@i AS VARCHAR(255)), 'Country' + CAST(@i AS VARCHAR(255)))
	SET @i = @i + 1
END
GO


CREATE PROCEDURE populateTablePerson(@rows INT)
AS
DECLARE @i INT
SET @i = 0
DECLARE @clubId INT
SET @clubId = (SELECT TOP 1
	ClubId
FROM Club)
WHILE @i < @rows BEGIN
	INSERT INTO Person
		(PId, FirstName, LastName, DateOfBirth, Country, ClubId)
	VALUES(@i, 'FirstName' + CAST(@i AS VARCHAR(255)), 'LastName' + CAST(@i AS VARCHAR(255)), DATEADD(DAY, @i, '2018-01-01'), 'Country' + CAST(@i AS VARCHAR(255)), @clubId)
	SET @i = @i + 1
END
GO


CREATE PROCEDURE populateTableTrainer(@rows INT)
AS
DECLARE @i INT
SET @i = 0
DECLARE @clubId INT
SET @clubId = (SELECT TOP 1
	ClubId
FROM Club)
WHILE @i < @rows BEGIN
	INSERT INTO Trainer
		(TId, FirstName, LastName, DoB, ClubId, Experience)
	VALUES(@i, 'FirstName' + CAST(@i AS VARCHAR(255)), 'LastName' + CAST(@i AS VARCHAR(255)), DATEADD(DAY, @i, '2018-01-01'), @clubId, @i)
	SET @i = @i + 1
END
GO

CREATE PROCEDURE populateTableisTrainerOf(@rows INT)
AS
-- match all the trainers with all the people, ensure that number of rows does not exceed the number of people times the number of trainers
DECLARE @trainerIndex INT
DECLARE @personIndex INT
DECLARE @trainerCount INT
DECLARE @personCount INT
SET @trainerIndex = 0
SET @personIndex = 0
SET @trainerCount = (SELECT COUNT(*)
FROM Trainer)
SET @personCount = (SELECT COUNT(*)
FROM Person)
WHILE @trainerIndex < @trainerCount AND @rows > 0 BEGIN
	SET @personIndex = 0
	WHILE @personIndex < @personCount AND @rows > 0 BEGIN
		INSERT INTO isTrainerOf
			(TId, PId)
		VALUES(@trainerIndex, @personIndex)
		SET @personIndex = @personIndex + 1
		SET @rows = @rows - 1
	END
	SET @trainerIndex = @trainerIndex + 1
END
GO

CREATE PROCEDURE populateTableCubeType(@rows INT)
AS
DECLARE @i INT
SET @i = 0
WHILE @i < @rows BEGIN
	INSERT INTO CubeType
		(CubeTypeId, Name, Shape, Description)
	VALUES(@i, 'Name' + CAST(@i AS VARCHAR(255)), 'Shape' + CAST(@i AS VARCHAR(255)), 'Description' + CAST(@i AS VARCHAR(255)))
	SET @i = @i + 1
END
GO

CREATE PROCEDURE populateTableCube(@rows INT)
AS
DECLARE @i INT
SET @i = 0
DECLARE @cubeTypeId INT
SET @cubeTypeId = (SELECT TOP 1
	CubeTypeId
FROM CubeType)
DECLARE @personId INT
SET @personId = (SELECT TOP 1
	PId
FROM Person)
WHILE @i < @rows BEGIN
	INSERT INTO Cube
		(CubeId, CubeTypeId, PId, Manufacturer, Model, Options)
	VALUES(@i, @cubeTypeId, @personId, 'Manufacturer' + CAST(@i AS VARCHAR(255)), 'Model' + CAST(@i AS VARCHAR(255)), 'Options' + CAST(@i AS VARCHAR(255)))
	SET @i = @i + 1
END
GO

-- a view with a SELECT statement operating on one table: ClubView
CREATE VIEW ClubView
AS
	SELECT *
	FROM Club
GO

-- a view with a SELECT statement that operates on at least 2 different tables and contains at least one JOIN operator: Person and Cube joined on PId
CREATE VIEW PersonCubeView
AS
	SELECT p.FirstName, p.LastName, c.Model
	FROM Person p JOIN Cube c ON p.PId = c.PId
GO

-- a view with a SELECT statement that has a GROUP BY clause, operates on at least 2 different tables and contains at least one JOIN operator: Person and Cube joined on PId, grouped by the last digit of the day of birth
CREATE VIEW PersonCubeGroupedView
AS
	SELECT p.FirstName, p.LastName, c.Model,
		RIGHT(CAST(DAY(p.DateOfBirth) AS VARCHAR(2)), 1) AS DayOfBirth
	FROM Person p JOIN Cube c ON p.PId = c.PId
	GROUP BY RIGHT(CAST(DAY(p.DateOfBirth) AS VARCHAR(2)), 1), p.FirstName, p.LastName, c.Model
GO

-- delete procedure populateTable if exists
IF EXISTS (SELECT *
FROM INFORMATION_SCHEMA.ROUTINES
WHERE ROUTINE_NAME = 'populateTable') BEGIN
	EXEC ('DROP PROCEDURE populateTable')
END
GO

-- create procedure to poplate tables, generally
CREATE PROCEDURE populateTable(@tableName VARCHAR(255), @rows INT)
AS
IF @tableName NOT IN (SELECT Name
FROM Tables) BEGIN
	PRINT 'Table not in Tables'
	RETURN
END
DECLARE @i INT
SET @i = 0


PRINT 'Populating table ' + @tableName + ' with ' + CAST(@rows AS VARCHAR(255)) + ' rows'

-- -- get the columns of the table
DECLARE @columns TABLE (
	ColumnName VARCHAR(255),
	DataType VARCHAR(255),
	OrdinalPosition INT
)


INSERT INTO @columns
SELECT COLUMN_NAME, DATA_TYPE, ORDINAL_POSITION
FROM INFORMATION_SCHEMA.COLUMNS
WHERE TABLE_NAME = @tableName

DECLARE @columnsCount INT
SET @columnsCount = (SELECT COUNT(*) FROM @columns)

-- generate the insert statement
DECLARE @insertStatement VARCHAR(MAX)
DECLARE @columnIndex INT

WHILE @rows > 0
BEGIN
SET @columnIndex = 1
SET @insertStatement = 'INSERT INTO ' + @tableName + ' VALUES ('

WHILE @columnIndex <= @columnsCount BEGIN
	-- depending on the column type, generate a value
	
	IF (SELECT DataType FROM @columns WHERE OrdinalPosition = @columnIndex) = 'int' BEGIN
		SET @insertStatement = @insertStatement + CAST(@rows AS VARCHAR(255))
	END

	IF (SELECT DataType FROM @columns WHERE OrdinalPosition = @columnIndex) = 'varchar' BEGIN
		SET @insertStatement = @insertStatement + '''' + (SELECT ColumnName FROM @columns WHERE OrdinalPosition = @columnIndex) + CAST(@rows AS VARCHAR(255)) + ''''
	END

	IF (SELECT DataType FROM @columns WHERE OrdinalPosition = @columnIndex) = 'date' BEGIN
		SET @insertStatement = @insertStatement + 'DATEADD(DAY, ' + CAST(@rows AS VARCHAR(255)) + ', ''2018-01-01'')'
	END

	-- if not the last column, add a comma
	IF @columnIndex < @columnsCount BEGIN
		SET @insertStatement = @insertStatement + ', '
	END

	SET @columnIndex = @columnIndex + 1
	END
	SET @insertStatement = @insertStatement + ')'
	SET @rows = @rows - 1
	-- execute the insert statement
	-- PRINT @insertStatement
	EXEC (@insertStatement)
END

GO

DELETE FROM isTrainerOf
DELETE FROM Cube
DELETE FROM Person
DELETE FROM Trainer
DELETE FROM CubeType
DELETE FROM Club
GO



EXEC addToTables 'Club'
-- EXEC addToTables 'Person'
-- EXEC addToTables 'Trainer'
-- EXEC addToTables 'isTrainerOf'
-- EXEC addToTables 'Cube'
-- EXEC addToTables 'CubeType'
-- EXEC addToViews 'ClubView'
-- EXEC addToViews 'PersonCubeView'
-- EXEC addToViews 'PersonCubeGroupedView'
EXEC addToTests 'MainTest'
-- EXEC connectTableToTest 'isTrainerOf', 'MainTest', 100, 1
-- EXEC connectTableToTest 'Cube', 'MainTest', 100, 2
-- EXEC connectTableToTest 'Person', 'MainTest', 100, 3
-- EXEC connectTableToTest 'Trainer', 'MainTest', 100, 4
-- EXEC connectTableToTest 'CubeType', 'MainTest', 100, 5
EXEC connectTableToTest 'Club', 'MainTest', 100, 6
-- EXEC connectViewToTest 'ClubView', 'MainTest'
-- EXEC connectViewToTest 'PersonCubeView', 'MainTest'
-- EXEC connectViewToTest 'PersonCubeGroupedView', 'MainTest'
EXEC runTest 'MainTest', 'Test1'
GO