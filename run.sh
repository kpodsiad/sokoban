#!/bin/bash
echo "cha"
for i in {0..6}
do
   ./sokoban/bin/sokoban < "./examples/cha$i.in" > "./examples/cha$i.out"
   echo $i `python judge.py "./examples/cha$i.in" "./examples/cha$i.out"`
done

echo "chb"
for i in {0..11}
do
   ./sokoban/bin/sokoban < "./examples/chb$i.in" > "./examples/chb$i.out"
   echo $i `python judge.py "./examples/chb$i.in" "./examples/chb$i.out"`
done


