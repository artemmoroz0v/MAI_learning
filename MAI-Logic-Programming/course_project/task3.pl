:- ['familytree.pl'].

%A - man, B - potential brother_in_law.
%First of all, we need to declare that X is man. Secondly, we have to connect husband and wife. We've done this by means of their children.
%Third step: wife is not the husband. Fourth step: we need to find mother of wife. And the final step: find another wife's mother child. Here is the brother in law for our man!
brother_in_law(A, B):-sex(A, 'm'), parent(A, C), parent(D, C), D \= A, parent(E, D), sex(E, 'f'), parent(E, B), sex(B, 'm').
%?-brother_in_law('Борис Морозов', Y).
%?-brother_in_law(X, Y).
%?-brother_in_law('Алексей Горшелев', Y).