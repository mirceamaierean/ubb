# !/bin/zsh
# Usage: ./script.sh <number_of_nodes> <extra_edges>
python3 generator.py --nodes $1 --extra_edges $2 --output graph.in
g++ -std=c++11 hamilton.cpp -o hamilton
./hamilton