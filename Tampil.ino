void dataMuatan(){
    Serial.print("<DIPO");
    Serial.print(",");
    Serial.print(altM, 2);
    Serial.print(",");
    Serial.print(suhu, 1);
    Serial.print(",");
    Serial.print(lembab);
    Serial.print(",");
    Serial.print(tekanan);
    Serial.print(",");
    Serial.print(compassBear);
    Serial.print(",");
    Serial.print(vGps, 2);
    Serial.print(",");
    Serial.print(mLat,6);
    Serial.print(",");
    Serial.print(mLon,6);
    Serial.print(",");
    Serial.print(mLat1, 6);
    Serial.print(",");
    Serial.print(mLon1, 6);
    Serial.print(",");
    Serial.print(Lat,6);
    Serial.print(",");
    Serial.print(Lon,6);
    Serial.print(",");
    Serial.print("00");
    Serial.println();
}

void tampilanData(){
  Serial.print(alt);
  Serial.print("\t");
  Serial.print(sudutHeading);
  Serial.print("\t");
  Serial.print(trackBear);
  Serial.print("\t");
  Serial.print(Pitch);
  Serial.print("\t");
  Serial.print(spPitch);
  Serial.print("\t");
  Serial.print(Lat);
  Serial.print("\t");
  Serial.print(Lon);
  Serial.print("\t");
  Serial.print(pwmYaw);
  Serial.print("\t");
  Serial.print(pwmPitch);
  Serial.print("\t");
  Serial.println();
}
