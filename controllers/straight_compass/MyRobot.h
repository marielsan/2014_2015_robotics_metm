/**
 * @file    MyRobot.h
 * @brief   A simple example for maintaining a straight line with the compass.
*
* @author  MªElvira Tomeo Martin <100292974@alumnos.uc3m.es>
* @date    2014-10
 */

#include <iostream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define MAX_SPEED       100
#define DESIRED_ANGLE  45.0002

class MyRobot : public DifferentialWheels {
    private:
        int _time_step;
        int contador;

        Compass * _my_compass;
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

        /**
          * @brief An example for converting bearing vector from compass to angle (in degrees).
          */
        double convert_bearing_to_degrees(const double* in_vector);
};
