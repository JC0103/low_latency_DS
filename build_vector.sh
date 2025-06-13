g++ -std=c++23 -O3 -march=native -fno-exceptions -fno-rtti  -I./header\
    -DNDEBUG src/vector_bench.cpp -o vector_bench