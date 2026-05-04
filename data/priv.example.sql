CREATE DATABASE IF NOT EXISTS financial_system;
CREATE USER IF NOT EXISTS 'user'@'localhost' IDENTIFIED BY 'password';
GRANT SELECT, INSERT, UPDATE, DELETE ON financial_system.* TO 'user'@'localhost';
USE financial_system;