
/**
 * @file    obstacle_avoidance.cpp
 * @brief   obstacle_avoidance
 *
 * @author  MªElvira Tomeo Martin <100292974@alumnos.uc3m.es>
 * @date    2014-10
 */

#include "MyRobot.h"
/**
 * @brief Main program.
 */
int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
