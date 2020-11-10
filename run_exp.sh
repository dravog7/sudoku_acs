#!/bin/bash
declare -a arr=(instances/logic-solvable/*)
arr+=(instances/general/inst25x25*)
echo "BVE" >> results/ACS.txt
for i in "${arr[@]}"
do
   echo "$i" >> results/ACS.txt
   ./sudokusolver --file "$i" --timeout 120
done