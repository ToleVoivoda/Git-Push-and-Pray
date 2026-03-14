CREATE DATABASE IF NOT EXISTS `streets`;
USE `streets`;

CREATE TABLE IF NOT EXISTS `userLogin`
(
    `email` VARCHAR(254) NOT NULL PRIMARY KEY,
    `password` VARCHAR(254) NOT NULL
);

CREATE TABLE IF NOT EXISTS `userProfile`
(
    `email` VARCHAR(254) NOT NULL PRIMARY KEY,
    `name` VARCHAR(254)
);

CREATE TABLE IF NOT EXISTS `update`
(
    `id` BIGINT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    `v1` BIGINT NOT NULL,
    `v2` BIGINT NOT NULL,
    `rating` INT NOT NULL,
    `userEmail` VARCHAR(254) NOT NULL,
    `categoryId` INT NOT NULL
);

CREATE TABLE IF NOT EXISTS `updateCategory`
(
    `id` INT NOT NULL AUTO_INCREMENT,
    `name` VARCHAR(254) NOT NULL
);

CREATE TABLE IF NOT EXISTS `userUpdate`
(
    `id` BIGINT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    `userEmail` VARCHAR(354) NOT NULL,
    `updateId` BIGINT NOT NULL
);

CREATE TABLE IF NOT EXISTS `edgeVertex`
(
    `id` BIGINT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    `vertexId` BIGINT NOT NULL,
    `edgeId` BIGINT NOT NULL
);

CREATE TABLE IF NOT EXISTS `vertex`
(
    `id` BIGINT NOT NULL PRIMARY KEY,
    /*STANDART STREET NAME MAX LENGTH: */
    `name` VARCHAR(95)
);

CREATE TABLE IF NOT EXISTS `edge`
(
    `id` BIGINT AUTO_INCREMENT NOT NULL PRIMARY KEY,
    `v1` INT NOT NULL,
    `v2` INT NOT NULL,
    `rating` FLOAT,
    `distance` FLOAT
);

ALTER TABLE `userProfile`
ADD CONSTRAINT `userProfile_userLogin_id` FOREIGN KEY (`email`) REFERENCES userLogin(`email`);

ALTER TABLE `userUpdate`
ADD CONSTRAINT `userUpdate_userProfile_id` FOREIGN KEY (`userEmail`) REFERENCES userProfile(`email`);

ALTER TABLE `userUpdate`
ADD CONSTRAINT `userUpdate_update_id` FOREIGN KEY (`updateId`) REFERENCES `update`(`id`);

ALTER TABLE `update`
ADD CONSTRAINT `update_userProfile_id` FOREIGN KEY (`userEmail`) REFERENCES userProfile(`email`);

ALTER TABLE `update`
ADD CONSTRAINT `update_updateCategory_id` FOREIGN KEY (`categoryId`) REFERENCES updateCategory(`id`);

ALTER TABLE `edgeVertex`
ADD CONSTRAINT `edgeVertex_vertex_id` FOREIGN KEY (`vertexId`) REFERENCES vertex(`id`);

ALTER TABLE `edgeVertex`
ADD CONSTRAINT `edgeVertex_edge_id` FOREIGN KEY (`edgeId`) REFERENCES edge(`id`);

INSERT INTO `updateCategory` (`name`)
    VALUES ("Намалена видимост");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Трудно пресичане");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Пътен инцидент");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Опасен терен");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Опасно животно");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Препятствие на пътя");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Липсва осветление");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Липсва видеонаблюдение");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Подозрителни индивиди");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Опасни индивиди");
INSERT INTO `updateCategory` (`name`)
    VALUES ("Друго");