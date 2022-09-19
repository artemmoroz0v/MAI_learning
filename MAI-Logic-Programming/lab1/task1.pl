% Первая часть задания - предикаты работы со списками

%Standart predicates realization
remove(X, [X|T], T).
remove(X, [Y|T], [Y|T1]) :- remove(X, T, T1).
%?-remove(3,[1,2,3,4],L), write(L).

length(L, Length):-length(L, 0, Length).
length([], Length, Length):-!.
length([_|T], Y, Length):- Res is Y + 1, length(T, Res, Length).
%?-length([1,2,3,4,5,6],L), write(L).

member(H, [H|_]) :- !.
member(H, [_|T]) :- member(H, T).
%?-member(3, [1,2,5]).

sublist([], []).
sublist([H|L1], [H|L2]) :-sublist(L1, L2).
sublist(H, [_|L2]) :-sublist(H, L2).
%?-sublist([a,c],[a,b,c,d]). 

append([], L, L).
append([H|T], List, [H|TRes]):- append(T, List, TRes).
%?-append([1,2,3,4],[2,3,4],L), write(L). 

permute([], []).
permute(L, [X|T]):-remove(X, L, L1), permute(L1, T).
%?-findall(X, permute([a,b,c,d], X), L), write(L).





%Task (recursive and standart solutions)
%Option17
del_standart(L, X, R) :- member(X, L), !, append(R, [X|_], L).
del_standart(L, X, R) :- append(R, [], L).
%?-del_standart([1,2,3,4,5,6,7,8,9],5, L), write(L).

del_recursive([], X, []) :- !.
del_recursive([X|T], X, []) :- !.
del_recursive([H|T], X, [H|R]) :- del_recursive(T, X, R).
%?-del_recursive([1,2,3,4], 4, L), write(L).

%Example which includes usage of append predicate and my deleting predicate.
%In this example I've done three cases:
%First of all, I've created one list, then I've called "del_standart" predicate for this list.
%Second case is almost the same. But I've made another list.
%Last step - I've called append predicate for two lists. The result is new list.
example(L1, X1, L2, X2):-del_standart(L1, X1, L), del_standart(L2, X2, R), append(L, R, Result), write(Result).
%?-example([1,2,3],3,[4,5,6],6).


%Option2
multiplication_standart([], 1):- !.
multiplication_standart([0|_], 0):- !.
multiplication_standart([X], X):- !.
multiplication_standart([X, Y|T], P):- PC is X * Y, remove(X, [X, Y|T], L1), remove(Y, L1, L2), append([PC], L2, L3), multiplication_standart(L3, P).
%?-multiplication_standart([1,2,3,4,5],L), write(L).

multiplication_recursive([], 1):-!.
multiplication_recursive([Head|Tail], Result):-multiplication_recursive(Tail, TailRes), Result is TailRes * Head.
%?-multiplication_recursive([1,2,3,4,5],L), write(L).

