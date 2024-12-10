-- Create a database to manage services offered by a stock exchange. The database will store data about all the intermediaries involved in trading. 
-- The entities of interest to the problem domain are: Clients, Brokers, StockExchange, Stocks and Bonds. 
-- A client has a name and a unique identification number. 
-- Clients can work with multiple brokers. 
-- A broker has a name and a list of clients. Brokers can work with multiple stock exchanges. 
-- A stock exchange has a list of brokerage companies containing all the brokers the exchange is working with Multiple stocks or bonds can be listed on the same exchange.
--  Both stocks and bonds have a name and the identification number of the client which bought it through a broker.
-- 2. Implement a stored procedure that receives a client and returns all the stocks and bonds names bought
-- by the client and also the name of the brokerage company through which the client made the purchases.
-- 3. Create a view that shows all the stocks bought by the clients from identification numbers of those clients.
-- 4. Implement a function that lists the identification numbers of the clients which are investing in multiple stock exchanges.

-- 1. Write an SQL script that creates the corresponding relational data model.
USE StockExchangeDB;
GO

-- Drop tables if they exist
IF OBJECT_ID('Clients', 'U') IS NOT NULL DROP TABLE Clients;
IF OBJECT_ID('Brokers', 'U') IS NOT NULL DROP TABLE Brokers;
IF OBJECT_ID('StockExchange', 'U') IS NOT NULL DROP TABLE StockExchange;
IF OBJECT_ID('Stocks', 'U') IS NOT NULL DROP TABLE Stocks;
IF OBJECT_ID('Bonds', 'U') IS NOT NULL DROP TABLE Bonds;
GO

-- Create tables
CREATE TABLE Clients (
    ClientID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    UNIQUE (Name)
);

CREATE TABLE Brokers (
    BrokerID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL
);

CREATE TABLE StockExchange (
    ExchangeID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL
);

CREATE TABLE Stocks (
    StockID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    ClientID INT,
    BrokerID INT,
    ExchangeID INT,
    FOREIGN KEY (ClientID) REFERENCES Clients(ClientID),
    FOREIGN KEY (BrokerID) REFERENCES Brokers(BrokerID),
    FOREIGN KEY (ExchangeID) REFERENCES StockExchange(ExchangeID)
);

CREATE TABLE Bonds (
    BondID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    ClientID INT,
    BrokerID INT,
    ExchangeID INT,
    FOREIGN KEY (ClientID) REFERENCES Clients(ClientID),
    FOREIGN KEY (BrokerID) REFERENCES Brokers(BrokerID),
    FOREIGN KEY (ExchangeID) REFERENCES StockExchange(ExchangeID)
);
GO

-- 2. Implement a stored procedure that receives a client and returns all the stocks and bonds names bought
--    by the client and also the name of the brokerage company through which the client made the purchases.
DROP PROCEDURE IF EXISTS GetClientStocksAndBonds;
GO

CREATE PROCEDURE GetClientStocksAndBonds (
    @ClientName VARCHAR(255)
)
AS
BEGIN
    SELECT 
        C.Name AS ClientName,
        S.Name AS StockName,
        B.Name AS BondName,
        B2.Name AS BrokerName
    FROM Clients C
    LEFT JOIN Stocks S ON C.ClientID = S.ClientID
    LEFT JOIN Bonds B ON C.ClientID = B.ClientID
    LEFT JOIN Brokers B2 ON S.BrokerID = B2.BrokerID OR B.BrokerID = B2.BrokerID
    WHERE C.Name = @ClientName;
END;
GO

-- 3. Create a view that shows all the stocks bought by the clients from a specific brokerage company and the
--    identification numbers of those clients.
CREATE VIEW StocksByBrokerView AS
SELECT 
    B.Name AS BrokerName,
    C.ClientID,
    C.Name AS ClientName,
    S.StockID,
    S.Name AS StockName
FROM Clients C
JOIN Stocks S ON C.ClientID = S.ClientID
JOIN Brokers B ON S.BrokerID = B.BrokerID;
GO

-- 4. Implement a function that lists the identification numbers of the clients which are investing in multiple stock exchanges.
DROP FUNCTION IF EXISTS GetClientsInvestingInMultipleExchanges;
GO

CREATE FUNCTION GetClientsInvestingInMultipleExchanges ()
RETURNS TABLE
AS
RETURN
(
    SELECT 
        C.ClientID
    FROM Clients C
    JOIN Stocks S ON C.ClientID = S.ClientID
    GROUP BY C.ClientID
    HAVING COUNT(DISTINCT S.ExchangeID) > 1
);
GO
