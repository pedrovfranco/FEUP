.mode columns
.headers on
.nullvalue NULL

CREATE TRIGGER IF NOT EXISTS gatilho1
BEFORE INSERT ON Estudante
WHEN (new.ID > 0)
BEGIN
    insert into amizade values (
    	select new.ID, estudante.ID
    	from estudante
    	where estudante.curso = new.curso and estudante.ID <> new.ID
    	)
    insert into amizade values (
    	select estudante.ID, new.ID
    	from estudante
    	where estudante.curso = new.curso and estudante.ID <> new.ID
    	)
END;

