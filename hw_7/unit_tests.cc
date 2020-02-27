#include "gtest/gtest.h"
#include "elma/elma.h"
#include "power.h"
#include "microwave.h"
#include "robot.h"
#include "betterstatemachine.h"

using namespace std::chrono;
using namespace elma;

namespace {
   
    /*TEST(Microwave, Safety) {

        Manager m;

        Power power;      

        Microwave microwave =  Microwave("What a very nice robot.");

        m.schedule(power, 10_ms)
         .schedule(microwave, 10_ms)
         .init();

        m.start();
        m.emit(Event("on button pressed"));
        ASSERT_EQ(true, power.running);


        m.start();
        m.emit(Event("door opened"));    
        m.emit(Event("on button pressed"));
        ASSERT_EQ(false, power.running);
        //EXPECT_EQ(microwave.current().name(), "Evade");
        // ETC

    }*/

    TEST(Ro, Robot){
        Robot robot = Robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
            .init()
            .start();

        std::cout << robot.current().name() << "\n";
        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        std::cout << robot.current().name() << "\n";
        EXPECT_EQ(robot.current().name(), "Make Noise");
        std::cout << robot.current().name() << "\n";
        m.emit(Event("proximity warning"));
        std::cout << robot.current().name() << "\n";
        EXPECT_EQ(robot.current().name(), "Evade");
        std::cout << robot.current().name() << "\n";
        m.emit(Event("battery full"));
        std::cout << robot.current().name() << "\n";
        EXPECT_EQ(robot.current().name(), "Evade");
        std::cout << robot.current().name() << "\n";
    }
    TEST(j, j){
        Mode off("off"), on("on");
        BetterStateMachine fsm("better state machine");

        fsm.set_initial(off)
        .set_propagate(false)
        .add_transition("switch", off, on)
        .add_transition("switch", on, off);
        
        json j = fsm.to_json();
        ASSERT_EQ(j["name"], "better state machine");
        ASSERT_EQ(j["states"].size(), 2);
    }
}
