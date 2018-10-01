.mode columns
.headers on
.nullvalue NULL
.width 20 20 


select E1.nome, E2.nome
from estudante E1, amizade, estudante E2
where E1.ID = amizade.ID1 and amizade.ID2 = E2.ID;