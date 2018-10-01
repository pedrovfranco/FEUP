.mode columns
.headers on
.nullvalue NULL

select nome, anoCurricular from (
	select nome, anoCurricular, max(nrDeAmigos) as maximoAmigos from (
		select nome, anoCurricular, count(*) as nrDeAmigos
		from estudante, amizade
		where amizade.id1 = estudante.ID
		group by nome
		)
	)
;