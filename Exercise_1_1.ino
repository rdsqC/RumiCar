#include <RumiCar.h>
#include <cmath>

void move(int power){
    if(0<power){
        RC_drive(FORWARD,power);
    }else{
        RC_drive(REVERSE,-power);
    }
}

bool moving = false;
void setup()
{
    RC_setup();
}

void loop()
{

    int ibound =250;
    int s0, s1, s2, d0, d1, d2;
    s0 = s1 = s2 = d0 = d1 = d2 = 0;
    d0=sensor0.readRangeSingleMillimeters() - s0;
    d1=sensor1.readRangeSingleMillimeters() - s1;
    d2=sensor2.readRangeSingleMillimeters() - s2;
    s0=sensor0.readRangeSingleMillimeters();
    s1=sensor1.readRangeSingleMillimeters();
    s2=sensor2.readRangeSingleMillimeters();




    if (s1<310){
        if(moving){//前動いていた時バックを始める前にとまる。
            RC_drive(BRAKE,0);
            delay(150);
        }

        move(-230);

        if(d0 > d2){
            RC_steer(RIGHT);
        }else{
            RC_steer(LEFT);
        }

        moving = false;
    }else{
        if(!moving){//前バックをしていたとき進む前にとまる。
            RC_drive(BRAKE,0);
            delay(150);
        }

        if (s1<200){
            move(220);
        }else{
            move(240);
        }
        if(abs(d0 - d2) < 70){
            RC_steer(CENTER);
        }else{
            if(d0 > d2){
                RC_steer(LEFT);
            }else{
                RC_steer(RIGHT);
            }
        }

        moving = true;
    }

}
