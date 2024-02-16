//from https://forums.adafruit.com/viewtopic.php?f=19&t=137995

#ifndef __SIMPLE_LIS3DH_I2C_CPP_
#define __SIMPLE_LIS3DH_I2C_CPP_
//Registers and Datasheet: https://www.st.com/content/ccc/resource/technical/document/datasheet/3c/ae/50/85/d6/b1/46/fe/CD00274221.pdf/files/CD00274221.pdf/jcr:content/translations/en.CD00274221.pdf
#include <stdint.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>

#define LIS3DH_DEFAULT_ADDRESS 0x19

#define LIS3DH_REG_STATUS_REG_AUX 0x07
#define LIS3DH_REG_OUT_ADC1_L 0x08
#define LIS3DH_REG_OUT_ADC1_H 0x09
#define LIS3DH_REG_OUT_ADC2_L 0x0A
#define LIS3DH_REG_OUT_ADC2_H 0x0B
#define LIS3DH_REG_OUT_ADC3_L 0x0C
#define LIS3DH_REG_OUT_ADC3_H 0x0D
#define LIS3DH_REG_WHO_AM_I 0x0F
#define LIS3DH_REG_CTRL_REG0 0x1E
#define LIS3DH_REG_TEMP_CFG_REG 0x1F
#define LIS3DH_REG_CTRL_REG1 0x20
#define LIS3DH_REG_CTRL_REG2 0x21
#define LIS3DH_REG_CTRL_REG3 0x22
#define LIS3DH_REG_CTRL_REG4 0x23
#define LIS3DH_REG_CTRL_REG5 0x24
#define LIS3DH_REG_CTRL_REG6 0x25
#define LIS3DH_REG_REFERENCE 0x26
#define LIS3DH_REG_STATUS_REG 0x27
#define LIS3DH_REG_OUT_X_L 0x28            //n-axis acceleration data. The value is expressed as twoâ€s complement left-justified.
#define LIS3DH_REG_OUT_X_H 0x29
#define LIS3DH_REG_OUT_Y_L 0x2A
#define LIS3DH_REG_OUT_Y_H 0x2B
#define LIS3DH_REG_OUT_Z_L 0x2C
#define LIS3DH_REG_OUT_Z_H 0x2D
#define LIS3DH_REG_FIFO_CTRL_REG 0x2E
#define LIS3DH_REG_FIFO_SRC_REG 0x2F
#define LIS3DH_REG_INT1_CFG 0x30
#define LIS3DH_REG_INT1_SRC 0x31
#define LIS3DH_REG_INT1_THS 0x32
#define LIS3DH_REG_INT1_DURATION 0x33
#define LIS3DH_REG_INT2_CFG 0x34
#define LIS3DH_REG_INT2_SRC 0x35
#define LIS3DH_REG_INT2_THS 0x36
#define LIS3DH_REG_INT2_DURATION 0x37
#define LIS3DH_REG_CLICK_CFG 0x38
#define LIS3DH_REG_CLICK_SRC 0x39
#define LIS3DH_REG_CLICK_THS 0x3A
#define LIS3DH_REG_TIME_LIMIT 0x3B
#define LIS3DH_REG_TIME_LATENCY 0x3C
#define LIS3DH_REG_TIME_WINDOW 0x3D
#define LIS3DH_REG_ACT_THS 0x3E
#define LIS3DH_REG_ACT_DUR 0x3F
typedef enum {
   LIS3DH_RANGE_16_G         = 0b11,   // +/- 16g
   LIS3DH_RANGE_8_G           = 0b10,   // +/- 8g
   LIS3DH_RANGE_4_G           = 0b01,   // +/- 4g
   LIS3DH_RANGE_2_G           = 0b00    // +/- 2g (default value)
} lis3dh_range_t;
typedef enum {
   LIS3DH_AXIS_X         = 0x0,
   LIS3DH_AXIS_Y         = 0x1,
   LIS3DH_AXIS_Z         = 0x2,
} lis3dh_axis_t;
typedef enum {//Used with register 0x2A (LIS3DH_REG_CTRL_REG1) to set bandwidth
   LIS3DH_DATARATE_400_HZ = 0b0111, //  400Hz
   LIS3DH_DATARATE_200_HZ = 0b0110, //  200Hz
   LIS3DH_DATARATE_100_HZ = 0b0101, //  100Hz
   LIS3DH_DATARATE_50_HZ = 0b0100, //   50Hz
   LIS3DH_DATARATE_25_HZ = 0b0011, //   25Hz
   LIS3DH_DATARATE_10_HZ = 0b0010, // 10 Hz
   LIS3DH_DATARATE_1_HZ = 0b0001, // 1 Hz
   LIS3DH_DATARATE_POWERDOWN = 0,
   LIS3DH_DATARATE_LOWPOWER_1K6HZ = 0b1000,
   LIS3DH_DATARATE_LOWPOWER_5KHZ =  0b1001,
} lis3dh_dataRate_t;

#define LIS3DH_ALL_AXIS_AVAILABLE  0b0111

class Simple_Lis3dh_i2c {
private:
      bool  _initiated = false;
      int     _deviceAddress = 0;
      int     _deviceIdentifier = 0;
      float  _accelerometerConversion = 1.0f;//for converting "xyz raw" to "xyz"
      
      short read_raw_data(int address){
         short result;
         result = wiringPiI2CReadReg8(this->_deviceIdentifier, address);
         return result;
      }
      short read_raw_data(int address_high, int address_low){
         short byte_high, byte_low, result;
         byte_high = wiringPiI2CReadReg8(this->_deviceIdentifier, address_high);
         byte_low = wiringPiI2CReadReg8(this->_deviceIdentifier, address_low);
         result = (byte_high << 8) | byte_low;
         return result;
      }
      void write_raw_data(int address, int value){
         wiringPiI2CWriteReg8(this->_deviceIdentifier, address, value);
      }
public:
      void SetAllAxisEnabled(){
         uint8_t ctrl_reg1 = read_raw_data(LIS3DH_REG_CTRL_REG1);
         ctrl_reg1 |= LIS3DH_ALL_AXIS_AVAILABLE;
         write_raw_data(LIS3DH_REG_CTRL_REG1, ctrl_reg1);
      }
      void SetDataRate(lis3dh_dataRate_t dataRate){
         uint8_t ctrl_reg1 = read_raw_data(LIS3DH_REG_CTRL_REG1);
         ctrl_reg1 &= 0b00001111;//left 4 bits reset to 0, right 4 bits are untouched
         ctrl_reg1 |= dataRate << 4;
         write_raw_data(LIS3DH_REG_CTRL_REG1, ctrl_reg1);
      }
      lis3dh_dataRate_t GetDataRate(){
         uint8_t ctrl_reg1 = read_raw_data(LIS3DH_REG_CTRL_REG1);
         return (lis3dh_dataRate_t)(ctrl_reg1 >> 4);
      }
      void SetRange(lis3dh_range_t range){
         uint8_t ctrl_reg4 = read_raw_data(LIS3DH_REG_CTRL_REG4);
         ctrl_reg4 &= 0b11001111;//2 bits reset to 0, 6 bits are untouched
         ctrl_reg4 |= range << 4;
         write_raw_data(LIS3DH_REG_CTRL_REG4, range);
         switch(range){
            case LIS3DH_RANGE_2_G:   this->_accelerometerConversion = 0.001f; break;
            case LIS3DH_RANGE_4_G:   this->_accelerometerConversion = 0.002f; break;
            case LIS3DH_RANGE_8_G:   this->_accelerometerConversion = 0.004f; break;
            case LIS3DH_RANGE_16_G: this->_accelerometerConversion = 0.012f; break;
            default: this->_accelerometerConversion = 1.0f; break;
         }
      }
      bool SetHighResolutionMode(){
         uint8_t ctrl_reg1 = read_raw_data(LIS3DH_REG_CTRL_REG1);
         if((~ctrl_reg1 & 0b00001000) > 0){//4. bit needs to be 0 (0: high-resolution mode / normal mode, 1: low-power mode)
            uint8_t ctrl_reg4 = read_raw_data(LIS3DH_REG_CTRL_REG4);
            ctrl_reg4 |= 0b00001000;//4. bit need to be 1 (0: high-resolution disabled; 1: high-resolution enabled)
            write_raw_data(LIS3DH_REG_CTRL_REG4, ctrl_reg4);
            return true;
         }
         return false;
      }
      lis3dh_range_t GetRange(){
         uint8_t ctrl_reg4 = read_raw_data(LIS3DH_REG_CTRL_REG4);
         return (lis3dh_range_t)(ctrl_reg4 >> 4);
      }
      void GetAccelerometerData(float& x, float& y, float& z){
         int xraw,yraw,zraw;
         GetAccelerometerRawData(xraw,yraw,zraw);
         x = xraw * this->_accelerometerConversion;
         y = yraw * this->_accelerometerConversion;
         z = zraw * this->_accelerometerConversion;
      }
      void GetAccelerometerRawData(int& x, int& y, int& z){//raw values, stored as 8,10,12 bit left assigned in 16 bit int, so >> 4
         x = this->read_raw_data(LIS3DH_REG_OUT_X_H, LIS3DH_REG_OUT_X_L) >> 4;
         y = this->read_raw_data(LIS3DH_REG_OUT_Y_H, LIS3DH_REG_OUT_Y_L) >> 4;
         z = this->read_raw_data(LIS3DH_REG_OUT_Z_H, LIS3DH_REG_OUT_Z_L) >> 4;
      }
      bool Init(int deviceAddress = LIS3DH_DEFAULT_ADDRESS){
         if(!this->_initiated){
            this->_deviceAddress = deviceAddress;
            this->_deviceIdentifier = wiringPiI2CSetup(this->_deviceAddress);
            int who_am_i = this->read_raw_data(LIS3DH_REG_WHO_AM_I);
            if(who_am_i == 0b00110011){//00110011 is the fixed who_am_i identification to determine the lis3dh
               this->SetAllAxisEnabled();
               this->SetDataRate(LIS3DH_DATARATE_100_HZ);//100Hz rate
               this->SetRange(LIS3DH_RANGE_2_G);//2g sensitivity
               this->_initiated = true;
            }
         }
         return this->_initiated;
      }
};
#endif