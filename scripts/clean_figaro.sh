#!/bin/bash

# SUPPLY MATRIX
# 2945 -> 2944 lines
# tail -n+2 "../data/matrix_eu-ic-supply_24ed_2022.csv" > "../data/tmp.csv"
# 2945 -> 2944 columns
# cut --complement -d',' -f1 ../data/tmp.csv > ../data/supply.csv

# awk -F',' '{print NF; exit}' "../data/supply.csv"
# wc -l ../data/supply.csv

# USE MATRIX
# 3175 -> 3174 lines
# tail -n+2 "../data/matrix_eu-ic-use_24ed_2021.csv" > "../data/tmp.csv"
# 2951 -> 2950 columns
# cut --complement -d',' -f1 ../data/tmp.csv > ../data/use.csv

# awk -F',' '{print NF; exit}' "../data/use.csv"
# wc -l ../data/use.csv

# IO Industry Matrix
#tail -n+2 "../data/matrix_eu-ic-io_ind-by-ind_24ed_2022.csv" > "../data/tmp.csv"
#cut --complement -d',' -f1 ../data/tmp.csv > ../data/io.csv
#awk -F',' '{print NF; exit}' "../data/io.csv"
#wc -l ../data/io.csv

# FIGARO-E3 SUPPLY 8096 x 9798
#tail -n+2 "../data/matrix_FIGARO-e-ic-supply_millionEUR_2015.csv" > "../data/tmp.csv"
#cut --complement -d',' -f1 ../data/tmp.csv > ../data/supply-e3.csv
#awk -F',' '{print NF; exit}' "../data/supply-e3.csv"
#wc -l ../data/supply-e3.csv

# FIGARO-E3 USE 8326 x 9809
tail -n+2 "../data/matrix_FIGARO-e-ic-use_millionEUR_2015.csv" > "../data/tmp.csv"
cut --complement -d',' -f1 ../data/tmp.csv > ../data/use-e3.csv
awk -F',' '{print NF; exit}' "../data/use-e3.csv"
wc -l ../data/use-e3.csv