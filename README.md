# SensorIntegrate
센서 모듈 통합

## PIN MAP
### SPI 통신
CS PIN: wpi GPIO 1

조도센서 ADC 채널: 0

빗물감지센서 ADC 채널: 1

미세먼지센서 ADC 채널: 2

수위센서 ADC 채널: 3

### 온습도 센서 (one-wire)
온습도센서1 DATA PIN: wpi GPIO 10

온습도센서2 DATA PIN: wpi GPIO 11

## 주요 함수
### int setWiringPi()
SPI를 setup. SPI에 사용되는 CS, LED를 OUTPUT모드로 설정.

성공시 1, 실패시 -1 반환

### int readDustSensor()
미세먼지 센서로부터 아날로그 값을 읽어와 반환.

### int readWaterLevelSensor()
수위 센서로부터 값을 읽어와 반환.

### int readLightSensor();
조도센서로부터 값을 읽어와 반환.

### int readRainSensor();
빗물감지 센서로부터 값을 읽어와 반환

### int readDHTSensor(unsigned char gpio_pin)
온습도센서로부터 온도 정수값만 반환.

checksum에 의해 읽어온 데이터가 정확하지 않다고 판단할 시 -1을 반환.
