# Leontief

Leontief is a C++ package to work with economic Input-Output models

## Functionality

* Download Public IO Data Sets
* Pre-process Input-Output tables using command line tools
* Ingest IO matrices into a C++ environment
* Solve IO systems using the Eigen linear algebra library

## Workflow

Clone the repository into your work environment (e.g., a leontief directory). The command line scripts included in the leontief/scripts directory should be working immediately on a standard linux distribution. Specific instructions are not provided as those will vary depending on use setup.  

Create a leontief/data subdirectory. Download, move and extract the IO databases into the data directory.

Strip the matrix files (e.g., bash strip_exiobase.sh) from label data (we will not need those for numerical C++ calculations).

Compile the C++ code. Leontief uses cmake and conan. Test that everything is running properly.


## Further Resources

Working with CLI tools to process large matrices is elaborated further on the eLearning platform [Open Risk Academy](https://www.openriskacademy.com/course/view.php?id=76)


