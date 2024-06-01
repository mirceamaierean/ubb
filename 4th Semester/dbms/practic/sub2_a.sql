create table Doctor(
    DoctorId INT NOT NULL PRIMARY KEY,
    DateOfBirth DATE,
    Specialization VARCHAR(50) NOT NULL,
)

create table Medication(
    MedicationId INT NOT NULL PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Instructions VARCHAR(200) NOT NULL,
)

create table Treatment(
    TreatmentId INT NOT NULL PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    MedicationId INT NOT NULL REFERENCES Medication(MedicationId),
    Dosage INT NOT NULL,
)

create table Patient(
    PatientId INT NOT NULL PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    Address VARCHAR(100) NOT NULL,
    Phone VARCHAR(20) NOT NULL,
    DoctorId INT NOT NULL REFERENCES Doctor(DoctorId),
    TreatmentId INT NOT NULL REFERENCES Treatment(TreatmentId),
)

create table Assistant(
    AssistantId INT NOT NULL PRIMARY KEY,
    Name VARCHAR(50) NOT NULL,
    DateOfBirth DATE,
    DoctorId INT NOT NULL REFERENCES Doctor(DoctorId),
)

create table Appointment(
    AppointmentId INT NOT NULL PRIMARY KEY,
    AppointmentDateTime DATETIME NOT NULL,
    ReasonOfVisit VARCHAR(200) NOT NULL,
    PatientId INT NOT NULL REFERENCES Patient(PatientId),
    DoctorId INT NOT NULL REFERENCES Doctor(DoctorId),
)

create table Payment(
    PaymentId INT NOT NULL PRIMARY KEY,
    PaymentMethod VARCHAR(50) NOT NULL,
    DateOfPaymnt DATE NOT NULL,
    Status VARCHAR(50) NOT NULL,
)
