#!/bin/bash
for i in {1..1000}
do
    echo "Iteration $i"
    python3 main.py
    # sleep 0.5
done