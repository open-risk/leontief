# Leontief

Leontief is a C++ toolkit to work with economic Input-Output models. 

![IO](docs/US-IO.png)

## Overall Functionality Objectives

The overall design principle behind Leontief is to strike a balance between usability and performance when working with and/or developing algorithms and tools related to economic input-output systems. A key such design decision is to use a user-friendly C++ library for vector, matrix, tensor manipulations that offers a higher-level API similar e.g., to that of Matlab.  

Leontief helps with a number of typical tasks in Input-Output modeling:

* Pre-processing Input-Output tables using command line tools.
* Ingesting IO matrices into a C++ environment for further calculations.
* Solving typical IO problems using a library of tested algorithms. 
* Investigating ad-hoc research questions by writing new high-level code in the form scripts.

## Installation / Workflow

* Clone the repository into your own work environment (e.g., a leontief directory). 
* The command line scripts included in the leontief/scripts directory should be working immediately on a standard linux distribution. 

### Dependencies

Leontief is a C++ library. To augment or rebuild it from source you will need to have a working C++ toolchain. Conan is recommended as a means to pull in dependencies but is not absolutely required. The current dependency list includes:

* eigen
* poco
* catch2

For compiling the C++ code, Leontief uses cmake. 

### Testing

There is a suit of catch2 based tests that help verify that everything is installed and running properly.

### Conan Installation

* pip install conan
* conan install . --output-folder=cmake-build-debug --build=missing -s build_type=Debug

### Data Organization

#### Downloading Scripts

Create a leontief/data subdirectory. Download, move and extract publicly available IO databases into the data directory. Current download scripts:

* exiobase
* figaro
* oecd-icio

#### Pre-processing

The focus of Leontief is on high performance *numerical calculations* involving large matrices. It does not offer dataframe type functionality for searching or filtering data. The following scripts offer some needed functionality:

* Strip the matrix files (e.g., bash strip_exiobase.sh) from label data (we will not need those for numerical C++ calculations).

#### IO Systems

TODO

#### SUT Systems

TODO

## Further Resources

* Working with CLI tools to process large matrices is elaborated further on the eLearning platform [Open Risk Academy](https://www.openriskacademy.com/course/view.php?id=76)


