/**
 * @file    MyRobot.cpp
 * @brief   A simple example for maintaining a straight line with the compass.
*
* @author  MªElvira Tomeo Martin <100292974@alumnos.uc3m.es>
* @date    2014-10
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);


    // get and enable the sensors

    _Distance_sensor[0] = getDistanceSensor("ds0");
    _Distance_sensor[0]->enable(_time_step);
    _Distance_sensor[1] = getDistanceSensor("ds1");
    _Distance_sensor[1]->enable(_time_step);
    _Distance_sensor[2] = getDistanceSensor("ds2");
    _Distance_sensor[2]->enable(_time_step);
    _Distance_sensor[3] = getDistanceSensor("ds3");
    _Distance_sensor[3]->enable(_time_step);
    _Distance_sensor[4] = getDistanceSensor("ds12");
    _Distance_sensor[4]->enable(_time_step);
    _Distance_sensor[5] = getDistanceSensor("ds13");
    _Distance_sensor[5]->enable(_time_step);
    _Distance_sensor[6] = getDistanceSensor("ds14");
    _Distance_sensor[6]->enable(_time_step);
    _Distance_sensor[7] = getDistanceSensor("ds15");
    _Distance_sensor[7]->enable(_time_step);

}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{   //Loop for disable the sensor
    _my_compass->disable();

    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _Distance_sensor[i]->disable();
    }
}

//////////////////////////////////////////////

void MyRobot::run()
{
    double compass_angle;
    int contador = 0;
    double ir_val;

    while (step(_time_step) != -1) {

        for(int i=0;i<NUM_DISTANCE_SENSOR;i++){
        ir_val = _Distance_sensor[i]->getValue();
        cout << "valor sensor: " << ir_val << endl;
        }
        // Read the sensors
        const double *compass_val = _my_compass->getValues();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
        contador++;
        cout << "" << contador << endl;
        // Pongo el contador a 600 para que no se pare y sea capad de mostrar un valor cuando llegue a la pared
        if (contador >= 600)
        {
            _left_speed = 0;
            _right_speed = 0;
            cout << "LLEGA!!" << endl;
        }
        else { // Simple bang-bang control
            if (compass_angle < (DESIRED_ANGLE - 2)) {
                // Turn right
                _left_speed = MAX_SPEED;
                _right_speed = MAX_SPEED - 15;
            }
            else {
                if (compass_angle > (DESIRED_ANGLE + 2)) {
                    // Turn left
                    _left_speed = MAX_SPEED - 15;
                    _right_speed = MAX_SPEED;
                }
                else {
                    // Move straight forward
                    _left_speed = MAX_SPEED;
                    _right_speed = MAX_SPEED;
                }
            }
        }

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////

double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;

}
//////////////////////////////////////////////
