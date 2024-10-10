

void GPS() {

  Serial.println("GPS");

  nemalat = gps.location.lat();
  nemalon = gps.location.lng();
  nmeaspeed = gps.speed.mph();
  nmeacourse = gps.course.deg();
  nmeasats = gps.satellites.value();
  hdop = (gps.hdop.value() / 100);

  if (gps.location.isUpdated()) {
    //telnet.print("LOCATION   Fix Age=");
  //  telnet.print(gps.location.age());
   // telnet.print(" Lat=");
   // telnet.print(gps.location.lat());
   /// telnet.print(" Long=");
   // telnet.println(gps.location.lng());
    MAVLINK_GPS();
  }

  else if (gps.hdop.isUpdated()) {
  //  telnet.print(" hdop=");
   // telnet.println(gps.hdop.hdop());
  }

    

  //telnet.print("DIAGS      Chars=");
  //telnet.print(gps.charsProcessed());
  // telnet.print(" Sentences-with-Fix=");
  // telnet.print(gps.sentencesWithFix());
  // telnet.print(" Failed-checksum=");
  ////  telnet.print(gps.failedChecksum());
  // telnet.print(" Passed-checksum=");
  // telnet.print(gps.passedChecksum());

  if (gps.charsProcessed() < 10)
    telnet.print("WARNING: No GPS data.  Check wiring.");

  last = millis();
}
