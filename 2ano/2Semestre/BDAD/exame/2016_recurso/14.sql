.mode columns
.headers on
.nullvalue NULL
.width 20 20


select estudante.nome
from estudante, curso
where estudante.curso = curso.ID and curso.nome = "MIEIC" and (estudante.nome like "%a%" or estudante.nome like "%A%");