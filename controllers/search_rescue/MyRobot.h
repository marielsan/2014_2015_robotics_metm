/**
 * @file    MyRobot.h
 * @brief   Controlador para realizar la búsqueda y rescate de personas
 *
 * @author  Sergio Sánchez Martín <100292704@alumnos.uc3m.es>
 * @author  María Elvira Toemo Martín <100292974@alumnos.uc3m.es>
 * @date    2014-12-05
 */

#include <iostream>
#include <sstream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 4
#define DISTANCE_LIMIT      100
#define MAX_SPEED           60
#define DESIRED_ANGLE_GO   162.0002
#define DESIRED_ANGLE_BACK   -162.0002

class MyRobot : public DifferentialWheels {
private:

    int _time_step;
    int timer=0; // Variable para realizar la cuenta de la espera


    DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];
    Compass * _my_compass;
    Camera * _forward_camera;
    double _left_speed, _right_speed;



    enum Mode {
        STOP,
        FORWARD,
        TURN_LEFT,
        TURN_RIGHT,
        OBSTACLE_AVOID_LEFT,
        OBSTACLE_AVOID_RIGHT,
        COMPASS,
        COMPASS_BACK,
        WALL_FOLLOWER,
        FORWARD_ROUND,
        ROUND_SLOW,
        TURN_RIGHTPoco,
        BACK,
        ROUND

    };

    Mode _mode;


public:
    /**
         * @brief Constructor vacio de la clase
         * @param
         * @return
         */
    MyRobot();

    /**
         * @brief Destructor de la clase
         * @param
         * @return
         */
    ~MyRobot();

    /**
         * @brief Función para inicializar el controlador
         * @param
         * @return
         */
    void run();

    /**
          * @brief Función para convertir el ángulo a grados
          * @param in_vector
          * @return double
          */
    double convert_bearing_to_degrees(const double* in_vector);

    /**
          * @brief Función para orientar el robot en la ida
          * @param
          * @return
          */
    void compass_go();

    /**
          * @brief Función para orientar el robot en la vuelta
          * @param
          * @return
          */
    void compass_back();

    /**
          * @brief Función para realizar la búsqueda
          * @param
          * @return
          */
    void detectorlineaamarilla();

    /**
          * @brief Función para esperar dos segundos
          * @param
          * @return bool
          */
    bool esperar();

    /**
          * @brief Función para realizar la navegación en la ida
          * @param
          * @return
          */
    void navegacion();

    /**
          * @brief Función para realizar la navegación en la vuelta
          * @param
          * @return
          */
    void navegacionvuelta();

};

