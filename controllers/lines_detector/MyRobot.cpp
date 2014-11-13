/**
 * @file    MyRobot.cpp
 * @brief  lines_detector
 *
 * @author MªElvira Tomeo Martin <100292974@alumnos.uc3m.es>
 * @date    2014-11
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    // Habilito camara
    _spherical_camera = getCamera("camera_s");
    _spherical_camera->enable(_time_step);

}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    // Deshabilito camara
    _spherical_camera->disable();

}

//////////////////////////////////////////////

void MyRobot::run()
{
    int sum;
    unsigned char green = 0, red = 0, blue = 0;
    double percentage_yellow = 0.0;

    // Tamaño de la imagen
    int image_width_s =  _spherical_camera->getWidth();
    int image_height_s = _spherical_camera->getHeight();
    cout << "Size of forward camera image: " << image_width_s << ", " <<  image_height_s << endl;


    while (step(_time_step) != -1) {
        sum = 0; // inicializo el sumador a cero

        // Get current image from forward camera
        const unsigned char *image_s =  _spherical_camera->getImage();

        // Loop for get size of green, blue and red.
        for (int x = 0; x < image_width_s; x++) {
            for (int y = 0; y < image_height_s; y++) {
                green =  _spherical_camera->imageGetGreen(image_s, image_width_s, x, y);
                red =  _spherical_camera->imageGetRed(image_s, image_width_s, x, y);
                blue =  _spherical_camera->imageGetBlue(image_s, image_width_s, x, y);

                if ((green > 245) && (red > 245) && (blue < 51)) {
                    sum = sum + 1;
                }
            }
        }

        percentage_yellow = (sum / (float) (image_width_s * image_height_s)) * 100;
        cout << "Percentage of yellow in spherical camera image: " << percentage_yellow << endl;
        if ( percentage_yellow > 0.2)
        {
            cout << " Linea detectada "<<endl;
        }


        // Turn around slowly
        _left_speed = 5;
        _right_speed = -5;

        // Set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
