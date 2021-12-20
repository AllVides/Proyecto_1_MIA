
USE practica;

CREATE TEMPORARY TABLE temp_country_codes (
name VARCHAR(50) NOT NULL,
iso2 VARCHAR(5),
name_name varchar(50) NOT NULL,
name_aiddata_code INT UNSIGNED,
name_aiddata_name VARCHAR(50),
name_cow_alpha VARCHAR(50),
name_cow_numeric INT UNSIGNED,
name_fao_code INT UNSIGNED,
name_fips VARCHAR(5),
name_geonames_id INT UNSIGNED,
name_imf_code INT UNSIGNED,
name_iso2 VARCHAR(5),
name_iso3 VARCHAR(5),
name_iso_numeric INT UNSIGNED,	
name_oecd_code INT UNSIGNED,
name_oecd_name VARCHAR(50),
name_un_code INT UNSIGNED,	
name_wb_code VARCHAR(5)
);






CREATE TEMPORARY TABLE temp_geonames (
geoname_id INT UNSIGNED,
place_name VARCHAR(50),
latitude FLOAT,
longitude FLOAT,
location_type_code VARCHAR(50),
location_type_name VARCHAR(100),
gazetteer_adm_code VARCHAR(200),
gazetteer_adm_name VARCHAR(200),
location_class INT,
geographic_exactness INT
);


CREATE TEMPORARY TABLE temp_levela (
project_id VARCHAR(10),
project_location_id VARCHAR(30),
geoname_id INT,
transactions_start_year INT,
transactions_end_year INT,
even_split_commitments FLOAT,
even_split_disbursements FLOAT
);

CREATE TEMPORARY TABLE temp_location (
location_type_code VARCHAR(10),
location_type_name VARCHAR(150)
);


CREATE TEMPORARY TABLE temp_projects (
project_id VARCHAR(20),
is_geocoded INT,
project_title VARCHAR(200),
start_actual_isodate VARCHAR(30),
end_actual_isodate VARCHAR(30),
donors VARCHAR(50),
donors_iso3 VARCHAR(100),
recipients VARCHAR(50),
recipients_iso3 VARCHAR(50),
ad_sector_codes VARCHAR(100),
ad_sector_names VARCHAR(300),
status VARCHAR(100),
transactions_start_year YEAR,
transactions_end_year YEAR,
total_commitments FLOAT,
total_disbursements FLOAT
/*SET start_actual_isodate=STR_TO_DATE(@start_actual_isodate, `%d/%m/%Y`),
SET end_actual_isodate=STR_TO_DATE(@end_actual_isodate, `%d/%m/%Y`)*/
);

CREATE TEMPORARY TABLE temp_transaction (
transaction_id VARCHAR(50),
project_id VARCHAR(20),
transaction_isodate VARCHAR(30),
transaction_year YEAR,
transaction_value_code VARCHAR(10),
transaction_currency VARCHAR(10),
transaction_value FLOAT

/*SET transaction_isodate=STR_TO_DATE(@transaction_isodate, `%d/%m/%Y`)*/
);
