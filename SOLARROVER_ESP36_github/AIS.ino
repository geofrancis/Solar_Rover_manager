

 
void ais() {
  Serial.println("AIS");
  AIS ais_msg(aismsg);

  unsigned long mmsi = ais_msg.get_mmsi();
  Serial.print("Returned MMSI: ");
  Serial.print(mmsi);
  Serial.print(" (");
  Serial.print(mmsi, 16);
  Serial.print(" )");
  Serial.println("");


  unsigned int SOG = ais_msg.get_SOG();
  Serial.print("Returned SOG: ");
  Serial.print((SOG) / 10);
  Serial.print(".");
  Serial.print((SOG) % 10);
  Serial.println(" nm");

  unsigned int COG = ais_msg.get_COG();
  Serial.print("Returned COG: ");
  Serial.print((COG) / 10);
  Serial.print(".");
  Serial.print((COG) % 10);
  Serial.println(" degrees");

  long LAT = ais_msg.get_latitude();
  Serial.print("Returned LAT: ");
  printDegrees(LAT);
  Serial.println(" degrees");

  long LONG = ais_msg.get_longitude();
  Serial.print("Returned LONG: ");
  printDegrees(LONG);
  Serial.println(" degrees");
}


void printDegrees(long min4) {
  //    Serial.print(min4); Serial.print(" (");Serial.print(min4,16);Serial.println(")");
  long intPart = min4 / 60L;
  long fracPart = intPart % 10000L;
  if (fracPart < 0)
    fracPart = -fracPart;
  char frac[6];
  sprintf(frac, "%04ld", fracPart);
  Serial.print(intPart / 10000L);
  Serial.print(".");
  Serial.print(frac);
}
