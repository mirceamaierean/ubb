% 13.
% a. Transform a list in a set, in the order of the last occurrences of elements. 
% Eg.: [1,2,3,1,2] is transformed in [3,1,2].
% b. Define a predicate to determine the greatest common divisor of all numbers in a list

% a
member([E|_], E).
member([_|T], E) :- 
    member(T, E).

set_from_list([], []).
set_from_list([X], [X]).
set_from_list([H|T], R) :- 
    set_from_list(T, R1), 
    member(R1, H),
    R = R1.
set_from_list([H|T], R) :-
    set_from_list(T, R1),
    \+ member(R1, H),
    R = [H|R1].

% b
gcd(A, 0, A).
gcd(0, B, B).
gcd(A, A, A).
gcd(A, B, R):-
    A > B,
    A1 is A mod B,
    gcd(A1, B, R).
gcd(A, B, R):-
    A < B,
    B1 is B mod A,
    gcd(A, B1, R).

gcd_list([], 0).
gcd_list([H], H).
gcd_list([H|T], R):-
    gcd_list(T, R1),
    gcd(H, R1, R).