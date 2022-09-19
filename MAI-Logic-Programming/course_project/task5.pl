:- ['familytree.pl'].
:- ['task3.pl'].
:- ['task4.pl'].
%Here we are setting instructions for our relations:
check_relation(X):- member(X, [father, mother, sister, brother, daughter, son, wife, husband, grand_mother, grand_father]).
check_relative(A, B, C):- check_relation(C), !, relation(A, B, C).

%REQUESTS!!! NESSECARY FOR PARSING OUR QUESTIONS!
beginning_of_question(Val) :- member(Val, [how, who, "How", "Who"]).
indefinite_prns(Val) :- member(Val,[much, many]).
relatives(Val) :- member(Val, [sisters, brothers, sons, daughters, grand_mothers, grand_fathers]).
family_accordance(sister, sisters).
family_accordance(brother, brothers).
family_accordance(grand_mother, grand_mothers).
family_accordance(grand_father, grand_fathers).
family_accordance(son, sons).
family_accordance(daughter, daughters).
auxiliary_do(Val) :- member(Val, [do, does]).
pronouns_list(Val) :- member(Val, [his, her, he, she]).
auxiliary_have(Val) :- member(Val, [have, has]).
is(Val) :- member(Val, [is]).
engl_ap(Val) :- member(Val, [" s"]).
interrogate(Val) :- member(Val, ['?']).

%DOING ALL TYPES OF QUESTIONS!!!
%First question: how many/much sisters/sons/daughters etc does our name have/has?
question(Question):- Question = [A, B, C, D, E, F, G], beginning_of_question(A), indefinite_prns(B), relatives(C), 
auxiliary_do(D), (sex(E, 'f'); sex(E, 'm')), nb_setval(lastName, E), auxiliary_have(F), interrogate(G),
family_accordance(C1, C), setof(X, check_relative(X, E, C1), L), length(L, Res), write(E), write(" has "),
((Res =:= 1, write(Res), write(" "), write( C1)); (\+(Res =:= 1), write(Res), write(" "), write( C))), !.

question(Question):- Question = [A, B, C, D, E, F, G], beginning_of_question(A), indefinite_prns(B), 
relatives(C), auxiliary_do(D), pronouns_list(E), nb_getval(lastName, Y), auxiliary_have(F), interrogate(G),
family_accordance(Z, C), setof(X, check_relative(X, Y, Z), L), length(L, Ans), write(Y), write(" has "),
((Ans =:= 1, write(Ans), write(" "), write(Z)); (\+(Ans =:= 1), write(Ans), write(" "), write(C))), !.

%Second question: type of questions a-la "Who is our name's mother/father/son etc...?"
question(Question):- Question = [A, B, C, D, E, F], beginning_of_question(A), is(B), (sex(C, 'f'); sex(C, 'm')), 
nb_setval(lastName, C), engl_ap(D), check_relation(E), interrogate(F), !, relation(Res, C, E),
write(Res), write(" is "), write(C), write(" s "), write(E).

question(Question):- Question = [A, B, C, D, E], beginning_of_question(A), is(B), pronouns_list(C), 
nb_getval(lastName, Z), check_relation(D), interrogate(E), !, relation(Z, Res, D),write(Res), 
write(" is "), write(Z), write(" s "), write(D).

%Third question: is name helpname's son/daughter/brother etc...?
question(Question):- Question = [A, B, C, D, E, F], nb_setval(lastName, C), is(A), (sex(B, 'f'); sex(B, 'm')),
(sex(C, 'f'); sex(C, 'm')), engl_ap(D), check_relation(E), interrogate(F), relation(B, C, E), !.

question(Question):- Question = [A, B, C, D, E], is(A), (sex(B, 'f'); sex(B, 'm')), pronouns_list(C), check_relation(D),
interrogate(E), nb_getval(lastName, Z), relation(B, Z, D), !.


%PARSING SENTENCES!!!
%Who is name's son/daughter/brother etc...?
sentence_parser(Sentence, ResSentence):- append(List1, List2, Sentence), q_type(List1, S), append(X, Y, List2), person_name(X, Sent1),
append(A, B, Y), relations(A, Sent2), q_mark(B, Sent3), ResSentence = sentence(S, Sent1, Sent2, Sent3).

%How many sons/brothers etc.. does name have?
sentence_parser(List, Res):- List = [A, B, C, D, E, F, G], q_type([A, B], X), relations([C], Y),
do_or_does([D], Z), person_name([E], Q), have_or_has([F], W), q_mark([G], R), Res = sentence(X, Y, Z, Q, W, R).

%who is
q_type(Sentence, sentence_parse_is:(A, B)):- beginning_of_question(X), is(Y), Sentence = [X, Y],
A = question_beginning(X), B = helpverb(Y).
%how many
q_type(Sentence, sentence_parse_is:(A, B)):- beginning_of_question(X), indefinite_prns(Y), Sentence = [X, Y],
A = question_beginning(X), B = much_or_many(Y).
q_type(Sentence, sentence_parse_is:(A)):- is(X), Sentence = [X], A = helpverb(X).

person_name(Sentence, names_list(X)):- Sentence = [A, B], ((sex(A, 'f'); sex(A, 'm')); (pronouns_list(A))), 
engl_ap(B), X = cur_person:(A, B).

person_name(Sentence, names_list(X)):- Sentence = [A], ((sex(A, 'f'); sex(A, 'm')); (pronouns_list(A))), X = cur_person:(A).

person_name(Sentence, names_list(A, B)):- Sentence = [X, Y, Z], ((sex(X, 'f'); sex(X, 'm'))), ((sex(Y, 'f'); sex(Y, 'm')); 
(pronouns_list(Y))), engl_ap(Z), A = cur_person:(X), B = relative_(Y, Z).

relations([H], SentencePart):- relatives(H), SentencePart = relation_type(H).
relations([H], SentencePart):- check_relation(H), SentencePart = relation_type(H).
have_or_has([H], SentencePart):- auxiliary_have(H), SentencePart = have_or_has(H).
do_or_does([H], SentencePart):- auxiliary_do(H), SentencePart = do_or_does(H).
q_mark([H], SentencePart):- interrogate(H), SentencePart = special_symbol(H).
