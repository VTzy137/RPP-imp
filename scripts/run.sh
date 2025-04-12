
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build

cd RPP-imp
cd target
g++ boot.cpp -o server -lpthread -lboost_system
./server