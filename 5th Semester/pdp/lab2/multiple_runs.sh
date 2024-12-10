# run ./cond 100000 times
g++ -std=c++11 $1.cpp -o $1
for i in {1..100000}
do
    echo "Run $i"
    ./cond
done