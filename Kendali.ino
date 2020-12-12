float cariError(){
  spYaw = bearingDeg;
  float errorYaw = spYaw-sudutHeading;
  if(errorYaw>180) errorYaw-=360;
  if(errorYaw<-180) errorYaw+=360;
    return errorYaw;
}

void kendaliAzimuth(float kpYaw, float kiYaw, float kdYaw){//50Hz

    const float yawMax = 125;
    error = cariError();
    if(error>-1 && error<1) error=0;
    pYaw = kpYaw * error;
    if(-5<error<5){
      iYaw = iYaw+(kiYaw*lastErrorYaw)*elapsedTime;
      if(iYaw>yawMax) iYaw = yawMax;
      else if(iYaw<-yawMax) iYaw = -yawMax;
    }
    //if(pwmYaw==servoYawMin)iYaw = -iYaw;
    dYaw = kdYaw*(error-lastErrorYaw)/elapsedTime;
    lastErrorYaw = error;
    
    pidYaw = pYaw+iYaw+dYaw;
    if(pidYaw>125) pidYaw = 125;//125
    if(pidYaw<-125) pidYaw = -125;//125
    pwmYaw = pwmYawBase + (int) pidYaw;
}

void kendaliElevasi(float kpPitch, float kiPitch, float kdPitch){//50Hz
  errorPitch = spPitch - Pitch;
  const float pitchMax = 250;
//  if(spPitch<50){//tuning bawah
//    kpPitch = 12;
//    kiPitch = 55;
//    kdPitch = 0.5;
//  }
  if(errorPitch>-1 && errorPitch<1) errorPitch=0;
  pPitch = kpPitch * errorPitch;
  
  iPitch = iPitch+(kiPitch*lastErrorPitch)*elapsedTime;
  if(iPitch>pitchMax) iPitch = pitchMax;
  else if(iPitch<-pitchMax) iPitch = -pitchMax;
      
  dPitch = kdPitch*(errorPitch-lastErrorPitch)/elapsedTime;
  lastErrorPitch = errorPitch;
  pidPitch = pPitch+iPitch+dPitch;
  if(pidPitch > 300) pidPitch=300;
  if(pidPitch < -300) pidPitch=-300;
  pwmPitch = 1700 -((int)(pidPitch));
  //pos = map(elev, 1960, 1000,0,90);  
}

void kendaliElevasi1(){//30Hz
  kpPitch = 8;
  kiPitch = 35;
  kdPitch = 0.80817;

  errorPitch = spPitch - Pitch;
  /*if(spPitch<50){//tuning bawah
    kpPitch = 12;
    kiPitch = 55;
    kdPitch = 0.5;
  }*/
  if(errorPitch>-1 && errorPitch<1) errorPitch=0;
  pPitch = kpPitch * errorPitch;
  iPitch = iPitch+(kiPitch*lastErrorPitch)*dt;
  dPitch = kdPitch*(errorPitch-lastErrorPitch)/dt;
  lastErrorPitch = errorPitch;
  pidPitch = pPitch+iPitch+dPitch;
  if(pidPitch > 250) pidPitch=250;
  if(pidPitch < -250) pidPitch=-250;
  pwmPitch = 1850 -((int)(pidPitch));
  //pos = map(elev, 1960, 1000,0,90);  
}


void kendaliAzimuth1(){//30hz
    kpYaw = 2;
    kiYaw = 2;
    kdYaw = 0.08;
    const float yawMax = 125;
    error = cariError();
    if(error>-1 && error<1) error=0;
    pYaw = kpYaw * error;
    if(-5<error<5){
      iYaw = iYaw+(kiYaw*lastErrorYaw)*dt;
      if(iYaw>yawMax) iYaw = yawMax;
      else if(iYaw<-yawMax) iYaw = -yawMax;
    }
    //if(pwmYaw==servoYawMin)iYaw = -iYaw;
    dYaw = kdYaw*(error-lastErrorYaw)/dt;
    lastErrorYaw = error;
    
    pidYaw = pYaw+iYaw+dYaw;
    if(pidYaw>125) pidYaw = 125;
    if(pidYaw<-125) pidYaw = -125;
    pwmYaw = pwmYawBase + (int) pidYaw;
}
