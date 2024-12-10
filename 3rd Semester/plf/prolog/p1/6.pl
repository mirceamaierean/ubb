% 6.
% a. Write a predicate to test if a list is a set.
% b. Write a predicate to remove the first three occurrences of an element in a list. 
% If the element occurs less than three times, all occurrences will be removed.

% a
% member(E:atom, L:list)
% member(i,i)
member(E,[E|_]).
member(E,[_|T]):-
    member(E,T).

% set(L:list)
% set(i)
set([]).
set([H|T]):-
    not(member(H,T)),
    set(T).

% b. Write a predicate to remove the first three occurrences of an element in a list. 
% If the element occurs less than three times, all occurrences will be removed.

remove_k_ocurrences([], _, _, []).
remove_k_occurences(L, _, 0, L).
remove_k_occurences([H|T], E, K, R):-
    H =:= E,
    K1 is K - 1,
    remove_k_occurences(T, E, K1, R).
remove_k_occurences([H|T], E, K, [H|R]):-
    H =\= E,
    remove_k_occurences(T, E, K, R).

remove_3_occurences(L, E, R):-
    remove_k_occurences(L, E, 3, R).
