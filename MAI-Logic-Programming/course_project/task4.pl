:- ['familytree.pl'].
:- ['task3.pl'].
%Realization of family-relations:
relation(Father, Person, father):- parent(Father, Person), sex(Father, 'm').
relation(Mother, Person, mother):- parent(Mother, Person), sex(Mother, 'f').
relation(Person, Parent, son):- parent(Parent, Person), sex(Person, 'm').
relation(Person, Parent, daughter):- parent(Parent, Person), sex(Person, 'f').
relation(Person, HelpPerson, brother) :- parent(Parent, Person), parent(Parent, HelpPerson), Person \= HelpPerson, sex(Person, 'm').
relation(Person, HelpPerson, sister) :- parent(Parent, Person), parent(Parent, HelpPerson), Person \= HelpPerson, sex(Person, 'f').
relation(Husband, Wife, husband):- parent(Wife, Person), parent(Husband, Person), Husband \= Wife, sex(Husband, 'm').
relation(Wife, Husband, wife):- parent(Wife, Person), parent(Husband, Person), Husband \= Wife, sex(Wife, 'f').
relation(Person, GrandFather, grand_father):- parent(HelpPerson, Person), parent(GrandFather, HelpPerson), sex(GrandFather, 'm').
relation(Person, GrandMother, grand_mother):- parent(HelpPerson, Person), parent(GrandMother, HelpPerson), sex(GrandMother, 'f').
relative(X, Y, Res):- iterative_searching_predicate(X, Y, Res), !.
%Iterative-deepening search realization according to lab3 task:
prolong([H|T], [X,H|T]):- move(H, X), not(member(X,[H|T])).
transform([_], []) :- !.
transform([X,Y|Z], Answer):- relation(X, Y, C), Answer = [C|D], 
transform([Y|Z], D), !.
move(A, B) :- relation(A, B, _).
int(1).
int(X) :- int(Y), X is Y + 1.
iterative_searching_predicate(X, Y, Z, Depth):- iter([X], Y, Answer, Depth), reverse(Answer, Z).
iter([H|T], H, [H|T], 0).
iter(X, Y, Z, N):- N > 0, prolong(X, A), M is N - 1, iter(A, Y, Z, M).
iterative_searching_predicate(X, Y, Z):- int(CurrentPosition), iterative_searching_predicate(X, Y, Answer, CurrentPosition), 
transform(Answer, Z).
