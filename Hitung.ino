void bearing(){
    float Lat1 = Lat*dtor;
    float Lon1 = Lon*dtor;
    float mLat1 = mLat*dtor;
    float mLon1 = mLon*dtor;
    
    dLon = mLon1 - Lon1;
    y = sin(dLon)*cos(mLat1);
    x = cos(Lat1)*sin(mLat1)-sin(Lat1)*cos(mLat1)*cos(dLon);
    bearingRad = atan2(y, x);
    bearingDeg = bearingRad*rtod;
    trackBear = ((int)bearingDeg+360)%360;

    if(bearingDeg<0) bearingDeg += 360;
    //if(bearingDeg>360) bearingDeg -= 360;
}

void haversine(){
    x1 = (mLat - Lat)*dtor;
    yI = (mLon - Lon)*dtor;

    a = sin(x1/2)*sin(x1/2)+cos(Lat*dtor)*cos(mLat*dtor)*sin(yI/2)*sin(yI/2);
    c = 2*asin(sqrt(a));
    d = R*c;//Nilai jarak/Haversine

    //Trigonometri
    ting = altM - alt;
    trigonometri = atan(ting/d);
    spPitch =trigonometri*rtod;

    //if(spPitch>60) spPitch = 60;    
    
}
