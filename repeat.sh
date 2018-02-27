#!/bin/bash

COUNTER=0
while [  $COUNTER -lt 1000 ]; do
  ./a.out 100 result_mergesort_100.txt
  ./a.out 1000 result_mergesort_1000.txt
  ./a.out 10000 result_mergesort_10000.txt
  ./a.out 100000 result_mergesort_100000.txt
  let COUNTER=COUNTER+1
done
