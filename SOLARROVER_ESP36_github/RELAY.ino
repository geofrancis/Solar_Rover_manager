

/*
--#define Relay1 32;
#define Relay2 33;
#define Relay3 25;
#define Relay4 26;
#define Relay5 27;
#define Relay6 14;
#define Relay7 12;
#define Relay8 13;
*/
void setRELAY() {

  if (MAINPOWER == 20) {
    mcp.digitalWrite(5, HIGH);
    // telnet.println("48v stepdown on");
  }
  if (MAINPOWER == 10) {
    mcp.digitalWrite(5, LOW);
    // telnet.println("48v stepdown off");
  }


  if (AUXPOWER == 20) {
    digitalWrite(4, 1);
    // telnet.println("12v FC ON");
  }
  if (AUXPOWER == 10) {
    digitalWrite(4, 0);
    // telnet.println("12v FC OFF");
  }


  if (FCPOWER == 20) {
    digitalWrite(17, 1);
    //telnet.println("12v FC ON");

    if (MOTPOWER == 20) {
      mcp.digitalWrite(4, HIGH);
      //    telnet.println("MOTPOWER ON");
    }
  }

  if (MOTPOWER == 10) {
    mcp.digitalWrite(4, LOW);
    //     telnet.println("MOTPOWER OFF");
    delay(3000);
    if (FCPOWER == 10) {
      digitalWrite(17, 0);
      //  telnet.println("12v FC OFF");
    }
  }



  if (LIDAR == 10) {
    digitalWrite(12, 0);
    //   telnet.println("Lidar OFF");
  }

  if (LIDAR == 20) {
    digitalWrite(12, 1);
    //  telnet.println("Lidar ON");
  }


  if (RADAR == 10) {
    digitalWrite(14, 0);
    //  telnet.println("RADAR OFF");
  }

  if (RADAR == 20) {
    digitalWrite(14, 1);
    //   telnet.println("RADAR ON");
  }



  if (WIFICAM == 10) {
    digitalWrite(13, 0);
    //   telnet.println("Camera OFF");
  }
  if (WIFICAM == 20) {
    digitalWrite(13, 1);
    //   telnet.println("Camera ON");
  }



  if (LIGHTS == 10) {
    mcp.digitalWrite(0, LOW);
    mcp.digitalWrite(1, LOW);
    //   telnet.println("LIGHTS OFF");
  }
  if (LIGHTS == 20) {
    mcp.digitalWrite(0, HIGH);
    mcp.digitalWrite(1, LOW);
    //    telnet.println("LOW ON");
  }
  if (LIGHTS == 30) {
    mcp.digitalWrite(0, HIGH);
    mcp.digitalWrite(1, HIGH);
    //     telnet.println("HIGH + LOW ON");
  }
  if (LIGHTS == 40) {
    mcp.digitalWrite(0, LOW);
    mcp.digitalWrite(1, HIGH);
    //  telnet.println("HIGH ON");
  }




  if (INDICATOR == 10) {
    mcp.digitalWrite(3, LOW);
    mcp.digitalWrite(2, LOW);
    //    telnet.println("INDICATOR OFF");
  }
  if (INDICATOR == 20) {
    mcp.digitalWrite(3, LOW);
    mcp.digitalWrite(2, HIGH);
    //    telnet.println("INDICATOR left");
  }
  if (INDICATOR == 30) {
    mcp.digitalWrite(3, HIGH);
    mcp.digitalWrite(2, LOW);
    //    telnet.println("INDICATOR RIGHT");
  }
  if (INDICATOR == 40) {
    mcp.digitalWrite(3, HIGH);
    mcp.digitalWrite(2, HIGH);
    //   telnet.println("INDICATOR HAZARD");
  }



  if (SENSORR == 20) {
    digitalWrite(27, 1);
    //     telnet.println("MOTPOWER OFF");
  }
  if (SENSORR == 10) {
    digitalWrite(27, 0);
    //    telnet.println("MOTPOWER ON");
  }



  if (HORN == 20) {
    digitalWrite(14, 1);
    //     telnet.println("MOTPOWER OFF");
  }
  if (HORN == 10) {
    digitalWrite(14, 0);
    //    telnet.println("MOTPOWER ON");
  }





  // telnet.println("           ");
  // telnet.println("           ");
  // telnet.println("           ");
  // telnet.println("           ");
  telnet.println("           ");
}
