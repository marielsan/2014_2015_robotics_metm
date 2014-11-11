/**
 * @file   MyRobot.cpp
 * @brief  obstacle_odometry
 *
 * @author  MªElvira Tomeo Martin <100292974@alumnos.uc3m.es>
 * @date    2014-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    //Inicializo variables
    _time_step = 64;
    _left_speed = MAX_SPEED ;
    _right_speed = MAX_SPEED;
    _right_encoder = 0.0;
    _left_encoder = 0.0;
    _distance =0.0 ;

    //Habilito Encoders
    enableEncoders(_time_step);
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    //Deshabilito Encoders
    disableEncoders();
}

//////////////////////////////////////////////

void MyRobot::run()
{

    while (step(_time_step) != -1) {


        if (_distance <DESIRED_DISTANCE){   //Bucle hasta que la distancia sea la deseada

            //get the encoders
            _left_encoder = getLeftEncoder();
            _right_encoder = getRightEncoder();

            straight();

            _distance = _left_encoder/1000*0.825;
            cout<<"left_encoder  "<<_left_encoder <<endl;
            cout<<"right_encoder"<<_right_encoder<<endl;
            cout <<"distance "<< _distance<< endl;


            if(_distance > DESIRED_DISTANCE-0.77)
            {
                turn_right();

                if(_distance > DESIRED_DISTANCE-0.735)

                {     straight();
                }
                if(_distance>DESIRED_DISTANCE-0.57)
                {
                    turn_left();

                    if(_distance>DESIRED_DISTANCE-0.56)


                    {
                        straight();
                    }
                }
            }
        }


        else {  //Paro motores cuando la distancia sea la deseada
            _left_speed = MAX_SPEED -100;
            _right_speed =MAX_SPEED -100;
        }
        //Set speed
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
void MyRobot::turn_right() //Funcion para girar a la derecha
{
    _left_speed = MAX_SPEED ;
    _right_speed = MAX_SPEED -100;
}
/////////////////////////////////////////////
void MyRobot::turn_left() //Funcion para girara a la izquierda
{
    _left_speed = MAX_SPEED-100;
    _right_speed = MAX_SPEED;
}

//////////////////////////////////////////////
void MyRobot ::straight() // Funcion para ir recto
{

    if(_left_encoder > _right_encoder)
    {
        _left_speed = MAX_SPEED -10 ;
        _right_speed = MAX_SPEED;
    }
    else{
        _left_speed = MAX_SPEED  ;
        _right_speed = MAX_SPEED-10;

    }
}
