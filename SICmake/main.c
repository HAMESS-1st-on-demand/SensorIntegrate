#include <stdio.h>
#include <SI.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define LIGHT_TH 200
#define RAIN_TH 1700
#define WATERLEV_TH 2800
#define DUST_TH 2000


int main(void){
    int now;
    int lightTime, rainTime, dustTime, waterTime, temperTime;
    int lightPeriod = 500;
    int rainPeriod = 1000;
    int dustPeriod = 1500;
    int waterPeriod = 2000;
    int temperPeriod = 3000;
    if(setWiringPi()==-1) {
        printf("Failed to setup WiringPi\n");
        return -1;
    }
    now = lightTime = rainTime = dustTime = waterTime = temperTime = millis();
    while(1){
        now = millis();
        if(now - lightTime>=lightPeriod){
            lightTime = now;
            int light = readLightSensor();
            printf("[%d] light = %d\n", now/100,light);
            if(readLightSensor()<LIGHT_TH) {
                printf("썬루프 어둡게\n");
            }
        }
        if(now - rainTime>=rainPeriod){
            rainTime =now;
            int rain = readRainSensor();
            printf("[%d] rain = %d\n", now/100,rain);
            if(readRainSensor()<RAIN_TH){
                printf("썬루프 닫아\n");
            }
        }
        if(now - dustTime>=dustPeriod){
            dustTime=now;
            int dust = readDustSensor();
            printf("[%d] dust = %d\n", now/100,dust);
            if(readDustSensor()>DUST_TH){
                printf("썬루프 닫아\n");
            }
        }
        if(now - waterTime>=waterPeriod){
            waterTime = now;
            int waterLev = readWaterLevelSensor();
            printf("[%d] waterLev = %d\n", now/100,waterLev);
            if(readWaterLevelSensor()>WATERLEV_TH){
                printf("썬루프 열어\n");
            }
        }
        if(now - temperTime>=temperPeriod){
            temperTime = now;
            int temper1 = readDHTSensor(DHT_PIN1);        // 10번 핀으로부터 데이터를 읽음
            int temper2 = readDHTSensor(DHT_PIN2);        // 11번 핀으로부터 데이터를 읽음
            if(temper1 ==-1||temper2 ==-1){
                printf("DHT data not good\n");
                continue;
            }
            else{
                printf("[%d] temper1 = %d, temper2 = %d \n", now/10000,temper1,temper2);
            }

            if(temper1<=40||temper2<=30){
                continue;
            }
            else if(temper1<temper2&&temper2>30){
                printf("썬루프 닫아");
            }
            else if(temper1>temper2&&temper1>40){
                printf("썬루프 열어");
            }
        }
    }

    return 0;
}