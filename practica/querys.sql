select count(*) as currency from currency;
select count(*) as status from status;
select count(*) as country_codes from country_codes;
select count(*) as locations from location;
select count(*) as geonames from geonames;
select count(*) as projects from projects;
select count(*) as transactions from transaction;
select count(*) as level_a from levela;



select count(transactions_start_year) from projects where transactions_start_year=2011;


select project_title from projects where transactions_end_year is not null order by transactions_start_year ASC, transactions_end_year DESC LIMIT 1;

/*DATE_FORMAT(Date, '%Y%m%d')

select project_title from projects order by DATE_FORMAT(start_actual_isodate, '%d/%m/%Y') ASC, DATE_FORMAT(end_actual_isodate, '%d/%m/%Y') DESC LIMIT 1;*/

select project_title from projects where transactions_end_year is not null order by transactions_start_year DESC, transactions_end_year ASC LIMIT 1;


SELECT recipients , count(*) as active_projects
from projects
group by recipients
order by count(*) desc
limit 5;

SELECT recipients , count(*) as active_projects
from projects
group by recipients
order by count(*) asc
limit 5;

select project_title as proyecto_mas_costosos
from projects 
order by total_disbursements desc LIMIT 1;

select project_title as proyecto_menos_costosos
from projects 
where total_disbursements is not null
order by total_disbursements ASC LIMIT 1;

select project_title, total_disbursements as cost 
from projects 
where total_disbursements is not null
order by total_disbursements desc LIMIT 5;

select SUM(total_disbursements ) as costo_total
from projects;


select transaction_id, projects.project_id, transaction_value, currency.name as currency
from transaction, currency, projects
where
transaction.project_id = projects.id
and projects.project_title like "%RI-East Africa Public Health Laboratory Networking Project%"
and currency.id = transaction.transaction_currency
order by transaction.transaction_value DESC LIMIT 3;
    
    
    

