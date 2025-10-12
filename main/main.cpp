#include <chrono>
#include <iostream>

#include "stackcollection/ArrayStack.hpp"
#include "stackcollection/ListStack.hpp"
#include "stackcollection/RBTreeStack.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

const int TENMIL = 10'000'000;

void stack_measure_bulk_push(IStack* stack)
{
    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < TENMIL; ++i)
        stack->push(i);
    auto t2 = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << ms_int.count() << "ms\n";
}

int main()
{
    ArrayStack* as = new ArrayStack;
    std::cout << "ArrayStack created\n";
    ListStack* ls = new ListStack;
    std::cout << "ListStack created\n";
    RBTreeStack* ts = new RBTreeStack;
    std::cout << "TreeStack created\n";

    std::cout << "Array stack bulk push time: ";
    stack_measure_bulk_push(as);

    std::cout << "List stack bulk push time: ";
    stack_measure_bulk_push(ls);

    std::cout << "Tree stack bulk push time: ";
    stack_measure_bulk_push(ts);
}