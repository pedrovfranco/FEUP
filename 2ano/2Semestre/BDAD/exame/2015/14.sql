.mode columns
.headers on
.nullvalue NULL
.width 20 20

PRAGMA foreign_keys = ON;

select caption
from (
	select caption, julianday(uploadDate) - julianday(creationDate) as deltaTime
	from photo, user
	where deltaTime == 2
	and user.id = photo.user
	and user.name = "Daniel Ramos"
	);