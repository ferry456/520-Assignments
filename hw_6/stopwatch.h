#include <iostream>
#include "gtest/gtest.h"
#include "elma/elma.h"

namespace{
    
    using namespace elma;
    using namespace std::chrono;

    class Stopwatch : public Process{
        public:
            typedef enum { UNINITIALIZED, STOPPED, RUNNING } status_type;
            typedef std::chrono::duration<double,std::ratio<60, 1>> m;
            typedef std::chrono::duration<double,std::ratio<1 , 1>> s;
            typedef std::chrono::duration<double,std::milli> ms;
            typedef std::chrono::duration<double,std::nano> nanos;

            void init() {}
            void update() {}
            void start();              // starts the timer
            void stop();               // stops the timer
            void reset();              // sets stopwatch to zero
            double get_minutes();      // number of minutes counted, as a double
            double get_seconds();      // number of seconds counted, as a double
            double get_milliseconds(); // number of milliseconds counted, as a double
            double get_nanoseconds();  // number of nanoseconds counted, as a double
        
        //private:
            status_type status;
            /*high_resolution_clock::duration period,          // request time between updates
                                            previous_update, // duration from start to update before last
                                            last_update; */    // duration from start to last update
            high_resolution_clock::time_point time_start;    // time of most recent start
            high_resolution_clock::time_point time_stop;
    };

    void Stopwatch::start(){
        status = RUNNING;
        time_start = high_resolution_clock::now();
    }

    void Stopwatch::stop(){
        status = STOPPED;
        time_stop = high_resolution_clock::now();
    }

    void Stopwatch::reset(){
        status = UNINITIALIZED;
        time_stop = time_start;
    }

    double Stopwatch::get_minutes(){
        if (status == RUNNING){
            return m(high_resolution_clock::now() - time_start).count();
        }else{
            return m(time_stop - time_start).count();
        }
    }

    double Stopwatch::get_seconds(){
        if (status == RUNNING){
            return s(high_resolution_clock::now() - time_start).count();
        }else{
            return s(time_stop - time_start).count();
        }
    }
    
    double Stopwatch::get_milliseconds(){
        if (status == RUNNING){
            return ms(high_resolution_clock::now() - time_start).count();
        }else{
            return ms(time_stop - time_start).count();
        }
    }

    double Stopwatch::get_nanoseconds(){
        if (status == RUNNING){
            return nanos(high_resolution_clock::now() - time_start).count();
        }else{
            return nanos(time_stop - time_start).count();
        }
    }













}