select pmr.LastName, pmr.FirstName
from PacientsMedicalRecords pmr 
inner join Patients p on p.PId = pmr.PatientId
where DoctorSecialty = 'radiology' 
intersect
select pmr.LastName, pmr.FirstName
from PacientsMedicalRecords pmr 
inner join Patients p on p.PId = pmr.PatientId
where DoctorSecialty = 'cardiology' 

select pmr.DoctorSpeciality, SUM(p.Price), COUNT(*)
from PacientsMedicalRecords pmr 
inner join Procedures p on p.ProcId = pmr.ProcedureId
group by pmr.DoctorSpeciality
having SUM(p.price) >= ALL
(
    SELECT SUM(p.price)
    from PacientsMedicalRecords pmr  
    inner join Procedures p on p.ProcId = pmr.ProcedureId
    group by pmr.DoctorSpeciality
)
