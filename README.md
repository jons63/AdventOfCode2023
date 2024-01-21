# Advent of code 2023

## Day 10
Solution uses ["Shoelace formula"](https://en.wikipedia.org/wiki/Shoelace_formula), triange formula, to to find the area of the loop from the coordinates of all points on the loops boundary.

This area can then be used in ["Pick's theorem"](https://en.wikipedia.org/wiki/Pick%27s_theorem). Unknowns in picks theorem are area, points on boundary and points within boundary. To are known to us so we can calculate points within boundary.

## Day 12
Solution uses recursion but it is to slow to do just recursion for second part so "Dynamic Programming" is used. Dynamic programming is recursion with memory. We save the solution of states and when that state is later encountered again we can simply read the already saved value. We are also returning early if we see that a solution will not be found based on current state.