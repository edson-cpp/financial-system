CREATE TABLE users (
  users_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  name VARCHAR(50) NOT NULL,
  login VARCHAR(32) NOT NULL UNIQUE,
  pwd VARCHAR(255) NOT NULL,
  national_id VARCHAR(14) NOT NULL UNIQUE,
  national_id_type VARCHAR(3) NOT NULL DEFAULT 'CPF',
  country_code CHAR(2) NOT NULL DEFAULT 'BR',
  phone VARCHAR(20),
  email VARCHAR(50),
  level TINYINT UNSIGNED NOT NULL,
  PRIMARY KEY (users_id)
) ENGINE=InnoDB;

CREATE TABLE cost_center (
  cost_center_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  description VARCHAR(50) NOT NULL,
  PRIMARY KEY(cost_center_id)
) ENGINE=InnoDB;

CREATE TABLE credit_card (
  credit_card_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  card_brand VARCHAR(50) NOT NULL,
  bank VARCHAR(50) NOT NULL,
  PRIMARY KEY(credit_card_id)
) ENGINE=InnoDB;

CREATE TABLE movement (
  movement_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
  cost_center_id INT UNSIGNED NOT NULL,
  credit_card_id INT UNSIGNED NOT NULL,
  description VARCHAR(100) NOT NULL,
  purch_date DATE,
  due_date DATE,
  pay_date DATE,
  value DECIMAL(8,2),
  paid_value DECIMAL(8,2),

  PRIMARY KEY(movement_id),

  FOREIGN KEY (cost_center_id)
    REFERENCES cost_center(cost_center_id)
    ON DELETE RESTRICT
    ON UPDATE NO ACTION,

  FOREIGN KEY (credit_card_id)
    REFERENCES credit_card(credit_card_id)
    ON DELETE RESTRICT
    ON UPDATE NO ACTION
) ENGINE=InnoDB;