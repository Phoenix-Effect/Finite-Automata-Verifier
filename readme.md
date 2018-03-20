# CSE355 - Optional Project
Milestone - 1
-------------

## Overview
This program takes in either an NFA or a DFA, converts it to a DFA if needed, makes a compliment of the new DFA, prints it in the same format as the input and prints the shortest string within that DFA. It uses Gallier's subset construction algorithm for converting the NFA to DFA and uses BFS to find the shortest string in the new DFA.

## How to use
### Compiling
The program is written in C++ and requires g++ to compile. A makefile is included in the program so the program can be compiled by going into the directory and running the command `make`. The make file generates a file with name `optionalProject` which can be executed directly.

### Input
The program takes input from stdin by default which can be redirected through the terminal `./optionalProject < inputText.txt`. This can be changed using the program config.

### Output
The program outputs 2 files by default (this behavior can be changed through program config).

1. **ASUAD\_Milestone1\_Dp.txt** - Which contains the compliment of the input machine.
2. **ASUAD\_Milestone1\_str.txt** - Which contains the shortest string in the new machine.

### Program config
For ease of use I've grouped up all of the important values in the same place which might help with testing and debugging the program. The config box is in the **main.cpp** file start from line 18 and ending at line 35.

  * **outputDFAToFile** - bool - *(default: true)* - If true then outputs the DFA to a file else prints the DFA to the console. Can be helpful in case there are r/w permission issues as well.
  * **outputShortestStringToFile** - bool - *(default: true)* - Shortest string is always printed to the screen but this bool decides if it should also output to a file or not.
  * **takeInputFromFile** - bool - *(default: false)* - Allows you to hardcode the path to the input file within the program. If set to true then **inputFilePath** also needs to be defined.
  * **inputFilePath** - string - *(default: "")* - Absolute path to the input file. **takeInputFromFile** needs to be set to true to make the program use this. The type of slashes in the absolute are determined by your OS. (forward slashes for MAC OS, double backslashes for windows).
  * **printEpsilonInsteadOfEmptyString** - bool - *(default: true)* - Prints out the string "epsilon" instead of an empty string "" which can help visually to see whats going on.
  * **printStateSets** - bool - *(default: true)* - When an NFA is converted to DFA then each state in the DFA is a subset of states of the NFA. If this is set to true then each state name is shown as a set of states. When set to false it assigns an integer to each state instead. The input file mentions that the name of each state is represented by integers and setting this to false makes the program comply with that.
  * **deadStateName** - string - *(default: "Dead-State")* - Since the dead-state is technically not a subset of the set of states of the NFA, a new 'dead state' needs to be added in order to successfully construct a DFA. This value lets you set the name of that dead state. *Note: This value is only used if **printStateSets** is set to true and has no effect if it is false.*

#### Notes:
  * The program gives parameter mismatch errors in some compilers but still compiles fine. It has been tested on my local computer and ASU general server where it compiled without any issue.
  *  If console is used for input then you need to press Enter twice since the program looks for an empty line before it starts parsing.