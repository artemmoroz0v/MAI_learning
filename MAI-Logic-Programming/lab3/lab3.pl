%Here we need to swap elements:
swap_element(X,Y,Z,Result):- length(X,FirstLength), length(Result,SecondLength), FirstLength =:= SecondLength,
append(A,[B|C],X), append(A,[D|C],F), append(H,[D|E],F),
append(H,[B|E],Result), length(A,Y), length(H,Z), !.
%Here we need to find an element.
take_element([H|_],H, 0):-!.
take_element([_|T],A,C):- B is C-1, take_element(T,A,B).
%According to the task: check correct order
correct_order(X,Y,Z):- take_element(X,A,Y), take_element(X,B,Z),
((A == b, B == r); (A == b, B == w); (A == w, B == r)), !.
%Go to next state:
move([List|_],Result):- move(List,Result).
move(st(List),st(Result)):- length(List,FirstLength), SecondLength is FirstLength - 1, 
between(0,SecondLength,X), between(0,SecondLength,Y), X @< Y, 
correct_order(List,X,Y), swap_element(List,X,Y,C), Result = C.
%Extension of paths:
prolong([Head1|T],[Head2,Head1|T]):- move(Head1,Head2), \+ member(Head2,[Head1|T]).
%Printing of results:
inv_print([]).
inv_print([H|T]):-inv_print(T), write(H), nl.
int(1).
int(A):- int(B), A is B + 1.
%Help-predicate:
breadth_search([[H|T]|_],H,[H|T]).
breadth_search([H|T],X,Res):- findall(Z,prolong(H,Z),C), append(T,C,D),
breadth_search(D,X,Res).
breadth_search([_|T],X,Res):- breadth_search(T,X,Res).
%Breadth-search:
breadth_searching_predicate(X,Y):-get_time(CurTime),
breadth_search([[X]],Y,List), inv_print(List), get_time(EndTime),
TimeDifference is EndTime - CurTime, write('Time passed: '), write(TimeDifference), nl.
%Help-predicate:
depth_search([H|T],H,[H|T]).
depth_search(A,B,C):- prolong(A,Z), depth_search(Z,B,C).
%Depth-search predicate:
depth_searching_predicate(A,B):-get_time(CurTime), depth_search([A],B,Head),
inv_print(Head), get_time(EndTime), TimeDifference is EndTime - CurTime,
write('Time passed: '), write(TimeDifference), nl.
%Help-predicate
depth_check([H|T],H,[H|T],0).
depth_check(X,H,R,A):- A @> 0, prolong(X,Y), B is A - 1, depth_check(Y,H,R,B).
%iterative-deepening search:
iterative_searching_predicate(H,T):-get_time(CurTime),
int(List), depth_check([H],T,Result,List), inv_print(Result),
get_time(EndTime), TimeDifference is EndTime - CurTime,
write('Time passed: '), write(TimeDifference), nl.
iterative_searching_predicate(H,T,Depth):- int(List), iterative_searching_predicate(H,T,Depth,List).
