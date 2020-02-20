#include "gtest/gtest.h"
#include "elma/elma.h"

namespace {

    using namespace elma;

    class DoNothing : public Process {
      public:
        DoNothing(std::string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {}
        void stop() {}
    };   
    
    TEST(Elma,Basics) {

      Manager m;
      DoNothing p("Do Nothing");

      m.schedule(p, 1_ms)    // process updates every 1ms
        .init()              // initialize all processes
        .run(10_ms);         // run for 1s

    }

    class MyProcess : public elma::Process {
      public:
        MyProcess(std::string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() { 
          std::cout << name() << ": " 
                    << milli_time()
                    << "ms\n";
        }
        void stop() {}
    };    

    TEST(Elma,NumUpdates) {
        Manager m;
        MyProcess p("A"), q("B");

        m.schedule(p, 1_ms)
         .schedule(q, 5_ms)
         .init()
         .run(11_ms);

        ASSERT_EQ(p.num_updates(), 10);
        ASSERT_EQ(q.num_updates(), 2);      
    }
/*
    TEST(RandomProcess, RandomProcess){
        elma::Manager m;
        RandomProcess r("random numbers");
        Filter f("filter");
        elma::Channel link("link");

        m.schedule(p,1ms);
          .schedule(f,1ms)
          .add_channel(link)
          .init()
          .run(100ms);
        ASSERT_EQ(f.value(), 0.5, 0.001);

    }

    TEST(Integrator, Integrator){
      elma::Manager m;
      elma::Channel link("link");
      elma::Channel afterlink("afterlink");

      Integrator y ("test i");
      Integrator y1 ("test in");
      m.schedule(y, 1ms);
        .schedule(y1, 1ms);
        .add_channel(link);
        .init();
        .run(100ms);

        ASSERT_EQ(y1.value(), 10, 0.000001);
    }
*/
}