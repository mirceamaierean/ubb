subset([], []).
subset([E|T], [E|R]):-
  subset(T, R).
subset([_|T], R):-
  subset(T, R).

collinear([[X1, Y1], [X2, Y2], [X3, Y3]]):-
    (Y2 - Y1) * (X3 - X2) =:= (Y3 - Y2) * (X2 - X1).

process([], []).
process(L, K):-
	subset(L, K),
	collinear(K).

allSolutions(L, R) :-
    findall(RPartial, process(L, RPartial), R).
