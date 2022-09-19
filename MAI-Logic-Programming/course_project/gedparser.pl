%Let's start! First of all, we need to introduce some variables. As everyone know, GEDCOM file is not easy to read.
%That's why it is necessary to let programm know something about symbols in GEDCOM file. So, come on. Here we are parsing some file:
nameline(A, [X, Y, Z|Something], B, C):-X = "0", Y = B, Z = "INDI", read_string(A, "\n", "\r",_,_), read_string(A, "\n", "\r", _, _),
read_string(A, "\n", "\r",_, N), split_string(N, " ", "", NL), linetreatment(NL, CN_), read_string(A, "\n", "\r",_, S), 
split_string(S, " ", "", SL), linetreatment(SL, CS), string_concat("'", CN_, CN), string_concat(CN, " ", R), string_concat(R, CS, R_), string_concat(R_, "'", C).
nameline(A, B, C, D).
namefile(A, B, C):-at_end_of_stream(A), !.
namefile(A, B, C):-read_string(A, "\n", "\r", EOF, S), split_string(S, " ", "", SS), nameline(A, SS, B, C), namefile(A, B, C).
%We need to initialize every person. Let's think about it. 
%The best idea in my opinion is juxtapose to every person his ID.
getperson(A, B):-open("familytree.ged", read, C), namefile(C, A, B).
%Super. Now we have to find out ALL the childs in a family. Let's write a special predicate and do this in the next case.
%How does this predicate works? So let me explain it: first argument is some symbol, as a third. Second argument is our variable
%which will be a child. We also need a special predicate for help in parsing. Let's name it "linetreatment". %CHIL is a keyword in GEDCOM file.
childchecker([A, "CHIL", B]).
linetreatment([A, B, C], C).
%Good job. The next task for me - initialize every child. 
%So, let's create a predicate called "childtreatment" which will contain a lot of standart predicates :D
childtreatment(A, RESULT):-read_string(A, "\n", "\r",_, B), split_string(B, " ", "", C), childchecker(C), linetreatment(C, CUR), 
childtreatment(A, P), RESULT = [CUR|P].
childtreatment(A, []).
%Fantastic! Next case that have to be done: in current step we have a necessity to print our work.
%The idea is too trivial: we must check ID of each person and create a special predicate for this operation.
printpredicate(HID, WID, [], FD1).
printpredicate(HID, WID, [CURID|TID], FD1):-getperson(CURID, CURRENT), getperson(HID, HUSBAND), getperson(WID, WIFE), write(FD1, "parent("), 
write(FD1, HUSBAND), write(FD1, ", "), write(FD1, CURRENT), write(FD1, ").\n"), write(FD1, "parent("), write(FD1, WIFE), write(FD1, ", "), 
write(FD1, CURRENT), write(FD1, ").\n"), printpredicate(HID, WID, TID, FD1).
%Help predicate for making "familytree.pl". We unfortunately can initialize wrong line. That's why we need to be sure that we are right.
parentline(A, B, [X, Y, Z|Something]):-X = "0", Y = FID, Z = "FAM", read_string(A, "\n", "\r",_,_), read_string(A, "\n", "\r", SS, HS),
split_string(HS, " ", "", HSL), linetreatment(HSL, CH), read_string(A, "\n", "\r",_, WF),
split_string(WF, " ", "", WL), linetreatment(WL, CW), childtreatment(A, CC), printpredicate(CH, CW, CC, B), !.
parentline(A, B, C).
%Great, but we forgot about gedcome file format. For clear parsing our familytree.ged we need ignore some useful lines.
%Let's create some predicate:
sexfile(A, B):-at_end_of_stream(A), !.
sexfile(A, B):-read_string(A, "\n", "\r", EOF, S), split_string(S, " ", "", SS), sexline(A, B, SS), sexfile(A, B).
parentfile(A, B):-at_end_of_stream(A), !.
parentfile(A, B):-read_string(A, "\n", "\r", EOF, S), split_string(S, " ", "", SS), parentline(A, B, SS), parentfile(A, B).
%Awesome! It's time for append our results by means of next predicates:
%These predicates are responsible for writing sex: male or female.
fillfile("M", N, S, FD1):-string_concat("'", N, N_), string_concat(N_, " ", RT), string_concat(RT, S, R_), string_concat(R_, "'", R),
write(FD1, "sex("), write(FD1, R), write(FD1, ", 'm').\n").
fillfile("F", N, S, FD1):-string_concat("'", N, N_), string_concat(N_, " ", RT), string_concat(RT, S, R_), string_concat(R_, "'", R),
write(FD1, "sex("), write(FD1, R), write(FD1, ", 'f').\n").
%Penultimate predicate is responsible for the final version of how the content in "familytree.pl" will look.
sexline(FD0, FD1, [X, Y, W|Something]):-X = "0", Y = FID, W = "INDI", read_string(FD0, "\n", "\r",_,_), read_string(FD0, "\n", "\r",SS,ST),
read_string(FD0, "\n", "\r",_, NS), split_string(NS, " ", "", NL), linetreatment(NL, N), read_string(FD0, "\n", "\r", _, SN), split_string(SN, " ", "", SNL),
linetreatment(SNL, SN1), read_string(FD0, "\n", "\r",_, S_), split_string(S_, " ", "", SL), linetreatment(SL, S), fillfile(S, N, SN1, FD1). 
sexline(S1, S2, S3).
%Conrats! Now only one thing still remains: we have to get the final result. It's time to run our gedparser. 
%It will fill the "familytree.pl" file with a lot of connections which is need for next tasks. 
%In the end we will be able to see two predicates: 
%parent and sex. Parent-predicate sets family-connection between child and parent. Sex-predicate set gender-connection of each person in family tree. 
%Here we just need to create three fd-s (file-descriptors): two for reading from lines and one for writing in familytree.pl file.
gedparser:-open("familytree.ged", read, FD0), open("familytree.pl", write, FD2), parentfile(FD0, FD2), close(FD0), open("familytree.ged", read, FD1), 
sexfile(FD1, FD2), close(FD2), close(FD1). 