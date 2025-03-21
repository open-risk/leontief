#!/bin/bash

# Download FIGARO data sets from eurostat URL's

# https://ec.europa.eu/eurostat/web/esa-supply-use-input-tables/database
# The format of the full URL is along the lines of: base_URL/NNN/NNNN/matrix_eu_ic-SUPPLY/USE_NNed_YEAR.csv

# wget --content-disposition https://ec.europa.eu/eurostat/documents/51957/17979411/matrix_eu-ic-io_prod-by-prod_23ed_2021.csv
# https://ec.europa.eu/eurostat/documents/51957/19580537/matrix_eu-ic-use_24ed_2022.csv
# https://ec.europa.eu/eurostat/documents/51957/19580267/matrix_eu-ic-supply_24ed_2022.csv

# wget --content-disposition https://ec.europa.eu/eurostat/documents/51957/19580267/matrix_eu-ic-supply_24ed_2021.csv
# wget --content-disposition https://ec.europa.eu/eurostat/documents/51957/19580537/matrix_eu-ic-use_24ed_2021.csv
# wget --content-disposition https://ec.europa.eu/eurostat/documents/51957/19580762/matrix_eu-ic-io_ind-by-ind_24ed_2022.csv

# Download FIGARO-E3 data sets from JRC URL's

# wget --content-disposition https://jeodpp.jrc.ec.europa.eu/ftp/jrc-opendata/FIGARO-E3/supply%20and%20use/matrix_FIGARO-e-ic-supply_millionEUR_2015.csv
wget --content-disposition https://jeodpp.jrc.ec.europa.eu/ftp/jrc-opendata/FIGARO-E3/supply%20and%20use/matrix_FIGARO-e-ic-use_millionEUR_2015.csv