%Using of standart predicate - number. It's nessecary for finding a rational number in our string.
count([Head], Head):- number(Head).

%Here is difference.
count(Value, Result) :- append(First, [-|Second], Value), count(First, Res1), count(Second, Res2), !, Result is Res1 - Res2.
%Here is sum.
count(Value, Result) :- append(First, [+|Second], Value), count(First, Res1), count(Second, Res2), !, Result is Res1 + Res2.
%Here is multiplication.
count(Value, Result) :- append(First, [*|Second], Value), count(First, Res1), count(Second, Res2), !, Result is Res1 * Res2.
%Here is division.
count(Value, Result) :- append(First, [/|Second], Value), count(First, Res1), count(Second, Res2), !, Res2 \= 0, Result is Res1 / Res2.
%Here is exponentiation.
count(Value, Result) :- append(First, [^|Second], Value), count(First, Res1), count(Second, Res2), !, Result is Res1 ** Res2.
