#!/bin/bash
for i in {0..11}
do
   ./sokoban/bin/sokoban < "./examples/chb$i.in" > "./examples/chb$i.out"
   echo $i `python judge.py "./examples/chb$i.in" "./examples/chb$i.out"`
done
