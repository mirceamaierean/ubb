-- Transaction 1 (Console 1)
BEGIN TRANSACTION
UPDATE Courses SET CourseName='Mathematics 101 transaction 1' WHERE CourseID=11;
WAITFOR DELAY '00:00:10';
UPDATE Students SET StudentName='John Doe transaction 1' WHERE StudentID=12;
COMMIT TRANSACTION;

-- Transaction 2 (Console 2)
BEGIN TRANSACTION
UPDATE Students SET StudentName='Jane Smith transaction 2' WHERE StudentID=1;
WAITFOR DELAY '00:00:10';
UPDATE Courses SET CourseName='Physics 101 transaction 2' WHERE CourseID=1;
COMMIT TRANSACTION;

-- solution
BEGIN TRANSACTION
UPDATE Courses SET CourseName='Physics 101 transaction 2' WHERE CourseID=1;
WAITFOR DELAY '00:00:10';
UPDATE Students SET StudentName='Jane Smith transaction 2' WHERE StudentID=1;
COMMIT TRANSACTION;