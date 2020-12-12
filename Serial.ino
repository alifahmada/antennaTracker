void parseAscii(){
  String data, dataLat, dataLon, dataLat1, dataLon1, dataAlt, dataTemp, dataHum, dataBear, dataV, dataPress;
  String d;
  int data0, data1, data2, data3, data4, data5, data6, data7, data8, data9, data10;
  while(terima.available()>0){
    d = terima.readStringUntil('\n');
    data += d;
  }
  if(data.length()>0){
    //format data -> $latitude,longitude,altitude
    data0 = data.indexOf('<');
    data1 = data.indexOf(',',data0+1);
    data2 = data.indexOf(',',data1+1);
    data3 = data.indexOf(',',data2+1);
    data4 = data.indexOf(',',data3+1);
    data5 = data.indexOf(',',data4+1);
    data6 = data.indexOf(',',data5+1);
    data7 = data.indexOf(',',data6+1);
    data8 = data.indexOf(',',data7+1);
    data9 = data.indexOf(',',data8+1);
    data10 = data.indexOf(',',data9+1);

    dataAlt = data.substring(data0+1, data1);
    dataTemp = data.substring(data1+1, data2);
    dataHum = data.substring(data2+1, data3);
    dataPress = data.substring(data3+1, data4);
    dataBear = data.substring(data4+1, data5);
    dataV = data.substring(data5+1, data6);
    dataLat = data.substring(data6+1, data7);
    dataLon = data.substring(data7+1, data8);
    dataLat1 = data.substring(data8+1, data9);
    dataLon1 = data.substring(data9+1, data10);

    altM = dataAlt.toFloat();
    suhu = dataTemp.toFloat();
    lembab = dataHum.toFloat();
    tekanan = dataPress.toFloat();
    compassBear = dataBear.toFloat();
    vGps = dataV.toFloat();
    mLat = dataLat.toFloat();
    mLon = dataLon.toFloat();
    mLat1 = dataLat1.toFloat();
    mLon1 = dataLon1.toFloat();

    data="";
  }
}

void bacaSerial(){
  baca();
  if(dataBaru==true){
    strcpy(tempChar, dataTerima);
  parseData();
  //tampilSerial();
  dataBaru= false;
  } 
}

void baca(){
  static bool terimaData = false;
  static byte ndx;
  char header = '<';
  char endline = '>';
  char c;

  while(terima.available() > 0 && dataBaru == false){
    c = terima.read();

    if(terimaData == true){
      if(c != endline){
        dataTerima[ndx] = c;
        ndx++;
        if(ndx >= dataByte){
          ndx = dataByte - 1;
        }
      }
      else{
        dataTerima[ndx] = '\0';
        terimaData = false;
        ndx = 0;
        dataBaru = true;
      }
    }
    else if(c == header){
      terimaData = true;
    }
  }
}

void parseData(){
  char * strtokIndx;

  strtokIndx = strtok(tempChar,",");
  strcpy(dataPayload, strtokIndx);

  strtokIndx = strtok(NULL, ",");
  altM = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  suhu = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  lembab = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  tekanan = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  compassBear = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  vGps = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  mLat = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  mLon = atof(strtokIndx);

//  strtokIndx = strtok(NULL, ",");
//  mLat1 = atof(strtokIndx);
//
//  strtokIndx = strtok(NULL, ",");
//  mLon1 = atof(strtokIndx);
}
