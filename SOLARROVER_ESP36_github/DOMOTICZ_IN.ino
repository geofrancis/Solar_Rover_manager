
void Fetchdomoticz1() {

  POWERMODE();

  if (SLEEPMODE == 40) {


    mainpowerR();
    AUXpowerR();
    flightcontrollerR();
    NAVMODE();
  }

  if (SLEEPMODE == 30) {

    mainpowerR();
    AUXpowerR();
    flightcontrollerR();
    NAVMODE();
    talkie();
    cameraR();
  }


  if (SLEEPMODE < 20) {

    mainpowerR();
    AUXpowerR();
    flightcontrollerR();
    NAVMODE();
    talkie();
    cameraR();
    talkie();
  if (FCHB > 1) {
    motorpowerR();
    ARMING();
    lightsR();
    indicatorsR();
    flightmodein();
    SPEED();
  }
}
}


void Fetchdomoticz2() {

  if (SLEEPMODE == 40) {
  }

  if (SLEEPMODE == 30) {


    lidarR();
    radarR();
    SensorR();

    Rain();
    Visibility();
    Cloud();
    Wind();
    Sun();
  }

  if (SLEEPMODE == 20) {

    lidarR();
    radarR();
    SensorR();

    Rain();
    Visibility();
    Cloud();
    Wind();
    Sun();
  }

  if (SLEEPMODE == 10) {

    lidarR();
    radarR();
    SensorR();
  }
}



void DOMOTICZ_CONNECT() {
 
  client.setTimeout(10000);
  if (!client.connect("yourserver.yourdomain.org", 9000)) {
    //telnet.ptintln(F("Connection failed4"));
    return;
  }
  // Send HTTP request
     Serial.println("DM Get");

}


void DOMOTICZ_AUTHENTICATE() {

  client.println(F("Host: yourserver.yourdomain.org:9000"));
  client.println("Authorization: Basic cm9999999999999==");
  client.println(F("Connection: close"));
  if (client.println() == 0) {
    //telnet.ptintln(F("Failed to send request1"));
    client.stop();
    return;
  }

  char status[32] = { 0 };
  client.readBytesUntil('\r', status, sizeof(status));
  // It should be "HTTP/1.0 200 OK" or "HTTP/1.1 200 OK"
  if (strcmp(status + 9, "200 OK") != 0) {
    //telnet.ptint(F("Unexpected response1: "));
    //telnet.ptintln(status);
    client.stop();
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    //telnet.ptintln(F("Invalid response1"));
    client.stop();
    return;
  }

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    //telnet.ptint(F("deserializeJson() failed: 1"));
    //telnet.ptintln(error.f_str());
    client.stop();
    return;
    Serial.println("DC Get");
  }
}



void tide() {
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=452 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  WARNING = doc["result"][0]["Level"];
  //telnet.print("WARNING ");
  //telnet.println(WARNING);
  http.end();
}

void SPEED() {
  //LIDAR
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=367 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  int thr = doc["result"][0]["Level"];
  //char chars = doc["result"][0]["Level"];
  if (thr == 100) {
    dom_thr = -2;
  }
  if (thr < 100) {
    dom_thr = thr;
  }
  //if (chars == "Off") {
  // dom_thr = -1
  //}
  telnet.print(dom_thr);
  //telnet.print(chars);
  http.end();
}

void talkie() {

  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=452 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  WARNING = doc["result"][0]["Level"];
  telnet.print("WARNING ");
  telnet.println(WARNING);
  http.end();
}



void Sun() {
  //LIDAR
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=450 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  DAYLEGNTH = doc["DayLength"];
  SUNRISE = doc["Sunrise"];
  SUNSET = doc["Sunset"];
  //telnet.print("DAYLEGNTH ");
  //telnet.println(DAYLEGNTH);
  //telnet.print("SUNRISE ");
  //telnet.println(SUNRISE);
  //telnet.print("SUNSET ");
  //telnet.println(SUNSET);
  DayLength = atof(DAYLEGNTH);
  //telnet.println(DayLength);
  http.end();
}


void Cloud() {
  //LIDAR
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=450 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  CLOUD = doc["result"][0]["Data"];
  //telnet.print("CLOUD ");
  // telnet.println(CLOUD);
  cloud = atof(CLOUD);
  //  telnet.println(cloud);
  http.end();
}

void Wind() {
  //LIDAR
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=445 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  WINDD = doc["result"][0]["Direction"];
  WINDS = doc["result"][0]["Speed"];
  WINDG = doc["result"][0]["Gust"];
  TEMP = doc["result"][0]["Temp"];
  CHILL = doc["result"][0]["Chill"];


  winds = atof(WINDS);
  windg = atof(WINDG);

  // telnet.println("Wind ");
  //telnet.println(WINDD);
  //telnet.println(WINDS);
  //// telnet.println(WINDG);
  // telnet.println(TEMP);
  // telnet.println(CHILL);
  //  telnet.print("Wind ");
  //  telnet.println(winds);
  //  telnet.println(windg);


  http.end();
}

void Visibility() {
  //LIDAR
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=448 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  VISIBILITY = doc["result"][0]["Data"];
  // telnet.print("Visibility ");
  // telnet.println(VISIBILITY);
  visi = atof(VISIBILITY);
  // telnet.println(visi);
  http.end();
}

void Rain() {
  //LIDAR
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=447 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  RAINFALL = doc["result"][0]["Rain"];
  RAINRATE = doc["result"][0]["RainRate"];
  //telnet.print("RAIN ");
  //telnet.println(RAINFALL);
  rain = atof(RAINFALL);
  rainrate = atof(RAINRATE);
  // telnet.print(rain);
  http.end();
}

void SensorR() {
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=454 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  SENSORR = doc["result"][0]["Level"];
  //telnet.print("SENSORR ");
  //telnet.println(SENSORR);
  http.end();
}

void POWERMODE() {
  //LIDAR
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=423 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  SLEEPMODE = doc["result"][0]["Level"];
  //telnet.print("SLEEPMODE ");
  //telnet.println(SLEEPMODE);
  http.end();
}


void NAVMODE() {
  //LIDAR
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=466 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  NAVIMODE = doc["result"][0]["Level"];
  telnet.print("NAVMODE ");
  telnet.println(NAVIMODE);
  http.end();
}


void cameraR() {

  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=413 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  WIFICAM = doc["result"][0]["Level"];
  //telnet.ptint("WIFICAM ");
  //telnet.ptintln(WIFICAM);
  http.end();
}

void flightcontrollerR() {
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=368 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  FCPOWER = doc["result"][0]["Level"];
  // //telnet.ptint("FCPOWER ");
  // //telnet.ptintln(FCPOWER);
  http.end();
}


void AUXpowerR() {
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=417 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  AUXPOWER = doc["result"][0]["Level"];
  //telnet.ptint("FCPOWER ");
  //telnet.ptintln(FCPOWER);
  http.end();
}


void lidarR() {
  //LIDAR
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=420 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  LIDAR = doc["result"][0]["Level"];
  //telnet.ptint("LIDAR ");
  //telnet.ptintln(LIDAR);
  http.end();
}




void radarR() {
  //LIDAR
  DOMOTICZ_CONNECT();
 client.println(F("GET /json.htm?type=command&param=getdevices&rid=442 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  RADAR = doc["result"][0]["Level"];
  //telnet.ptint("LIDAR ");
  //telnet.ptintln(LIDAR);
  http.end();
}

void mainpowerR() {
  //Main Power
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=443 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  MAINPOWER = doc["result"][0]["Level"];
  //telnet.ptint("MAINPOWER ");
  //telnet.ptintln(MAINPOWER);
  http.end();
}

void motorpowerR() {
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=326 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  MOTPOWER = doc["result"][0]["Level"];
  //telnet.ptint("MOTPOWER ");
  //telnet.ptintln(MOTPOWER);
  http.end();
}


void lightsR() {
  //Lights
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=315 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  LIGHTS = doc["result"][0]["Level"];
  ////telnet.ptint("LIGHTS ");
  // //telnet.ptintln(LIGHTS);
  http.end();
}


void indicatorsR() {
  //Indicators
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=412 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  INDICATOR = doc["result"][0]["Level"];
  //telnet.ptint("INDICATOR ");
  //telnet.ptintln(INDICATOR);
  http.end();
}



void ARMING() {
  DOMOTICZ_CONNECT();
  client.println(F("GET /json.htm?type=command&param=getdevices&rid=441 HTTP/1.0"));
  DOMOTICZ_AUTHENTICATE();
  ARM = doc["result"][0]["Level"];
  //telnet.ptint("ARM ");
  //telnet.ptintln(ARM);
  http.end();
}
