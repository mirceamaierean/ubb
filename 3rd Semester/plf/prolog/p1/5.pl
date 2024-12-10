% 5.
% a. Write a predicate to compute the union of two sets.
% b. Write a predicate to determine the set of all the pairs of elements in a list.
% Eg.: L = [a b c d] => [[a b] [a c] [a d] [b c] [b d] [c d]].

% a
% first, we need a predicate to check if an element is in a list
member([], _, 0).
member([X], X, 1).
member([X|T], X, 1).
member([H|T], X, R) :-
    H =\= X,
    member(T, X, R).

% now, we can write the union predicate

% union(L1:list, L2:list, R:list)
union([], L2, L2).
union([H|T], L2, R) :-
    member(L2, H, 0),
    union(T, L2, R1),
    R = [H|R1].

union([H|T], L2, R) :-
    member(L2, H, 1),
    union(T, L2, R).

% b
% define a predicate to check if a pair is already in the list
% is_pair_in_list(E1:element, E2:element, L:list)
is_pair_in_list(E1, E2, [[E1, E2]|_]).
is_pair_in_list(E1, E2, [_|T]) :-
    is_pair_in_list(E1, E2, T).

% now, for each element, we compute the pairs with the ones that come after it
% and we add them to the result list
% pairs(L:list, R:list)
pairs([], []).
pairs([H|T], R) :-
    pairs(T, R1),
    pairs_aux(H, T, R2),
    is_pair_in_list(H, H, R2),
    append(R1, R2, R).

% pairs_aux(E:element, L:list, R:list)
pairs_aux(_, [], []).
pairs_aux(E, [H|T], R) :-
    pairs_aux(E, T, R1),
    is_pair_in_list(E, H, R1),
    R = R1.

pairs_aux(E, [H|T], R) :-
    pairs_aux(E, T, R1),
    \+ is_pair_in_list(E, H, R1),
    R = [[E, H]|R1].

