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
                channel("afterlink").send(v);
            }
        }

        void stop() {}

        double value(){
            double v_old = 0;
            double v_new = 0;
            if ( channel("link").nonempty() && channel("afterlink").nonempty()) {
                v_old = channel("afterlink").latest();
                v_new = channel("link").latest();
                v_new = v_new * delta();
                channel("afterlink").send(v_new);
                v = (v_new - v_old) / delta();
            }else{
                v_new = channel("link").latest();
                channel("afterlink").send(v_new);
                v = 0.0;
            }
            return v;
        }
    };


}