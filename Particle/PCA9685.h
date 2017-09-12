#include "spark_wiring_i2c.h"
#include "spark_wiring_constants.h"

//Mode 1 Register
#define PCA9685_MODE1_REGISTER 0x00
#define PCA9685_MODE1_RESTART 0x80
#define PCA9685_MODE1_EXTCLK 0x40
#define PCA9685_MODE1_AI 0x20
#define PCA9685_MODE1_SLEEP 0x10
#define PCA9685_MODE1_SUB1 0x08
#define PCA9685_MODE1_SUB2 0x04
#define PCA9685_MODE1_SUB3 0x02
#define PCA9685_MODE1_ALLCALL 0x01

//Mode 2 Register
#define PCA9685_MODE2_REGISTER 0x01
#define PCA9685_MODE2_INVRT 0x10
#define PCA9685_MODE2_OCH 0x08
#define PCA9685_MODE2_OUTDRV 0x04

//Active LOW Output Enable input pin settings described in table 6 of datasheet
#define PCA9685_MODE2_OUTNE_1 0x01
#define PCA9685_MODE2_OUTNE_1 0x02

//Additional addressing
#define PCA9685_SUBADR1 0x02
#define PCA9685_SUBADR1_ENABLE 0x71
#define PCA9685_SUBADR2 0x03
#define PCA9685_SUBADR1_ENABLE 0x72
#define PCA9685_SUBADR3 0x04
#define PCA9685_SUBADR1_ENABLE 0x74
#define PCA9685_ALLCALLADR 0x05
#define PCA9685_ALLCALLADR_ENABLE 0x70

//Starting point for all calls to specific channels
#define PCA9685_LED0_ON_L 0x06

#define PCA9685_ALL_LED_ON_L 0xFA

#define PCA9685_PRE_SCALE 0xFE
#define PCA9685_TEST_MODE 0xFF


class PCA9685{
public:
    //Constructor
    PCA9685(void);
    
    int address = 0x40;
    
    int mode1 = PCA9685_MODE1_AI;
    
    //Set Address.  Indicate status of jumpers on board.  Send 0 for not installed, send 1 for installed
    void setAddress(int a0, int a1, int a2, int a3, int a4, int a5);
    
    void init();
    void reset();
    
    void setPWMFreq(float freq);
    
    void _setPWM(int reg, int on, int off);
    void setChannel(int num, int val);
    void setAll(int val);
private:
    void sendCommand(int reg, int data);
    int readByte(int reg);
    void readBytes(int reg, int *bytes, int length);
};
