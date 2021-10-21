#!/bin/bash

# To more easily compile and run this program on CSS Linux Lab
# Lines starting with '$' indicate what is typed on command line

# if you get the following error:
# -bash: ./simplecompile.sh: /bin/bash^M: bad interpreter: No such file or directory
# run dos2unix to fix it
# $ dos2unix simplecompile.sh

# make this file executable
# $ chmod 700 simplecompile.sh
# redirect the output and stderr from this file to output.txt
# $ ./simplecompile.sh > output.txt 2>&1

#TO ENABLE CLANGTIDY do this EVERYTIME on linux lab: scl enable llvm-toolset-7.0 bash

date

echo "*** compiling with clang++ to create an executable called myprogram"
clang++ --version
clang++ -std=c++14 -Wall -Wextra -Wno-sign-compare *.cpp -g -o myprogram

echo "*** running clang-tidy using options from .clang-tidy"
clang-tidy --version
clang-tidy *.cpp -- -std=c++14

echo "*** running myprogram"
./myprogram

# valgrind will detect memory leaks
# echo "*** running with valgrind"
# valgrind ./myprogram.exe

echo "*** cleaning up, deleting myprogram"
rm myprogram

date
