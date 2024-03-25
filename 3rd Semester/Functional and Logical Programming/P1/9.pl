% 9.
% a. Insert an element on the position n in a list.
% b. Define a predicate to determine the greatest common divisor of all numbers from a list

% a
insert_after_n([], _, _, _, []).
insert_after_n([H|T], N, N, E, [H, E|T]).
insert_after_n([H|T], N, C, E, [H|R]) :-
    C1 is C + 1,
    insert_after_n(T, N, C1, E, R).

insert_on_pos(X, N, E, R):-
    insert_after_n(X, N, 1, E, R).

% b
gcd(A, 0, A).
gcd(0, B, B).
gcd(A, B, A):-
    A =:= B.
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