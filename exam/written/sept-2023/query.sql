select distinct d.DriverId, d.DriverName, d.Salary
from Drivers d
inner join Cars c on c.DriverID = d.DriverID
inner join Rider r on r.CarId = c.CarId
where c.CarMake = 'Ford' and r.Destination = 'Iulius Mall Cluj' and d.salary = (
    select max(d2.Salary)
    from Drivers d2
    inner join Cars c2 on c2.DriverID = d2.DriverID
    inner join Rider r2 on r2.CarId = c2.CarId
    where c2.CarMake = 'Ford' and r2.Destination = 'Iulius Mall Cluj' 
)

0600 - 110 - rwx (in fifo avem acces de read si de write)

abc_def
abc
def

linia 7 face grep in fisier si extrage liniile care incep cu unul din argumentele din linia de comanda, iar dupa aceea sunt urmate de grupuri de form (_cuvant), de 0 sau mai multe ori, numara folosind wc-l cate linii respecta acest pattern iar daca sunt cel putin 2 atunci executa un sir de comenzi

linia 8 regexul verifica liniile care incep cu $A, dupa se asigura ca exista grupuri de forma
- _, cel putin o data, urmate de $A, iar aceste grupuri exista de 0 sau mai multe ori
