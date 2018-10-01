.mode columns
.headers on
.nullvalue NULL
.width 20 20

PRAGMA foreign_keys = ON;

select *
from photo, likes
where photo.id = likes.photo;