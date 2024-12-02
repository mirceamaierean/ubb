#!/bin/bash
for i in {1..1000}
do
    echo "Iteration $i"
    python main.py
    # sleep 0.5
done