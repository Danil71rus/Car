/*
   -- Car --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.13 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.13.13 or later version;
     - for iOS 1.10.3 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// можете включить вывод отладочной информации в Serial на 115200
//#define REMOTEXY__DEBUGLOG    

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__WIFI_CLOUD

#include <ESP8266WiFi.h>

// настройки соединения 
#define REMOTEXY_WIFI_SSID "Stepin71"
#define REMOTEXY_WIFI_PASSWORD "354627DON71RUS"
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com"
#define REMOTEXY_CLOUD_PORT 6376
#define REMOTEXY_CLOUD_TOKEN "00d12f7909ae7183974757de7a186066"


// мин. сигнал, при котором мотор начинает вращение
#define MIN_DUTY 960

// пины драйвера
#define MOT_RA D6
#define MOT_RB D5
#define MOT_LA D7
#define MOT_LB D8


#include <RemoteXY.h>
#include <GyverMotor.h>
// (тип, пин, ШИМ пин, уровень)
GMotor motorR(DRIVER2WIRE, MOT_RA, MOT_RB, HIGH);
GMotor motorL(DRIVER2WIRE, MOT_LA, MOT_LB, HIGH);

// конфигурация интерфейса RemoteXY  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 34 bytes
  { 255,2,0,0,0,27,0,17,0,0,0,31,2,106,200,200,84,1,1,1,
  0,5,14,88,78,78,20,35,39,39,32,4,31,25 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
    int8_t jost1_x; // oт -100 до 100
    int8_t jost1_y; // oт -100 до 100

    // other variable
    uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
    Serial.begin(115200);
    RemoteXY_Init ();

    motorR.setResolution(10);
    motorL.setResolution(10);

    motorR.setMode(AUTO);
    motorL.setMode(AUTO);

    // НАПРАВЛЕНИЕ ГУСЕНИЦ (зависит от подключения)
    motorR.setDirection(REVERSE);
    motorL.setDirection(REVERSE);

    // мин. сигнал вращения
    motorR.setMinDuty(MIN_DUTY);
    motorL.setMinDuty(MIN_DUTY);

    // плавность скорости моторов
//    motorR.setSmoothSpeed(80);
//    motorL.setSmoothSpeed(80);
    // TODO you setup code
}

void loop() 
{ 
    RemoteXY_Handler ();
    // Serial.println(RemoteXY.jost1_x);
    motorControl();
    // TODO you loop code
    // используйте структуру RemoteXY для передачи данных
    // не используйте функцию delay(), вместо нее используйте RemoteXY_delay()
}


void motorControl() {
    if (RemoteXY.connect_flag) {
        // Serial.println("x: " + String(RemoteXY.jost1_x));
        // Serial.println("y: " + String(RemoteXY.jost1_y));

        int lx = map(RemoteXY.jost1_x, -100, 100, -1023, 1023);
        int ly = map(RemoteXY.jost1_y, -100, 100, -1023, 1023);

        int dr = ly + lx;
        int dl = ly - lx;

        dr = constrain(dr, -1023, 1023);
        dl = constrain(dl, -1023, 1023);

        Serial.println("lx: " + String(lx) + ", ly: " +  String(ly) + "; dr: " + String(dr) + ", dl: " + String(dl));

        // задаём целевую скорость
        motorR.setSpeed(dr);
        motorL.setSpeed(dl);
    } else {
        // проблема с геймпадом - остановка
        motorR.setSpeed(0);
        motorL.setSpeed(0);
    }
}
