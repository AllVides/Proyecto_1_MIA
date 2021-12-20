USE practica IF EXISTS;
DROP TEMPORARY TABLE IF EXISTS temp_country_codes, temp_geonames, temp_levela, temp_location, temp_projects, temp_transaction;
DROP TABLE IF EXISTS country_codes, geonames, levela, location, projects, transaction, currency, status;

DROP DATABASE practica;

CREATE DATABASE practica;
