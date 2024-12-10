-- Create a database for managing the 2023 Rugby World Cup. The entities of interest to the problem
-- domain are: Cities, Stadiums, National Teams, Players, Coaches and Games. Cities have a name.
-- Names must be unique. Stadiums have a name and belong to a city. National teams belong to a
-- country and have a list of players and a list of coaches. There can be only one national team per
-- country. Players have a name, birth date, nationality, position and a flag indicating if the player is
-- captain. Coaches have a name and nationality. The system stores information about all the games
-- played during the World Cup: the date, the two teams involved, stadium, final score, winner and a
-- flag indicating if the final score was decided in overtime.
-- 1. Write a SQL script that creates the corresponding relational data model.
-- 2. Implement a stored procedure that receives the details of a game and stores the game in the
-- database. If the two teams already played against each other on the same date, then the final score is
-- updated.
-- 3. Create a view that shows the names of the stadiums where all games played were decided in
-- overtime.
-- 4. Implement a function that returns the number of teams that won all the games played on a
-- stadium S with a score difference greater than R. where S and R are function parameters.

-- 1. Create the corresponding relational data model
CREATE DATABASE RugbyWorldCup;

USE RugbyWorldCup;

-- Cities table
CREATE TABLE Cities (
    CityID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(100) UNIQUE
);

-- Stadiums table
CREATE TABLE Stadiums (
    StadiumID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(100),
    CityID INT FOREIGN KEY REFERENCES Cities(CityID)
);

-- National Teams table
CREATE TABLE NationalTeams (
    NationalTeamID INT PRIMARY KEY IDENTITY(1,1),
    Country NVARCHAR(100) UNIQUE
);

-- Players table
CREATE TABLE Players (
    PlayerID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(100),
    BirthDate DATE,
    Nationality NVARCHAR(100),
    Position NVARCHAR(50),
    IsCaptain BIT,
    NationalTeamID INT FOREIGN KEY REFERENCES NationalTeams(NationalTeamID)
);

-- Coaches table
CREATE TABLE Coaches (
    CoachID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(100),
    Nationality NVARCHAR(100),
    NationalTeamID INT FOREIGN KEY REFERENCES NationalTeams(NationalTeamID)
);

-- Games table
CREATE TABLE Games (
    GameID INT PRIMARY KEY IDENTITY(1,1),
    Date DATE,
    Team1ID INT FOREIGN KEY REFERENCES NationalTeams(NationalTeamID),
    Team2ID INT FOREIGN KEY REFERENCES NationalTeams(NationalTeamID),
    StadiumID INT FOREIGN KEY REFERENCES Stadiums(StadiumID),
    FinalScore NVARCHAR(20),
    Winner INT FOREIGN KEY REFERENCES NationalTeams(NationalTeamID),
    Overtime BIT
);
GO

-- 2. Implement a stored procedure
CREATE PROCEDURE AddOrUpdateGame
    @Date DATE,
    @Team1ID INT,
    @Team2ID INT,
    @StadiumID INT,
    @FinalScore NVARCHAR(20),
    @Winner INT,
    @Overtime BIT
AS
BEGIN
    DECLARE @ExistingGameID INT;

    -- Check if the teams already played on the same date
    SELECT @ExistingGameID = GameID
    FROM Games
    WHERE (Team1ID = @Team1ID AND Team2ID = @Team2ID AND Date = @Date)
       OR (Team1ID = @Team2ID AND Team2ID = @Team1ID AND Date = @Date);

    -- If the game exists, update the final score
    IF @ExistingGameID IS NOT NULL
    BEGIN
        UPDATE Games
        SET FinalScore = @FinalScore
        WHERE GameID = @ExistingGameID;
    END
    ELSE -- If the game doesn't exist, insert a new record
    BEGIN
        INSERT INTO Games (Date, Team1ID, Team2ID, StadiumID, FinalScore, Winner, Overtime)
        VALUES (@Date, @Team1ID, @Team2ID, @StadiumID, @FinalScore, @Winner, @Overtime);
    END
END;
GO

-- 3. Create a view
CREATE VIEW OvertimeStadiums AS
SELECT DISTINCT S.Name AS StadiumName
FROM Games G
JOIN Stadiums S ON G.StadiumID = S.StadiumID
WHERE G.Overtime = 1;
GO

-- 4. Implement a function
CREATE FUNCTION CountTeamsWithScoreDifferenceGreaterThanR
    (@StadiumName NVARCHAR(100), @R INT)
RETURNS INT
AS
BEGIN
    DECLARE @Count INT;

    SELECT @Count = COUNT(DISTINCT G.Winner)
    FROM Games G
    JOIN Stadiums S ON G.StadiumID = S.StadiumID
    WHERE S.Name = @StadiumName
      AND ABS(CONVERT(INT, SUBSTRING(G.FinalScore, 1, CHARINDEX('-', G.FinalScore) - 1)) -
              CONVERT(INT, SUBSTRING(G.FinalScore, CHARINDEX('-', G.FinalScore) + 1, LEN(G.FinalScore)))) > @R;

    RETURN @Count;
END;
GO