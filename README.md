# Leontief

Leontief is a C++ package to work with economic Input-Output models

## Overall Functionality Objectives

Leontief helps with a number of typical tasks in Input-Output modeling:

* Pre-processing Input-Output tables using command line tools
* Ingesting IO matrices into a C++ environment for further calculations
* Solving typical IO problems using the existing library. 
* Investing ad-hoc questions by writing new code using the very usable and performant Eigen C++ linear algebra library


## Installation / Workflow

* Clone the repository into your work environment (e.g., a leontief directory). 
* The command line scripts included in the leontief/scripts directory should be working immediately on a standard linux distribution. 

### Dependencies

Leontief is a C++ library. To augment or rebuild it from source you will need a working C++ toolchain. Conan is recommended as a means to pull in dependencies. The current dependency list includes:

* eigen
* poco
* catch2

For compiling the C++ code, Leontief uses cmake and conan. There is a suit of tests that helps verify that everything is installed and running properly.

### Conan Installation

* pip install conan
* conan install . --output-folder=cmake-build-debug --build=missing -s build_type=Debug

### Data Organization

#### Downloading Scripts

Create a leontief/data subdirectory. Download, move and extract publicly available IO databases into the data directory. Current download scripts:

* exiobase
* figaro
* oecd-icion

#### Pre-processing

The focus of Leontief is on high performance *numerical calculations* involving large matrices. It does not offer dataframe type functionality for searching or filtering data. The following scripts offer some needed functionality:

* Strip the matrix files (e.g., bash strip_exiobase.sh) from label data (we will not need those for numerical C++ calculations).



## Further Resources

Working with CLI tools to process large matrices is elaborated further on the eLearning platform [Open Risk Academy](https://www.openriskacademy.com/course/view.php?id=76)


