https://ec.europa.eu/eurostat/web/esa-supply-use-input-tables/database#Use%20tables

## Countries

Total 46

* 27 EU Members
* 18 Others
* 1 "ROW"

## FIGARO Supply Table Header (CSV Flat)

csv column headers:

* icsupRow: Concatenation (flattening) of refArea and rowPi codes
* icsupCol: Concatenation of counterpartArea and colPi codes
* rowPi: 64 products, as per CPA2.1
* colPi: 64 industries, as per NACE rev.2
* refArea: 46 geographical areas / countries of origin
* counterpartArea: 46 geographical areas / countries of destination
* obsValue: Domestic flows of goods and services

Total csv rows: 8667136 = (46 x 64)^2

46 geographical entities; 64 production activities
(46x64 x 46x64 = 2 944 x 2 944 = 8 667 1360)

## FIGARO Use Table Header  (CSV Flat)

csv column headers:

* icuseRow: Concatenation (flattening) of refArea and rowPi codes
* icuseCol: Concatenation of counterpartArea and colPi codes
* rowPi: 64 products (CPA2.1) plus 6 accounting items (ESA2010 / VA) - 3 adjustments + 3 value added components
* colPi: 64 industries (NACE rev.2) plus 5 accounting items (ESA2010) - 5 final use categories
* refArea: 46 geographical areas / countries of origin plus 1 domestic area
* counterpartArea: 46 geographical areas / countries of destination
* obsValue:
  * off-diagonal blocks: Cross-border flows of intermediate goods and services
  * diagonal blocks: Domestic flows of intermediate goods and services
  * final use off-diagonal blocks:
  * final use diagonal blocks:

Total csv rows: 9363300 = 8667136 + 696164 (= 46 x 15134 = 46 x 46 x (6 + 1) x (46 + 1))

## FIGARO Supply Table Header (CSV Matrix)

* icsupRow: Concatenation (flattening) of refArea and rowPi codes
* icsupCol: Concatenation of counterpartArea and colPi codes

Total csv rows / columns: 2944

## FIGARO USE Table Header (CSV Matrix)

* icsupRow: Concatenation (flattening) of refArea and rowPi codes
* icsupCol: Concatenation of counterpartArea and colPi codes

Total csv rows: 2950 = 2944 + 6
Total csv columns: 2944 + 5 * 46 (230) = 3174

## CO2 emissions vector (Eurostat E.2)

46 geographical entities; 64 production activities + 1 households
(1 x 46 x (64+1) = 2 990)

## FIGARO-E3 

176 industries and 213 products

### FIGARO-E3 SUPPLY Cols=8096 x Rows=9798

Rows: 9798 = 213 x 46 (products x countries)
Cols: 8096 = 176 x 46 (industries x countries)

### FIGARO-E3 USE Cols=8326 x Rows=9809

Rows: 9809 = 213 x 46 (products x countries) + 11 (VA Rows)
Cols: 8096 = 176 x 46 (industries x countries) + 230 (= 5 FD Rows x 46 Countries)


