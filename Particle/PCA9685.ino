// This #include statement was automatically added by the Particle IDE.
#include "PCA9685.h"

PCA9685 pwm;

void setup() {
    pwm.init();
    pwm.setPWMFreq(30);
    Particle.function("channel1", channel_1);
}

int channel_1(String val){
    pwm.setChannel(0, val.toInt());
    return 1;
}
void loop() {

}
