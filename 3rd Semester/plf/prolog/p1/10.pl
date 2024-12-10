% 10.
% a. Define a predicate to test if a list of an integer elements has a "valley" aspect (a set has a "valley" aspect if
% elements decreases up to a certain point, and then increases.
% eg: 10 8 6 9 11 13 – has a “valley” aspect
% b. Calculate the alternate sum of list’s elements (l1 - l2 + l3 ...).

% a
% mathematical model
% valley(l1...ln, dec) =
% 	true, n = 1 and dec = 0
% 	valley(l2...ln, 1), l1 > l2
% 	valley(l2...ln, 0), l1 < l2
% 	false, otherwise

% valley(L:list, D:integer)
valley([_], 0).
valley([H1, H2|T], _) :- 
    H1 < H2, 
    valley([H2|T], 0),
    !.
valley([H1, H2|T], 1) :-
    H1 > H2,
    valley([H2|T], 1),
    !.

% b
alternate_sum([], 0).
alternate_sum([H], H).
alternate_sum([H1, H2|T], S) :-
    alternate_sum(T, S1),
    S is S1 + H1 - H2.