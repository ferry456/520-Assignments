#ifndef __EXAMPLES_H
#define __EXAMPLES_H

#include <string>
#include <tuple>
#include <map>
#include <vector>
#include <functional>
#include <stdexcept>

using namespace std;
using std::vector;

class examples {
    public :
    typedef tuple<int,int> x;
    void sort_by_magnitude(vector<double> &a);
    vector<int> primes(int n);
    vector<tuple<int,int>> twins(vector<int> nums);
};




#endif