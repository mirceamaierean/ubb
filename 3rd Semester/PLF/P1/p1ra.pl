member(Element, [Element|_]).
member(Element, [_|Rest]) :-
    member(Element, Rest).

% base case, if the list is empty, then the difference is also an empty set
set_difference([], _, []).

% if element is member, do not add it to the list
set_difference([H|T], Set2, Difference) :-
    member(H, Set2),
    !,
    set_difference(T, Set2, Difference).

% if the element is not a member of the second set, add it to the list
set_difference([H|T], Set2, [H|RestDifference]) :-
    set_difference(T, Set2, RestDifference).


