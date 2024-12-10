-- Create a database for the Spotify application. The entities of interest to the problem domain are:
-- Songs, Artists, Accounts and Playlists. 
-- Each song has a name, duration in minutes and release date. Duration must be greater than 0 and lower than 20. 
-- An artist has a name, country of origin and date of birth. 
-- Each song can have one main artist and multiple featuring artists. An account has a username and email address. Usernames must be unique.
--  Both artists and users (accounts) can create playlists. One playlist contains multiple songs and has a name.

USE PRACTICAL;
GO


DROP TABLE PlaylistSongs;
DROP TABLE Playlists;
DROP TABLE Accounts;
DROP TABLE FeaturedArtists;
DROP TABLE Songs;
DROP TABLE Artists;
GO

-- 1. Write a SQL script that creates the corresponding relational data model.
CREATE TABLE Artists (
    ArtistID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Country VARCHAR(100) NOT NULL,
    DateOfBirth DATE
);
GO

CREATE TABLE Songs (
    SongID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Duration DECIMAL(4,2) CHECK (Duration > 0 AND Duration < 20),
    ReleaseDate DATE,
    MainArtistID INT,
    FOREIGN KEY (MainArtistID) REFERENCES Artists(ArtistID)
);
GO

CREATE TABLE FeaturedArtists (
    SongID INT,
    ArtistID INT,
    PRIMARY KEY (SongID, ArtistID),
    FOREIGN KEY (SongID) REFERENCES Songs(SongID),
    FOREIGN KEY (ArtistID) REFERENCES Artists(ArtistID)
);
GO

CREATE TABLE Accounts (
    AccountID INT PRIMARY KEY,
    Username VARCHAR(50) UNIQUE NOT NULL,
    Email VARCHAR(255) NOT NULL
);
GO

CREATE TABLE Playlists (
    PlaylistID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    ArtistID INT,
    FOREIGN KEY (ArtistID) REFERENCES Artists(ArtistID), -- Assuming both Artists and Accounts can create playlists
    AccountID INT, 
    FOREIGN KEY (AccountID) REFERENCES Accounts(AccountID)
);
GO

CREATE TABLE PlaylistSongs (
    PlaylistID INT,
    SongID INT,
    PRIMARY KEY (PlaylistID, SongID),
    FOREIGN KEY (PlaylistID) REFERENCES Playlists(PlaylistID),
    FOREIGN KEY (SongID) REFERENCES Songs(SongID)
);
GO

INSERT INTO Artists (ArtistID, Name, Country, DateOfBirth) VALUES
    (1, 'John Artist', 'USA', '1990-05-15'),
    (2, 'Maria Singer', 'UK', '1985-02-20'),
    (3, 'Carlos Musician', 'Spain', '1988-09-10');

-- Inserting data into Songs table
INSERT INTO Songs (SongID, Name, Duration, ReleaseDate, MainArtistID) VALUES
    (1, 'Song1', 3, '2022-01-01', 1),
    (2, 'Song2', 4, '2022-02-15', 2),
    (3, 'Song3', 5, '2022-03-20', 3);

-- Inserting data into FeaturedArtists table
INSERT INTO FeaturedArtists (SongID, ArtistID) VALUES
    (1, 2),
    (2, 1),
    (3, 1),
    (3, 2);

-- Inserting data into Accounts table
INSERT INTO Accounts (AccountID, Username, Email) VALUES
    (1, 'user1', 'user1@email.com'),
    (2, 'user2', 'user2@email.com');

-- Inserting data into Playlists table
INSERT INTO Playlists (PlaylistID, Name, ArtistID, AccountID) VALUES
    (1, 'Playlist1', 1, NULL),
    (2, 'Playlist2', 2, NULL),
    (3, 'Playlist2', NULL, 1),
    (4, 'Playlist2', NULL, 2);

-- Inserting data into PlaylistSongs table
INSERT INTO PlaylistSongs (PlaylistID, SongID) VALUES
    (1, 1),
    (1, 2),
    (2, 3);
GO
-- 2. Implement a stored procedure that receives details of an account and stores the account in the database.

DROP PROCEDURE IF EXISTS AddAccount;
GO

CREATE PROCEDURE AddAccount (
    @AccountID INT,
    @Username VARCHAR(50),
    @Email VARCHAR(255)
)
AS
BEGIN
    INSERT INTO Accounts (AccountID, Username, Email)
    VALUES (@AccountID, @Username, @Email);
END;
GO

EXEC AddAccount 6, 'user3', 'user3@gmail.com';
GO

-- 3. Create a view that shows the names of the playlists that contain the most songs.
DROP VIEW IF EXISTS MostSongsPlaylists;
GO

CREATE VIEW MostSongsPlaylists AS
    SELECT TOP 1 Playlists.Name, COUNT(PlaylistSongs.SongID) AS NumberOfSongs
    FROM Playlists
    JOIN PlaylistSongs ON Playlists.PlaylistID = PlaylistSongs.PlaylistID
    GROUP BY Playlists.PlaylistID, Playlists.Name
    ORDER BY NumberOfSongs DESC;
GO

SELECT * FROM MostSongsPlaylists;

-- 4. Implement a function that returns the number of artists that have created more than R playlists that have a total duration greater than T, where R and T are function parameters.
DROP FUNCTION IF EXISTS GetArtists;
GO

CREATE FUNCTION GetArtists (
    @R INT,
    @T INT
)
RETURNS INT
AS
BEGIN
    DECLARE @NumberOfArtists INT;
    
    SELECT @NumberOfArtists = COUNT(DISTINCT Artists.ArtistID)
    FROM Artists
    JOIN Playlists ON Artists.ArtistID = Playlists.ArtistID
    JOIN PlaylistSongs ON Playlists.PlaylistID = PlaylistSongs.PlaylistID
    JOIN Songs ON PlaylistSongs.SongID = Songs.SongID
    GROUP BY Artists.ArtistID
    HAVING COUNT(DISTINCT Playlists.PlaylistID) > @R AND SUM(Songs.Duration) > @T;

    RETURN @NumberOfArtists;
END;
GO

-- Testing the GetArtists function
DECLARE @Result INT;
EXEC @Result = GetArtists @R = 1, @T = 1;
PRINT(@Result);

