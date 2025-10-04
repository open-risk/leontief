#!/bin/bash

# command line scripts to "clean" EXIOBASE data from labels,
# as those are not relevant for the purely numerical algebraic operations in Leontief

# awk 'NR > 3 { print }' ../data/IOT_2022_pxp/A.txt > ../data/IOT_2022_pxp/tmp.txt
# cut -f 3- <../data/IOT_2022_pxp/tmp.txt >../data/IOT_2022_pxp/A_Clean.txt

# awk 'NR > 3 { print }' ../data/IOT_2022_pxp/Z.txt > ../data/IOT_2022_pxp/tmp.txt
# cut -f 3- <../data/IOT_2022_pxp/tmp.txt >../data/IOT_2022_pxp/Z_Clean.txt

# awk 'NR > 1 { print }' ../data/IOT_2022_pxp/x.txt > ../data/IOT_2022_pxp/tmp.txt
# cut -f 3- <../data/IOT_2022_pxp/tmp.txt >../data/IOT_2022_pxp/X_Clean.txt

awk 'NR > 3 { print }' ../data/IOT_2022_pxp/Y.txt > ../data/IOT_2022_pxp/tmp.txt
cut -f 3- <../data/IOT_2022_pxp/tmp.txt >../data/IOT_2022_pxp/Y_Clean.txt
