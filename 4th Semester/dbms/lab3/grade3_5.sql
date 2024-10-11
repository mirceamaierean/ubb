CREATE OR ALTER PROCEDURE AddStudent
    @StudentName NVARCHAR(100)
AS
BEGIN
    IF (@StudentName IS NULL)
    BEGIN
        RAISERROR('Student name must not be null', 16, 1);
        RETURN;
    END
    -- Insert student
    INSERT INTO Students (StudentName)
    VALUES (@StudentName);
    DECLARE @StudentID INT;
    SET @StudentID = SCOPE_IDENTITY();
    EXEC sp_log_changes NULL, @StudentName, 'Added row to Students'
END;
GO

CREATE OR ALTER PROCEDURE AddCourse
    @CourseName NVARCHAR(200)
AS
BEGIN
    IF (@CourseName IS NULL)
    BEGIN
        RAISERROR('Course name must not be null', 16, 1);
        RETURN;
    END
    INSERT INTO Courses (CourseName)
    VALUES (@CourseName);
    DECLARE @CourseID INT;
    SET @CourseID = SCOPE_IDENTITY();
    EXEC sp_log_changes NULL, @CourseName, 'Added row to Courses'
END;
GO

CREATE OR ALTER PROCEDURE AddStudentCourse
    @StudentName NVARCHAR(100),
    @CourseName NVARCHAR(200)
AS
BEGIN
    DECLARE @StudentID INT;
    DECLARE @CourseID INT;

    IF (@StudentName IS NULL)
    BEGIN
        RAISERROR('Student name must not be null', 16, 1);
        RETURN;
    END

    IF (@CourseName IS NULL)
    BEGIN
        RAISERROR('Course name must not be null', 16, 1);
        RETURN;
    END

    SET @StudentID = (SELECT StudentID FROM Students WHERE StudentName = @StudentName);
    SET @CourseID = (SELECT CourseID FROM Courses WHERE CourseName = @CourseName);

    IF (@StudentID IS NULL)
    BEGIN
        RAISERROR('Student does not exist', 16, 1);
        RETURN;
    END

    IF (@CourseID IS NULL)
    BEGIN
        RAISERROR('Course does not exist', 16, 1);
        RETURN;
    END

    INSERT INTO StudentCourses (StudentID, CourseID) VALUES (@StudentID, @CourseID);

    DECLARE @newData NVARCHAR(100);
    SET @newData = @StudentName + ' - ' + @CourseName;
    EXEC sp_log_changes NULL, @newData, 'Linked student with course';
END;
GO

CREATE OR ALTER PROCEDURE RollbackScenarioNoFail
AS
BEGIN
    BEGIN TRANSACTION;
    BEGIN TRY
        EXEC AddStudent 'John Doe';
        EXEC AddCourse 'Math 101';
        EXEC AddStudentCourse 'John Doe', 'Math 101';
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
        THROW;
    END CATCH;
END;
GO

CREATE OR ALTER PROCEDURE RollbackScenarioFail
AS
BEGIN
    BEGIN TRANSACTION;
    BEGIN TRY
        EXEC AddStudent 'John Doe';
        EXEC AddCourse 'Math 101';
        EXEC AddStudentCourse 'John Doe', 'Science 101'; -- Intentional failure: course does not exist
        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
        THROW;
    END CATCH;
END;
GO

CREATE OR ALTER PROCEDURE NoRollbackScenarioManyToManyNoFail
AS
BEGIN
    DECLARE @ERRORS INT;
    SET @ERRORS = 0;

    BEGIN TRY
        EXEC AddStudent 'Alice';
    END TRY
    BEGIN CATCH
        SET @ERRORS = @ERRORS + 1;
    END CATCH;

    BEGIN TRY
        EXEC AddCourse 'Physics 101';
    END TRY
    BEGIN CATCH
        SET @ERRORS = @ERRORS + 1;
    END CATCH;

    IF (@ERRORS = 0)
    BEGIN
        BEGIN TRY
            EXEC AddStudentCourse 'Alice', 'Physics 101';
        END TRY
        BEGIN CATCH
        END CATCH;
    END
END;
GO

CREATE OR ALTER PROCEDURE NoRollbackScenarioManyToManyFail
AS
BEGIN
    DECLARE @ERRORS INT;
    SET @ERRORS = 0;

    BEGIN TRY
        EXEC AddStudent 'Bob';
    END TRY
    BEGIN CATCH
        SET @ERRORS = @ERRORS + 1;
    END CATCH;

    BEGIN TRY
        EXEC AddCourse 'Chemistry 101';
    END TRY
    BEGIN CATCH
        SET @ERRORS = @ERRORS + 1;
    END CATCH;

    IF (@ERRORS = 0)
    BEGIN
        BEGIN TRY
            EXEC AddStudentCourse 'Bob', 'Nonexistent Course'; -- Intentional failure: course does not exist
        END TRY
        BEGIN CATCH
        END CATCH;
    END
END;
GO

EXEC RollbackScenarioFail;
EXEC RollbackScenarioNoFail;
EXEC NoRollbackScenarioManyToManyFail;
EXEC NoRollbackScenarioManyToManyNoFail;

SELECT * FROM Students;
SELECT * FROM Courses;
SELECT * FROM StudentCourses;
SELECT * FROM ActionLogs;

DELETE FROM StudentCourses;
DELETE FROM Students;
DELETE FROM Courses;
DELETE FROM ActionLogs;
