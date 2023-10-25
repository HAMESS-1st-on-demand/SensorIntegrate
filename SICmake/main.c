#include <stdio.h>

#include <SI.h>

int main(void){

    if(setWiringPi()==-1) {
        printf("Failed to setup WiringPi\n");
        return -1;
    }

    while(1){
        int light = readLightSensor();
        int rain = readRainSensor();
        
        int dust = readDustSensor();
        int waterLev = readWaterLevelSensor();

        int temper1 = readDHTSensor(DHT_PIN1);        // 10번 핀으로부터 데이터를 읽음
        int temper2 = readDHTSensor(DHT_PIN2);        // 11번 핀으로부터 데이터를 읽음

        printf("light = %d\n", light);
        printf("rain = %d\n",rain);

        printf("Dust = %d\n", dust);
        printf("Water Level = %d\n", waterLev);

        if(temper1!=-1){
            printf( "DHT sensor1: Temperature = %d C\n", temper1);
        }
        else{
            printf("DHT data not good\n");
        }

        if(temper2!=-1){
            printf("DHT sensor2: Temperature = %d C\n", temper2);
        }
        else{
            printf("DHT data not good\n");
        }
        printf("\n");
        
        delay(1000);
    }

    return 0;
}