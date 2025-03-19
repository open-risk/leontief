#!/bin/bash

# SUPPLY MATRIX
# 2945 -> 2944 lines
tail -n+2 "../data/matrix_eu-ic-supply_24ed_2022.csv" > "../data/tmp.csv"
# 2945 -> 2944 columns
cut --complement -d',' -f1 ../data/tmp.csv > ../data/supply.csv

# awk -F',' '{print NF; exit}' "../data/supply.csv"
# wc -l ../data/supply.csv

# USE MATRIX
# 3175 -> 3174 lines
# tail -n+2 "../data/matrix_eu-ic-use_24ed_2021.csv" > "../data/tmp.csv"
# 2951 -> 2950 columns
# cut --complement -d',' -f1 ../data/tmp.csv > ../data/use.csv

# awk -F',' '{print NF; exit}' "../data/use.csv"
# wc -l ../data/use.csv


