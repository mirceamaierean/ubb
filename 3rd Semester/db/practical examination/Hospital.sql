-- Create a database for a hospital management system. The entities of interest to the problem domain are: Patients, Doctors, Medications, Appointments and Prescriptions. A patient has an ID, a name, a date of birth and a gender. IDs are unique. A doctor has a name and a department. A medication has a name and a manufacturer. Names are unique. The system stores data about scheduled appointments between patients and doctors and it will store the date and time for each appointment. A prescription represents the medication that was prescribed during the appointment, including the dosage.
-- 1. Write an SQL script that creates the corresponding relational data model.
-- 2. Implement a stored procedure that receives a patient, a doctor and a date-time and creates a new appointment. If there is already an appointment for the same doctor and patient, the date of the existing appointment is updated.
-- 3. Create a view that shows the names of the doctors with scheduled appointments during the month of February, 2024.
-- 4. Implement a function that returns the total count of each medication prescribed by a doctor D across all appointments, where D is a function parameter.

-- 1. Write an SQL script that creates the corresponding relational data model.
USE HospitalManagementDB;
GO

-- Drop tables if they exist
IF OBJECT_ID('Patients', 'U') IS NOT NULL DROP TABLE Patients;
IF OBJECT_ID('Doctors', 'U') IS NOT NULL DROP TABLE Doctors;
IF OBJECT_ID('Medications', 'U') IS NOT NULL DROP TABLE Medications;
IF OBJECT_ID('Appointments', 'U') IS NOT NULL DROP TABLE Appointments;
IF OBJECT_ID('Prescriptions', 'U') IS NOT NULL DROP TABLE Prescriptions;
GO

-- Create tables
CREATE TABLE Patients (
    PatientID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    DateOfBirth DATE,
    Gender VARCHAR(10)
);

CREATE TABLE Doctors (
    DoctorID INT PRIMARY KEY,
    Name VARCHAR(255) NOT NULL,
    Department VARCHAR(255)
);

CREATE TABLE Medications (
    MedicationID INT PRIMARY KEY,
    Name VARCHAR(255) UNIQUE NOT NULL,
    Manufacturer VARCHAR(255)
);

CREATE TABLE Appointments (
    AppointmentID INT PRIMARY KEY,
    PatientID INT,
    DoctorID INT,
    AppointmentDateTime DATETIME,
    CONSTRAINT FK_PatientID FOREIGN KEY (PatientID) REFERENCES Patients(PatientID),
    CONSTRAINT FK_DoctorID FOREIGN KEY (DoctorID) REFERENCES Doctors(DoctorID)
);

CREATE TABLE Prescriptions (
    PrescriptionID INT PRIMARY KEY,
    AppointmentID INT,
    MedicationID INT,
    Dosage VARCHAR(50),
    CONSTRAINT FK_AppointmentID FOREIGN KEY (AppointmentID) REFERENCES Appointments(AppointmentID),
    CONSTRAINT FK_MedicationID FOREIGN KEY (MedicationID) REFERENCES Medications(MedicationID)
);
GO

-- 2. Implement a stored procedure that receives a patient, a doctor and a date-time and creates a new appointment.
--    If there is already an appointment for the same doctor and patient, the date of the existing appointment is updated.
DROP PROCEDURE IF EXISTS ScheduleAppointment;
GO

CREATE PROCEDURE ScheduleAppointment (
    @PatientID INT,
    @DoctorID INT,
    @AppointmentDateTime DATETIME
)
AS
BEGIN
    -- Check if there's an existing appointment for the same doctor and patient
    IF EXISTS (SELECT 1 FROM Appointments WHERE PatientID = @PatientID AND DoctorID = @DoctorID)
    BEGIN
        -- Update the existing appointment date and time
        UPDATE Appointments
        SET AppointmentDateTime = @AppointmentDateTime
        WHERE PatientID = @PatientID AND DoctorID = @DoctorID;
    END
    ELSE
    BEGIN
        -- Insert a new appointment
        INSERT INTO Appointments (PatientID, DoctorID, AppointmentDateTime)
        VALUES (@PatientID, @DoctorID, @AppointmentDateTime);
    END
END;
GO

-- 3. Create a view that shows the names of the doctors with scheduled appointments during the month of February, 2024.
CREATE VIEW DoctorsWithAppointments AS
SELECT DISTINCT
    D.Name AS DoctorName
FROM Doctors D
JOIN Appointments A ON D.DoctorID = A.DoctorID
WHERE YEAR(A.AppointmentDateTime) = 2024 AND MONTH(A.AppointmentDateTime) = 2;
GO

-- 4. Implement a function that returns the total count of each medication prescribed by a doctor D across all appointments,
--    where D is a function parameter.
DROP FUNCTION IF EXISTS GetMedicationPrescriptionCount;
GO

CREATE FUNCTION GetMedicationPrescriptionCount (
    @DoctorID INT
)
RETURNS TABLE
AS
RETURN
(
    SELECT
        M.Name AS MedicationName,
        COUNT(P.MedicationID) AS PrescriptionCount
    FROM Medications M
    LEFT JOIN Prescriptions P ON M.MedicationID = P.MedicationID
    LEFT JOIN Appointments A ON P.AppointmentID = A.AppointmentID
    WHERE A.DoctorID = @DoctorID
    GROUP BY M.Name
);
GO
