# Problem overview
Original sokoban problem description https://en.wikipedia.org/wiki/Sokoban.
This repository contains algorithm for slightly modified version of this problem - 
worker is pulling boxes to storage locations instead of pushing.

## Usage
* Build executable `./build.sh sokoban`. 
* Run the compiled program and pass the input data to its stdin, optionally you can redirect 
  program stdout to a file. `./sokoban < in.txt > out.txt`
* Use `judge.py` to check solution `python judge.py in.txt out.txt -v`. 
  (`-v` flag run judge in visualization mode)

## judge.py
I am not an author of judge's program. I assume that the author is instructor of Algorithms for Computationally 
Hard Problems course [Piotr Faliszewski](http://home.agh.edu.pl/~faliszew/)