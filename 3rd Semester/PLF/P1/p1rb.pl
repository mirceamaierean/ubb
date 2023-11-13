add_one_after_even([], []). 

add_one_after_even([X | Rest], [X, 1 | Result]) :-
    mod(X, 2) =:= 0,
    add_one_after_even(Rest, Result).

add_one_after_even([X | Rest], [X | Result]) :-
    mod(X, 2) =\= 0, 
    add_one_after_even(Rest, Result).

