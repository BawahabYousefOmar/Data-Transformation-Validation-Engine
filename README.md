**CSCE2301 – Digital Design I**  
**Fall 2026**

#  Quine-McCluskey Logic Minimization
A C++ command-line program that minimizes Boolean functions up to 20 variables using the Quine-McCluskey algorithm.
 
## Team
| Name | GitHub username | Student ID |
|------|-----------------|------------|
| Yousef Bawahab | @BawahabYousefOmar | 900243149 |
| Mohammed Al-Kaf | @m-kaf10 | 900243151 |
| Amro Elsafoury | @amrosafory | 900242312 |
 
## Features
1. Read Boolean functions from a text file.
2. Store variables, minterms, maxterms, and don't-care terms.
3. Use minterms and don't-care terms to generate and display all prime implicants along with their binary representations.
4. Identify from the prime implicants the essential prime implicants (EPIs), and list the minterms they do not cover.
5. Solve the coverage chart and deduce the minimized Boolean expression.
6. Manipulate the minimized expression to use only NAND gates.
7. **(Bonus)** Generate a Verilog module for the function using Verilog primitives.

## Input File Format
The input is a text file with 3 lines:
- Line 1: number of variables
- Line 2: either minterms (`m`) or maxterms (`M`) - comma-separated
- Line 3: don't-care terms (`d`) - comma-separated  

e.g.

```
3
m1,m3,m5,m7
d0,d5
```

The example above is a 3-variable function with minterms 1, 3, 5 and 7 and don't-cares 0 and 5.
 
## Repository Structure
```
.
├── README.md      # this file
├── src/           # source code
├── tests/         # test circuits (input files and expected outputs)
└── report/        # final report
```
 
## Build and Run
_Build instructions to be created once the program is implemented_
 
```
# build
# run
```
 
## Testing
Test circuits can be found in the `tests/` folder. Each test has an input file and its expected output.
 
## Milestones
- [x] Group formation (Oct 20)
- [x] Repository with initial README (Oct 20)
- [ ] Five test circuits in `tests/` (Oct 24)
- [ ] First source code commit (Oct 24)
- [ ] Semi-functional implementation (Oct 28)
- [ ] Fully functional implementation, tagged as release (Nov 7)
- [ ] Report (Nov 7)
- [ ] Final interview (Nov 8)