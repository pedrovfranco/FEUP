.mode columns
.headers on
.nullvalue NULL
.width 20 20

select E1.ID as e1id, E3.ID as e3id
from (
	select distinct E1.ID, E3.ID
	from estudante E1, amizade A1, estudante E2, amizade A2, estudante E3
	where E1.ID = A1.ID1 and E2.ID = A1.ID2 and E2.ID = A2.ID1 and A1.ID1 <> A2.ID2 and A2.ID2 = E3.ID
	)
where e1id, e3id not in (
	select distinct E1.ID, E3.ID
	from estudante E1, amizade A1, estudante E2, amizade A2, estudante E3, amizade A3
	where E1.ID = A1.ID1 and E2.ID = A1.ID2 and E2.ID = A2.ID1 and A1.ID1 <> A2.ID2 and A2.ID2 = E3.ID and A3.ID1 == E1.ID and A3.ID2 == E3.ID
);