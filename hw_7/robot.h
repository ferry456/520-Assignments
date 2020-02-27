#ifndef _ROBOT_H
#define _ROBOT_H

#include "elma/elma.h"
#include <iostream>

using namespace elma;



class Mode : public State {
    public:
    Mode(std::string name) : State(name) {}
    void entry(const Event& e) {
        std::cout << "entering " + name() << "\n";
    }
    void during() {}
    void exit(const Event& ) {}
};

class Robot : public StateMachine {
    public :
        Mode Wander = Mode("Wander");
        Mode Make_Noise = Mode("Make Noise"); 
        Mode Evade = Mode("Evade"); 
        Mode Find_Recharge_Station = Mode("Find Recharge Station");
        Mode Recharge = Mode("Recharge");

    Robot(std::string name) : StateMachine(name) {
        set_initial(Wander);
        add_transition("intruder detected", Wander, Make_Noise);
        add_transition("battery low", Wander, Find_Recharge_Station);
        add_transition("battery full", Recharge, Wander);
        add_transition("reset", Make_Noise, Wander);
        add_transition("proximity warning", Make_Noise, Evade);
        add_transition("reset", Evade, Make_Noise);
        add_transition("battery low", Evade, Find_Recharge_Station);
        add_transition("found recharge station", Find_Recharge_Station, Recharge);
    }

};

/*namespace{
    TEST (ro, robot){
        Robot robot = Robot("What a very nice robot.");

        Manager m;
        m.schedule(robot, 10_ms)
            .init()
            .start();

        EXPECT_EQ(robot.current().name(), "Wander");
        m.emit(Event("intruder detected"));
        EXPECT_EQ(robot.current().name(), "Make Noise");
        m.emit(Event("proximity warning"));
        EXPECT_EQ(robot.current().name(), "Evade");
        m.emit(Event("battery full"));
        EXPECT_EQ(robot.current().name(), "Evade");      

/// ETC
    }
}
*/

#endif
