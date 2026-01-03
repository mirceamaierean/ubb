SELECT R.codregizor,
       R.nume
FROM   regizori R
WHERE  R.codregizor IN(SELECT F.codregizor
                       FROM   filme F
                              INNER JOIN filmepremii FP
                                      ON FP.codfilm = F.codfilm
                              INNER JOIN premii P
                                      ON P.codpremiu = FP.codpremiu
                       WHERE  P.denumire = 'Oscar')
       AND R.codregizor IN(SELECT F.codregizor
                           FROM   filme F
                                  INNER JOIN filmepremii FP
                                          ON FP.codfilm = F.codfilm
                                  INNER JOIN premii P
                                          ON P.codpremiu = FP.codpremiu
                           WHERE  P.denumire = 'Ursul de Aur')

SELECT R.codregizor,
       R.nume
FROM   regizori R
WHERE  R.codregizor IN (SELECT F.codregizor
                        FROM   filme F
                               JOIN filmepremii FP
                                 ON F.codfilm = FP.codfilm
                               JOIN premii P
                                 ON P.codpremiu = FP.codpremiu
                        WHERE  P.denumire IN ( 'Oscar', 'Ursul de Aur' )
                        GROUP  BY F.codregizor
                        HAVING Count(DISTINCT P.denumire) = 2)

SELECT f.codfilm,
       f.titlu
FROM   filme f
WHERE  NOT EXISTS (SELECT p.codpremiu
                   FROM   premii p
                   EXCEPT
                   SELECT DISTINCT fp.codpremiu
                   FROM   filmepremii fp
                   WHERE  fp.codfilm = f.codfilm)
       AND f.incasari > (SELECT Max(incmed)
                         FROM   (SELECT Avg(f2.incasari) IncMed
                                 FROM   filme f2
                                 GROUP  BY f2.codregizor) t) 