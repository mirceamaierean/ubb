% 7.
% a. Write a predicate to compute the intersection of two sets.
% b. Write a predicate to create a list (m, ..., n) of all integer numbers from the interval [m, n].

% a
% define a member predicate
member(X, [X|_]).
member(X, [_|T]) :- 
    member(X, T).

% define an intersection predicate
intersection([], _, []).
intersection([H|T], L2, [H|R]) :- 
    member(H, L2),
    intersection(T, L2, R).
intersection([_|T], L2, R) :-
    intersection(T, L2, R).

% b
create(N, N, [N]).

create(M, N, [M|R]):-
    M < N,
    M1 is M + 1,
    create(M1, N, R).

create(M, N, R):-
    M > N,
    create(N, M, R)