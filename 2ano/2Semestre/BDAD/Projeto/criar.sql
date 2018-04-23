-- PRAGMA foreign_keys = ON;
-- db.execSQL(ENABLE_FOREIGN_KEYS);

CREATE TABLE Praia(
    idPraia INTEGER PRIMARY KEY,
    nome TEXT NOT NULL,
    bandeiraAzul BIT NOT NULL,
    capacidade INTEGER NOT NULL,
    dataDeInaguguracao DATE,
    localizacao GEOGRAPHY
);

CREATE TABLE Rio(
	idRio INTEGER PRIMARY KEY REFERENCES Praia(idRio),
  	caudal REAL NOT NULL,
 	profundidade REAL NOT NULL,
 	largura REAL NOT NULL
);

CREATE TABLE Albufeira(
	idAlbufeira INTEGER PRIMARY KEY REFERENCES Praia(idAlbufeira),
  	area REAL NOT NULL
);

CREATE TABLE Servico(
    idServico INTEGER PRIMARY KEY,
    nome TEXT NOT NULL
);

CREATE TABLE PraiaServico(
	idPraia INTEGER REFERENCES Praia(idPraia),
	idServico INTEGER REFERENCES Servico(idServico),
	PRIMARY KEY (idPraia, idServico)
);

CREATE TABLE PontoTuristico(
    idPontoTuristico INTEGER PRIMARY KEY,
    nome TEXT NOT NULL,
    localizacao GEOGRAPHY
);

CREATE TABLE PraiaPontoTuristico(
	idPraia INTEGER REFERENCES Praia(idPraia),
	idPontoTuristico INTEGER REFERENCES PontoTuristico(idPontoTuristico),
	PRIMARY KEY (idPraia, idPontoTuristico)
);

CREATE TABLE Evento(
    idEvento INTEGER PRIMARY KEY,
    nome TEXT NOT NULL,
    inicio DATE,
    fim DATE
);

CREATE TABLE EventoPraia(
	idEvento INTEGER PRIMARY KEY REFERENCES Evento(idEvento),
	idPraia INTEGER REFERENCES Praia(idPraia)
);

CREATE TABLE EventoTuristico(
	idEvento INTEGER PRIMARY KEY REFERENCES Evento(idEvento),
	idPontoTuristico INTEGER REFERENCES PontoTuristico(idPontoTuristico)
);

CREATE TABLE Rating(
	idRating INTEGER PRIMARY KEY,
	pontuacao INTEGER,
	comentario TEXT NOT NULL,
	data DATE
);

CREATE TABLE RatingServico(
	idRating INTEGER PRIMARY KEY REFERENCES Rating(idRating),
	idServico INTEGER REFERENCES Servico(idServico)
);

CREATE TABLE RatingPraia(
	idRating INTEGER PRIMARY KEY REFERENCES Rating(idRating),
	idPraia INTEGER REFERENCES Praia(idPraia)
);

CREATE TABLE RatingTuristico(
	idRating INTEGER PRIMARY KEY REFERENCES Rating(idRating),
	idPontoTuristico INTEGER REFERENCES PontoTuristico(idPontoTuristico)
);

CREATE TABLE Horario(
	epoca TEXT PRIMARY KEY NOT NULL
);

CREATE TABLE HorarioPraia(
	epoca TEXT PRIMARY KEY NOT NULL REFERENCES Horario(epoca),
	idPraia INTEGER REFERENCES Praia(idPraia)
);

CREATE TABLE HorarioServico(
	epoca TEXT PRIMARY KEY NOT NULL REFERENCES Horario(epoca),
	idServico INTEGER REFERENCES Servico(idServico)
);

CREATE TABLE HorarioPontoTuristico(
	epoca TEXT PRIMARY KEY NOT NULL REFERENCES Horario(epoca),
	idPontoTuristico INTEGER REFERENCES PontoTuristico(idPontoTuristico)
);