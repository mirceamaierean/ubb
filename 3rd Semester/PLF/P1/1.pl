% 1.
% a. Write a predicate to determine the lowest common multiple of a list formed from integer numbers.
% b. Write a predicate to add a value v after 1-st, 2-nd, 4-th, 8-th, … element in a list.

gcd(0, A, A) :- !.
gcd(A, 0, A) :- !.

gcd(A, B, R) :-
    A >= B,
    A1 is A mod B,
    gcd(A1, B, R),
    !.

gcd(A, B, R) :-
    A < B,
    B1 is B mod A,
    gcd(A, B1, R),
    !.

lcm(A, B, R) :-
	gcd(A, B, RGCD),
    R is A * B / RGCD.

lcml([X], [X]).
lcml([X, Y], R) :-
    lcm(X, Y, R).

lcml([X, Y | T], R) :-
    lcm(X, Y, A),
    lcml([A | T], R).

insert_after([], _, _, _, []).

insert_after([H | T], V, POS, INDEX, [H, V | R]) :-
             POS =:= INDEX,
             NEXT_POS is POS * 2,
             NEXT_INDEX is INDEX + 1,
             insert_after(T, V, NEXT_POS, NEXT_INDEX, R).
             
insert_after([H | T], V, POS, INDEX, [H | R]) :-
             POS =\= INDEX,
             NEXT_INDEX is INDEX + 1,
             insert_after(T, V, POS, NEXT_INDEX, R).
             
insert(L, V, R) :- insert_after(L, V, 1, 1, R).
	