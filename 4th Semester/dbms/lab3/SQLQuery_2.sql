SET TRANSACTION ISOLATION LEVEL READ COMMITTED
BEGIN TRAN
    UPDATE Project 
    SET Name = 'Green Campus' 
    WHERE ProjectID = 7
COMMIT TRAN
I
ex 1: c)


READ UNCOMMITTED

(read SELECT) S - X
(write UPDATE) X Locks = acquired + released when T ends

READ COMMITTED

S - acquired + released when select stmt ends
X - ✔️

REPETEABLE READ

S - acquired + released when T ends
X - ✔️

ex 2: c)


SERIALIZABLE

S,X acquired + released when T ends  (T = transaction)
key range locks

ex 3: bcd 

sub2
ex 1: e

ex 2: e

ex 3: ac


sub3

ex1:b

ex2:b

ex3: ac