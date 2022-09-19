%Task 15.

%Okay, let's start. 
%In fact, all we need is translate our task to predicates. No more!
%Firstly, we can designate that we have some ping-pong players:
pingpongplayers(Neighbor1, Neighbor2, List):-List = [Neighbor1,Neighbor2,_,_]; List = [Neighbor2,Neighbor1,_,_].
%Secondly we MUST know are two closed in list people neighbors or not:
checkneighbors(Neighbor1, Neighbor2, List):-List = [_,Neighbor1,Neighbor2,_]; List = [_,Neighbor2,Neighbor1,_]. 
%All right. Now we should pay attention on fact that neighbors always drive  car:
driveacar(Neighbor1,Neighbor2):-checkneighbors(Neighbor1,_,Neighbor2).
%Don't forget about fact that some people in our task have met each other only one time:
singlemeeting(Neighbor1,Neighbor2,List):-not(checkneighbors(Neighbor1,Neighbor2,List)), not(pingpongplayers(Neighbor1,Neighbor2,List)).
%Great! And now we have to do only one thing: create our main predicate.
%According the task, the length of our list is four.

mainpredicate(List):-length(List, 4),                       
%We should initialize each member in list through the "member" predicate:
member((_,_,4), List), member((_,_,3), List), member((_,_,2), List), member((_,_,1), List),
%Now we should initialize profession of each person:              
member((_,baker,_), List), member((_,doctor,_), List), member((_,policeman,_), List), member((_,engineer,_), List),
%The important fact: Korneev and Dokshin are neighbors (according to the task!)             
checkneighbors((korneev,_,_), (dokshin,_,_), List), driveacar((korneev,_,_), List),driveacar((dokshin,_,_), List),
%According to the task, we need to have  prediate which will be reliable for connection of each person's age: 
member((_,policeman, PolicemanYO), List), member((_,doctor,DoctorYO), List), PolicemanYO > DoctorYO,
member((dokshin,_, DokshinYO), List), member((mareev,_, MareevYO), List), DokshinYO > MareevYO,
member((_,engineer, EngineerYO), List), PolicemanYO > EngineerYO,
%Last part: Policeman is not living close to doctor, engineer and policeman have met each other only one time,
%baker is not driving  car and Korneev and Skobelev are ping-pong players.
not(checkneighbors((_,policeman,_), (_,doctor,_), List)), singlemeeting((_,engineer,_), (_,policeman,_), List), 
not(driveacar((_,baker,_), List)), pingpongplayers((korneev,_,_),(skobelev,_,_), List).
