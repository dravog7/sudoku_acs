#!/bin/bash
declare -a arr=(instances/logic-solvable/*)
arr+=(instances/general/inst25x25*)
echo "BVE" > results/BVE.txt
echo "GPE" > results/GPE.txt
echo "BS" > results/BS.txt
for i in "${arr[@]}"
do
   echo "$i" >> results/BVE.txt
   echo "$i" >> results/BS.txt
   echo "$i" >> results/GPE.txt
   ./sudokusolver --alg 0 --file "$i" --timeout 40 >> results/BVE.txt
   ./sudokusolver --alg 1 --file "$i" --timeout 40 >> results/BS.txt
   ./sudokusolver --alg 2 --file "$i" --timeout 40 >> results/GPE.txt --evap 0.01 --q0 0.1
done