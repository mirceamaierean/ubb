% 11.
% a. Write a predicate to substitute an element from a list with another element in the list.
% b. Write a predicate to create the sublist (lm, …, ln) from the list (l1,…, lk).

% a
% substitute(L:list, E:element, R:element, R:list)
% flow model: (i i i o), (i i i i)
substitute([], _, _, []).
substitute([H|T], E, R, [R|TR]) :- 
    H =:= E, 
    substitute(T, E, R, TR).
substitute([H|T], E, R, [H|TR]) :-
    H =\= E,
    substitute(T, E, R, TR).

% b
sub_list(_, _, N, POS, []):-
    POS > N,
    !.
sub_list([H|T], M, N, POS, [H|TR]):-
    POS =< N,
    POS >= M,
    POS1 is POS + 1,
    sub_list(T, M, N, POS1, TR),
    !.
sub_list([_|T], M, N, POS, TR):-
    POS < M,
    POS1 is POS + 1,
    sub_list(T, M, N, POS1, TR).

% for testing
% substitute([1,2,3,4,5,6,7,8,9,10], 3, 0, R).
% sub_list([1,2,3,4,5,6,7,8,9,10], 3, 7, 1, R).