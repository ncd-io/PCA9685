// This #include statement was automatically added by the Particle IDE.
#include "PCA9685.h"

PCA9685 pwm;

void setup() {
    pwm.init();
    pwm.setPWMFreq(30);
    Particle.function("channel1", channel_1);
    Particle.function("readPWM", read_pwm);
}

int channel_1(String val){
    pwm.setChannel(0, val.toInt());
    return 1;
}
int read_pwm(String cmd){
    return pwm.readChannel(cmd.toInt());
}
void loop() {

}
