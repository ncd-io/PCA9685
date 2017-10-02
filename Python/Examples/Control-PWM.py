#import smbus for i2c communications
import smbus
#import the chip library
import pca9685
import time

# Get I2C bus, this is I2C Bus 1
bus = smbus.SMBus(1)
#kwargs is a Python set that contains the address of your device as well as a device attenuation value.
#according to our instrumentation a value of .95 will give you the most accurate results.
#If you are running into issues with your pwm frequency being incorrect you can change this number to zero in on a per board/chip basis
#The default address for this chip is 0x40, this simply allows you to manually set it for multi-board chains.
kwargs = {'address': 0x40, 'device_attenuation': .95}
#create the PCA9685 object from the PCA9685 library and pass it the kwargs and com bus.
#the object requires that you pass it the bus object so that it can communicate and share the bus with other chips/boards if necessary
pca9685 = pca9685.PCA9685(bus, kwargs)

while True :
    #set the frequency to 200 hertz
    pca9685.set_pwm_frequency(200)
    #set channel 0 to the maximum setting
    pca9685.set_single_channel(0, 4095)
    #read the status of channel 0
    pca9685.read_single_channel(0)
    time.sleep(.5)
    pca9685.set_single_channel(0, 2046)
    pca9685.read_single_channel(0)
    time.sleep(.5)
    #set channel 0 to off
    pca9685.set_single_channel(0, 0)
    pca9685.read_single_channel(0)
    time.sleep(.5)
