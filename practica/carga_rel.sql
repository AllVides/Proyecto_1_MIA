INSERT INTO status(name)
SELECT DISTINCT status
FROM temp_projects;
select count(*) as status from status;


INSERT INTO currency(name)
SELECT DISTINCT transaction_currency
FROM temp_transaction;
select count(*) as currency from currency;






INSERT INTO country_codes(
name,
iso2,
name_name,
name_aiddata_code,
name_aiddata_name,
name_cow_alpha,
name_cow_numeric,
name_fao_code,
name_fips,
name_geonames_id,
name_imf_code,
name_iso2,
name_iso3,
name_iso_numeric,	
name_oecd_code,
name_oecd_name,
name_un_code,	
name_wb_code)
SELECT * FROM temp_country_codes;
DROP TEMPORARY TABLE IF EXISTS temp_country_codes;
select count(*) as country_codes from country_codes;





INSERT INTO location (
location_type_code,
location_type_name)
SELECT * FROM temp_location;
select count(*) as locations from location;






UPDATE temp_geonames SET location_type_code=(SELECT id FROM location WHERE location.location_type_code = temp_geonames.location_type_code);

ALTER TABLE temp_geonames DROP COLUMN location_type_name;

INSERT INTO geonames (
geoname_id,
place_name,
latitude,
longitude,
location_type_code,
gazetteer_adm_code,
gazetteer_adm_name,
location_class,
geographic_exactness)
SELECT * FROM temp_geonames;
DROP TEMPORARY TABLE IF EXISTS temp_geonames;

select count(*) as geonames from geonames;






UPDATE temp_projects SET status=(SELECT name FROM status WHERE name = status);
/*UPDATE temp_projects SET start_actual_isodate=STR_TO_DATE(start_actual_isodate, "%d/%m/%Y");
UPDATE temp_projects SET end_actual_isodate=STR_TO_DATE(end_actual_isodate, "%d/%m/%Y");*/

INSERT INTO projects (project_id,
is_geocoded,
project_title,
start_actual_isodate,
end_actual_isodate,
donors,
donors_iso3,
recipients,
recipients_iso3,
ad_sector_codes,
ad_sector_names,
status ,
transactions_start_year,
transactions_end_year,
total_commitments,
total_disbursements
)
SELECT * FROM temp_projects;
DROP TEMPORARY TABLE IF EXISTS  temp_projects;
select count(*) as projects from projects;





UPDATE temp_transaction SET transaction_currency=(SELECT id FROM currency WHERE name = transaction_currency);

UPDATE temp_transaction SET project_id=(SELECT id FROM projects WHERE temp_transaction.project_id = projects.project_id);
/*UPDATE temp_transaction SET transaction_isodate=STR_TO_DATE(transaction_isodate, "%d/%m/%Y");*/

INSERT INTO transaction (transaction_id,
project_id,
transaction_isodate,
transaction_year,
transaction_value_code,
transaction_currency,
transaction_value)
SELECT * FROM temp_transaction;
DROP TEMPORARY TABLE IF EXISTS temp_transaction;



select count(*) as transactions from transaction;





INSERT INTO levela (project_id,
project_location_id,
geoname_id,
transactions_start_year,
transactions_end_year,
even_split_commitments,
even_split_disbursements)
SELECT * FROM temp_levela;
DROP TEMPORARY TABLE IF EXISTS temp_levela;
select count(*) as level_a from levela;

/*select * from status;
select * from currency;
/*select * from country_codes Limit 10;*/
/*select * from transaction Limit 10;
select * from geonames Limit 10; */
