%participant(Id,Age,Performance)
participant(1234, 17, 'Pé coxinho').
participant(3423, 21, 'Programar com os pés').
participant(3788, 20, 'Sing a Bit').
participant(4865, 22, 'Pontes de esparguete').
participant(8937, 19, 'Pontes de pen-drives').
participant(2564, 20, 'Moodle hack').

%performance(Id,Times)
performance(1234,[120,120,120,120]).
performance(3423,[32,120,45,120]).
performance(3788,[110,2,6,43]).
performance(4865,[120,120,110,120]).
performance(8937,[97,101,105,110]).



madeItThrough(Participant):-
	participant(Participant, _, _),
	performance(Participant, Times),
	madeItThrough2(Times).


madeItThrough2([]):-
	false,!.
madeItThrough2([H|T]):-
	H = 120,!;
	madeItThrough2(T).




juriTimes(Participants, JuriMember, Times, Total):-
	NewJuriMember is JuriMember-1,

	juriTimes2(Participants, NewJuriMember, Times, 0, Total).


juriTimes2([], _, [], Total, Total).
juriTimes2([Participant|T], JuriMember, [Time|T2], Total1, Total2):-
	participant(Participant, _, _),
	performance(Participant, Times),

	nth0(JuriMember, Times, Time),
	NewTotal1 is Total1+Time,

	juriTimes2(T, JuriMember, T2, NewTotal1, Total2).


patientJuri(JuriMember):-
	NewJuriMember is JuriMember-1,

	participant(Participant1, _, _),
	performance(Participant1, Times1),
	nth0(NewJuriMember, Times1, Time1),

	participant(Participant2, _, _),
	performance(Participant2, Times2),
	nth0(NewJuriMember, Times2, Time2),

	Participant1 \= Participant2,
	Time1 = 120,
	Time2 = 120, !.





%% isOrdered([_|[]]).
%% isOrdered([H|T]):-
%% 	nth0(0, T, H2),
%% 	H =< H2,
%% 	isOrdered(T), !.

%% getAllParticipants(List):-
%% 	getAllParticipants([], List).

%% getAllParticipants(List, List).
%% getAllParticipants(List, List2):-
%% 	participant(Participant, _, _),
%% 	length(List, L),
%% 	L1 is L-1,

%% 	((nth0(L1, List, Previous), Previous =< Participant) ;L1 < 0),

	
%% 	\+(member(Participant, List)),
%% 	append(List, [Participant], NewList),
%% 	getAllParticipants(NewList, List2).

%% patientJuri(JuriMember):-
%% 	juriTimes([1234,3423,3788,4865,8937], JuriMember, Times, _),
%% 	patientJuri2(JuriMember, 0, Times), !.

%% patientJuri2(_, 2, _).

%% patientJuri2(_, _, []):-
%% 	false.

%% patientJuri2(JuriMember, Counter1, [H|T]):-

%% 	H = 120,
%% 	Counter2 is Counter1+1,
%% 	patientJuri2(JuriMember, Counter2, T).

%% patientJuri2(JuriMember, Counter1, [H|T]):-
%% 	H \= 120,
%% 	patientJuri2(JuriMember, Counter1, T).



bestParticipant(P, P, _):-
	false.

bestParticipant(P1, P2, P):-
	participant(P1, _, _),
	performance(P1, Times1),
	sumTimes(Times1, Sum1),

	participant(P2, _, _),
	performance(P2, Times2),
	sumTimes(Times2, Sum2),

	Sum1 > Sum2,
	P = P1, !.

bestParticipant(P1, P2, P):-
	participant(P1, _, _),
	performance(P1, Times1),
	sumTimes(Times1, Sum1),

	participant(P2, _, _),
	performance(P2, Times2),
	sumTimes(Times2, Sum2),

	Sum1 < Sum2,
	P = P2, !.




sumTimes(Times, Sum1):-
	sumTimes(Times, 0, Sum1).

sumTimes([], Sum, Sum).
sumTimes([H|T], Sum1, Sum2):-
	NewSum1 is Sum1+H,
	sumTimes(T, NewSum1, Sum2).

isMember([Target|_], Target):-
	!.
isMember([], _):-
	false.

isMember([_|T], Target):-
	isMember(T, Target).


allPerfs:-
	(participant(Participant, _, Theme),
	performance(Participant, Times),

	write(Participant),write(':'),
	write(Theme),write(':'),
	write(Times),nl,

	false);
	
	true.




nSuccessfulParticipants(T):-
	findall(P, (participant(P, _, _), performance(P, Times), allMembers(Times, 120)), L),
	length(L, T).

allMembers([], _).
allMembers([H|T], Value):-
	H = Value,
	allMembers(T, Value).




juriFans(JuriFansList):-
	findall(P-L,
	(participant(P, _, _), performance(P, Times), juriFans2(Times, L)), 
	JuriFansList).

juriFans2(Times, Output):-
	I is 1,
	juriFans2(Times, I, [], Output).

juriFans2([], _, Output, Output).
juriFans2([H|T], I, List2, Output):-
	H = 120,
	
	append(List2, [I], List3),
	I1 is I+1,
	juriFans2(T, I1, List3, Output).

juriFans2([H|T], I, List2, Output):-
	H \= 120,
	
	I1 is I+1,
	juriFans2(T, I1, List2, Output).




:- use_module(library(lists)).

eligibleOutcome(Id,Perf,TT) :-
	performance(Id,Times),
	madeItThrough(Id),
	participant(Id,_,Perf),
	sumlist(Times,TT).


nextPhase(N, Participants):-
	findall(TT-P-T, eligibleOutcome(P,T,TT), L),
	sort(1, @>, L, L2),
	length(L2, L2l),
	L2l @>= N,
	N2 is L2l-N,
	cutLastElements(L2, N2, Participants).


cutLastElements(List, N, List2):-
	length(List, L),
	N2 is L-N,
	cutLastElements2(List, N2, List2), !.


cutLastElements2(_, 0, []).
cutLastElements2([H|T], N, [H|T2]):-
	N2 is N-1,
	cutLastElements2(T, N2, T2).
	


% 9:
% O predicado predX cria uma lista de participantes e uma lista de temas respetivo, para os participantes com idade menor ou igual a Q.


predX(Q,[R|Rs],[P|Ps]) :-
participant(R,I,P), I=<Q, !,
predX(Q,Rs,Ps).
predX(Q,[R|Rs],Ps) :-
participant(R,I,_), I>Q,
predX(Q,Rs,Ps).
predX(_,[],[]).

impoe(X,L) :-
    length(Mid,X),
    append(L1,[X|_],L), append(_,[X|Mid],L1).