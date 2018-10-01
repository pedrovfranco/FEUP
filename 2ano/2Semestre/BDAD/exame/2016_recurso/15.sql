.mode columns
.headers on
.nullvalue NULL
.width 20 20


select distinct E1.nome
from estudante as E1, amizade, estudante as E2
where E1.ID = amizade.ID1 and E2.ID = amizade.ID2 and E2.nome like "Gabriel%";