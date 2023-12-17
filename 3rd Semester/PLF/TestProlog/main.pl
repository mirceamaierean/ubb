% replace all occurences of an element E in a lit L with the elementes of another list
% example: substitute_elem([1, 2, 1, 3, 1, 4], 1, [10, 11]) -> [10, 11, 2, 10, 11, 3, 10, 11, 4]

insert([], L, L).
insert([H|T], L, [H|R]) :-
    insert(T, L, R).

substitute_elem([], _, _, []).
substitute_elem([H|T], H, L, R):-
    substitute_elem(T, H, L, RT),
    insert(L, RT, R).
substitute_elem([H|T], E, L, [H|R]):-
    H =\= E,
    substitute_elem(T, E, L, R).

test_all:-
    % test substitute if element exists in the list
    substitute_elem([1, 2, 1, 3, 1, 4], 1, [10, 11], [10, 11, 2, 10, 11, 3, 10, 11, 4]),
    % test substitute if element exists in the list and replace it with an empty list
	substitute_elem([1, 2, 1, 3, 1, 4], 1, [], [2, 3, 4]),
    % test substitute if element does not exist in the list
    substitute_elem([1, 2, 1, 3, 1, 4], 5, [6, 7, 8], [1, 2, 1, 3, 1, 4]),
    % test substitute if list is empty
	substitute_elem([], 1, [1, 2, 3], []),
    % test substitute if both lists are empty
	substitute_elem([], 1, [], []),
	% test substitue if only one element exists
	substitute_elem([1], 1, [1, 2, 3], [1, 2, 3]).
	
