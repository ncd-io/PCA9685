# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# This code is designed to work with PCA9685 I2C Devices available from ncd.io.
import time

PCA9685_DEFAULT_ADDRESS                = 0x40
PCA9685_DEVICE_ATTENUATION             = 0.95

class PCA9685():
    def __init__(self, smbus, kwargs = {}):
        self.__dict__.update(kwargs)
        #set address to default if not passed
        if not hasattr(self, 'address'):
            self.address = PCA9685_DEFAULT_ADDRESS
        if not hasattr(self, 'device_attenuation'):
            self.device_attenuation = PCA9685_DEVICE_ATTENUATION

        self.smbus = smbus
        self.reset()

    def set_pwm_frequency(self, frequency_in_hertz):
        prescaleval = 25000000
        prescaleval /= 4096
        prescaleval /= (frequency_in_hertz * self.device_attenuation)
        prescaleval -= 1
        prescale = prescaleval + 0.5

        old_mode = self.smbus.read_byte_data(self.address, 0x00)

        new_mode = (old_mode&0x7F) | 0x10
        self.smbus.write_byte_data(self.address, 0x00, (old_mode&0x7F) | 0x10)
        self.smbus.write_byte_data(self.address, 0xFE, int(prescale))
        self.smbus.write_byte_data(self.address, 0x00, old_mode)
        time.sleep(.005)
        self.smbus.write_byte_data(self.address, 0x00, old_mode | 0x80)

    def _pwm_command(self, channel, on, off):
        self.smbus.write_i2c_block_data(self.address, channel, [on, on>>8, off, off>>8])

    def set_single_channel(self, channel, value):
        channel = 6+4*channel
        if value == 4095:
            self._pwm_command(channel, 4096, 0)
        elif value == 0:
            self._pwm_command(channel,  0, 4096)
        else:
            self._pwm_command(channel, 0, value)


    def read_single_channel(self, channel):
        retval = self.smbus.read_i2c_block_data(self.address, 6+4*channel, 4)
        return retval

    def set_all_channels(self, value):
        self.set_single_channel(61, value)

    def reset(self):
        self.smbus.write_byte_data(self.address, 0x00, 0x20)
