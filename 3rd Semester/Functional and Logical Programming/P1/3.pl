% 3.
% a. Define a predicate to remove from a list all repetitive elements.
% Eg.: l=[1,2,1,4,1,3,4] => l=[2,3])
% b. Remove all occurrence of a maximum value from a list on integer numbers.

% a
remove([], _, []).
remove([H|T], H, R) :-
    remove(T, H, R).
remove([H|T], E, [H|R]) :-
    H =\= E,
    remove(T, E, R).

count_occ([], _, 0).
count_occ([H|T], H, R) :-
    count_occ(T, H, R1),
    R is R1 + 1.
count_occ([H|T], E, R) :-
    H =\= E,
    count_occ(T, E, R).

remove_all([], []).
remove_all([H|T], [H|R]) :-
    count_occ(T, H, C),
    C =:= 0,
    remove_all(T, R).
remove_all([H|T], R) :-
    count_occ(T, H, C),
    C =\= 0,
    remove([H|T], H, R1),
    remove_all(R1, R).

% b
max([], -999).
max([H|T], R) :-
    max(T, R1),
    H > R1,
    R is H.
max([H|T], R) :-
    max(T, R1),
    H =< R1,
    R is R1.

remove_max([], []).
remove_max(L, R) :-
    max(L, M),
    remove(L, M, R).
