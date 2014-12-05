/**
 * @file    MyRobot.cpp
 * @brief   Controlador para realizar la búsqueda y rescate de personas
 *
 * @author  Sergio Sánchez Martín <100292704@alumnos.uc3m.es>
 * @author  María Elvira Toemo Martín <100292974@alumnos.uc3m.es>
 * @date    2014-12-05
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;


    _left_speed = 0;
    _right_speed = 0;


    // Se habilita y se obtiene la brújula
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);

    // Se habilita la camara frontal
    _forward_camera = getCamera("camera_f");
    _forward_camera->enable(_time_step);


    // Se habilita y se obtiene los diferentes sensores de proximidad
    _distance_sensor[0]=getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1]=getDistanceSensor("ds3");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2]=getDistanceSensor("ds15");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3]=getDistanceSensor("ds12");
    _distance_sensor[3]->enable(_time_step);

    // Se inicializa el modo compass
    _mode =COMPASS;

}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    // Se deshabilita la brújula
    _my_compass->disable();

    // Se deshabilitan los sensores de proximidad
    _distance_sensor[0]->disable();
    _distance_sensor[1]->disable();
    _distance_sensor[2]->disable();
    _distance_sensor[3]->disable();

    // Se deshabilita la cámara frontal
    _forward_camera->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{

    int contador =0;
    int primera_vez = 0;
    int contador2 =0;

    while (step(_time_step) != -1)
    {
        double val_ir0=0.0, val_ir3=0.0, val_ir15=0.0, val_ir12=0.0;

        // Lectura de los sensores de proximidad
        val_ir0 = _distance_sensor[0]->getValue();
        val_ir3 = _distance_sensor[1]->getValue();
        val_ir15 = _distance_sensor[2]->getValue();
        val_ir12 = _distance_sensor[3]->getValue();

        // Mostrar el valor de los sensores
        cout << "sensor 0: " <<  val_ir0 <<endl;
        cout << "sensor 3: " <<  val_ir3 <<endl;
        cout << "sensor 15: " << val_ir15 <<endl;
        cout << "sensor 12: " <<  val_ir12 <<endl;

        //Lógica para la navegación y búsqueda

        if((primera_vez==0)&&(val_ir0<DISTANCE_LIMIT-99)&&(val_ir15<DISTANCE_LIMIT-99)&&(val_ir3<DISTANCE_LIMIT-99)&&(val_ir12<DISTANCE_LIMIT-99))
        {
            _mode = COMPASS;
            cout <<"Compas"<<endl;
        }else
        {
            //Contador para determinar los ciclos de navegación
            if(contador<2000)
            {
                primera_vez=1;
                cout<<"Estoy navegando"<<endl;
                contador=contador +1;
                // Llamada a la función de navegación
                navegacion();

                cout<<"Contador"<<contador<<endl;
            }
            else{
                if ( contador2<500){
                    cout<<"Estoy buscando"<<endl;

                    // Llamada a la función de búsqueda
                    detectorlineaamarilla();
                    contador2= contador2 +1;
                }
                else
                {
                    // Llamada a la función de la navegación de vuelta
                    navegacionvuelta();
                    cout<<"Estoy navegando de vuelta"<<endl;
                }
            }
        }

        // Modos de actuación
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
            _left_speed = (MAX_SPEED/1.5)-8;
            _right_speed = MAX_SPEED-8;
            break;
        case TURN_RIGHT:
            _left_speed = MAX_SPEED-8;
            _right_speed = (MAX_SPEED/1.5)-8;
            break;
        case OBSTACLE_AVOID_RIGHT:
            _left_speed = - MAX_SPEED/20 ;
            _right_speed = -MAX_SPEED ;
            break;
        case OBSTACLE_AVOID_LEFT:
            _left_speed = - MAX_SPEED ;
            _right_speed = -MAX_SPEED/10;
            break;
        case COMPASS:
            compass_go();
            break;
        case COMPASS_BACK:
            compass_back();
            break;
        case FORWARD_ROUND:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED-30;
            break;
        case BACK:
            _left_speed = -MAX_SPEED;
            _right_speed = - MAX_SPEED;
            break;
        case ROUND:
            _left_speed =MAX_SPEED;
            _right_speed = MAX_SPEED-60;
            break;

        case ROUND_SLOW:
            _left_speed =MAX_SPEED-55;
            _right_speed = -(MAX_SPEED-55);
            break;


        default:
            break;
        }



        // Actuación
        setSpeed(_left_speed, _right_speed);
    }
}


//////////////////////////////////////////////

void MyRobot::navegacion()
{
    double val_ir0=0.0, val_ir3=0.0, val_ir15=0.0, val_ir12=0.0;
    int primera_vez = 0;

    // Lectura de sensores
    val_ir0 = _distance_sensor[0]->getValue();
    val_ir3 = _distance_sensor[1]->getValue();
    val_ir15 = _distance_sensor[2]->getValue();
    val_ir12 = _distance_sensor[3]->getValue();

    // Mostrar valores de los sensores
    cout << "sensor 0: " <<  val_ir0 <<endl;
    cout << "sensor 3: " <<  val_ir3 <<endl;
    cout << "sensor 15: " << val_ir15 <<endl;
    cout << "sensor 12: " <<  val_ir12 <<endl;




    // LOGICA DE CONTROL
    if((val_ir0<DISTANCE_LIMIT-70)&&(val_ir15<DISTANCE_LIMIT-70)){

        if((val_ir12<DISTANCE_LIMIT-70))
        {
            _mode = TURN_RIGHT;
            cout << "right" << endl;
        }
        if((val_ir12>DISTANCE_LIMIT-70) )
        {
            _mode = TURN_LEFT;
            cout << "left" << endl;
        }
        if(val_ir12 == DISTANCE_LIMIT)
        {
            _mode = FORWARD;
            cout << "forward" << endl;
        }
    }
    else{
        if((val_ir0<DISTANCE_LIMIT-70)&&(val_ir15<DISTANCE_LIMIT-70))
        {
            _mode = TURN_RIGHT;
            cout << "right"<<endl;
        }

        if((val_ir0>DISTANCE_LIMIT)&&(val_ir15>DISTANCE_LIMIT))
        {_mode = OBSTACLE_AVOID_LEFT;

            cout << "left"<< endl;
        }
        if(val_ir12>DISTANCE_LIMIT)

        {
            _mode = OBSTACLE_AVOID_LEFT;
            cout << "avoid left" <<endl;
        }
        if(val_ir3>val_ir12+50)

        {
            _mode = OBSTACLE_AVOID_RIGHT;
            cout << "avoid right" <<endl;
        }
        if(val_ir12 == DISTANCE_LIMIT)
        {
            _mode = FORWARD;
            cout << "forward" << endl;
        }
    }
}

void MyRobot ::navegacionvuelta()
{

    double val_ir0=0.0, val_ir3=0.0, val_ir15=0.0, val_ir12=0.0;
    int primera_vez = 0;

    // Lectura de sensores
    val_ir0 = _distance_sensor[0]->getValue();
    val_ir3 = _distance_sensor[1]->getValue();
    val_ir15 = _distance_sensor[2]->getValue();
    val_ir12 = _distance_sensor[3]->getValue();

    // Mostrar valor de los sensores
    cout << "sensor 0: " <<  val_ir0 <<endl;
    cout << "sensor 3: " <<  val_ir3 <<endl;
    cout << "sensor 15: " << val_ir15 <<endl;
    cout << "sensor 12: " <<  val_ir12 <<endl;




    //LOGICA DE CONTROL
    if((val_ir0<DISTANCE_LIMIT-70)&&(val_ir15<DISTANCE_LIMIT-70))
    {
        if( val_ir12 !=0)
        {
            _mode = COMPASS_BACK;
       }

        if((val_ir12<DISTANCE_LIMIT-70))
        {
            _mode = TURN_RIGHT;
            cout << "right" << endl;
        }
        if((val_ir12>DISTANCE_LIMIT-70))
        {
            _mode = TURN_LEFT;
            cout << "left" << endl;
        }
        if(val_ir12 == DISTANCE_LIMIT)
        {
            _mode = FORWARD;
            cout << "forward" << endl;
        }
    }
    else{
        if((val_ir0<DISTANCE_LIMIT-70)&&(val_ir15<DISTANCE_LIMIT-70))
        {
            _mode = TURN_RIGHT;
            cout << "right"<<endl;
        }

        if((val_ir0>DISTANCE_LIMIT)&&(val_ir15>DISTANCE_LIMIT))
        {
            _mode = OBSTACLE_AVOID_LEFT;
            cout << "left"<< endl;
        }
        if(val_ir12>DISTANCE_LIMIT)
        {
            _mode = OBSTACLE_AVOID_LEFT;
            cout << "avoid left" <<endl;
        }
        if(val_ir3>val_ir12+50)
        {
            _mode = OBSTACLE_AVOID_RIGHT;
            cout << "avoid right" <<endl;
        }
        if(val_ir12 == DISTANCE_LIMIT)
        {
            _mode = FORWARD;
            cout << "forward" << endl;
        }
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

void MyRobot :: compass_go()
{
    double compass_angle;

    // Lectura de la brújula
    const double *compass_val = _my_compass->getValues();

    // Conversion del ángulo en grados
    compass_angle = convert_bearing_to_degrees(compass_val);

    cout << "Compass angle (degrees): " << compass_angle << endl;



    if (compass_angle < (DESIRED_ANGLE_GO - 2))
    {
        // Turn right
        _left_speed = MAX_SPEED;
        _right_speed = MAX_SPEED-60;
    }



    else {
        if (compass_angle > (DESIRED_ANGLE_GO + 2))
        {
            // Turn left
            _left_speed = MAX_SPEED-60;
            _right_speed = MAX_SPEED;
        }
        else
        {
            // Move straight forward
            _left_speed = MAX_SPEED+40;
            _right_speed = MAX_SPEED+40;

        }
    }

}
void MyRobot::compass_back()
{
    double compass_angle;

    // Lectura de la brújula
    const double *compass_val = _my_compass->getValues();

    // Conversión del ángulo a grados
    compass_angle = convert_bearing_to_degrees(compass_val);

    cout << "Compass angle (degrees): " << compass_angle << endl;



    if (compass_angle < (DESIRED_ANGLE_BACK - 2))
    {
        // Turn right
        _left_speed = MAX_SPEED;
        _right_speed = MAX_SPEED-60;
    }


    else {
        if (compass_angle > (DESIRED_ANGLE_BACK + 2))
        {
            // Turn left
            _left_speed = MAX_SPEED-60;
            _right_speed = MAX_SPEED;
        }
        else
        {
            // Move straight forward
            _left_speed = MAX_SPEED+40;
            _right_speed = MAX_SPEED+40;

        }
    }

}
//////////////////////////////////////////////

void MyRobot::detectorlineaamarilla()
{
    bool proximolinea = false;
    bool espera = true;
    bool giro = true;
    bool cruzarlinea = false;

    double val_ir0=0.0, val_ir3=0.0, val_ir15=0.0, val_ir12=0.0;
    int primera_vez = 0;

    // Lectura de los sensores
    val_ir0 = _distance_sensor[0]->getValue();
    val_ir3 = _distance_sensor[1]->getValue();
    val_ir15 = _distance_sensor[2]->getValue();
    val_ir12 = _distance_sensor[3]->getValue();

    // Mostrar el valor de los sensores
    cout << "sensor 0: " <<  val_ir0 <<endl;
    cout << "sensor 3: " <<  val_ir3 <<endl;
    cout << "sensor 15: " << val_ir15 <<endl;
    cout << "sensor 12: " <<  val_ir12 <<endl;

    _mode = FORWARD;
    cout << "delante"<<endl;
    int sumy=0;
    int sumg=0;
    unsigned char green = 0, red = 0, blue = 0;
    double percentage_yellow = 0.0;
    double percentage_green = 0.0;

    // Tamaño de la  imagen
    int image_width_f = _forward_camera->getWidth();
    int image_height_f = _forward_camera->getHeight();
    cout << "Size of forward camera image: " << image_width_f << ", " <<  image_height_f << endl;

    // Obtención de la imagen desde la cámara frontal
    const unsigned char *image_f = _forward_camera->getImage();

    // Bucle para obtener el tamaño de azul, rojo y verde
    for (int x = 0; x < image_width_f; x++) {
        for (int y = 0; y < image_height_f; y++) {
            green = _forward_camera->imageGetGreen(image_f, image_width_f, x, y);
            red = _forward_camera->imageGetRed(image_f, image_width_f, x, y);
            blue = _forward_camera->imageGetBlue(image_f, image_width_f, x, y);

            if ((green > 245) && (red > 245) && (blue < 51)) {
                sumy = sumy + 1;
            }
            if ((green > 190) && ( red <102) && ( blue < 102 )) {
                sumg = sumg + 1;
            }
        }
    }

    percentage_yellow = (sumy / (float) (image_width_f * image_height_f)) * 100;
    cout << " Porcentaje de amarillo " << percentage_yellow << endl;
    percentage_green = (sumg / (float) (image_width_f * image_height_f)) * 100;
    cout << " Porcentaje de verde " << percentage_green << endl;



    if((val_ir0<DISTANCE_LIMIT-70)&&(val_ir15<DISTANCE_LIMIT-70)){

        if((val_ir12<DISTANCE_LIMIT-70))
        {
            _mode = TURN_RIGHT;
            cout << "right" << endl;
        }
        if((val_ir12>DISTANCE_LIMIT-70) )
        {
            _mode = TURN_LEFT;
            cout << "left" << endl;
        }
        if(val_ir12 == DISTANCE_LIMIT)
        {
            _mode = FORWARD;
            cout << "forward" << endl;
        }
    }
    else{
        if((val_ir0<DISTANCE_LIMIT-70)&&(val_ir15<DISTANCE_LIMIT-70)){
            _mode = TURN_RIGHT;
            cout << "right"<<endl;}

        if((val_ir0>DISTANCE_LIMIT)&&(val_ir15>DISTANCE_LIMIT))
        {_mode = OBSTACLE_AVOID_LEFT;

            cout << "left"<< endl;}
        if(val_ir12>DISTANCE_LIMIT)

        {
            _mode = OBSTACLE_AVOID_LEFT;
            cout << "avoid left" <<endl;
        }
        if(val_ir3>val_ir12+50)

        {
            _mode = OBSTACLE_AVOID_RIGHT;
            cout << "avoid right" <<endl;
        }
        if(val_ir12 == DISTANCE_LIMIT)
        {
            _mode = FORWARD;
            cout << "forward" << endl;
        }
    }



    if ( percentage_yellow > 0.7)
    {
        cout<<"Proximo a la linea"<<endl;
        proximolinea=true;
    }


    if(proximolinea =true && percentage_green>2 )
    {
        _mode = TURN_RIGHT;

        if(percentage_green < 2)
        {
            _mode = TURN_LEFT;
        }

        if(percentage_green > 10)
        {

            _mode= FORWARD;

            cout<<"moviendo hacia victima..."<<endl;

            if ( percentage_green >60 )
            {
                cout << "Persona detectada" << endl;
                espera =true;

                if(espera==true)
                {
                    espera=esperar();
                    navegacionvuelta();

                }

                if(espera==false)
                {

                    cout<<"han pasado 2 segundos"<<endl;

                }

            }
        }
    }

}

//////////////////////////////////////////////

bool MyRobot::esperar()
{

    if(timer<50)
    {
        _mode = STOP;
        cout<<"Stop"<<endl;
        timer=timer+1;
        cout<<"timer "<<timer<<endl;
        return true;

    }
    else
    {
        return false;
    }


}

//////////////////////////////////////////////


