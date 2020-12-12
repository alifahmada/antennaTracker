void bacaGps(){
  while(serialGps.available()){
    gps.encode(serialGps.read());
  }
  if(gps.location.isUpdated()){
    //Lat = gps.location.lat();
    //Lon = gps.location.lng();
    //alt = gps.altitude.meters();

    if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
      
    //smartDelay(100);  
  }
}

void initMag(){
  sensor_t sensor;
  mag.getSensor(&sensor);
  if(!mag.begin()){
    Serial.print("Kompas tidak terdeteksi");
    while(1);
  }
}

void bacaCompass(){
  sensors_event_t event;
  mag.getEvent(&event);
  
  float xFs = 1;
  float yFs = 1;
  float offsetX = -10*xFs;//-7.64dalam, -3.14luar//-10
  float offsetY = 9;//-9.5dalam, -11.91luar//9
  float offsetZ = -15.85;//-15.85dalam, luar belum kalibrasi z
  compassX = (event.magnetic.x*xFs)+offsetX;
  compassY = (event.magnetic.y*yFs)+offsetY;
  compassZ = event.magnetic.z;
  heading = atan2(compassY, -compassX);
  deklinasi = 0.013962634016;// http://www.magnetic-declination.com/
  heading += deklinasi;
  
  if(heading > -1.56){
    heading += 1.56;
  }
  if(heading < -1.56){
    heading +=(2*pi)+1.56;
  }
  /*tilt compensation belum bisa
   * 
   * mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  float pitch = atan2(-ax, sqrt(az*az+ay*ay));
  float roll = atan2(ay, sqrt(az*az + ax*ax));
  float xh = compassX*cos(pitch) +compassY*sin(roll)*sin(pitch)+compassZ*cos(roll)*sin(pitch);
  float yh = compassY*cos(roll)-compassZ*sin(roll);
  float heading1 = atan(yh/xh);
  if(heading > -1.56){
    heading += 1.56;
  }
  if(heading1 < -1.56){
    heading1 +=(2*pi)+1.56;
  }*/
  sudutHeading = heading*rtod;
}

void initMpu(){
  //Sensor readings with offsets:  1 -6  16382 0 2 0
  //740  2443  1680  75  -49 48



//  mpu.initialize();
//  mpu.setXAccelOffset(784);
//  mpu.setYAccelOffset(2431);
//  mpu.setZAccelOffset(5599);
//  mpu.setXGyroOffset(75);
//  mpu.setYGyroOffset(-49);
//  mpu.setZGyroOffset(57);
//  mpu.setDMPEnabled(true);
//  fifoCount = mpu.getFIFOCount();
//  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //float pitch = atan(-ax/sqrt(ay*ay+az*az))*rtod;///
  //float roll = atan(ay/sqrt(ax*ax+az+az))*rtod;///
  //kalmanX.setAngle(roll);
  //kalmanY.setAngle(pitch);
  //gyYangle = pitch;

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.getAccelOffsetX();
  mpu.getAccelOffsetY();
  mpu.getAccelOffsetZ();
  mpu.getGyroOffsetX();
  mpu.getGyroOffsetY();
  mpu.getGyroOffsetZ();
  mpu.setAccelOffsetX(740);
  mpu.setAccelOffsetY(2443);
  mpu.setAccelOffsetZ(1680);
  mpu.setGyroOffsetX(75);
  mpu.setGyroOffsetY(-49);
  mpu.setGyroOffsetZ(48);
}

//void bacaMpu(){
//  //mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
//  
//  float akselX = atan(ax/sqrt(pow(ay,2)+pow(az,2)))*rtod;
//  float akselY = atan(ax/sqrt(pow(ax,2)+pow(az,2)))*rtod;
//  float akselZ = atan(sqrt(sq(ay)+sq(ax))/az)*rtod;
//
//  float pitch = atan(-ax/sqrt(ay*ay+az*az))*rtod;///atan(-ax/sqrt(ay*ay+az*az))//atan2(-ax,az)
//  float roll = atan(ay/sqrt(ax*ax+az+az))*rtod;///
//
//  float gyRateX = gx/131.0;
//  float gyRateY = gy/131.0;
//  float gyRateZ = gz/131.0;
//
//  
//  float kalAngleY = kalmanY.getAngle(pitch, gyRateY, elapsedTime);
//  float kalAngleX = kalmanX.getAngle(roll, gyRateX, elapsedTime);
//
//  float gyX = gyX + gyRateX*elapsedTime;
//  float gyY = gyY + gyRateY*elapsedTime;
//  float gyZ = gyZ + gyRateZ*elapsedTime;
//
//  //float actRoll = (KA*akselRoll) + (KG+(actRoll+(gyX*dt)));
//  //float actPitch = (KA*akselPitch) + (KG*(actPitch+(gyY*rtod*dt)));
//  
//  //Pitch = kalAngleY;
//  Pitch = (0.96*akselY)+(0.04*gyY);
//}

void bacaMpu(){
  Vector normAccel = mpu.readNormalizeAccel();
  Vector normGyro = mpu.readNormalizeGyro();
  float ax,ay,az,gx,gy,gz;
  ax = normAccel.XAxis;
  ay = normAccel.YAxis;
  az = normAccel.ZAxis;

  gx = normGyro.XAxis;
  gy = normGyro.YAxis;
  gz = normGyro.ZAxis;

  float gyRX = gx/131.0;
  float gyRY = gy/131.0;
  float gyRZ = gz/131.0;
  float pitch = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;
  float kalAngleY = kalmanY.getAngle(pitch, gyRX, elapsedTime);
  // Calculate Pitch & Roll
  //int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  //Pitch = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;//roll
  Pitch = kalAngleY;
}
