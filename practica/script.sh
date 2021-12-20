#!/bin/bash

mysql --local-infile=1 -e "source createdb.sql source temporales.sql; source cargamasiva.sql; source tablas_rel.sql; source carga_rel.sql; source querys.sql;"
