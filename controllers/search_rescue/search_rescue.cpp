/**
 * @file    search_rescue.cpp
 * @brief   Controlador para realizar la búsqueda y rescate de personas
 *
 * @author  Sergio Sánchez Martín <100292704@alumnos.uc3m.es>
 * @author  María Elvira Toemo Martín <100292974@alumnos.uc3m.es>
 * @date    2014-12-05
 */
#include "MyRobot.h"


int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
