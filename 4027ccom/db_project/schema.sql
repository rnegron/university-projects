CREATE TABLE `Obras` (
	`obra_id` INT(4) AUTO_INCREMENT,
	`teatro_id` INT(4) NOT NULL,
	`caja` INT(2) NOT NULL,
	`num_de_prod` INT(4) NOT NULL,
	`titulo` VARCHAR(1024) NOT NULL,
	`año` INT(4) NOT NULL,
	`notas` VARCHAR(4096),
	PRIMARY KEY (`obra_id`)
);

CREATE TABLE `Teatros` (
	`teatro_id` INT(4) AUTO_INCREMENT,
	`nombre_teatro` VARCHAR(32) NOT NULL UNIQUE,
	PRIMARY KEY (`teatro_id`)
);

CREATE TABLE `Autores` (
	`autor_id` INT(4) AUTO_INCREMENT,
	`primer_nombre` VARCHAR(12) NOT NULL,
	`segundo_nombre` VARCHAR(12),
	`apellido` VARCHAR(32) NOT NULL,
    `nombre_completo` VARCHAR(56) GENERATED ALWAYS as (CONCAT(primer_nombre, ' ', apellido)) NOT NULL,
	PRIMARY KEY (`autor_id`)
);

CREATE TABLE `Directores` (
	`director_id` INT(4) AUTO_INCREMENT,
	`primer_nombre` VARCHAR(12) NOT NULL,
	`segundo_nombre` VARCHAR(12),
	`apellido` VARCHAR(32),
    `nombre_completo` VARCHAR(56) GENERATED ALWAYS as (CONCAT(primer_nombre, ' ', apellido)) NOT NULL,
	PRIMARY KEY (`director_id`)
);

CREATE TABLE `Diseñadores_de_Escenografia` (
	`d_id` INT(4) AUTO_INCREMENT,
	`primer_nombre` VARCHAR(12) NOT NULL,
	`segundo_nombre` VARCHAR(12),
	`apellido` VARCHAR(32),
    `nombre_completo` VARCHAR(56) GENERATED ALWAYS as (CONCAT(primer_nombre, ' ', apellido)) NOT NULL,
	PRIMARY KEY (`d_id`)
);

CREATE TABLE `Diseñadores_de_Vestuario` (
	`d_id` INT(4) AUTO_INCREMENT,
	`primer_nombre` VARCHAR(12) NOT NULL,
	`segundo_nombre` VARCHAR(12),
	`apellido` VARCHAR(32),
    `nombre_completo` VARCHAR(56) GENERATED ALWAYS as (CONCAT(primer_nombre, ' ', apellido)) NOT NULL,
	PRIMARY KEY (`d_id`)
);

CREATE TABLE `Diseñadores_de_Luces` (
	`d_id` INT(4) AUTO_INCREMENT,
	`primer_nombre` VARCHAR(12) NOT NULL,
	`segundo_nombre` VARCHAR(12),
	`apellido` VARCHAR(32),
    `nombre_completo` VARCHAR(56) GENERATED ALWAYS as (CONCAT(primer_nombre, ' ', apellido)) NOT NULL,
	PRIMARY KEY (`d_id`)
);

CREATE TABLE `Autores_de_Obras` (
	`autor_id` INT(4),
	`obra_id` INT(4),
	PRIMARY KEY (`autor_id`,`obra_id`)
);

CREATE TABLE `Directores_de_Obras` (
	`director_id` INT(4),
	`obra_id` INT(4),
	PRIMARY KEY (`director_id`,`obra_id`)
);

CREATE TABLE `Diseño_de_Luces` (
	`d_id` INT(4),
	`obra_id` INT(4),
	PRIMARY KEY (`d_id`,`obra_id`)
);

CREATE TABLE `Diseño_de_Escenografía` (
	`d_id` INT(4),
	`obra_id` INT(4),
	PRIMARY KEY (`d_id`,`obra_id`)
);

CREATE TABLE `Diseño_de_Vestuario` (
	`d_id` INT(4),
	`obra_id` INT(4),
	PRIMARY KEY (`d_id`,`obra_id`)
);

ALTER TABLE `Obras` ADD CONSTRAINT `Obras_fk0` FOREIGN KEY (`teatro_id`) REFERENCES `Teatros`(`teatro_id`);

ALTER TABLE `Autores_de_Obras` ADD CONSTRAINT `Autores_de_Obras_fk0` FOREIGN KEY (`autor_id`) REFERENCES `Autores`(`autor_id`);

ALTER TABLE `Autores_de_Obras` ADD CONSTRAINT `Autores_de_Obras_fk1` FOREIGN KEY (`obra_id`) REFERENCES `Obras`(`obra_id`);

ALTER TABLE `Directores_de_Obras` ADD CONSTRAINT `Directores_de_Obras_fk0` FOREIGN KEY (`director_id`) REFERENCES `Directores`(`director_id`);

ALTER TABLE `Directores_de_Obras` ADD CONSTRAINT `Directores_de_Obras_fk1` FOREIGN KEY (`obra_id`) REFERENCES `Obras`(`obra_id`);

ALTER TABLE `Diseño_de_Luces` ADD CONSTRAINT `Diseño_de_Luces_fk0` FOREIGN KEY (`d_id`) REFERENCES `Diseñadores_de_Luces`(`d_id`);

ALTER TABLE `Diseño_de_Luces` ADD CONSTRAINT `Diseño_de_Luces_fk1` FOREIGN KEY (`obra_id`) REFERENCES `Obras`(`obra_id`);

ALTER TABLE `Diseño_de_Escenografía` ADD CONSTRAINT `Diseño_de_Escenografía_fk0` FOREIGN KEY (`d_id`) REFERENCES `Diseñadores_de_Escenografia`(`d_id`);

ALTER TABLE `Diseño_de_Escenografía` ADD CONSTRAINT `Diseño_de_Escenografía_fk1` FOREIGN KEY (`obra_id`) REFERENCES `Obras`(`obra_id`);

ALTER TABLE `Diseño_de_Vestuario` ADD CONSTRAINT `Diseño_de_Vestuario_fk0` FOREIGN KEY (`d_id`) REFERENCES `Diseñadores_de_Vestuario`(`d_id`);

ALTER TABLE `Diseño_de_Vestuario` ADD CONSTRAINT `Diseño_de_Vestuario_fk1` FOREIGN KEY (`obra_id`) REFERENCES `Obras`(`obra_id`);
