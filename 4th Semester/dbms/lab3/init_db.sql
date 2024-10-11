drop table if exists StudentCourses;
drop table if exists Students;
drop table if exists Courses;
drop table if exists ActionLogs;
drop table if exists LockLogs;
drop procedure if exists sp_log_changes;


CREATE TABLE Students (
    StudentID INT PRIMARY KEY IDENTITY,
    StudentName NVARCHAR(100) NOT NULL
);

CREATE TABLE Courses (
    CourseID INT PRIMARY KEY IDENTITY,
    CourseName NVARCHAR(200) NOT NULL
);

CREATE TABLE StudentCourses (
    StudentID INT,
    CourseID INT,
    PRIMARY KEY (StudentID, CourseID),
    FOREIGN KEY (StudentID) REFERENCES Students(StudentID),
    FOREIGN KEY (CourseID) REFERENCES Courses(CourseID)
);

CREATE TABLE ActionLogs (
    LogID INT PRIMARY KEY IDENTITY,
    OldData NVARCHAR(100),
    NewData NVARCHAR(100),
    Action NVARCHAR(100),
    LogDate DATETIME DEFAULT GETDATE()
);
GO

CREATE OR ALTER PROCEDURE sp_log_changes
    @OldData NVARCHAR(100),
    @NewData NVARCHAR(100),
    @Action NVARCHAR(100)
AS
BEGIN
    INSERT INTO ActionLogs (OldData, NewData, Action)
    VALUES (@OldData, @NewData, @Action);
END;
GO

-- Insert data into Courses table
INSERT INTO Courses (CourseName) VALUES ('Mathematics 101');
INSERT INTO Courses (CourseName) VALUES ('Physics 101');
INSERT INTO Courses (CourseName) VALUES ('Chemistry 101');

-- Insert data into Students table
INSERT INTO Students (StudentName) VALUES ('John Doe');
INSERT INTO Students (StudentName) VALUES ('Jane Smith');
INSERT INTO Students (StudentName) VALUES ('Alice Johnson');
INSERT INTO Students (StudentName) VALUES ('Bob Brown');

-- Insert data into StudentCourses table
INSERT INTO StudentCourses (StudentID, CourseID) VALUES (1, 1);
INSERT INTO StudentCourses (StudentID, CourseID) VALUES (2, 2);
INSERT INTO StudentCourses (StudentID, CourseID) VALUES (3, 3);
INSERT INTO StudentCourses (StudentID, CourseID) VALUES (4, 1);
INSERT INTO StudentCourses (StudentID, CourseID) VALUES (1, 2);
INSERT INTO StudentCourses (StudentID, CourseID) VALUES (2, 3);

