-- Create a database to manage services offered by banks. The database will store data about the all the services
-- provided by banks. The entities of interest to the problem domain are: Clients, Banks, BankingServices and
-- InvestingServices. A client has a name and unique identification number, also each client can work with
-- multiple banks. A bank has a list of clients containing the name of the client and the identification number.
-- Also, one bank can offer multiple banking services or multiple investing opportunities. Banking services have a
-- list of clients which chose at least one service of this type, the list is composed only of identification numbers.
-- Investing services contains a list of clients as well, which chose at least one service of this type, but the list is
-- composed of client names.
-- 1. Write an SQL script that creates the corresponding relational data model.
-- 2. Implement a stored procedure that receives a bank and a client, if a client chose the banking services add
-- his identification number into the banking services list, do the same thing if the client chose investing services
-- but this time add his name into the investing services list, in case we have the same name multiple
-- times(investing services list) you may have to add the identification number as well. If a client chooses both
-- services add the necessary data of that client to both lists (based on what was described above).
-- 3. Create a view that shows all the clients which chose both banking and investing services, for each client of
-- that type show the identification number, name and which number the client is on both lists(each list has a
-- specific number of clients, in ascending order).
-- 4. Implement a function that lists the names of the clients which are working with multiple banks and the
-- services used from each bank.

-- 1. Create the corresponding relational data model
CREATE DATABASE BankServices;

CREATE TABLE Clients (
    ClientID INT PRIMARY KEY,
    Name NVARCHAR(100) NOT NULL
);

CREATE TABLE Banks (
    BankID INT PRIMARY KEY,
    Name NVARCHAR(100) NOT NULL
);

CREATE TABLE BankingServices (
    ServiceID INT PRIMARY KEY,
    BankID INT,
    ClientID INT,
    FOREIGN KEY (BankID) REFERENCES Banks(BankID),
    FOREIGN KEY (ClientID) REFERENCES Clients(ClientID)
);

CREATE TABLE InvestingServices (
    ServiceID INT PRIMARY KEY,
    BankID INT,
    ClientName NVARCHAR(100),
    ClientID INT,
    FOREIGN KEY (BankID) REFERENCES Banks(BankID)
);
GO

CREATE PROCEDURE AddClientService
    @BankName NVARCHAR(100),
    @ClientName NVARCHAR(100),
    @ClientID INT
AS
BEGIN
    DECLARE @BankID INT
    SET @BankID = (SELECT BankID FROM Banks WHERE Name = @BankName)

    -- Update BankingServices
    IF @ClientID IS NOT NULL
    BEGIN
        INSERT INTO BankingServices (BankID, ClientID)
        VALUES (@BankID, @ClientID)
    END

    -- Update InvestingServices
    IF @ClientName IS NOT NULL
    BEGIN
        INSERT INTO InvestingServices (BankID, ClientName, ClientID)
        VALUES (@BankID, @ClientName, @ClientID)
    END
END;
GO

CREATE VIEW ClientsWithBothServices AS
SELECT 
    B.ClientID,
    C.Name AS ClientName,
    I.ClientID AS InvestingServiceNumber,
    RANK() OVER (PARTITION BY I.BankID ORDER BY I.ClientID) AS BankingServiceNumber
FROM BankingServices B
JOIN InvestingServices I ON B.ClientID = I.ClientID AND B.BankID = I.BankID
JOIN Clients C ON B.ClientID = C.ClientID;
GO

CREATE FUNCTION GetClientsWithMultipleBanks()
RETURNS TABLE
AS
RETURN
(
    SELECT
        C.Name AS ClientName,
        B.Name AS BankName,
        STRING_AGG('Banking', ', ') WITHIN GROUP (ORDER BY S1.ServiceID) AS ServicesUsed
    FROM Clients C
    JOIN BankingServices S1 ON C.ClientID = S1.ClientID
    JOIN Banks B ON S1.BankID = B.BankID
    GROUP BY C.Name, B.Name
    HAVING COUNT(DISTINCT S1.BankID) > 1
);
GO


