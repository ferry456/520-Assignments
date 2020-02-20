#include "gtest/gtest.h"
#include "elma/elma.h"
#include "stopwatch.h"
//#include "random_process.h"
#include "filter.h"
#include "derivative.h"
#include "random_process.h"
#include "integrator.h"
#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

namespace {

    using namespace std::chrono; 
    using namespace elma;   

    TEST(TIME,HIGH_RES) {
       
        high_resolution_clock::time_point t = high_resolution_clock::now();
        std::cout << t.time_since_epoch().count() << " ns since 1970\n";
        typedef duration<double,std::ratio<3600*24*365,1>> years;
        auto y = years(t.time_since_epoch());
        std::cout << y.count() << " years since 1970\n";

    }

    void waste_time() {
        std::this_thread::sleep_for(10_ms);
    }

    TEST(TIME,EXEC_TIME) {

        high_resolution_clock::time_point t1, t2;
        t1 = high_resolution_clock::now();
        waste_time();
        t2 = high_resolution_clock::now();
        std::cout << "waste_time took " << (t2 - t1).count() << " ns\n";
        ASSERT_GE((t2-t1).count(), 10 * 1000 * 1000);

    }

    TEST(stopwatch, stopwatch){
        Stopwatch w; // should set the stopwatch to 0 seconds
        w.start(); 
        SLEEP;
        w.stop();    
        std::cout << w.get_seconds() << "\n"; // about 1.5
        SLEEP;
        std::cout << w.get_seconds() << "\n"; // still about 1.5
        w.start(); 
        SLEEP;
        w.stop();    
        std::cout << w.get_seconds() << "\n"; // about 3.0
        w.reset();
        std::cout << w.get_seconds() << "\n"; // 0.0
    }

    TEST(filter, Filter){
        elma::Manager m;

        RandomProcess r("random numbers");
        Filter f("filter");
        elma::Channel link("link");

        m.schedule(r, 1_ms)
            .schedule(f, 1_ms)
            .add_channel(link)
            .init()
            .run(100_ms);
        double x = f.value();
        std::cout << x << "\n";  
    }

}