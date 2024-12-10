USE Speedcubing;
DROP PROCEDURE IF EXISTS changeTimedSolutionDNFTypeInt
DROP PROCEDURE IF EXISTS changeTimedSolutionDNFTypeBit
DROP PROCEDURE IF EXISTS removeCubeDescription
DROP PROCEDURE IF EXISTS addCubeDescription
DROP PROCEDURE IF EXISTS addTimedSolutionDNFDefault
DROP PROCEDURE IF EXISTS removeTimedSolutionDNFDefault
DROP PROCEDURE IF EXISTS addCubeIdPrimary
DROP PROCEDURE IF EXISTS removeCubeIdPrimary
DROP PROCEDURE IF EXISTS addSessionIdCandidate
DROP PROCEDURE IF EXISTS removeSessionIdCandidate
DROP PROCEDURE IF EXISTS addClubIdForeign
DROP PROCEDURE IF EXISTS removeClubIdForeign
DROP PROCEDURE IF EXISTS goToVersion
DROP PROCEDURE IF EXISTS addPrimaryKeyToCubeManufacturer
DROP PROCEDURE IF EXISTS removePrimaryKeyFromCubeManufacturer
DROP PROCEDURE IF EXISTS createTables
DROP PROCEDURE IF EXISTS dropTables
DROP PROCEDURE IF EXISTS createCubeManufacturer
DROP PROCEDURE IF EXISTS dropCubeManufacturer
DROP TABLE IF EXISTS PROCEDURES_TABLE
GO

-- a. modify the type of a column;
-- create procedure to change the type of DNF for timedSolution from bit to int
CREATE PROCEDURE changeTimedSolutionDNFTypeInt AS
    -- the constraint is dropped because it is not possible to change the type of a column with a constraint
    ALTER TABLE timedSolution DROP CONSTRAINT DNF;
    -- the column is changed
    ALTER TABLE timedSolution ALTER COLUMN DNF int;
    -- the constraint is added again, DNF can only be 0
    ALTER TABLE timedSolution ADD CONSTRAINT DNF CHECK (DNF = 0);
GO

-- create procedure to change the type of DNF for timedSolution from int to bit
CREATE PROCEDURE changeTimedSolutionDNFTypeBit AS
    -- the constraint is dropped because it is not possible to change the type of a column with a constraint
    ALTER TABLE timedSolution DROP CONSTRAINT DNF;
    -- the column is changed
    ALTER TABLE timedSolution ALTER COLUMN DNF bit;
    -- the constraint is added again, DNF can only be 0
    ALTER TABLE timedSolution ADD CONSTRAINT DNF CHECK (DNF = 0);
GO
-- b. add / remove a column;
-- create procedure to remove the description column from the cube type, if it exists
CREATE PROCEDURE removeCubeDescription AS
    IF EXISTS (SELECT * FROM sys.columns WHERE Name = N'description' AND Object_ID = Object_ID(N'cube'))
        ALTER TABLE cube DROP COLUMN description;
GO
-- create procedure to add a description column to the cube type, if it does not exist
CREATE PROCEDURE addCubeDescription AS
    IF NOT EXISTS (SELECT * FROM sys.columns WHERE Name = N'description' AND Object_ID = Object_ID(N'cube'))
        ALTER TABLE cube ADD description varchar(255);
GO

-- c. add / remove a DEFAULT constraint;
-- create procedure to add a default value of 0 to the DNF column of the timedSolution type
CREATE PROCEDURE addTimedSolutionDNFDefault AS
    ALTER TABLE timedSolution ADD CONSTRAINT DNF DEFAULT 0 FOR DNF;
GO

-- create procedure to remove the default value of 0 from the DNF column of the timedSolution type
CREATE PROCEDURE removeTimedSolutionDNFDefault AS
    ALTER TABLE timedSolution DROP CONSTRAINT DNF;
GO

-- d. add / remove a primary key;
-- create a new table that represents cube manufactureres, without a primary key
CREATE PROCEDURE createCubeManufacturer AS
    CREATE TABLE cubeManufacturer(
        cubeManufacturerId int NOT NULL,
        name varchar(255)
    );
GO

CREATE PROCEDURE dropCubeManufacturer AS
    DROP TABLE IF EXISTS cubeManufacturer;
GO

-- create procedure to add to the cubeManufacturer the primary key as the cubeManufacturerId
CREATE PROCEDURE addPrimaryKeyToCubeManufacturer AS
    ALTER TABLE cubeManufacturer ADD CONSTRAINT cubeManufacturerId PRIMARY KEY (cubeManufacturerId);
GO

-- create procedure to remove from the cubeManufacturer the primary key as the cubeManufacturerId
CREATE PROCEDURE removePrimaryKeyFromCubeManufacturer AS
    ALTER TABLE cubeManufacturer DROP CONSTRAINT cubeManufacturerId;
GO

-- e. add / remove a candidate key;
-- create procedure to add to the timedSolution the session id as a candidate key
CREATE PROCEDURE addSessionIdCandidate AS
    ALTER TABLE timedSolution ADD CONSTRAINT sessionIdCandidate UNIQUE (SId);
GO

-- create procedure to remove from the timedSolution the session id as a candidate key
CREATE PROCEDURE removeSessionIdCandidate AS
    ALTER TABLE timedSolution DROP CONSTRAINT sessionIdCandidate;
GO
-- f. add / remove a foreign key;
-- create procedure to add to the trainer the foreign key as the clubId
CREATE PROCEDURE addClubIdForeign AS
    ALTER TABLE trainer ADD CONSTRAINT clubId FOREIGN KEY (clubId) REFERENCES club(clubId);
GO

-- create procedure to remove from the trainer the foreign key as the clubId
CREATE PROCEDURE removeClubIdForeign AS
    ALTER TABLE trainer DROP CONSTRAINT clubId;
GO

-- g. create / drop a table.
-- create procedure to create VERSION_TABLE and PROCEDURES_TABLE
CREATE PROCEDURE createTables AS
    CREATE TABLE VERSION_TABLE(
        version int,
        PRIMARY KEY(version)
    );
    INSERT INTO VERSION_TABLE VALUES(0);
    GO
-- create procedure to drop VERSION_TABLE and PROCEDURES_TABLE
CREATE PROCEDURE dropTables AS
    DROP TABLE IF EXISTS VERSION_TABLE;
    DROP TABLE IF EXISTS PROCEDURES_TABLE;
GO


CREATE TABLE PROCEDURES_TABLE(
	fromVersion INT,
	toVersion INT,
	nameProc VARCHAR(255),
	PRIMARY KEY(fromVersion, toVersion)
);
GO

INSERT INTO PROCEDURES_TABLE VALUES(0, 1, 'addTimedSolutionDNFDefault');
INSERT INTO PROCEDURES_TABLE VALUES(1, 2, 'addCubeDescription');
INSERT INTO PROCEDURES_TABLE VALUES(2, 3, 'changeTimedSolutionDNFTypeInt');
INSERT INTO PROCEDURES_TABLE VALUES(3, 4, 'createCubeManufacturer');
INSERT INTO PROCEDURES_TABLE VALUES(4, 5, 'addPrimaryKeyToCubeManufacturer');
INSERT INTO PROCEDURES_TABLE VALUES(5, 6, 'addSessionIdCandidate');
INSERT INTO PROCEDURES_TABLE VALUES(6, 7, 'addClubIdForeign');
INSERT INTO PROCEDURES_TABLE VALUES(7, 6, 'removeClubIdForeign');
INSERT INTO PROCEDURES_TABLE VALUES(6, 5, 'removeSessionIdCandidate');
INSERT INTO PROCEDURES_TABLE VALUES(5, 4, 'removePrimaryKeyFromCubeManufacturer');
INSERT INTO PROCEDURES_TABLE VALUES(4, 3, 'dropCubeManufacturer');
INSERT INTO PROCEDURES_TABLE VALUES(3, 2, 'changeTimedSolutionDNFTypeBit');
INSERT INTO PROCEDURES_TABLE VALUES(2, 1, 'removeCubeDescription');
INSERT INTO PROCEDURES_TABLE VALUES(1, 0, 'removeTimedSolutionDNFDefault');
GO

CREATE PROCEDURE goToVersion(@newVersion INT) AS
    BEGIN
        DECLARE @currentVersion INT;
        DECLARE @procName VARCHAR(255);

        SELECT @currentVersion=version FROM VERSION_TABLE

        IF @newVersion > (SELECT MAX(toVersion) FROM PROCEDURES_TABLE)
            RAISERROR('Invalid version', 16, 1);
        
        IF @newVersion < (SELECT MIN(fromVersion) FROM PROCEDURES_TABLE)
            RAISERROR('Invalid version', 16, 1);

        WHILE @currentVersion < @newVersion BEGIN
            SELECT @procName = nameProc FROM PROCEDURES_TABLE WHERE fromVersion = @currentVersion AND toVersion = @currentVersion + 1;

            EXEC (@procName);

            SET @currentVersion = @currentVersion + 1;
            UPDATE VERSION_TABLE SET version = @currentVersion;
        END;
            
        WHILE @currentVersion > @newVersion BEGIN
            SELECT @procName = nameProc FROM PROCEDURES_TABLE WHERE fromVersion = @currentVersion AND toVersion = @currentVersion - 1;

            EXEC (@procName);

            SET @currentVersion = @currentVersion - 1;
            UPDATE VERSION_TABLE SET version = @currentVersion;
        END;
    END;
GO
EXEC createTables;
GO

EXEC goToVersion 0;
GO

select * from sys.objects where type = 'PK'
