-- set the isolation level to snapshot
SET TRANSACTION ISOLATION LEVEL SNAPSHOT
BEGIN TRANSACTION
    SELECT Name 
    FROM Project 
    WHERE ProjectID = 7
    WAITFOR DELAY '00:00:10'
    SELECT Name 
    FROM Project 
    WHERE ProjectID = 7
    UPDATE Project 
    SET Name = 'Disaster Management' 
    WHERE ProjectID = 7
COMMIT TRANSACTION

select * from Project