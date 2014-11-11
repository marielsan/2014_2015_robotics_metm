/**
 * @file    MyRobot.cpp
 * @brief  abostacle_avoidance
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

    _mode = FORWARD;

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);


      // Loop for enable the sensors
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->enable(_time_step);}




    // get sensors and enable

     _distance_sensor[0] = getDistanceSensor("ds0");
      _distance_sensor[1] = getDistanceSensor("ds1");
     _distance_sensor[2] = getDistanceSensor("ds2");
     _distance_sensor[3] = getDistanceSensor("ds3");
     _distance_sensor[4] = getDistanceSensor("ds4");
     _distance_sensor[5] = getDistanceSensor("ds5");
     _distance_sensor[6] = getDistanceSensor("ds6");
     _distance_sensor[7] = getDistanceSensor("ds7");
     _distance_sensor[8] = getDistanceSensor("ds8");
     _distance_sensor[9] = getDistanceSensor("ds9");
     _distance_sensor[10] = getDistanceSensor("ds10");
     _distance_sensor[11] = getDistanceSensor("ds11");
     _distance_sensor[12] = getDistanceSensor("ds12");
     _distance_sensor[13] = getDistanceSensor("ds13");
     _distance_sensor[14] = getDistanceSensor("ds14");
     _distance_sensor[15] = getDistanceSensor("ds15");
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{ //Loop for disable the sensors
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
    _my_compass->disable(); //Disable the compas

}

//////////////////////////////////////////////

void MyRobot::run()
{
    double compass_angle;

    int ir0_val=0 , ir1_val=0 , ir2_val=0 ,  ir3_val=0,  ir4_val =0,  //Inicializo valores de sensores a cero
            ir5_val=0, ir6_val=0, ir7_val=0, ir8_val=0,
            ir9_val=0, ir10_val =0, ir11_val=0, ir12_val=0,
            ir13_val =0, ir14_val =0, ir15_val=0;

    while (step(_time_step) != -1) {
        // Read the sensors

        ir0_val = _distance_sensor[0]->getValue();
        ir1_val = _distance_sensor[1]->getValue();
        ir2_val = _distance_sensor[2]->getValue();
        ir3_val = _distance_sensor[3]->getValue();
        ir4_val = _distance_sensor[4]->getValue();
        ir5_val = _distance_sensor[5]->getValue();
        ir6_val = _distance_sensor[6]->getValue();
        ir7_val = _distance_sensor[7]->getValue();
        ir8_val = _distance_sensor[8]->getValue();
        ir9_val = _distance_sensor[9]->getValue();
        ir10_val = _distance_sensor[10]->getValue();
        ir11_val = _distance_sensor[11]->getValue();
        ir12_val = _distance_sensor[12]->getValue();
        ir13_val = _distance_sensor[13]->getValue();
        ir14_val = _distance_sensor[14]->getValue();
        ir15_val = _distance_sensor[15]->getValue();

        const double *compass_val = _my_compass->getValues();



        // Control logic of the robot  //Condicion para usar la brujula

        if(ir0_val + ir1_val + ir2_val + ir3_val + ir4_val +
                ir5_val + ir6_val + ir7_val + ir8_val +
                + ir9_val + ir10_val + ir11_val+ ir12_val+
                ir13_val + ir14_val + ir15_val <=360)
        {
            // Convert compass bearing vector to angle, in degrees
            compass_angle = convert_bearing_to_degrees(compass_val);
            // Simple bang-bang control
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

        else{  if ((ir1_val > DISTANCE_LIMIT) || (ir14_val > DISTANCE_LIMIT) ||(ir0_val > DISTANCE_LIMIT)||(ir15_val > DISTANCE_LIMIT))
            {_mode = WALL_FOLLOWER;
                cout<<"Delante"<<endl;}
            if (ir9_val >DISTANCE_LIMIT+200)
            {_mode = TURN_LEFT;
                cout <<"Turning left"<<endl;
                if (ir12_val >DISTANCE_LIMIT+300  )
                {_mode = TURN_LEFTF;
                    cout <<"Turning left "<<endl;}}
            if (ir6_val > DISTANCE_LIMIT+200  ) {
                _mode = TURN_RIGHT ;
                cout << "Turning right." << endl;
                if(ir3_val > DISTANCE_LIMIT+300)
                    _mode= TURN_RIGHTF;}



        }



        // Send actuators commands according to the mode
        switch (_mode){
        case STOP:
            _left_speed = 0;
            _right_speed = 0;
            break;
        case FORWARD:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED;
            break;
        case TURN_LEFT:
            _left_speed = MAX_SPEED / 0.80;
            _right_speed = MAX_SPEED;
            break;
        case TURN_LEFTF:  //Giro rapido a la izquiera
            _left_speed = MAX_SPEED / 0.90;
            _right_speed = MAX_SPEED;
            break;
        case TURN_RIGHT:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED / 1.05;
            break;
        case TURN_RIGHTF: //Giro rapido a la derecha
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED /0.9;
            break;
        case WALL_FOLLOWER:
            _left_speed = -MAX_SPEED /3.0;
            _right_speed = -MAX_SPEED / 20.0;
            break;
        default:
            break;
        }

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}



//////////////////////////////////////////////

double MyRobot::convert_bearing_to_degrees(const double* in_vector)  //Funcion del angulo
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;

}
///////
