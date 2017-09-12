#include "spark_wiring_i2c.h"
#include "PCA9685.h"
#include "Particle.h"

PCA9685::PCA9685(){}

void PCA9685::setAddress(int a0, int a1, int a2, int a3, int a4, int a5){
    address |= (a0*1+a1*2+a2*4+a3*8+a4*16+a5*32);
}

void PCA9685::init(){
    if(!Wire.isEnabled()){
        Wire.begin();
    }
    reset();
}

void PCA9685::reset(){
    sendCommand(PCA9685_MODE1_REGISTER, mode1);
}

void PCA9685::setPWMFreq(float freq) {
   
  float prescaleval = 25000000 / 4096 / (freq * 0.9) - 1;
  int prescale = prescaleval + 0.5;
  
  int oldmode = readByte(PCA9685_MODE1_REGISTER);
  
  sendCommand(PCA9685_MODE1_REGISTER, (oldmode & ~PCA9685_MODE1_RESTART) | PCA9685_MODE1_SLEEP);
  sendCommand(PCA9685_PRE_SCALE, prescale);
  sendCommand(PCA9685_MODE1_REGISTER, oldmode);
  delay(5);
  sendCommand(PCA9685_MODE1_REGISTER, oldmode | PCA9685_MODE1_RESTART);
}

void PCA9685::_setPWM(int reg, int on, int off){
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(on);
    Wire.write(on >> 8);
    Wire.write(off);
    Wire.write(off >> 8);
    Wire.endTransmission();
}

void PCA9685::setChannel(int num, int val){
    if (val == 4095) {
      _setPWM(PCA9685_LED0_ON_L+(4*num), 4096, 0);
    }
    else if (val == 0) {
      _setPWM(PCA9685_LED0_ON_L+(4*num), 0, 4096);
    }
    else {
      _setPWM(PCA9685_LED0_ON_L+(4*num), 0, val);
    }
}

void PCA9685::setAll(int val){
    setChannel(PCA9685_ALL_LED_ON_L, val);
}

void PCA9685::sendCommand(int reg, int cmd){
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(cmd);
    Wire.endTransmission();
}

int PCA9685::readByte(int reg){
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(address, 1);
    return Wire.read();
}

void PCA9685::readBytes(int reg, int *bytes, int length){
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(address, length);
    for(int i=0;i<length;i++){
        bytes[i] = Wire.read();
    }
}
