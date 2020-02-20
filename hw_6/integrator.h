#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"

namespace{
    
    using namespace elma;
    using namespace std::chrono;
    using std::vector;

    class   Integrator : public Process{
        public:
        double v;
        Integrator(std::string name) : Process(name) {}

        void init() {
            double value = 0.0;
        }

        void start() {
            double value = 0.0;
        }

        void update() {
            if ( channel("link").nonempty() ) {
                v = channel("link").latest();
                v = v * delta();
            }
        }

        void stop() {}

        double value(){
            double v = 0;
            if ( channel("link").nonempty() ) {
                v = channel("link").latest();
                v = v * delta();
            }
            return v;
        }




    };


}