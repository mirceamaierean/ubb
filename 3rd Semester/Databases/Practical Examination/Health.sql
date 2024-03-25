-- Create a database for a health tracking system. The entities of interest to the problem domain are:
-- Users, Activities, Meals, Health Metrics and User Activities Journal. 
-- A user has a name, an age and a gender. Names are unique. 
-- An activity has a name and a number of calories burned per hour. Names are unique. 
-- A meal has a name and a number of calories per serving. Names are unique. 
-- The system stores data about health metrics: user, date of recording, weight, blood pressure and heart rate. 
-- Users can perform multiple activities. The system will store the date when the activity was performed and the duration (in minutes).
-- 2. Implement a stored procedure that receives the details of a health metric and adds the metric
-- in the database. If the date of recording is in the future (e.g. today is 05-01-2024 and the date of
-- recording for the health metric is 06-01-2024), the system will display an error message and it
-- will not save the health metric in the database.
-- 3. Create a view that displays the average weight and the maximum blood pressure for each user
-- based on the data recorded during the last year (2023).
-- 4. Implement a function that returns the average duration of a specific activity A for a given user
-- U, where A and U are function parameters.

USE PRACTICAL;
GO
-- 1. Write an SQL script that creates the corresponding relational data model.

-- Drop tables if they exist
IF OBJECT_ID('Users', 'U') IS NOT NULL DROP TABLE Users;
IF OBJECT_ID('Activities', 'U') IS NOT NULL DROP TABLE Activities;
IF OBJECT_ID('Meals', 'U') IS NOT NULL DROP TABLE Meals;
IF OBJECT_ID('HealthMetrics', 'U') IS NOT NULL DROP TABLE HealthMetrics;
IF OBJECT_ID('UserActivitiesJournal', 'U') IS NOT NULL DROP TABLE UserActivitiesJournal;
GO

-- Create tables
CREATE TABLE Users (
    UserID INT PRIMARY KEY,
    Name VARCHAR(255) UNIQUE NOT NULL,
    Age INT,
    Gender VARCHAR(10)
);

CREATE TABLE Activities (
    ActivityID INT PRIMARY KEY,
    Name VARCHAR(255) UNIQUE NOT NULL,
    CaloriesPerHour INT
);

CREATE TABLE Meals (
    MealID INT PRIMARY KEY,
    Name VARCHAR(255) UNIQUE NOT NULL,
    CaloriesPerServing INT
);

CREATE TABLE HealthMetrics (
    MetricID INT PRIMARY KEY,
    UserID INT,
    DateOfRecording DATE,
    Weight DECIMAL(5,2),
    BloodPressure VARCHAR(10),
    HeartRate INT,
    FOREIGN KEY (UserID) REFERENCES Users(UserID)
);

CREATE TABLE UserActivitiesJournal (
    JournalID INT PRIMARY KEY,
    UserID INT,
    ActivityID INT,
    DatePerformed DATE,
    DurationMinutes INT,
    FOREIGN KEY (UserID) REFERENCES Users(UserID),
    FOREIGN KEY (ActivityID) REFERENCES Activities(ActivityID)
);
GO

-- Inserting data into Users table
INSERT INTO Users (UserID, Name, Age, Gender) VALUES
    (1, 'John Doe', 30, 'Male'),
    (2, 'Jane Smith', 25, 'Female');

-- Inserting data into Activities table
INSERT INTO Activities (ActivityID, Name, CaloriesPerHour) VALUES
    (1, 'Running', 500),
    (2, 'Cycling', 300),
    (3, 'Swimming', 400);

-- Inserting data into Meals table
INSERT INTO Meals (MealID, Name, CaloriesPerServing) VALUES
    (1, 'Chicken Salad', 350),
    (2, 'Vegetable Stir Fry', 250),
    (3, 'Salmon with Quinoa', 400);

-- Inserting data into HealthMetrics table
INSERT INTO HealthMetrics (MetricID, UserID, DateOfRecording, Weight, BloodPressure, HeartRate) VALUES
    (1, 1, '2024-01-15', 75.0, '120/80', 72),
    (2, 1, '2024-02-01', 74.5, '118/78', 70),
    (3, 2, '2024-01-20', 62.5, '110/75', 65),
    (4, 2, '2024-02-05', 63.0, '112/76', 68);

-- Inserting data into UserActivitiesJournal table
INSERT INTO UserActivitiesJournal (JournalID, UserID, ActivityID, DatePerformed, DurationMinutes) VALUES
    (1, 1, 1, '2024-01-16', 45),
    (2, 1, 2, '2024-01-17', 30),
    (3, 2, 3, '2024-01-21', 60),
    (4, 2, 1, '2024-02-06', 40);


-- 2. Implement a stored procedure that receives the details of a health metric and adds the metric
-- in the database. If the date of recording is in the future, display an error message.
DROP PROCEDURE IF EXISTS AddHealthMetric;
GO

CREATE PROCEDURE AddHealthMetric (
    @HMID INT,
    @UserID INT,
    @DateOfRecording DATE,
    @Weight DECIMAL(5,2),
    @BloodPressure VARCHAR(10),
    @HeartRate INT
)
AS
BEGIN
    IF @DateOfRecording > GETDATE()
    BEGIN
        PRINT 'Error: Cannot record health metric in the future.';
        RETURN;
    END

    INSERT INTO HealthMetrics (MetricID, UserID, DateOfRecording, Weight, BloodPressure, HeartRate)
    VALUES (@HMID, @UserID, @DateOfRecording, @Weight, @BloodPressure, @HeartRate);
END;
GO

-- Example usage of the stored procedure
EXEC AddHealthMetric @HMID = 20, @UserID = 1, @DateOfRecording = '2024-01-15', @Weight = 70.5, @BloodPressure = '120/80', @HeartRate = 75;
EXEC AddHealthMetric @HMID = 30, @UserID = 2, @DateOfRecording = '2024-02-01', @Weight = 65.2, @BloodPressure = '110/75', @HeartRate = 80;
GO

-- 3. Create a view that displays the average weight and the maximum blood pressure for each user
-- based on the data recorded during the last year (2023).
CREATE VIEW UserHealthSummary AS
SELECT
    UserID,
    AVG(Weight) AS AverageWeight,
    MAX(CONVERT(INT, LEFT(BloodPressure, CHARINDEX('/', BloodPressure)-1))) AS MaxSystolicBP,
    MAX(CONVERT(INT, SUBSTRING(BloodPressure, CHARINDEX('/', BloodPressure)+1, LEN(BloodPressure)))) AS MaxDiastolicBP
FROM HealthMetrics
WHERE DateOfRecording BETWEEN '2023-01-01' AND '2023-12-31'
GROUP BY UserID;
GO

SELECT * FROM UserHealthSummary;
GO

-- 4 Implement a function that returns the average duration of a specific activity A for a given user U.
CREATE FUNCTION GetAverageActivityDuration (
    @UserID INT,
    @ActivityID INT
)
RETURNS DECIMAL(8, 2)
AS
BEGIN
    DECLARE @AvgDuration DECIMAL(8, 2);

    SELECT @AvgDuration = AVG(DurationMinutes)
    FROM UserActivitiesJournal
    WHERE UserID = @UserID AND ActivityID = @ActivityID;

    RETURN @AvgDuration;
END;
GO

-- Example: Call the GetAverageActivityDuration function
DECLARE @AverageDuration DECIMAL(8, 2);

-- Specify the user ID and activity ID for which you want to get the average duration
DECLARE @UserID INT = 1; -- Replace with the desired user ID
DECLARE @ActivityID INT = 1; -- Replace with the desired activity ID

-- Call the function and store the result in the variable @AverageDuration
SELECT @AverageDuration = dbo.GetAverageActivityDuration(@UserID, @ActivityID);

-- Display the result
PRINT 'Average Duration for User ' + CAST(@UserID AS VARCHAR) +
      ' and Activity ' + CAST(@ActivityID AS VARCHAR) +
      ': ' + CAST(@AverageDuration AS VARCHAR);