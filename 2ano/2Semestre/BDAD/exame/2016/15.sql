.mode columns
.headers on
.nullvalue NULL


select pilas from (
	select nome as pilas, count(*) as conta
	from estudante, amizade
	where amizade.ID1 = estudante.ID
	group by nome
	)
where (conta > 3);
