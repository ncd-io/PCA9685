#include "spark_wiring_i2c.h"
#include "PCA9685.h"
#include "Particle.h"

PCA9685::PCA9685(){}

void PCA9685::setAddress(int a0, int a1, int a2, int a3, int a4, int a5){
    address |= (a0*1+a1*2+a2*4+a3*8+a4*16+a5*32);
}

void PCA9685::init(){
    Wire.begin();
    reset();
}

void PCA9685::reset(){
    write8(0,0);
}

void PCA9685::setPWMFreq(float freq) {
   
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= (freq * 0.9);
  prescaleval -= 1;
  int prescale = prescaleval + 0.5;
  
  Wire.beginTransmission(address);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(address, 1);
  
  int oldmode = Wire.read();
  int newmode = (oldmode&0x7F) | 0x10; // sleep
  
  //Particle.publish("newmode", String(newmode));
  //Particle.publish("prescale", String(prescale));
  
  write8(0x00, newmode);
  write8(0xFE, prescale);
  write8(0x00, oldmode);
  delay(5);
  write8(0x00, oldmode | 0xA1);
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
      _setPWM(6+(4*num), 4096, 0);
    }
    else if (val == 0) {
      _setPWM(6+(4*num), 0, 4096);
    }
    else {
      _setPWM(6+(4*num), 0, val);
    }
}

void PCA9685::setAll(int val){
    setChannel(61, val);
}

void PCA9685::write8(int reg, int data){
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

int PCA9685::readChannel(int num){
    Wire.beginTransmission(address);
    Wire.write(6+(4*num));
    Wire.endTransmission();
    Wire.requestFrom(address, 2);
    int ret = Wire.read();
    ret = Wire.read() + (ret << 4);
    return ret;
}
