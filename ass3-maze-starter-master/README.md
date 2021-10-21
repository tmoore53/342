# Maze

Goals: Understand recursion and solve a maze

Given a text file representing a maze, as below, find the path for
creature to get to the exit and mark the path explored.
```
20 7
0 18
xxxxxxxxxxxxxxxxxx x
x     x       xxxx x
x xxxxx xxxxx   xx x
x xxxxx xxxxxxx xx x
x x          xx xx x
x xxxxxxxxxx xx    x
xxxxxxxxxxxxxxxxxxxx
```

Solution:
`*` shows the final path to exit

`+` shows areas explored but not part of the final path

```
Path: EEENNNEEEEEESEESSSEEENNNNN
xxxxxxxxxxxxxxxxxx*x
x     x*******xxxx*x
x xxxxx*xxxxx***xx*x
x xxxxx*xxxxxxx*xx*x
x x+****+++++xx*xx*x
x xxxxxxxxxx+xx****x
xxxxxxxxxxxxxxxxxxxx
```


## Included Files

- `CMakeLists.txt`: For complex projects, `cmake CMakeLists.txt` will
  generate a `Makefile`. We can then use `make` to compile the
  project. Optional for a small project like this, but included as an
  example.

- `maze.cpp` and `maze.h`: Definitions for maze functions

- `creature.cpp` and `creature.h`: Definitions for creature

- `main.cpp`: Runs all tests

- `output.txt`: Output from `./simple.compile.sh > output.txt 2>&1`
showing how the program is compiled and run.

- `simplecompile.sh`: Unix bash script file to compile, run 
and then delete the executable. Can be used to create an output.txt file


## Compile and Run

```
./simplecompile.sh
```


### Style Explanation
These options are defined in `.clang-tidy` file.

Perform all check except the following:

-fuchsia-* do not need specific checks for "fuchsia" a modular, capability-based operating system
- cppcoreguidelines-pro-bounds-array-to-pointer-decay: do not give warnings on assert
- google-build-using-namespace: for simplicity allow `using namespace std;`
- google-readability-braces-around-statements: allow compact code without `{`
- readability-braces-around-statements: allow compact code without `{`
This option is not available in CSS Linux lab under LLVM 3.8.1, but is needed on my PC when using 9.0.0
- hicpp-no-array-decay need to use assert
- modernize-use-trailing-return-type: not ready yet for `auto func() -> int` format
- hicpp-braces-around-statements: allow compact code without `{` (this option
- cppcoreguidelines-pro-bounds-pointer-arithmetic,
- llvm-header-guard: not using full directory name
- google-global-names-in-headers: for simplicity allow `using namespace std;`
- cppcoreguidelines-special-member-functions: not defining move operator
- hicpp-special-member-functions: not defining move operator
- cppcoreguidelines-owning-memory: not using gsl


