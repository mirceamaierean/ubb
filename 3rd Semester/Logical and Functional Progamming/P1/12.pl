% 12.
% a. Write a predicate to substitute in a list a value with all the elements of another list.
% b. Remove the n-th element of a list

% a
insert([], L, L).
insert([H|T], L, [H|R]) :- 
    insert(T, L, R).

substitute_elem([], _, _, []).
substitute_elem([H|T], E, L, R):-
    H =:= E,
    substitute_elem(T, E, L, RT),
    insert(L, RT, R).
substitute_elem([H|T], E, L, [H|R]):-
    H =\= E,
    substitute_elem(T, E, L, R).

% b
remove([], _, _, []).
remove([_|T], N, N, T).
remove([H|T], N, C, [H|R]) :- 
    C1 is C + 1, 
    remove(T, N, C1, R).

test_remove(L, N, R):-
    remove(L, N, 1, R).