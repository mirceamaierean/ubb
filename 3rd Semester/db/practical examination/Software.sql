-- Create a database to manage software developments companies. The database will store data about the software
-- development process. The entities of interest to the problem domain are: Clients, Company, Department,
-- Employees. A client has a name and a project, also each client can work with multiple companies. A company has a
-- name and a list of clients. A company has multiple departments. Each department has a type (Web, Automotive,
-- Mobile, loT) and a name Multiple employees are working for the same department. An employee can work only
-- for one department. Each employee has a name and a title (Teste, Developer, Manager).
-- 2p A.
-- Write an SQL script that creates the corresponding relational data model.
-- P. Implement a stored procedure that receives a client and returns the name of the company working on his
-- project and all the names and titles of the employees actively working on the project in question.
-- Create a view that shows the list of the clients of a company and the departments names working on those
-- projects.
-- 4. Implement a function that lists the names of the clients which are working with multiple companies and also
-- the names of the employees working on those projects.

-- Clients table
-- Companies table
CREATE TABLE Companies (
    CompanyID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(100)
);

CREATE TABLE Clients (
    ClientID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(100),
    Project NVARCHAR(100),
    CompanyID INT FOREIGN KEY REFERENCES Companies(CompanyID)
);


-- Departments table
CREATE TABLE Departments (
    DepartmentID INT PRIMARY KEY IDENTITY(1,1),
    Type NVARCHAR(50),
    Name NVARCHAR(100),
    CompanyID INT FOREIGN KEY REFERENCES Companies(CompanyID)
);

-- Employees table
CREATE TABLE Employees (
    EmployeeID INT PRIMARY KEY IDENTITY(1,1),
    Name NVARCHAR(100),
    Title NVARCHAR(50),
    DepartmentID INT FOREIGN KEY REFERENCES Departments(DepartmentID)
);
GO

-- 2p B. Implement a stored procedure
CREATE PROCEDURE GetProjectDetails(@ClientName NVARCHAR(100))
AS
BEGIN
    SELECT
        C.Name AS CompanyName,
        E.Name AS EmployeeName,
        E.Title
    FROM Clients CL
    INNER JOIN Companies C ON CL.CompanyID = C.CompanyID
    INNER JOIN Departments D ON C.CompanyID = D.CompanyID
    INNER JOIN Employees E ON D.DepartmentID = E.DepartmentID
    WHERE CL.Name = @ClientName;
END;
GO

-- 3. Create a view
CREATE VIEW CompanyProjectDetails AS
SELECT
    C.Name AS CompanyName,
    CL.Name AS ClientName,
    D.Name AS DepartmentName
FROM Companies C
INNER JOIN Clients CL ON C.CompanyID = CL.CompanyID
INNER JOIN Departments D ON C.CompanyID = D.CompanyID;
GO

-- 4. Implement a function
CREATE FUNCTION GetClientsWithMultipleCompanies()
RETURNS TABLE
AS
RETURN (
    SELECT
        CL.Name AS ClientName,
        E.Name AS EmployeeName
    FROM Clients CL
    INNER JOIN Companies C ON CL.CompanyID = C.CompanyID
    INNER JOIN Departments D ON C.CompanyID = D.CompanyID
    INNER JOIN Employees E ON D.DepartmentID = E.DepartmentID
    GROUP BY CL.Name, E.Name
    HAVING COUNT(DISTINCT C.CompanyID) > 1
);
GO