% 14.
% a. Write a predicate to test equality of two sets without using the set difference.
% b. Write a predicate to select the n-th element of a given list.

% a
same_length([], [], 1).
same_length([], [_], 0).
same_length([_], [], 0).
same_length([_|T1], [_|T2], R) :- 
    same_length(T1, T2, R).

exists(_, []).
exists(X, [X|_]).
exists(X, [_|T]) :- 
    exists(X, T).

same_set([], _).
same_set([H | T], L):-
    exists(H, L),
    same_set(T, L).


test_same_set(A, B):-
    same_length(A, B),
    same_set(A, B).

% b
nth_element([], _, []).
nth_element([H|_], 1, H).
nth_element([_|T], N, R):-
    N1 is N - 1,
    nth_element(T, N1, R).
