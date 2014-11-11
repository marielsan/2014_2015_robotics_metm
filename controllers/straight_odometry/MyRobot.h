/**
 * @file   MyRobot.h
 * @brief   straight_odometry
 *
 * @author  MªElvira Tomeo Martin <100292974@alumnos.uc3m.es>
 * @date    2014-11
 */

#include<iostream>


#include <webots/DifferentialWheels.hpp>

using namespace webots;
using namespace std;

#define MAX_SPEED 100  //Velocidad maxima
#define DISERED_DISTANCE 0.85  //Distancia maxima


class MyRobot : public DifferentialWheels {
private:

    int _time_step;
    double _left_speed, _right_speed; //Defino variables de velocidad
    double _left_encoder , _right_encoder; //Defino variables para el encoder
    double _distance; // variable para la distancia


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
         * @brief Funcion para girar a la izquierda
         */

    void turn_left();
    /**
         * @brief Funcion para girara a la derecha
         */

    void turn_right();




};
