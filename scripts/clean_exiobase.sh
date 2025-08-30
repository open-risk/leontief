#!/bin/bash

awk 'NR > 3 { print }' ../data/IOT_2022_pxp/A.txt > ../data/IOT_2022_pxp/tmp.txt
cut -f 3- <../data/IOT_2022_pxp/tmp.txt >../data/IOT_2022_pxp/A_Clean.txt