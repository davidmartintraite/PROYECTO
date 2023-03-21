DROP DATABASE IF EXIST bd;
CREATE DATABASE bd;
USE bd;

CREATE TABLE Jugador(
	ID INT,
	NOMBRE VARCHAR(20),
	CONTRASEÑA VARCHAR(20),
	MAIL VARCHAR(50),
	PUNTOS INT,
	PRIMARY KEY(ID)
)ENGINE = InnoDB;

CREATE TABLE Carta(
	ID INT,
	PALABRA VARCHAR(20),
	BAN1 VARCHAR(20),
	BAN2 VARCHAR(20),
	BAN3 VARCHAR(20),
	DIFICULTAD VARCHAR(20)
)ENGINE=InnoDB;

CREATE TABLE Partida(
	ID INT,
	JUG1 INT,
	JUG2 INT,
	JUG3 INT,
	JUG4 INT,
	IDCARTA INT,
	PUN1 INT,
	PUN2 INT,
	PUN3 INT,
	PUN4 INT,
	FORGEIN KEY (JUG1) REFERENCES Jugador(ID),
	FORGEIN KEY (JUG2) REFERENCES Jugador(ID),
	FORGEIN KEY (JUG3) REFERENCES Jugador(ID),
	FORGEIN KEY (JUG4) REFERENCES Jugador(ID),
	FORGEIN KEY (IDCARTA) REFERENCES Carta(ID),
)ENGINE = InnoDB;

CREATE TABLE Lista(
	IDJUGADOR INT,
	IDCARTA INT,
	PUNTOS INT,
	FORGEIN KEY (IDJUGADOR) REFERENCES Jugador(ID),
	FORGEIN KEY (IDCARTA) REFERENCES Carta(ID)
)ENGINE = InnoDB;		
	
	

	

