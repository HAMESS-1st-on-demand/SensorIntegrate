#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define ADC_CHANNEL1 0
#define ADC_CHANNEL2 1
#define ADC_CHANNEL3 2
#define ADC_CHANNEL4 3 
#define SPI_SPEED 1000000 // 1Mhz
#define CS 1

//For DustSensor
#define SAMPLINGTIME 280
#define LED 0 //미세먼지 측정LED
#define DELTA 40

unsigned char buffer[3];

int setWiringPi(){
    if(wiringPiSetup() == -1) return -1;
    if(wiringPiSPISetup(0, SPI_SPEED) == -1) return -1;
    pinMode(CS, OUTPUT);
    pinMode(LED, OUTPUT);
    return 1;
}

int setConfigBit(int channel){
    buffer[0] = 0b110; // 채널에 따른 시작 바이트 설정
    buffer[1] = channel<<6;
    buffer[2] = 0;
}

int ReadDustSensor(){
    int adc = 0;

    setConfigBit(ADC_CHANNEL3);

    digitalWrite(LED,LOW);
    delayMicroseconds(SAMPLINGTIME); //미세먼지를 측정하기위한 샘플링 시간
    
    digitalWrite(CS, LOW); // CS/SHDN bit을 0으로 만들어야 값을 얻을 수 있다.
    wiringPiSPIDataRW(0, buffer, 3); // SPI 장치와 데이터 교환
    digitalWrite(CS, HIGH); // CS/SHDN bit : CHANNEL 바뀔 때 1로 setting
    
    delayMicroseconds(DELTA);
    digitalWrite(LED,HIGH);
    adc = ((buffer[1] & 0x0F) << 8) + buffer[2]; // 데이터 교환 후 ADC 값 버퍼 추출, 반환
    return adc;
}

int ReadWaterLevelSensor(){ 
    int adc = 0;

    setConfigBit(ADC_CHANNEL4);
    digitalWrite(CS, LOW); // CS/SHDN bit을 0으로 만들어야 값을 얻을 수 있다.
    wiringPiSPIDataRW(0, buffer, 3); // SPI 장치와 데이터 교환
    digitalWrite(CS, HIGH); // CS/SHDN bit : CHANNEL 바뀔 때 1로 setting

    adc = ((buffer[1] & 0x0F) << 8) + buffer[2]; // 데이터 교환 후 ADC 값 버퍼 추출, 반환
    return adc;
}

int main(void){
    if(setWiringPi()==-1) {
        printf("Failed to setup WiringPi\n");
        return -1;
    }

    while(1){
        //채널 0: 미세먼지 센서 
        int dust = ReadDustSensor();
        int waterLev = ReadWaterLevelSensor();
        printf("Dust = %d\n", dust);
        printf("Water Level = %d\n", waterLev);
        delay(1000);
    }

    return 0;
}