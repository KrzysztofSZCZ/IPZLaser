CREATE TABLE `users` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `fullName` varchar(255)
);

CREATE TABLE `shape` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `fullName` varchar(255),
  `machineId` int,
  `data` int
);

CREATE TABLE `machine` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `orderId` int
);

CREATE TABLE `order` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `userId` int,
  `shapeId` int
);

ALTER TABLE `order` ADD FOREIGN KEY (`userId`) REFERENCES `users` (`id`);

ALTER TABLE `order` ADD FOREIGN KEY (`id`) REFERENCES `machine` (`orderId`);

ALTER TABLE `order` ADD FOREIGN KEY (`shapeId`) REFERENCES `shape` (`id`);

ALTER TABLE `shape` ADD FOREIGN KEY (`machineId`) REFERENCES `machine` (`id`);
