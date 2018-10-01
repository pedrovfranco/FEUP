select estudante.nome from
	select estudante.nome, count(*) as conta
	from estudante, amizade
	where amizade.id1 = estudante.idEstudante
where conta > 3;