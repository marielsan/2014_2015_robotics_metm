/**
 * @file    MyRobot.h
 * @brief   wall_detector
 *
 * @author MªElvira Tomeo Martin <100292974@alumnos.uc3m.es>
 * @date    2014-11
 */

#include <iostream>

#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define MAX_SPEED           100

class MyRobot : public DifferentialWheels {
private:

    int _time_step;
    Camera * _forward_camera;
    double _left_speed, _right_speed;

public:

    /**
         * @brief Empty constructor of the class.
         */
    MyRobot();

    /**
         * @brief Destructor of the class.
         */
    ~MyRobot();

    /**
         * @brief User defined function for initializing and running the template class.
         */
    void run();
};
