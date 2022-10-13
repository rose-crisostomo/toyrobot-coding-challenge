Toy Robot Coding Challenge - Iress
=======
The application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units. There are no
other obstructions on the table surface. The robot is free to roam around the surface of the table, but must be prevented
from falling to destruction. Any movement that would result in the robot falling from the table must be prevented,
however further valid movement commands must still be allowed.

# Commands:
* **PLACE X,Y,DIRECTION**: Places the robot on coordinates x,y (starting point is 0,0) facing a direction (NORTH, EAST, SOUTH, WEST)
* **MOVE**: Moves the robot one unit forward from where it's facing.
* **LEFT**: Rotates the robot to the left.
* **RIGHT**: Rotates the robot to the right.
* **REPORT**: Prints the current position and direction to the console (Example: 0,0,NORTH)

# How to run
1. Install gcc/g++ at least v.4.8.1 to get C++11 support
2. Go to `build/` and run the `run-main.cmd` script. The input.txt file inside build/ will be used as input.

The resulting `toy_robot.exe` may be supplied a filename as an argument which the program will consider as inputs. The default is the `input.txt` file. The input file should follow the format:
```
<set of commands>...

<set of commands>...
```

Example:
```
PLACE 1,0,NORTH
REPORT

PLACE 1,1,EAST
MOVE
REPORT
```
# Running tests
1. Go to build/ and run the `run-tests.cmd` script.

There's a test file inside `Tests/` called `TestDataFeed.cpp` which reads from `test-data.txt` to run automated tests and validates the console output. This follows the format:

```
<set of commands>...
Output:<expected output>

<set of commands>...
Output:<expected output>
```
Example:
```
PLACE 1,0,NORTH
REPORT
Output:1,0,NORTH

PLACE 1,1,EAST
MOVE
REPORT
Output:2,1,EAST
```