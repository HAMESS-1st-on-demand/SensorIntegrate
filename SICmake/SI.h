// ADC analog input 채널
#define ADC_CHANNEL1 0
#define ADC_CHANNEL2 1
#define ADC_CHANNEL3 2
#define ADC_CHANNEL4 3 

#define CS 1            // ADC CS 핀

#define SPI_SPEED 1000000 // 1Mhz

#define DHT_PIN1    10      // DHT 센서 10번 pin
#define DHT_PIN2    11      // DHT 센서 11번 pin

//For DustSensor
#define SAMPLINGTIME 280
#define LED 0 //미세먼지 측정LED
#define DELTA 40

#define MAX_TIMINGS	85        // 최대 신호 추출 개수
       

int setWiringPi();

void setConfigBit(int channel);

int readDustSensor();

int readWaterLevelSensor();

int readLightSensor();

int readRainSensor();

int readDHTSensor(unsigned char gpio_pin);