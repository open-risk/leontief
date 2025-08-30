#!/bin/bash

# mkdir oecd-2017-2022
# unzip 2017-2022_SML.zip -d oecd-2017-2022
# cd oecd-2017-2022
tail -n+2 "2022_SML.csv" > "tmp.csv"
cut --complement -d',' -f1 tmp.csv > icio.csv
awk -F',' '{print NF; exit}' "icio.csv"
wc -l icio.csv