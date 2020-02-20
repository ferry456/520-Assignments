#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"
#include <random>
#include <time.h>

namespace {

    using namespace elma;
    using namespace std::chrono;

    class RandomProcess : public Process {
        public:
            bool t = true;
            RandomProcess(std::string name) : Process(name) {}
            void init() {}
            void start() {}
            void update(){
                time_t timer;
                std::default_random_engine generator;
                std::uniform_real_distribution<double> distribution(0.00 , 1.00);
                srand(time(&timer));
                double value = distribution(generator);
                channel("link").send(value);
                /*if (t){
                    double value = 0.75;
                    channel("link").send(value);
                    t = false;
                }else{
                    double value = 0.25;
                    channel("link").send(value);
                    t = true;
                }*/
            }
            void stop(){}
        
    };














}