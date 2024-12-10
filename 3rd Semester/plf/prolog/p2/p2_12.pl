addDivisors(X, X, []).

addDivisors(X, Y, [Y | Res]):-
	mod(X, Y) =:= 0,
	Z is Y + 1,
	addDivisors(X, Z, Res).

addDivisors(X, Y, Res):-
	mod(X, Y) =\= 0,
	Z is Y + 1,
	addDivisors(X, Z, Res).

getAllDivisors(1, [1]).
getAllDivisors(X, [X | Res]):-
	addDivisors(X, 2, Res).

addDivisorsAfterElements([], []).
addDivisorsAfterElements([H | T], Ans):-
	getAllDivisors(H, L),
	addDivisorsAfterElements(T, Res),
	append(L, Res, Ans).

solveHeterogenousList([], []).

solveHeterogenousList([H | T], [AnswerH | AnswerT]):-
	is_list(H),
	!,
	addDivisorsAfterElements(H, AnswerH),
	solveHeterogenousList(T, AnswerT).

solveHeterogenousList([H | T], Ans):-
	\+ is_list(H),
	getAllDivisors(H, L),
	solveHeterogenousList(T, Res),
	append(L, Res, Ans).

testAddDivisor:-
	addDivisorsAfterElements([], []),
	addDivisorsAfterElements([1], [1]),
	addDivisorsAfterElements([4], [4, 2]),
	addDivisorsAfterElements([1, 2, 3, 4, 5, 6, 7], [1, 2, 3, 4, 2, 5, 6, 2, 3, 7]).

testSolveHeterogenousList:-
 	solveHeterogenousList([], []),
  	solveHeterogenousList([1, 4, 2, 3], [1, 4, 2, 2, 3]),
 	solveHeterogenousList([1, 1, 6, 3, 5, [2, 3, 4, 5, 1]], [1, 1, 6, 2, 3, 3, 5, [2, 3, 4, 2, 5, 1]]),
	solveHeterogenousList([1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2], [1, [2, 5, 7], 4, 2, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, 2, [7, 2, 8, 2, 4, 1], 2]).

testAll:-
	testAddDivisor,
	testSolveHeterogenousList.

