merge(A, [], A):-!.
merge([], B, B):-!.

merge([HA | TA], [HB | TB], [HA | AnswerT]):-
    HA =< HB,
    !,
    merge(TA, [HB | TB], AnswerT).

merge([HA | TA], [HB | TB], [HB | AnswerT]):-
    HB < HA,
    !,
    merge([HA | TA], TB, AnswerT).

% Usage: splitEqually(L, A, B) -> splits the elements of L almost equally in A and B
splitEqually([], [], []):- !.
splitEqually([H | T], [H | AnswerA], AnswerB):-
  splitEqually(T, AnswerB, AnswerA).

mergeSort(A, A):-
    length(A, LenA),
    LenA =< 1,
    !.

mergeSort(A, Answer):-
    length(A, LenA),
    LenA > 1,
    !,
    splitEqually(A, LA, RA),
    mergeSort(LA, LA_SORTED),
    mergeSort(RA, RA_SORTED),
    merge(LA_SORTED, RA_SORTED, Answer).
    
testMergeSort:-
    mergeSort([4, 2, 6, 2, 3, 4], [2, 2, 3, 4, 4, 6]),
	mergeSort([3, 52, 43, 563, 234, 453, 4353], [3, 43, 52, 234, 453, 563, 4353]),
	mergeSort([2, 2, 1, 1, 4, 3, 5, 8, 5, 5, 6], [1, 1, 2, 2, 3, 4, 5, 5, 5, 6, 8]).
