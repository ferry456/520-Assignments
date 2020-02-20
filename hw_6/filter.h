#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include <vector>
#include "random_process.h"

namespace {
    using namespace elma;
    using namespace std::chrono;
    using namespace std;

    class Filter : public Process{
        public:
        std::vector<double> rand;
        double sum;
        Filter(std::string name) : Process(name) {}

        void init() {
            double average = 0.0;
            double sum = 0.0;
            rand.erase(rand.begin() , rand.end());
        }

        void start() {
            double average = 0.0;
            double sum = 0.0;
            rand.erase(rand.begin(), rand.end());
        }

        void update() {
            double sum = 0;
            if ( rand.size() < 10 ) {
                rand.push_back(channel("link").latest());
            }else{
                rand.erase(rand.begin() + 9);
                rand.push_back(channel("link").latest());  
            }
        }

        void stop() {}

        double value(){
            double sum = 0.0;
            double average = 0;
            for (auto i : rand){
                sum += i;
            }
            average = sum / rand.size();
            return average;
        }

    };
}