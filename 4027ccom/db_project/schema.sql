CREATE TABLE `Obras` (
	`Obra ID` INT(4) NOT NULL AUTO_INCREMENT,
	`Teatro ID` INT(4) NOT NULL,
	`Caja` INT(2) NOT NULL,
	`Número de Producción` INT(4) NOT NULL UNIQUE,
	`Título` VARCHAR(128) NOT NULL,
	`Año` INT(4) NOT NULL,
	`Notas` VARCHAR(500),
	PRIMARY KEY (`Obra ID`)
);

CREATE TABLE `Teatros` (
	`Teatro ID` INT(4) NOT NULL AUTO_INCREMENT,
	`Nombre` VARCHAR(32) NOT NULL UNIQUE,
	PRIMARY KEY (`Teatro ID`)
);

CREATE TABLE `Autores` (
	`Autor ID` INT(4) NOT NULL AUTO_INCREMENT,
	`Primer Nombre` VARCHAR(12) NOT NULL,
	`Segundo Nombre` VARCHAR(12),
	`Apellido` VARCHAR(32) NOT NULL,
	PRIMARY KEY (`Autor ID`)
);

CREATE TABLE `Directores` (
	`Director ID` INT(4) NOT NULL AUTO_INCREMENT,
	`Primer Nombre` VARCHAR(12) NOT NULL,
	`Segundo Nombre` VARCHAR(12),
	`Apellido` VARCHAR(32) NOT NULL,
	PRIMARY KEY (`Director ID`)
);

CREATE TABLE `Diseñadores de Escenografía` (
	`Diseñador ID` INT(4) NOT NULL AUTO_INCREMENT,
	`Primer Nombre` VARCHAR(12) NOT NULL,
	`Segundo Nombre` VARCHAR(12),
	`Apellido` VARCHAR(32) NOT NULL,
	PRIMARY KEY (`Diseñador ID`)
);

CREATE TABLE `Diseñadores de Vestuario` (
	`Diseñador ID` INT(4) NOT NULL AUTO_INCREMENT,
	`Primer Nombre` VARCHAR(12) NOT NULL,
	`Segundo Nombre` VARCHAR(12),
	`Apellido` VARCHAR(32) NOT NULL,
	PRIMARY KEY (`Diseñador ID`)
);

CREATE TABLE `Diseñadores de Luces` (
	`Diseñador ID` INT(4) NOT NULL AUTO_INCREMENT,
	`Primer Nombre` VARCHAR(12) NOT NULL,
	`Segundo Nombre` VARCHAR(12),
	`Apellido` VARCHAR(32) NOT NULL,
	PRIMARY KEY (`Diseñador ID`)
);

CREATE TABLE `Autores de Obras` (
	`Autor ID` INT(4) NOT NULL,
	`Obra ID` INT(4) NOT NULL,
	PRIMARY KEY (`Autor ID`,`Obra ID`)
);

CREATE TABLE `Directores de Obras` (
	`Director ID` INT(4) NOT NULL,
	`Obra ID` INT(4) NOT NULL,
	PRIMARY KEY (`Director ID`,`Obra ID`)
);

CREATE TABLE `Diseño de Luces` (
	`Diseñador ID` INT(4) NOT NULL,
	`Obra ID` INT(4) NOT NULL,
	PRIMARY KEY (`Diseñador ID`,`Obra ID`)
);

CREATE TABLE `Diseño de Escenografía` (
	`Diseñador ID` INT(4) NOT NULL,
	`Obra ID` INT(4) NOT NULL,
	PRIMARY KEY (`Diseñador ID`,`Obra ID`)
);

CREATE TABLE `Diseño de Vestuario` (
	`Diseñador ID` INT(4) NOT NULL,
	`Obra ID` INT(4) NOT NULL,
	PRIMARY KEY (`Diseñador ID`,`Obra ID`)
);

ALTER TABLE `Obras` ADD CONSTRAINT `Obras_fk0` FOREIGN KEY (`Teatro ID`) REFERENCES `Teatros`(`Teatro ID`);

ALTER TABLE `Autores de Obras` ADD CONSTRAINT `Autores de Obras_fk0` FOREIGN KEY (`Autor ID`) REFERENCES `Autores`(`Autor ID`);

ALTER TABLE `Autores de Obras` ADD CONSTRAINT `Autores de Obras_fk1` FOREIGN KEY (`Obra ID`) REFERENCES `Obras`(`Obra ID`);

ALTER TABLE `Directores de Obras` ADD CONSTRAINT `Directores de Obras_fk0` FOREIGN KEY (`Director ID`) REFERENCES `Directores`(`Director ID`);

ALTER TABLE `Directores de Obras` ADD CONSTRAINT `Directores de Obras_fk1` FOREIGN KEY (`Obra ID`) REFERENCES `Obras`(`Obra ID`);

ALTER TABLE `Diseño de Luces` ADD CONSTRAINT `Diseño de Luces_fk0` FOREIGN KEY (`Diseñador ID`) REFERENCES `Diseñadores de Luces`(`Diseñador ID`);

ALTER TABLE `Diseño de Luces` ADD CONSTRAINT `Diseño de Luces_fk1` FOREIGN KEY (`Obra ID`) REFERENCES `Obras`(`Obra ID`);

ALTER TABLE `Diseño de Escenografía` ADD CONSTRAINT `Diseño de Escenografía_fk0` FOREIGN KEY (`Diseñador ID`) REFERENCES `Diseñadores de Escenografía`(`Diseñador ID`);

ALTER TABLE `Diseño de Escenografía` ADD CONSTRAINT `Diseño de Escenografía_fk1` FOREIGN KEY (`Obra ID`) REFERENCES `Obras`(`Obra ID`);

ALTER TABLE `Diseño de Vestuario` ADD CONSTRAINT `Diseño de Vestuario_fk0` FOREIGN KEY (`Diseñador ID`) REFERENCES `Diseñadores de Vestuario`(`Diseñador ID`);

ALTER TABLE `Diseño de Vestuario` ADD CONSTRAINT `Diseño de Vestuario_fk1` FOREIGN KEY (`Obra ID`) REFERENCES `Obras`(`Obra ID`);
