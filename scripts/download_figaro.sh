#!/bin/bash

# Download FIGARO data sets from eurostat URL's
# The format of the full URL is along the lines of: base_URL/NNN/NNNN/matrix_eu_ic-SUPPLY/USE_NNed_YEAR.csv

# wget --content-disposition https://ec.europa.eu/eurostat/documents/51957/17979411/matrix_eu-ic-io_prod-by-prod_23ed_2021.csv
# https://ec.europa.eu/eurostat/documents/51957/19580537/matrix_eu-ic-use_24ed_2022.csv
# https://ec.europa.eu/eurostat/documents/51957/19580267/matrix_eu-ic-supply_24ed_2022.csv


wget --content-disposition https://ec.europa.eu/eurostat/documents/51957/19580267/matrix_eu-ic-supply_24ed_2021.csv
wget --content-disposition https://ec.europa.eu/eurostat/documents/51957/19580537/matrix_eu-ic-use_24ed_2021.csv
