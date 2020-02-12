#include <exception>
#include "examples.h"
//include "math.h"

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
    vector<int> t;
    vector<int> result;
    if(n < 2){
        throw std::range_error("dont have such primes");
    }else{
        for (int i = 0; i < n + 1; i++){
            t.push_back(i);
        }
        for (int j = 2; j < t.size(); j++){
            while (j <= t.size() / 2){
                t[2 * j] = 0;
            }
        }
        for (int x = 2; x < t.size(); x++){
            if (t[x] != 0){
                result.push_back(t[x]);
            }
        }
    return result;
    }
}
/*
vector<tuple<int,int>> examples::twins(vector<int> nums){
    tuple<int, int> result;
    sort(nums.begin(), nums.end());
    vector<int> y = nums;
    vector<int> ready;
    vector<tuple<int, int>> fin;
    if (nums.size() < 2){
        throw std::range_error("cant find twins");
    }else{
        ready = primes(y.back());
        for (int i : ready){
            if (find(nums.begin(), nums.end(), i) && find(nums.begin(), nums.end(), i + 2) && find(ready.begin(), ready.end(), i + 2)){
                result = make_tuple(i, i+2);
                fin.push_back(result);
            }
        }
    return fin;
    }

}*/