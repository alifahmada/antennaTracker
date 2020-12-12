/* Nama  : Alif Ihza Ahmada
 * NIM   : 21060116130106
 * 
 * Last Edit  : 21 February 2019
 */


#include <TinyGPS++.h>
#include <math.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <MPU6050.h>
//#include <MPU6050_6Axis_MotionApps20.h>
#include <I2Cdev.h>
#include <Kalman.h>

#define serialGps Serial2
#define terima Serial1
#define servoYawMin 1375//1375
#define servoYawMax 1625//1625
#define servoPitchMin 1600
#define servoPitchMax 2100
#define rtod 57.2957795
#define dtor 0.0174532925

float bearingRad, bearingDeg, Lat=-7.643771, mLat, Lon=107.685608, mLon, dLon, mLat1, mLon1, alt = 5, y, x, x1, yI, a, c, d,
      ting, trigonometri, kpPitch, kiPitch, kdPitch, spPitch, akselX, akselY, 
      compassX, compassY, compassZ, heading, sudutHeading, deklinasi,actPitch,actRoll,
      kpYaw, kiYaw, kdYaw, spYaw, error, lastErrorYaw, errorAtas, error360,
      pYaw, iYaw, dYaw, pidYaw, pwmYawMax, errorPitch=0, lastErrorPitch, pPitch, iPitch, dPitch, pidPitch,
      ele, Pitch, Roll, gyYangle;
float vGps, altM, suhu, lembab, tekanan, compassBear;
const byte dataByte = 64;
char dataTerima[dataByte];
char tempChar[dataByte];
char dataPayload[dataByte] = {0};
bool dataBaru = false;
char e;

float lat1=-6.374119,  lon1=106.6283843;//-6.374163,106.628336
int pwmYaw, pwmYawBase = 1500, pwmPitch, pwmPitchBase=1700, trackBear, 
    gerak, coba, elev, yMin=0, yMax=0;
unsigned int xOffset=0, yOffset=0, zOffset=0;
unsigned long prevMill = 0;
const long interval = 3000;
float sLat = 51.509865;//51.509865
float sLon = -0.118092;//-0.118092 London Lat Long
float pi = 3.14159;
float R = 6371000; //Jari-jari bumi dalam meter
float dt=0.033, elapsedTime, Time,timePrev;
float KA=0.02, KG=0.98;

Servo servoYaw;
Servo servoPitch;
Servo cobaServo;
TinyGPSPlus gps;
MPU6050 mpu;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
//Kalman kalmanX;
Kalman kalmanY;
uint16_t packetSize;


void setup() {
  // put your setup code here, to run once:
  servoYaw.writeMicroseconds(pwmYawBase);
  servoPitch.writeMicroseconds(pwmPitchBase);
  servoPitch.attach(10, servoPitchMin, servoPitchMax);
  servoYaw.attach(11, servoYawMin, servoYawMax);
  
  Wire.begin();
  initMpu();
//  initMag();
  serialGps.begin(9600);
  terima.begin(9600);
  Serial.begin(115200);
  Time=millis();
}

void loop() {
  timePrev = Time;
  Time = millis();
  elapsedTime = (Time - timePrev)/1000;
  char inMode;
  
  bacaGps();
  bacaMpu();
//  bacaCompass();
  //parseAscii();//Terima data versi 1 String
  bacaSerial();//Terima data versi 2 char
  
  bearing();
  haversine();
  kendaliAzimuth(2,1,0.08);//kp,ki,kd
  kendaliElevasi(5,8.5,0);//kp,ki.kd

  if(mLat !=0 && mLon != 0){
    servo(); 
  }

  unsigned long curMill = millis();   
  if(curMill - prevMill >= interval){
    prevMill = curMill;
  dataMuatan();
  mLat1 = mLat;
  mLon1 = mLon;
  }
  tampilanData();
  delay(20);
}

void servo(){
  
    servoYaw.writeMicroseconds(pwmYaw);
    servoPitch.writeMicroseconds(pwmPitch);
  
}
