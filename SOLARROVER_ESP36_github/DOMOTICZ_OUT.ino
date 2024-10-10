void senddomoticz1() {



  if (SLEEPMODE == 40) {

    sendRADAR1();
    sendRADAR2();
    sendRADAR3();
    sendRADAR4();

    send_Main_Batt();
    send_batt1();
    send_batt2();

    PING();
  }



  if (SLEEPMODE == 30) {

    sendBOOT();
    sendRADAR1();
    sendRADAR2();
    sendRADAR3();
    sendRADAR4();
  }



  if (SLEEPMODE <= 20) {

    sendRADAR1();
    sendRADAR2();
    sendRADAR3();
    sendRADAR4();

    MAG_HEADING();
    sendNMEALAT();
    sendNMEALON();
    sendNMEASPEED();
    sendNMEACOURSE();
    WPSteering();
    sendNMEAWPDISTANCE();
    if (FCHB > 1) {
      sendflightmode();
      sendSPD();
      sendPITCH();
      sendROLL();
      sendYAW();

      confirmspeedchange();
      modeselect();
    }
  }



  if (SLEEPMODE == 10) {



    MAG_HEADING();
    sendNMEALAT();
    sendNMEALON();
    sendNMEASPEED();
    sendNMEACOURSE();
    sendNMEAWPDISTANCE();

    if (FCHB > 1) {
      sendflightmode();
      confirmspeedchange();
      modeselect();
    }
  }
}

void senddomoticz2() {

  if (SLEEPMODE == 40) {
  }


  if (SLEEPMODE == 30) {
    MAG_HEADING();
    sendNMEALAT();
    sendNMEALON();
    sendNMEASPEED();
    sendNMEACOURSE();
    sendNMEASATS();
    sendNMEAHDOP();
    WPSteering();
    sendNMEAWPCOURSE();
    sendNMEAWPDISTANCE();
    send_Main_Batt();
    send_batt1();
    send_batt2();

    sendSUNELE();
    sendSUNAZI();
    sendMOONP();
    sendMOONS();
    sendRAD();

    PING();
  }

  if (SLEEPMODE < 20) {
    MAG_HEADING();
    sendNMEALAT();
    sendNMEALON();
    sendNMEASPEED();
    sendNMEACOURSE();
    sendNMEASATS();
    sendNMEAHDOP();
    sendNMEAWPCOURSE();
    sendNMEAWPDISTANCE();
    PING();
    sendSUNELE();
    sendSUNAZI();
    sendMOONP();
    sendMOONS();
    sendRAD();

    send_Main_Batt();
    send_batt1();
    send_batt2();


    if (FCHB > 1) {
      sendSATS();
      sendHDOP();
      sendvoltage();
      sendcurrent();

      sendSPD();
      sendWP();
      sendGPSLAT();
      sendGPSLON();
      sendSATS();
      sendHDOP();
      sendvoltage();
      sendcurrent();

      NAVBEARING();
      WPDIST();
      XTRACKERROR();
      sendmsg();
      WP_COURSE();
      WP_DISTANCE();
      WP_ERROR();

      sendWP();
      sendGPSLAT();
      sendGPSLON();
    }
  }
}





void domoticzoutconnect() {

  if (client.connect(domoticz_server, port)) {
    client.print("GET /json.htm?type=command&param=udevice&idx=");
  }
}


void domoticzoutauthenticate() {
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.print(domoticz_server);
  client.print(":");
  client.println(port);
  client.println("Authorization: Basic cm99999999999999999==");
  client.println("User-Agent: Arduino-ethernet");
  client.println("Connection: close");
  client.println();
  client.stop();
}



void sendRADAR1() {
  //LEFT
  domoticzoutconnect();
  client.print(438);
  client.print("&nvalue=0&svalue=");
  if (RAD2 == 0) { client.print(10); }
  if (RAD2 == 1) { client.print(20); }
  domoticzoutauthenticate();
}


void sendRADAR2() {
  //FRONT
  domoticzoutconnect();
  client.print(341);
  client.print("&nvalue=0&svalue=");
  if (RAD3 == 0) { client.print(10); }
  if (RAD3 == 1) { client.print(20); }
  domoticzoutauthenticate();
}


void sendRADAR3() {
  //RIGHT
  domoticzoutconnect();
  client.print(338);
  client.print("&nvalue=0&svalue=");
  if (RAD1 == 0) { client.print(10); }
  if (RAD1 == 1) { client.print(20); }
  domoticzoutauthenticate();
}



void sendRADAR4() {
  //omni
  domoticzoutconnect();
  if (RAD1 == 0) { client.print(10); }
  if (RAD1 == 1) { client.print(20); }
  domoticzoutauthenticate();
}



void sendvoltage() {

  domoticzoutconnect();
  client.print(407);
  client.print("&nvalue=0&svalue=");
  client.print(VOLTS / 1000);
  domoticzoutauthenticate();
}



void sendcurrent() {

  domoticzoutconnect();
  client.print(431);
  client.print("&nvalue=0&svalue=");
  client.print(AMPS / 100);
  domoticzoutauthenticate();
}


void sendGPSLAT() {

  domoticzoutconnect();
  client.print(429);
  client.print("&nvalue=0&svalue=");
  client.print(GPSLAT, 7);
  domoticzoutauthenticate();
}


void sendGPSLON() {

  domoticzoutconnect();
  client.print(430);
  client.print("&nvalue=0&svalue=");
  client.print(GPSLON, 7);
  domoticzoutauthenticate();
}


void sendPITCH() {

  domoticzoutconnect();
  client.print(402);
  client.print("&nvalue=0&svalue=");
  client.print(pitch, 3);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.print(domoticz_server);
  domoticzoutauthenticate();
}



void sendROLL() {

  domoticzoutconnect();
  client.print(400);
  client.print("&nvalue=0&svalue=");
  client.print(roll, 3);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.print(domoticz_server);
  domoticzoutauthenticate();
}

void sendYAW() {

  domoticzoutconnect();
  client.print("&nvalue=0&svalue=");
  client.print(yaw, 3);
  domoticzoutauthenticate();
}

void sendSATS() {

  domoticzoutconnect();
  client.print(408);
  client.print("&nvalue=0&svalue=");
  client.print(satelites, 0);
  domoticzoutauthenticate();
}

void sendHDOP() {

  domoticzoutconnect();
  client.print(406);
  client.print("&nvalue=0&svalue=");
  client.print(HDOP, 0);
  domoticzoutauthenticate();
}

void sendSPD() {

  domoticzoutconnect();
  client.print(404);
  client.print("&nvalue=0&svalue=");
  client.print(gps_Vel, 0);
  domoticzoutauthenticate();
}


void sendWP() {

  domoticzoutconnect();
  client.print(399);
  client.print("&nvalue=0&svalue=");
  client.print(wp_number, 0);
  domoticzoutauthenticate();
}


void send_Main_Batt() {

  domoticzoutconnect();
  client.print(409);
  client.print("&nvalue=0&svalue=");
  client.print((MAINBATT / 10));
  domoticzoutauthenticate();
}

void send_batt1() {

  domoticzoutconnect();
  client.print(410);
  client.print("&nvalue=0&svalue=");
  client.print((BATT1 / 100));
  domoticzoutauthenticate();
}


void send_batt2() {

  domoticzoutconnect();
  client.print(405);
  client.print("&nvalue=0&svalue=");
  client.print((BATT2 / 100));
  domoticzoutauthenticate();
}


void modeselect() {

  if (RCIN <= 1000) { MODE = 0; }
  if (RCIN > 1001 && RCIN < 1100) { MODE = 10; }
  if (RCIN > 1101 && RCIN < 1200) { MODE = 20; }
  if (RCIN > 1201 && RCIN < 1300) { MODE = 30; }
  if (RCIN > 1301 && RCIN < 1400) { MODE = 40; }
  if (RCIN > 1401 && RCIN < 1500) { MODE = 50; }
  if (RCIN > 1501 && RCIN < 1600) { MODE = 60; }
  if (RCIN > 1601 && RCIN < 1700) { MODE = 70; }
  if (RCIN > 1701 && RCIN < 1800) { MODE = 80; }
  if (RCIN > 1801 && RCIN < 1900) { MODE = 90; }
  if (RCIN > 1901 && RCIN < 2000) {
    MODE = 100;
  } else if (RCIN >= 2000) {
    MODE = 110;
  }


  domoticzoutconnect();
  client.print(433);
  client.print("&nvalue=0&svalue=");


  if (fcmodein == 0) { client.print("Manual"); }
  if (fcmodein == 1) { client.print("Acro"); }
  if (fcmodein == 3) { client.print("Steering"); }
  if (fcmodein == 4) { client.print("Hold"); }
  if (fcmodein == 5) { client.print("Loiter"); }
  if (fcmodein == 6) { client.print("follow"); }
  if (fcmodein == 7) { client.print("Simple"); }
  if (fcmodein == 9) { client.print("Circle"); }
  if (fcmodein == 10) { client.print("Auto"); }
  if (fcmodein == 11) { client.print("RTL"); }
  if (fcmodein == 12) { client.print("SmartRTL"); }
  if (fcmodein == 15) { client.print("Guided"); }

  domoticzoutauthenticate();
}



void send_text() {
  domoticzoutconnect();
  client.print(366);
  client.print("&nvalue=0&svalue=");
  client.print(message);
  domoticzoutauthenticate();
}



void sendSUNELE() {

  domoticzoutconnect();
  client.print(456);
  client.print("&nvalue=0&svalue=");
  client.print(elevation);
  domoticzoutauthenticate();
}



void sendSUNAZI() {

  domoticzoutconnect();
  client.print(455);
  client.print("&nvalue=0&svalue=");
  client.print(azimuth);
  domoticzoutauthenticate();
}




void sendMOONP() {

  domoticzoutconnect();
  client.print(457);
  client.print("&nvalue=0&svalue=");
  client.print(moon.angle);
  domoticzoutauthenticate();
}



void sendMOONS() {

  domoticzoutconnect();
  client.print(458);
  client.print("&nvalue=0&svalue=");
  client.print(moon.percentLit * 100);
  domoticzoutauthenticate();
}




void sendRAD() {

  domoticzoutconnect();
  client.print(460);
  client.print("&nvalue=0&svalue=");
  client.print(CPM);
  domoticzoutauthenticate();
}






void NAVBEARING() {

  domoticzoutconnect();
  client.print(405);
  client.print("&nvalue=0&svalue=");
  client.print(navbearing);
  domoticzoutauthenticate();
}




void WPDIST() {

  domoticzoutconnect();
  client.print(398);
  client.print("&nvalue=0&svalue=");
  client.print(wpdist);
  domoticzoutauthenticate();
}




void XTRACKERROR() {

  domoticzoutconnect();
  client.print(411);
  client.print("&nvalue=0&svalue=");
  client.print(xtrackerror);
  domoticzoutauthenticate();
}




void sendNMEALAT() {

  domoticzoutconnect();
  client.print(461);
  client.print("&nvalue=0&svalue=");
  client.print(nemalat, 7);
  domoticzoutauthenticate();
}





void sendNMEALONWP() {

  domoticzoutconnect();
  client.print(477);
  client.print("&nvalue=0&svalue=");
  client.print(nemalon, 7);
  domoticzoutauthenticate();
}



void sendNMEALATWP() {

  domoticzoutconnect();
  client.print(476);
  client.print("&nvalue=0&svalue=");
  client.print(nemalat, 7);
  domoticzoutauthenticate();
}





void sendNMEALON() {

  domoticzoutconnect();
  client.print(462);
  client.print("&nvalue=0&svalue=");
  client.print(nemalon, 7);
  domoticzoutauthenticate();
}





void sendNMEASPEED() {

  domoticzoutconnect();
  client.print(463);
  client.print("&nvalue=0&svalue=");
  client.print(nmeaspeed);
  domoticzoutauthenticate();
}



void sendNMEACOURSE() {

  domoticzoutconnect();
  client.print(464);
  client.print("&nvalue=0&svalue=");
  client.print(nmeacourse);
  domoticzoutauthenticate();
}

void sendNMEAWPCOURSE() {

  domoticzoutconnect();
  client.print(475);
  client.print("&nvalue=0&svalue=");
  client.print(WPcourse);
  domoticzoutauthenticate();
}

void sendNMEAWPDISTANCE() {

  domoticzoutconnect();
  client.print(478);
  client.print("&nvalue=0&svalue=");
  client.print(WPdistance);
  domoticzoutauthenticate();
}


void sendNMEASATS() {

  domoticzoutconnect();
  client.print(465);
  client.print("&nvalue=0&svalue=");
  client.print(nmeasats);
  domoticzoutauthenticate();
}




void sendNMEAHDOP() {

  domoticzoutconnect();
  client.print(392);
  client.print("&nvalue=0&svalue=");
  client.print(hdop);
  domoticzoutauthenticate();
}





void sendmsg() {

  domoticzoutconnect();
  client.print(366);
  client.print("&nvalue=0&svalue=");
  client.print(message);
  domoticzoutauthenticate();
}




void sendBOOT() {

  domoticzoutconnect();
  client.print(440);
  client.print("&nvalue=0&svalue=");
  client.print(bootCount);
  domoticzoutauthenticate();
}


void WP_COURSE() {

  domoticzoutconnect();
  client.print(467);
  client.print("&nvalue=0&svalue=");
  client.print(WPcourse);
  domoticzoutauthenticate();
}



void WP_DISTANCE() {

  domoticzoutconnect();
  client.print(468);
  client.print("&nvalue=0&svalue=");
  client.print(WPdistance);
  domoticzoutauthenticate();
}




void WP_ERROR() {

  domoticzoutconnect();
  client.print(469);
  client.print("&nvalue=0&svalue=");
  client.print(WPerror);
  domoticzoutauthenticate();
}





void MAG_HEADING() {

  domoticzoutconnect();
  client.print(470);
  client.print("&nvalue=0&svalue=");
  client.print(heading);
  domoticzoutauthenticate();
}



void PING() {

  domoticzoutconnect();
  client.print(473);
  client.print("&nvalue=0&svalue=");
  client.print(Ping.averageTime());
  domoticzoutauthenticate();
}



void WPSteering() {

  domoticzoutconnect();
  client.print(474);
  client.print("&nvalue=0&svalue=");
  client.print(PIDyaw);
  domoticzoutauthenticate();
}

void confirmspeedchange() {

  domoticzoutconnect();
  client.print(367);
  client.print("&nvalue=0&svalue=");
  client.print(-2);
  domoticzoutauthenticate();
}

void confirmnavchange() {

  domoticzoutconnect();
  client.print(466);
  client.print("&nvalue=0&svalue=");
  client.print(0);
  domoticzoutauthenticate();
}