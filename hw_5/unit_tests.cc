#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <numeric>      // std::accumulate
#include "examples.h"
//#include "examples.cc"
#include "db.h"
//#include "db.cc"

namespace {

  using namespace std;

  class Imag {
      public: 
      Imag(double a, double b) : x(a), y(b) {}
      double x, y;
  };

  TEST(Vector,Vector) {

      vector<Imag> r;
      r.emplace(r.begin(),2.0,3.0);
      Imag h(1,2);
      r.push_back(h);

    vector<double> v;
    for (int i=0; i< 50; i++) {
      v.push_back(i);
    }
    v.pop_back();

    for (double &i : v)
      i *= i;
    for (double &i : v)        
      std::cout << i << " "; 

    std::cout << "\n";

    std::cout << v.capacity() << "\n";

    v.shrink_to_fit();

    std::cout << v.capacity() << "\n";
    v.push_back(1);
    std::cout << v.capacity() << "\n";     

    vector<int> w = { 1, 2, 3 };  // vector of three ints
    vector<double> x(10,3.14);    // vector of 10 3.14s
    vector<double> y = x;         // copy constructor with assignment operator       

    string s;
    string t = "hello";
    string u = t;

    t.pop_back();
    cout << t << ", "  << "\n";

    std::cout << u.capacity() << "\n";
    u.shrink_to_fit();    

  }

  TEST(VectorString,Common) {

      vector<double> v = { 1, 2, 3 };
      v.push_back(4);

      cout << v.empty() << v.size() << v[0] << (v==v) << (v!=v) << (v>v) << "\n";

      string s = "abc";
      s.push_back('d');

      cout << s << s.empty() << s.size() << s[0] << (s==s) << (s!=s) << (s>s) << "\n";

      vector<double> u;

      for ( double x : v ) {
          u.push_back(x);
      }

      string t;

      for ( char c : s ) {
          cout << c << "\n";
      }

      cout << t << "\n";    

        vector<string> V = { "i", "am", "on", "a", "bumpy", "flight" };
        for (string s : V ) {
            cout << s << "!\n";
        }      

        string q = "I know my ABC's and 123's.";


      for ( char &c : q ) {
          c = toupper(c);
      }

      for ( string::iterator i = q.begin(); i != q.end(); i++ ) {
          *i = tolower(*i);
      }      

      cout << q << "\n";

    auto i = v.begin();
    auto j = i + v.size() / 2;
    i < j; // true      

    q.insert(q.begin()+1, 'x');
    cout << q << "\n";
    q.erase(5,2);
    cout << q << "\n";


  }

  TEST(Find,Find) {
      vector<string> v = { "The", "quick", "brown", "fox" };
      string s = "this is a string";
      int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};      

      auto f1 = find(v.begin(), v.end(), "not quick");
      if ( f1 != v.end() ) {
        cout << *f1 << "\n";
      } else {
          cout << "not found \n";
      }

      auto f2 = find(s.begin(), s.end(), 'i');
      cout << *f2 << "\n"; 

      auto f3 = find(begin(a), end(a), 6);
      cout << *f3 << "\n";       

  }

  TEST(ALG,ALG) {
    vector<int> v = { 1, 2, 3, 4, 5 }, w = { 2,3,4,5,6,6,7,8 };
    cout << accumulate(v.begin(), v.end(), 0) << "\n"; // sum of the elements in v  
    cout << count(v.begin(), v.end(), 3) << "\n";
    cout << (equal(v.begin(), v.end(), w.begin()) ? "true" : "false") << "\n";
    sort(v.begin(), v.end());
    fill(v.begin(), v.end(), 1);
    fill_n(v.begin(), 3, 1);
    copy(v.begin(), v.end(), w.begin() + 3);
    replace(v.begin(), v.end(), 3,-1);
  }

  void add_to(vector<int> &v, int x) {
      transform(v.begin(), v.end(), v.begin(), [x](int y) { return x+y; });
  }


  TEST(LAMBDA,LAMBDA) {
   auto f = [](double x) { return x*x; };
   f(3);

    vector<int> v = { 1, 2, 3, 4, 5 };
    transform(
        v.begin(), 
        v.end(), 
        v.begin(),
        [](int x) { return x*x; }
    );

    for(auto x : v) {
        cout << x << "\n";
    }

  }

  TEST(Map,Map) {

    map<string,string> person;
    person["First"] = "Alan";
    person["Last"] = "Turing";
    person["Job"] = "Code breaker";

    map<string, vector<int>> sequence;
    sequence["fib"] = { 1, 1, 2, 3, 5, 8, 13 };
    sequence["ints"] = { 1, 2, 3, 4, 5, 6 };
    sequence ["squares"] = { 1, 4, 9, 16, 25, 36 };

    map<unsigned int, double> a;
    a[0] = 123;
    a[5] = 34;
    cout << "a[3] = " << a[3] << "\n";

  }

  TEST(sort, sort){
    vector<double> x = {1, 3, -2, 4, -7, -5, 5};
    examples a;
    a.sort_by_magnitude(x);
    for(int i : x){
      std::cout << i << "\n";
    }
  }

  TEST(primes, primes){
    int x = 18;
    examples a;
    vector<int> y = a.primes(x);
    for(auto i : y){
      std::cout << i << "\n";
    }
  }

  TEST(twins, twins){
    vector<int> x = {1,2,3,5,7,8,9,10,12,14,16,18,98};
    examples a;
    vector<tuple<int , int>> y = a.twins(x);
    for(auto i : y){
      int c = get<0>(i);
      int d = get<1>(i);
      std::cout << c << "\n";
      std::cout << d << "\n";
    }
  }

  
  TEST(insert , insert){
    DB db;
    db.insert("earth", 1, 1)
      .insert("mars", 0.11, 0.20)
      .insert("caonima", 0.22, 0.32)
      .insert("bf", 0.32, 0.63)
      .insert("BF", 0.33, 0.63);
      try{
        db.insert("BF", 2, 6);
      } catch (runtime_error e){
        ASSERT_STREQ(e.what(), "Name already exists");
      }
  }
  
  TEST(Ran, Ran){
    DB db;
    db.create_test_data(50);
    for(int i = 0; i < db.size(); i++){
      DB::Row t = db.find(i);
      cout << NAME(t) << " | ";
    }
  }
  
  TEST(find , find){
    DB db;
    db.insert("BATTLEFIELD", 1, 2);
    try{
      db.find_by_name("battlefield");
    }
    catch (runtime_error e){
      ASSERT_STREQ(e.what(), "Couldnt find the row by name");
    }
  }
  
  TEST(AC , AC){
    DB db;
    db.insert("BATTLEFIELD", 1, 2);
    db.insert("battlefield", 1, 2);
    db.insert("ACTIVISION" , 1, 2);
    db.insert("sucks" , 1, 2);
    double acc = db.accumulate([](DB::Row r){return MASS(r);});
    ASSERT_EQ(acc, 4);
  }

  TEST(M_A, M_A){
    DB db;
    db.insert("BATTLEFIELD", 1, 2);
    db.insert("battlefield", 1, 2);
    db.insert("ACTIVISION" , 1, 2);
    db.insert("sucks" , 1, 2);
    double acc = db.accumulate([](DB::Row r){return MASS(r);});
    double ac = db.average_mass();
    ASSERT_EQ(ac, 1);
  }

  TEST(D_A, D_A){
    DB db;
    db.insert("BATTLEFIELD", 1, 2);
    db.insert("battlefield", 1, 2);
    db.insert("ACTIVISION" , 1, 2);
    db.insert("sucks" , 1, 2);
    double acc = db.accumulate([](DB::Row r){return MASS(r);});
    double ac = db.average_distance();
    ASSERT_EQ(ac, 2);
  }

  TEST(size, size){
    DB db;
    db.insert("BATTLEFIELD", 1, 2);
    db.insert("battlefield", 1, 2);
    db.insert("ACTIVISION" , 1, 2);
    db.insert("sucks" , 1, 2);
    auto aq = db.size();
    ASSERT_EQ(aq, 4);
  }


}

 