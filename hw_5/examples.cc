#include <exception>
#include "examples.h"
//include "math.h"
#include <iostream>

using namespace std;
using std::vector;


void examples::sort_by_magnitude(vector<double> &a){
    if (a.size() < 1){
        throw std::range_error("range cant be 0");    
    }else if (a.size() < 2){
        return;
    }else{
        auto y = [](double a, double b){return abs(a) < abs(b);};
        sort(a.begin() , a.end(), y);
    }
}

vector<int> examples::primes(int n){
    vector<int> result;
    if(n < 2){
        throw std::range_error("dont have such primes");
    }else{
        result.push_back(2);
        for (int i = 3; i <= n; i = i + 2) {
            bool isPrime = true;
            for (auto &p : result) {
                if (i % p == 0) {
                    isPrime = false;
                    break;
                } 
            }
            if (isPrime) {
                result.push_back(i);
            }
        }
    return result;
    }
}

vector<tuple<int , int>> examples::twins(vector<int> nums){
    tuple<int, int> result;
    vector<int> x = nums;
    vector<tuple<int , int>> fin;
    for (int i = 0; i < nums.size(); i++){
        if (abs(x[i] - x[i + 1]) == 2){
            result = make_tuple(x[i] , x[i + 1]);
            fin.push_back(result);
        }
    }
    return fin;
}