#include "spark_wiring_i2c.h"
#include "spark_wiring_constants.h"

class PCA9685{
public:
    //Constructor
    PCA9685(void);
    
    int address = 0x40;
    
    //Set Address.  Indicate status of jumpers on board.  Send 0 for not installed, send 1 for installed
    void setAddress(int a0, int a1, int a2, int a3, int a4, int a5);
    
    void init();
    void reset();
    
    void setPWMFreq(float freq);
    
    void _setPWM(int reg, int on, int off);
    void setChannel(int num, int val);
    void setAll(int val);
    int readChannel(int num);
private:
    void write8(int reg, int data);
};
