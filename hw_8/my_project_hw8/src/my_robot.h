#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H 

#include "enviro.h"
#include <iostream>

using namespace enviro;

class MovingForward : public State, public AgentInterface {
    void entry(const Event& e) {}
    void during() {
        track_velocity(10,0);
        if (sensor_value(0) < 40){
            track_velocity(0,0);
            emit(Event("find_way"));
        }
    }
    void exit(const Event& e) {}
};

class Rotating : public State, public AgentInterface {
    void entry(const Event& e) {}
    void during() {
        track_velocity(0, 10);
        if (sensor_value(0) > 40 ){
            damp_movement();
            emit(Event("move_forward"));
        }
    }
    void exit(const Event& e) {}
};

class MyRobotController : public StateMachine, public AgentInterface {

    public:
    
    MyRobotController() : StateMachine(), AgentInterface() {
        set_initial(rotating);
        add_transition("find_way", moving_forward, rotating);
        add_transition("move_forward", rotating, moving_forward);
    }
    MovingForward moving_forward;
    Rotating rotating;
};

class MyRobot : public Agent {
    public:
    MyRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
        //add_process(b);
    }
    private:
    MyRobotController c;
    //MyOtherProcess b;
};

DECLARE_INTERFACE(MyRobot)

#endif