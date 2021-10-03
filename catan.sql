DROP DATABASE IF EXISTS catan;
CREATE DATABASE catan;

USE catan;

CREATE TABLE Jugador (
    id INT NOT NULL AUTO_INCREMENT,
    nombre VARCHAR(20) NOT NULL UNIQUE,
    pass VARCHAR(20),
    PRIMARY KEY (id)
)ENGINE=InnoDB;

CREATE TABLE Partida (
    id INT NOT NULL AUTO_INCREMENT,
    fechahora VARCHAR(16),
    duracion INT,
    ganador INT,
    PRIMARY KEY (id),
    FOREIGN KEY (ganador) REFERENCES Jugador(id)
)ENGINE=InnoDB;

CREATE TABLE Participacion (
    idJ INT NOT NULL,
    idP INT NOT NULL,
    puntos INT DEFAULT 0,
    PRIMARY KEY (idJ, idP),
    FOREIGN KEY (idJ) REFERENCES Jugador(id),
    FOREIGN KEY (idP) REFERENCES Partida(id)
)ENGINE=InnoDB;

INSERT INTO Jugador VALUES (0, 'Jonathan', '123456');
INSERT INTO Jugador VALUES (0, 'Alba', 'asdf');
INSERT INTO Jugador VALUES (0, 'Raul', 'qwerty');
INSERT INTO Jugador VALUES (0, 'Miguel', 'bimbo');
INSERT INTO Jugador VALUES (0, 'Antonia', 'tigreton');

INSERT INTO Partida VALUES (0, '01/10/2021 15:00', 20, 1);
INSERT INTO Partida VALUES (0, '02/10/2021 09:00', 15, 2);

INSERT INTO Participacion VALUES (1, 1, 10);
INSERT INTO Participacion VALUES (2, 1, 3);
INSERT INTO Participacion VALUES (3, 1, 8);
INSERT INTO Participacion VALUES (4, 1, 8);

INSERT INTO Participacion VALUES (1, 2, 6);
INSERT INTO Participacion VALUES (2, 2, 12);
INSERT INTO Participacion VALUES (3, 2, 9);
