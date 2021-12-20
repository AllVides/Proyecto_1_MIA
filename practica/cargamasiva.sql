USE practica IF EXISTS;


LOAD DATA LOCAL INFILE 'ArchivosCSV/locations.tsv' INTO TABLE temp_location
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

LOAD DATA LOCAL INFILE 'ArchivosCSV/country_codes.tsv' INTO TABLE temp_country_codes
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

LOAD DATA LOCAL INFILE 'ArchivosCSV/geonames.csv' INTO TABLE temp_geonames
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

LOAD DATA LOCAL INFILE 'ArchivosCSV/level_1a.csv' INTO TABLE temp_levela
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

LOAD DATA LOCAL INFILE 'ArchivosCSV/projects.csv' INTO TABLE temp_projects
CHARACTER SET latin1
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES;

LOAD DATA LOCAL INFILE 'ArchivosCSV/transactions.csv' INTO TABLE temp_transaction
FIELDS TERMINATED BY ','
LINES TERMINATED BY '\n'
IGNORE 1 LINES;


/*select count(*) from temp_country_codes; */
DELETE FROM temp_country_codes WHERE name = 'Unspecified';
/*select count(*) from temp_country_codes; 
/*select count(*) from temp_location; 
select count(*) from temp_country_codes; 
select count(*) from temp_geonames; 
select count(*) from temp_levela; 
select count(*) from temp_projects; 
select count(*) from temp_transaction;*/

