% 2.
% a. Write a predicate to remove all occurrences of a certain atom from a list.
% b. Define a predicate to produce a list of pairs (atom n) from an initial list of atoms.
% In this initial list atom has n occurrences.
% Eg.: numberatom([1, 2, 1, 2, 1, 3, 1], X) => X = [[1, 4], [2, 2], [3, 1]].

remove([], V, []).

remove([V|T], V, R) :-
    remove(T, V, R).

remove([H|T], V, [H|R]) :-
    H =\= V,
    remove(T, V, R).

% first, we define a predicate to count the number of occurences of an element in a list
count([], _, 0).
count([H|T], H, R) :-
    count(T, H, R1),
    R is R1 + 1.
count([H|T], E, R) :-
    H =\= E,
    count(T, E, R).

% for numberatom, we first count the number of occurences of each element in the list, then we remove the duplicates
numberatom([], []).
numberatom([H|T], [[H, R]|R1]) :-
    count([H|T], H, R),
    remove(T, H, R2),
    numberatom(R2, R1).


