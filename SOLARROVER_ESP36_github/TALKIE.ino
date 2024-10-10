

void talkieselect() {
  if (WARNING == 10) {
    talkietime();
    confirmmtalkie();
  }

  if (WARNING == 20) {
    talkieweather();
    confirmmtalkie();
  }

  if (WARNING == 30) {
    talkiedanger();
    confirmmtalkie();
  }

  if (WARNING == 40) {
    talkieradarcentre();
    confirmmtalkie();
  }


  if (WARNING == 50) {
    talkieradarleft();
    confirmmtalkie();
  }


  if (WARNING == 60) {
    talkieradarright();
    confirmmtalkie();
  }

  if (WARNING == 70) {
    talkieradaromni();
    confirmmtalkie();
  }

  if (WARNING == 80) {
    talkiepos();
    confirmmtalkie();
  }

  if (WARNING == 90) {
    talkieholdrain();
    confirmmtalkie();
  }

  if (WARNING == 100) {
    talkieholdcloud();
   
    confirmmtalkie();
  }

  if (WARNING == 110) {
     talkieholdcold();
   
    confirmmtalkie();
  }

  if (WARNING == 120) {
     talkieholdwind();
    confirmmtalkie();
  }

  if (WARNING == 130) {
    talkieholdnight();
    confirmmtalkie();
  }

}

void confirmmtalkie() {
  // Domoticz format /json.htm?type=command&param=udevice&idx=IDX&nvalue=0&svalue=VALUE

  if (client.connect(domoticz_server, port)) {

    client.print("GET /json.htm?type=command&param=udevice&idx=");
    client.print(452);
    client.print("&nvalue=0&svalue=");
    client.print(0);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    client.print(":");
    client.println(port);
    client.println("Authorization: Basic cm92ZXI6cGFzc3cwcmRlZA==");
    client.println("User-Agent: Arduino-ethernet");
    client.println("Connection: close");
    client.println();
    client.stop();
  }
}

void talkiearmed() {
  voice.say(sp5_ENGINE);
  voice.say(sp2_START);
}


void talkiedisarmed() {

  voice.say(sp5_ENGINE);
  voice.say(sp2_STOP);
}


void talkiesleep() {
  sayNumber(MAINBATT / 10);
  voice.say(sp2_VOLTS);
  talkieholdnight();

  voice.say(sp2_SHUT);
  voice.say(sp5_DOWN);
  voice.say(sp4_FOR);
  sayNumber(TIME_TO_SLEEP);
  voice.say(sp2_SECONDS);
}


void talkiemodechange() {

  if (fcmodein == 0) { voice.say(sp2_MANUAL); }
  if (fcmodein == 1) { voice.say(sp5_STABILISER); }
  if (fcmodein == 3) { voice.say(sp4_TURN); }
  if (fcmodein == 4) { voice.say(sp4_HOLD); }
  if (fcmodein == 5) { voice.say(sp2_POSITION); }
  if (fcmodein == 9) { voice.say(sp2_CIRCUIT); }
  if (fcmodein == 10) { voice.say(sp5_AUTOPILOT); }
  if (fcmodein == 11) { voice.say(sp5_INBOUND); }
  voice.say(sp2_SET);
}

void talkietime() {

  voice.say(spa_THE);
  voice.say(spa_TIME);
  voice.say(spa_IS);
  sayQNumber(&voice, rtc.getHour(true));
  sayQNumber(&voice, rtc.getMinute());
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);
}


void talkieweather() {



  voice.say(sp3_CURRENT);
  voice.say(sp3_WEATHER);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);


  voice.say(sp3_VISIBILITY);
  sayQFloat(&voice, visi, 1, true, false);
  voice.say(sp2_KILO);
  voice.say(sp2_METER);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);

  voice.say(sp3_OVERCAST);
  sayQNumber(&voice, cloud);
  voice.say(sp3_PERCENT);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);

  voice.say(sp5_AIRSPEED);
  sayQFloat(&voice, winds, 1, true, false);
  voice.say(sp2_METER);
  voice.say(sp3_PER);
  voice.say(sp2_SECONDS);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);

  voice.say(sp3_GUSTING_TO);
  sayQFloat(&voice, windg, 1, true, false);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);

  voice.say(sp2_TEMPERATURE);
  sayQFloat(&voice, TEMP, 1, true, false);
  voice.say(sp5_DEGREE);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);

  voice.say(sp3_WIND);
  sayQFloat(&voice, CHILL, 1, true, false);
  voice.say(sp5_DEGREE);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);

  voice.say(sp4_RAIN);
  voice.say(sp5_DOWN);
  sayQFloat(&voice, rain, 1, true, false);
  voice.say(sp2_METER);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);

  voice.say(sp3_CURRENT);
  voice.say(sp4_RAIN);
  sayQFloat(&voice, rain, 1, true, false);
  voice.say(sp2_METER);
  ;


  /*
  sayQNumber(&voice, DayLength);
voice.say(sp5_DOWN);
  voice.say(sp5_REFUELLING);
  voice.say(sp5_ABOVE);
*/


  //   voice.say(spONE_SMALL_STEP);
}




void talkiedanger() {
  voice.say(sp4_DANGER);
  voice.say(sp4_DANGER);
  voice.say(sp4_DANGER);
  voice.say(sp2_AUTOMATIC);
  voice.say(sp5_ENGINE);
  voice.say(sp2_START);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);
  voice.say(sp3_CLEAR);
  voice.say(sp4_THE);
  voice.say(sp2_AREA);
  voice.say(sp4_IMMEDIATELY);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);
  voice.say(sp2_REPEAT);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);
  voice.say(sp4_DANGER);
  voice.say(sp4_DANGER);
  voice.say(sp4_DANGER);
  voice.say(sp2_AUTOMATIC);
  voice.say(sp5_ENGINE);
  voice.say(sp2_START);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);
  voice.say(sp3_CLEAR);
  voice.say(sp4_THE);
  voice.say(sp2_AREA);
  voice.say(sp4_IMMEDIATELY);
}

void talkieradarleft() {

  voice.say(sp4_LEFT);
  voice.say(sp4_RADAR);
  voice.say(sp4_ALERT);
}
void talkieradarright() {

  voice.say(sp4_RIGHT);
  voice.say(sp4_RADAR);
  voice.say(sp4_ALERT);
}

void talkieradarcentre() {

  voice.say(sp4_FRONT);
  voice.say(sp4_RADAR);
  voice.say(sp4_ALERT);
}

void talkieradaromni() {

  voice.say(sp4_RADAR);
  voice.say(sp4_ALERT);
  voice.say(sp3_MOVING);
  voice.say(sp4_NEAR);
  voice.say(sp2_POSITION);
}


void talkieradarwake() {

  voice.say(sp4_SECURITY);
  voice.say(sp4_START);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);
  voice.say(sp4_RADAR);
  voice.say(sp4_ALERT);
  voice.say(spPAUSE1);
  voice.say(sp3_MOVING);
  voice.say(sp4_NEAR);
  voice.say(sp2_POSITION);
  voice.say(spPAUSE1);
  voice.say(spPAUSE1);
  talkiepos();
  
}


void talkiepos() {
  voice.say(sp3_CURRENT);
  voice.say(sp2_POSITION);

  sayQFloat(&voice, GPSLAT, 1, true, false);
  voice.say(sp3_NORTH);
  sayQFloat(&voice, GPSLON, 1, true, false);
  voice.say(sp3_EAST);
}

void talkierstartup() {
  voice.say(sp4_START);
  voice.say(sp4_SEQUENCE);
  voice.say(sp3_ONE);
}


void talkierstartuptime() {
  voice.say(sp4_START);
  voice.say(sp4_SEQUENCE);
  sayQNumber(&voice, bootCount);
}

void talkiewaypoint() {
  if (wp_numberold != wp_number) {
    voice.say(sp4_WAY);
    voice.say(sp3_POINT);
    sayQNumber(&voice, wp_number);
    voice.say(spPAUSE1);
    voice.say(spPAUSE1);

    voice.say(sp5_HEADING);
    sayQNumber(&voice, gps_Head);
    voice.say(sp3_DEGREES);
    voice.say(spPAUSE1);
    voice.say(spPAUSE1);

    voice.say(sp4_SPEED);
    sayQNumber(&voice, gps_Vel);

    voice.say(spPAUSE1);
    voice.say(spPAUSE1);

    wp_numberold = wp_number;
  }
}



void talkieholdrain() {

  voice.say(sp5_DEPARTURE);
  voice.say(sp4_ABORT);
  voice.say(sp4_RAIN);
}



void talkieholdcloud() {

  voice.say(sp5_DEPARTURE);
  voice.say(sp4_ABORT);
  voice.say(sp3_OVERCAST);
}


void talkieholdcold() {

  voice.say(sp5_DEPARTURE);
  voice.say(sp4_ABORT);
  voice.say(sp3_TEMPERATURE);
  voice.say(sp4_TOO_LOW);
}


void talkieholdwind() {
  voice.say(sp5_DEPARTURE);
  voice.say(sp4_ABORT);
  voice.say(sp3_HIGH);
  voice.say(sp3_WIND);
}


void talkieholdnight() {
  voice.say(sp5_DEPARTURE);
  voice.say(sp4_ABORT);
  voice.say(sp2_LIGHT);
  voice.say(sp4_TOO_LOW);
}



/* Say any number between -999,999 and 999,999 */
void sayNumber(long n) {
  if (n < 0) {
    voice.say(sp2_MINUS);
    sayNumber(-n);
  } else if (n == 0) {
    voice.say(sp2_ZERO);
  } else {
    if (n >= 1000) {
      int thousands = n / 1000;
      sayNumber(thousands);
      voice.say(sp2_THOUSAND);
      n %= 1000;
      if ((n > 0) && (n < 100))
        voice.say(sp2_AND);
    }
    if (n >= 100) {
      int hundreds = n / 100;
      sayNumber(hundreds);
      voice.say(sp2_HUNDRED);
      n %= 100;
      if (n > 0)
        voice.say(sp2_AND);
    }
    if (n > 19) {
      int tens = n / 10;
      switch (tens) {
        case 2:
          voice.say(sp2_TWENTY);
          break;
        case 3:
          voice.say(sp2_THIR_);
          voice.say(sp2_T);
          break;
        case 4:
          voice.say(sp2_FOUR);
          voice.say(sp2_T);
          break;
        case 5:
          voice.say(sp2_FIF_);
          voice.say(sp2_T);
          break;
        case 6:
          voice.say(sp2_SIX);
          voice.say(sp2_T);
          break;
        case 7:
          voice.say(sp2_SEVEN);
          voice.say(sp2_T);
          break;
        case 8:
          voice.say(sp2_EIGHT);
          voice.say(sp2_T);
          break;
        case 9:
          voice.say(sp2_NINE);
          voice.say(sp2_T);
          break;
      }
      n %= 10;
    }
    switch (n) {
      case 1:
        voice.say(sp2_ONE);
        break;
      case 2:
        voice.say(sp2_TWO);
        break;
      case 3:
        voice.say(sp2_THREE);
        break;
      case 4:
        voice.say(sp2_FOUR);
        break;
      case 5:
        voice.say(sp2_FIVE);
        break;
      case 6:
        voice.say(sp2_SIX);
        break;
      case 7:
        voice.say(sp2_SEVEN);
        break;
      case 8:
        voice.say(sp2_EIGHT);
        break;
      case 9:
        voice.say(sp2_NINE);
        break;
      case 10:
        voice.say(sp2_TEN);
        break;
      case 11:
        voice.say(sp2_ELEVEN);
        break;
      case 12:
        voice.say(sp2_TWELVE);
        break;
      case 13:
        voice.say(sp2_THIR_);
        voice.say(sp2__TEEN);
        break;
      case 14:
        voice.say(sp2_FOUR);
        voice.say(sp2__TEEN);
        break;
      case 15:
        voice.say(sp2_FIF_);
        voice.say(sp2__TEEN);
        break;
      case 16:
        voice.say(sp2_SIX);
        voice.say(sp2__TEEN);
        break;
      case 17:
        voice.say(sp2_SEVEN);
        voice.say(sp2__TEEN);
        break;
      case 18:
        voice.say(sp2_EIGHT);
        voice.say(sp2__TEEN);
        break;
      case 19:
        voice.say(sp2_NINE);
        voice.say(sp2__TEEN);
        break;
    }
  }
}



void PINGTALK() {
  // Ping Host
  const char* remote_host = "lunaticlabs.duckdns.org";
  telnet.print(remote_host);
  if (Ping.ping(remote_host) > 0) {
    telnet.printf(" response time : %d/%.2f/%d ms\n", Ping.minTime(), Ping.averageTime(), Ping.maxTime());
    voice.say(sp2_CONNECT);
    voice.say(sp4_AFFIRMATIVE);
    sayNumber(Ping.averageTime());
    voice.say(sp2_MILLI);
    voice.say(sp2_SECONDS);
  } else {
    telnet.println(" Ping Error !");
    voice.say(sp2_CONNECT);
    voice.say(sp4_NEGATIVE);
  }
}




void WARNINGS() {

  if (mode > 1) {
    telnet.println("mode change");

    if (mode == 10) { fcmode = 0; }
    if (mode == 20) { fcmode = 1; }
    if (mode == 30) { fcmode = 3; }
    if (mode == 40) { fcmode = 4; }
    if (mode == 50) { fcmode = 5; }
    if (mode == 60) { fcmode = 6; }
    if (mode == 70) { fcmode = 10; }
    if (mode == 80) { fcmode = 11; }
    if (mode == 90) { fcmode = 12; }
    if (mode == 100) { fcmode = 15; }

    telnet.print("MODE ");
    telnet.println(mode);
    // telnet.print("mode ");
    //   telnet.println(mode);
    telnet.print("fc mode ");
    telnet.println(fcmode);
    telnet.print("fc modein ");
    telnet.println(fcmodein);


    //Set message variables
    uint8_t _system_id = 255;    // id of computer which is sending the command (ground control software has id of 255)
    uint8_t _component_id = 1;   // seems like it can be any # except the number of what Pixhawk sys_id is
    uint8_t _target_system = 1;  // Id # of Pixhawk (should be 1)
    uint8_t _base_mode = 1;
    uint32_t _custom_mode = fcmode;  //10 = auto mode

    // Initialize the required buffers
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    // Pack the message
    mavlink_msg_set_mode_pack(_system_id, _component_id, &msg, _target_system, _base_mode, _custom_mode);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);  // Send the message (.write sends as bytes)

    Serial.write(buf, len);  //Write data to serial port
                             /*
*/
    if (fcmode == fcmodein) {
      //mode = 0;
      talkiemodechange();
      sendflightmode();
      confirmmodechange();
    }
  }
}
