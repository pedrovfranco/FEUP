.mode columns
.headers on
.nullvalue NULL
.width 20 20

PRAGMA foreign_keys = ON;

select user.name
from user
where id not in (
	select distinct user
	from photo
	);