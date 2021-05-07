# Problem overview
Modified version of [sokoban problem](https://en.wikipedia.org/wiki/Sokoban) - worker is pulling boxes to warehouse 
locations instead of pushing.

# Disclaimer
I haven't written C++ in over 2 years, it is almost certain that the code is far from good C++ 
practices and conventions. It's ugly, unclear, but has one major advantage: it passed the tests

## Usage
* Build executable `./build.sh sokoban`. 
* Run the compiled program and pass the input data to its stdin, optionally you can redirect 
  program stdout to a file. `./sokoban < in.txt > out.txt`
* Use `judge.py` to check solution `python judge.py in.txt out.txt -v`. 
  (`-v` flag run judge in visualization mode)
* `./run.sh` exec program on testcases and validate results

## Checkpoints
* (cha) - max board size is 6x6
* (chb) - only one box but max board size is 200x200
* (chc) - contains up to 3 boxes

## judge.py
I am not an author of judge's program. I assume that the author is instructor of Algorithms for Computationally 
Hard Problems course [Piotr Faliszewski](http://home.agh.edu.pl/~faliszew/)