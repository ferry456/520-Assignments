#include <exception>
#include "db.h"
//#include <cstdio>
#include <time.h>
#include <random>
#include <iostream>

using namespace std;

DB::DB() : _next_key(0) {}

DB &DB::insert(const string name, double mass, double distance) { 
    int key = _next_key++;
    for (int i = 0; i < key; i++){
        if (get<0>(_data[i]) == name){
            throw runtime_error("Name already exists");
        }
        
    }
    _data[key] = make_tuple(name, mass, distance);
    return *this;

}

DB &DB::drop(int key) {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        _data.erase (e);
    }

    return *this;
}

DB::Row DB::to_row(int key, const DB::Value value) const {
    return make_tuple(key, get<0>(value), get<1>(value), get<2>(value));
}

DB::Row DB::find(int key) const {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        return to_row(key,e->second);
    } else {
        throw runtime_error("Could not find an entry with the given key");
    }

}

vector<DB::Row> DB::where(function<bool(const DB::Row)> f) const {

    vector<Row> rows;

    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        if ( f(row) == true ) {
            rows.push_back(row);
        }
    }

    return rows;

}

DB::Row DB::find_by_name(const string name) const{
    for (auto [k , v] : _data){
        auto r = to_row(k, v);
        if (NAME(r) == name) {
            return r;
        }
    }    
    throw runtime_error("Couldnt find the row by name");
}

DB &DB::create_test_data(int n){
    time_t timer;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution_m(0.01 , 1000.00);
    std::uniform_real_distribution<double> distribution_d(0.1 , 10000000.0);
    std::uniform_int_distribution<int> distribution_name_number(8,11);
    auto name_get = [&timer]() -> char {
        srand(time(&timer));
        
        int s;                         
        s=rand()%2;                     
        if(s==1){                        
            return rand()%('Z'-'A'+1)+'A';
        }else{
            return rand()%('z'-'a'+1)+'a';  
        }             
    };

    /*auto randchar = []() -> char{
        const char charset[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand()% max_index];
    };*/

    for (int i = 0; i < n; i++){
        double a_mass = distribution_m(generator);
        double a_distance = distribution_d(generator);
        int k = distribution_name_number(generator);
        string a_name(k, 0);
        generate_n(a_name.begin(), k, name_get);
        cout << a_name << "\n";
        insert(a_name, distribution_m(generator), distribution_d(generator));
    }
    
    return *this;
}

int DB::size() const{
    int count = 0;
    for (auto [k , v] : _data){
        count++;
    }
    return count;
}

double DB::accumulate(function<double(const Row)> f) const{
    double total_acm = 0;
    for(auto [k , v] : _data){
        auto m = to_row(k , v);
        total_acm += f(m);
    }
    return total_acm;
}

double DB::average_mass() const{
    int total_m = 0;
    for(auto [k , v] : _data){
        auto m = to_row(k , v);
        total_m += MASS(m);
    }
    total_m = total_m / size();
    return total_m;
}

double DB::average_distance() const{
    int total_d = 0;
    for (auto [k , v] : _data){
        auto m = to_row(k , v);
        total_d += DISTANCE(m);
    }
    total_d = total_d / size();
    return total_d;
}

