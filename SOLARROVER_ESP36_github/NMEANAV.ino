void gps_nav() {
  telnet.println();

if (NAVIMODE == 20){
NAVLAT = nemalat, 
NAVLON = nemalon;
sendNMEALONWP();
sendNMEALATWP();
confirmnavchange();
Serial.println("GPS................................................................................................................. 	HOLD");
}

if (NAVIMODE == 40){
NAVLAT = 55.640328;
NAVLON = -4.797045;
sendNMEALONWP();
sendNMEALATWP();
confirmnavchange();
Serial.println("GPS................................................................................................................. 	HOME");
}


  if (gps.location.isValid()) {




    WPdistance = TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), NAVLAT, NAVLON);
    WPcourse = TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), NAVLAT, NAVLON);


    float error = WPcourse - nmeacourse;
    //normalize so that error is between -180 and 180
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    //set course
    WPerror = error;
    Steering = (Kp * error);

    WPyaw = map(WPerror, -180, 180, 0, 255);
    float WPsetcourse = map(WPcourse, -180, 180, 0, 255);
    Setpoint = WPsetcourse;
    Input = WPyaw;
    telnet.print(" wpyaw");
    telnet.println(WPyaw);

    telnet.print(" WPsetcourse");
    telnet.println(WPsetcourse);
    double gap = abs(Setpoint - Input);  //distance away from setpoint
    if (gap < 10) {                      //we're close to setpoint, use conservative tuning parameters
      myPID.SetTunings(consKp, consKi, consKd);
    } else {
      //we're far from setpoint, use aggressive tuning parameters
      myPID.SetTunings(aggKp, aggKi, aggKd);
    }

    myPID.Compute();
    PIDyaw = map(Output, 0, 255, 1000, 2000);
    telnet.print(" rudder");
    telnet.println(PIDyaw);


    telnet.print("LONDON     Distance=");
    telnet.print(WPdistance / 1000, 6);
    telnet.print(" km Course-to=");
    telnet.print(WPcourse, 6);
    telnet.print(" degrees [");
    telnet.print(TinyGPSPlus::cardinal(WPcourse));
    telnet.print("]");
  }
}
