CREATE TABLE `users` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `fullName` varchar(255)
);

CREATE TABLE `shape` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `fullName` varchar(255),
  `machineId` int
);

CREATE TABLE `machine` (
  `id` int PRIMARY KEY AUTO_INCREMENT,
  `userId` int
);

ALTER TABLE `shape` ADD FOREIGN KEY (`machineId`) REFERENCES `machine` (`id`);

ALTER TABLE `machine` ADD FOREIGN KEY (`userId`) REFERENCES `users` (`id`);
