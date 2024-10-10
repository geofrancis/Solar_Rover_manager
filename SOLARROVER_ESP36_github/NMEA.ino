void NMEA_IN() {


  if (Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read();
    // add it to the inputString:
    inputString += inChar;
    gps.encode(inChar);
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      char aismsg[] = "inputString";

      if (inputString.startsWith("$GPGGA")) {
        //Serial.println("GPS................................................................................................................. 	Time, position, and fix related data");
        GPS();
      }
      if (inputString.startsWith("$GPGLL")) {
       // Serial.println("GPS................................................................................................................. 	Position data: position fix, time of position fix, and status");
        GPS();
      }
      if (inputString.startsWith("$GPGSA")) {
      //  Serial.println("GPS................................................................................................................. 	GPS DOP and active satellites");
        GPS();
      }
      if (inputString.startsWith("$GPGSV")) {
       // Serial.println("GPS.................................................................................................................Number of SVs in view, PRN, elevation, azimuth, and SNR");
        GPS();
      }
      if (inputString.startsWith("$GPRMC")) {
       // Serial.println("GPS.................................................................................................................Time, date, position, course, speed data.");
        GPS();
      }
      if (inputString.startsWith("$GPVTG")) {
       // Serial.println("GPS.................................................................................................................Course, speed information relative to the ground.");
        GPS();
      }
      if (inputString.startsWith("$GPGAA")) {
       // Serial.println("GPS.................................................................................................................Time, position, and fix related data");
        GPS();
      }


      if (inputString.startsWith("!AB")) {
        Serial.println("AIS.................................................................................................................NMEA 4.0 Base AIS station");
        ais();
      }

      if (inputString.startsWith("!AD")) {
        Serial.println("AIS.................................................................................................................NMEA 4.0 Dependent AIS Base Station");
        ais();
      }

      if (inputString.startsWith("!AI")) {
        Serial.println("AIS.................................................................................................................Mobile AIS station");
        ais();
      }

      if (inputString.startsWith("!AN")) {
        Serial.println("AIS.................................................................................................................NMEA 4.0 Aid to Navigation AIS station");
        ais();
      }

      if (inputString.startsWith("!AR")) {
        Serial.println("AIS.................................................................................................................NMEA 4.0 AIS Receiving Station");
        ais();
      }

      if (inputString.startsWith("!AS")) {
        Serial.println("AIS.................................................................................................................NMEA 4.0 Limited Base Station");
        ais();
      }

      if (inputString.startsWith("!AT")) {
        Serial.println("AIS.................................................................................................................NMEA 4.0 AIS Transmitting Station");
        ais();
      }


      if (inputString.startsWith("!AX")) {
        Serial.println("AIS.................................................................................................................NMEA 4.0 Repeater AIS station");
        ais();
      }


      if (inputString.startsWith("!SA")) {
        Serial.println("AIS.................................................................................................................NMEA 4.0 Physical Shore AIS Station");
        ais();
      }



      if (stringComplete) {
        //  Serial.println(inputString);
        //clear the string:

        inputString = "";
        stringComplete = false;
      }
    }
  }
}