ALTER DATABASE SchoolDB SET ALLOW_SNAPSHOT_ISOLATION ON 
-- GO

BEGIN TRAN
UPDATE Courses SET CourseName='Mathematics 101 transaction 1' WHERE CourseID=1
waitfor delay '00:00:10' 
COMMIT TRAN

SET TRANSACTION ISOLATION LEVEL SNAPSHOT
BEGIN TRAN
Select * from Courses where CourseID=1
waitfor delay '00:00:10' 
select * from Courses where CourseID=1
update Courses set CourseName='am actualizat' where CourseID=1
COMMIT TRAN