%player(Name, UserName, Age).
player('Danny', 'Best Player Ever', 27).
player('Annie', 'Worst Player Ever', 24).
player('Harry', 'A-Star Player', 26).
player('Manny', 'The Player', 14).
player('Jonny', 'A Player', 16).


%game(Name, Categories, MinAge).
game('5 ATG', [action, adventure, open-world, multiplayer], 18).
game('Carrier Shift: Game Over', [action, fps, multiplayer, shooter], 16).
game('Duas Botas', [action, free, strategy, moba], 12).


%played(Player, Game, HoursPlayed, PercentUnlocked)
played('Best Player Ever', '5 ATG', 3, 83).
played('Worst Player Ever', '5 ATG', 52, 9).
played('The Player', 'Carrier Shift: Game Over', 44, 22).
played('A Player', 'Carrier Shift: Game Over', 48, 24).
played('A-Star Player', 'Duas Botas', 37, 16).
played('Best Player Ever', 'Duas Botas', 33, 22).

nth02(0, [Element|_], Element):-!.
nth02(_, [], _):-
	false.

nth02(N, [_|T], Element):-
	N2 is N-1,
	nth02(N2, T, Element).



member2([Element|_], Element):-!.
member2([], _):-
	false.

member2([_|T], Element):-
	member2(T, Element).


append2([], Ys, Ys).
append2([X|Xs], Ys, [X|Zs]):-
	append2(Xs, Ys, Zs).


achievedLittle(Player):-
	player(_, Player, _),
	played(Player, _, _, PercentUnlocked),
	PercentUnlocked < 10.


isAgeAppropriate(Name, Game):-
	player(Name, _, Age),
	game(Game, _, PEGI),
	Age @>= PEGI.


timePlayingGames(Player, Games, ListOfTimes, SumTimes):-
	player(_, Player, _),
	timePlayingGames2(Player, Games, ListOfTimes, 0, SumTimes), !.


timePlayingGames2(_, [], [], SumTimes, SumTimes).
timePlayingGames2(Player, [H|T], [H2|T2], Sum, SumTimes):-
	game(H, _, _),
	(played(Player, H, H2, _); H2 = 0),
	Sum2 is Sum + H2,
	timePlayingGames2(Player, T, T2, Sum2, SumTimes).



listGamesOfCategory(Cat):-
	(game(Game, Categories, PEGI),
	member2(Categories, Cat),
	write(Game), write(' ('),write(PEGI),write(')'),nl,
	false);

	true.

:-dynamic
	played/4.
updatePlayer(Player, Game, Hours, Percentage):-
	retract(played(Player, Game, PrevHours, PrevPercentage)),

	NewHours is PrevHours+Hours,
	NewPercentage is PrevPercentage+Percentage,

	assert(played(Player, Game, NewHours, NewPercentage)).

:-dynamic
	littleAchievList/1.
littleAchievement(Player, Games):-
	assert(littleAchievList([])),

	(player(_, Player, _),
	played(Player, Game, _, Percentage),

	Percentage @=< 20,
	retract(littleAchievList(X)),
	
	append2(X, [Game], Y),

	assert(littleAchievList(Y)),

	false); true,

	retract(littleAchievList(Games)).
	


ageRange(MinAge, MaxAge, Players):-
	findall(N,
	 (player(N, _, Age),
	  Age @=< MaxAge,
	  Age @>= MinAge) , 
	 Players).

averageAge(Game, AverageAge):-
	findall(Age,
	 (player(_, U, Age),
	  played(U, Game, _, _)) , 
	 Ages),
	averageList(Ages, AverageAge).


averageList(List, Average):-
	averageList(List, 0, Sum),
	length(List, L),
	Average is Sum/L.


averageList([], Sum, Sum). 
averageList([H|T], Sum, Sum2):-
	Sum1 is Sum+H,
	averageList(T, Sum1, Sum2). 




mostEffectivePlayers(Game, Players):-
	findall([U, Efficiency],
	 (player(_, U, _),
	  played(U, Game, Hours, Percentage),
	  Efficiency is Percentage/Hours
	  ) , 
	 L),
	mostEffectivePlayers2(L, 0, [], Players), !.

mostEffectivePlayers2([], _, Players, Players).
mostEffectivePlayers2([H|T], MaxValue, _, Players2):-	
	nth02(0, H, Player),
	nth02(1, H, Efficiency),


	Efficiency > MaxValue,

	mostEffectivePlayers2(T, Efficiency, [Player], Players2).


mostEffectivePlayers2([H|T], MaxValue, Players, Players2):-
	nth02(0, H, Player),
	nth02(1, H, Efficiency),

	Efficiency = MaxValue,

	append(Players, [Player], Players2),

	mostEffectivePlayers2(T, MaxValue, Players2, Players2).


mostEffectivePlayers2([H|T], MaxValue, Players, Players2):-
	nth02(0, H, _),
	nth02(1, H, Efficiency),

	Efficiency < MaxValue,

	mostEffectivePlayers2(T, MaxValue, Players, Players2).



% Este pedicado averigua se o jogador UserName joga um jogo com menos idade que o permitido.
whatDoesItDo(UserName):-
	player(_, UserName, Age), !,
	\+ ( played(UserName, Game, _, _),
	game(Game, _, PEGI),
	PEGI > Age ).


matz([[8,8,7,7],[2,4,4],[3,3],[1]]).

% Guardaria um lista do género : [[8,8,7,7],[2,4,4],[3,3],[1]] ...]

% Faria isto com um predicado que retira N elementos à esquerda de cada linha, N é o indice da lista começando em 1.


cut(List, N, Output):-
	length(List2, N),
	append(List2, Output, List).



areFar(N, MatDist, Pairs):-
	areFar(N, MatDist, 1, [], Pairs),!.

areFar(_, [], _, Output, Output).
areFar(N, [H|T], Y, List, Output):-
	areFar(N, H, Y, 2, List, List2),

	Y1 is Y+1,
	areFar(N, T, Y1, List2, Output).

areFar(_, [], _, _, Output, Output).
areFar(N, [H|T], Y, X, List, Output):-

	H @>= N,

	Element = X/Y,

	append(List, [Element], List2),

	X1 is X+1,
	areFar(N, T, Y, X1, List2, Output).


areFar(N, [H|T], Y, X, List, Output):-

	H @< N,

	X1 is X+1,
	areFar(N, T, Y, X1, List, Output).



tree([[[[['Australia', [['Sta Helena', 'Anguila'], 'Georgia do Sul']], 'Reino Unido'], ['Servia', 'França']], [['Niger', 'India'], 'Irlanda']], 'Brasil']).