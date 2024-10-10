
void loop() {
  //Serial.println("loop1");
  ArduinoOTA.handle();
  telnet.loop();
  FetchMavlink();
  NMEA_IN();




  unsigned long currentMillis4 = millis();
  if (currentMillis4 - previousMillis4 >= GPSinterval) {
    previousMillis4 = currentMillis4;
    //MAVLINK_GPS();
    //Serial.println("MAVGPS");
  }


  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.println("loop2");

    sensors();
    MAVLINK_HB();
    Fetchdomoticz1();
    senddomoticz1();
    setMODE();
    setRELAY();
    arming();
    talkieselect();
    gps_nav();
    getHeading();
  }

  unsigned long currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis2;
    Serial.println("loop3");

    Fetchdomoticz2();
    senddomoticz2();
    wificheck();
  }


  unsigned long currentMillistosleep = millis();
  if (currentMillistosleep - sleeppreviousMillis >= sleepinterval) {
    sleeppreviousMillis = currentMillistosleep;
    Serial.println("loop4");
    FCHBC();
    sleepcheck();
  }

  //per minute
  unsigned long currentMillis3 = millis();
  if (currentMillis3 - previousMillis3 > LOG_PERIOD) {
    previousMillis3 = currentMillis3;
    Serial.println("loop51");
    PINGSERVER();
    Serial.println("loop52");
    RADS();
    Serial.println("loop53");
    Calculate_Sun_Position(current_hour.toInt(), current_minute.toInt(), 0, current_day.toInt(), current_month.toInt(), current_year.toInt());
    Serial.println("loop54");
    Calculate_Moon_Position();
  }
}
