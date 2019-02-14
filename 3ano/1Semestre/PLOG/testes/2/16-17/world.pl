:- use_module(library(lists)), use_module(library(clpfd)).


sweet_recipes(MaxTime,NEggs,RecipeTimes,RecipeEggs,Cookings,Eggs) :-

	length(RecipeTimes, L),

	length(Cookings, 3),

	domain(Cookings, 1, L),
	all_distinct(Cookings),

	element(1, Cookings, A),
	element(A, RecipeTimes, TimeA),
	element(A, RecipeEggs, EggsA),

	element(2, Cookings, B),
	element(B, RecipeTimes, TimeB),
	element(B, RecipeEggs, EggsB),

	element(3, Cookings, C),
	element(C, RecipeTimes, TimeC),
	element(C, RecipeEggs, EggsC),

	Eggs #=< NEggs,
	Time #=< MaxTime,

	Time #= (TimeA+TimeB+TimeC),
	Eggs #= (EggsA+EggsB+EggsC),

	labeling([maximize(Eggs)], Cookings).

replace([_|T], 0, New, [New|T]).
replace([H|T], Index, New, [H|R]) :-
	I1 is Index - 1,
	replace(T, I1, New, R), !.


wrap(Presents, PaperRolls, SelectedPaperRolls):-
	
	length(Presents, L),
	length(PaperRolls, L2),

	length(SelectedPaperRolls, L),

	domain(SelectedPaperRolls, 1, L2),

	generateTasks(Presents, SelectedPaperRolls, [], Tasks),
	generateMachines(1, PaperRolls, [], Machines),
	cumulatives(Tasks, Machines, [bound(upper)]),

	labeling([], SelectedPaperRolls).


generateTasks([], [], Tasks, Tasks).
generateTasks([Present | Presents], [SelectedPaperRoll | SelectedPaperRolls], Tasks, Tasks2):-
	append(Tasks, [task(0, 1, 1, Present, SelectedPaperRoll)], NewTasks),
	generateTasks(Presents, SelectedPaperRolls, NewTasks, Tasks2).


generateMachines(_, [], Machines, Machines).
generateMachines(Id, [PaperRoll | PaperRolls], Machines, Machines2):-
	append(Machines, [machine(Id, PaperRoll)], NewMachines),
	
	Id1 is Id+1,
	generateMachines(Id1, PaperRolls, NewMachines, Machines2).



:- use_module(library(lists)).
:- use_module(library(between)).

prog1(N,M,L1,L2) :-
	length(L1,N),
	N1 is N-1, length(L2,N1),
	findall(E,between(1,M,E),LE),
	fill(L1,LE,LE_),
	fill(L2,LE_,_),
	check(L1,L2).

fill([],LEf,LEf).
fill([X|Xs],LE,LEf) :-
	select(X,LE,LE_),
	fill(Xs,LE_,LEf).

check([_],[]).
check([A,B|R],[X|Xs]) :-
	X #= A+B,
	check([B|R],Xs).


prog2(N,M,L1,L2) :-
	length(L1,N),
	N1 is N-1, length(L2,N1),
	
	domain(L1,1,M),
	all_distinct(L1),

	domain(L2,1,M),
	all_distinct(L2),

	sortX(L1),
	%% sortX(L2),

	check(L1,L2),
	labeling([],L1).


sortX([_]).
sortX([A, B | T]):-
	A #< B,
	sortX([B|T]).