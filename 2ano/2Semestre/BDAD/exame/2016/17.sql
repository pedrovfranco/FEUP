.mode columns
.headers on
.nullvalue NULL


-- select distinct A3.id2 as id23 from (
-- 	select A2.id2 as id22 from (
-- 		select amizade.id2 as id21
-- 		from estudante, amizade
-- 		where estudante.nome = "Miguel Sampaio" and estudante.id = amizade.id1
-- 		),
-- 		amizade as A2
-- 	where A2.id1 = id21
-- 	),
-- 	amizade as A3
-- where A3.id1 = id22;


select distinct A3.id2
from estudante, amizade A1, amizade A2, amizade A3
where estudante.nome = "Miguel Sampaio" and estudante.id = A1.id1
and A1.ID2 = A2.ID1 and A2.ID2 = A3.ID1;