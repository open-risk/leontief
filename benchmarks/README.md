# matrix2json

Benchmarks of matrix to JSON conversion performance in various languages / packages

Background about the context, methodology etc. in these blog posts:

* [Part 1](https://www.openriskmanagement.com/representing-matrices-as-json-objects-part-1/)
* [Part 2](https://www.openriskmanagement.com/representing-matrices-as-json-objects-part-2/)

NB: Work in Progress

| Package        | T_out         | T_in          | Size     |
|----------------|---------------|---------------|----------|
| jsonlite       | 19.23444 secs | 25.10679 secs | 238.9 MB |
| RJSONIO        | 19.62544 secs | 23.94082 secs | 238.9 MB |
| rjson          | 4.120749 secs | 16.52509 sec  | 238.9 MB |
| numpy / json   | 5.80395 secs  | 5.51479 secs  | 238.9 MB |
| pandas.to_json | 7.97321 secs  | 14.95067 secs | 238.9 MB |


## Installation

### C++ Benchmarks

If not already present, install the following:

#### Armadillo

* sudo apt-get install libarmadillo-dev
* Version 10 of [armadillo](https://arma.sourceforge.net/) is used

#### Eigen

* sudo apt-get install libeigen3-dev
* Version 3.4
