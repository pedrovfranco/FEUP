.mode columns
.headers on
.nullvalue NULL


select estudante.nome, curso.nome
from curso, estudante
where estudante.curso = curso.ID and anoCurricular = 3;