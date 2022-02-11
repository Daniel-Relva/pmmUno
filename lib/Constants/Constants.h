#ifndef Constants_h
#define Constants_h

// Configuration 
#define BAUDRATE            115200
#define DEVELOPMENT         TRUE

// State Machine
enum StateMachine {
    COLD_START,
    PAD_IDLE,
    POWERED_FLIGHT,
    APOGEE,
    DROGUE_DEPLOYMENT,
    MAIN_DEPLOYMENT,
    LANDED,
    ABORT,
    HOT_START
};

// I2C
#define INA219_ADDR         0x40
#define MPU9250_ADDR        0x68
#define BMP280_ADDR         0x76
#define BMP388_ADDR         0x77

const int I2C_ADDRESSES[4] = {
    INA219_ADDR,
    MPU9250_ADDR,
    BMP280_ADDR,
    BMP388_ADDR
};

// INA219
#define INA_INTERVAL                            	1000
#define MAX_INA_VALUES                            	20
#define MINIMUM_INCREASED_VOLTAGE_FOR_CHARGING   	0.2
#define CHARGING_VOLTAGE                         	4.0
#define LOW_BATTERY                              	3.2
#define CRITICAL_BATTERY                         	3.0
#define HIGH_POWER                             		10000
#define CRITICAL_POWER                         		20000

// BMP388
#define BMP388_INTERVAL               				5000
#define SEA_LEVEL_PRESSURE_HPA        				1010
#define BMP388_TEMP_OVERSAMP          				BMP3_OVERSAMPLING_8X  
#define BMP388_PRES_OVERSAMP          				BMP3_OVERSAMPLING_4X  
#define BMP388_FILTERING              				BMP3_IIR_FILTER_COEFF_3  
#define BMP388_DATARATE               				BMP3_ODR_50_HZ

// BMP280				
#define BMP280_OPMODE                 				Adafruit_BMP280::MODE_NORMAL  
#define BMP280_TEMP_OVERSAMP          				Adafruit_BMP280::SAMPLING_X2  
#define BMP280_PRES_OVERSAMP          				Adafruit_BMP280::SAMPLING_X16  
#define BMP280_FILTERING              				Adafruit_BMP280::FILTER_X16
#define BMP280_STANDBY                				Adafruit_BMP280::STANDBY_MS_500

// MPU9250
#define MPU9250_INTERVAL                            1000

// AdafruitSD
#define SD_ADAFRUIT_CS                   			8
#define SD_ADAFRUIT_SPI_FREQ            			20

#endif