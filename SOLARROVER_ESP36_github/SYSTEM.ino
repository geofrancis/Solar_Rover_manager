
void SLEEPWAKE() {
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  print_wakeup_reason();
  ADC1 = analogRead(35);
  MAINBATT = map(ADC1, 1563, 2942, 380, 530);
  Serial.println(MAINBATT);
  //TIME_TO_SLEEP = map(MAINBATT,480,420,1000,60);
  //if (TIME_TO_SLEEP < 60){TIME_TO_SLEEP =59;}
  //if (TIME_TO_SLEEP > 1000){TIME_TO_SLEEP =1001;}
  if (MAINBATT <= 490) { TIME_TO_SLEEP = TIME_TO_SLEEPshort; }
  if (MAINBATT <= 470) { TIME_TO_SLEEP = TIME_TO_SLEEPlong; }
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1);  //1 = High, 0 = Low
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
  // Serial.println(esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH));
}

void GPIOSETUP() {

  pinMode(17, OUTPUT);
  //pinMode(33, OUTPUT);
  //pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(23, OUTPUT);

  pinMode(33, INPUT);
  pinMode(15, INPUT);
  pinMode(5, INPUT);
  pinMode(4, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(5), impulse, FALLING);  //define external interrupts

  digitalWrite(32, 0);
  digitalWrite(33, 0);
  digitalWrite(25, 0);
  digitalWrite(26, 0);
  //  digitalWrite(27, 0);
  digitalWrite(14, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);
  //digitalWrite(19, 0);
  digitalWrite(23, 0);

  digitalWrite(27, 1);
}



void INA228SETUP() {
  if (!INA1.begin()) {
    Serial.println("Could not connect INA BATT. Fix and Reboot");
  }

  if (!INA2.begin()) {
    Serial.println("Could not connect INA SOLAR . Fix and Reboot");
  }
}


void MCPSETUP() {

  if (!mcp.begin_I2C()) {
    Serial.println("MCP Error.");
  }
  // configure pin for output
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);

  mcp.pinMode(8, INPUT_PULLUP);
  mcp.pinMode(9, INPUT_PULLUP);
  mcp.pinMode(10, INPUT_PULLUP);
  mcp.pinMode(11, INPUT_PULLUP);
  mcp.pinMode(12, INPUT_PULLUP);
  mcp.pinMode(13, INPUT_PULLUP);
  mcp.pinMode(14, INPUT_PULLUP);
  mcp.pinMode(15, INPUT_PULLUP);

  mcp.setupInterruptPin(15, HIGH);
}


void WIFICONNECT() {

  // Connecting to a WiFi AP
  WiFi.begin(ssid1, password1);
  Serial.println("Connecting to WiFi...");
  delay(2000);
  if (WiFi.isConnected()) {
    voice.say(sp2_CONNECT);
    voice.say(sp4_ALPHA);
  }

  while (!WiFi.isConnected()) {
    Serial.print("WIFI 1 FAIL: ");

    WiFi.disconnect();
    WiFi.begin(ssid2, password2);
    // Waiting until we connect to WiFi

    delay(5000);
    if (WiFi.isConnected()) {
      voice.say(sp2_CONNECT);
      voice.say(sp4_BRAVO);
    }
  }
  // Print the IP address in the local network
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void PINGSERVER() {
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

void OTASETUP() {

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else {  // U_SPIFFS
        type = "filesystem";
      }

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        Serial.println("Auth Failed");
      } else if (error == OTA_BEGIN_ERROR) {
        Serial.println("Begin Failed");
      } else if (error == OTA_CONNECT_ERROR) {
        Serial.println("Connect Failed");
      } else if (error == OTA_RECEIVE_ERROR) {
        Serial.println("Receive Failed");
      } else if (error == OTA_END_ERROR) {
        Serial.println("End Failed");
      }
    });

  ArduinoOTA.setHostname("Solar_Rover");
  ArduinoOTA.setPassword("passw0rded");
}

void wificheck() {

  unsigned long wificurrent = millis();
  // if WiFi is down, try reconnecting
  telnet.printf(" response time : %d/%.2f/%d ms\n", Ping.minTime(), Ping.averageTime(), Ping.maxTime());
  if ((WiFi.status() != WL_CONNECTED) && (wificurrent - wifimillis >= wifiinterval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    wifimillis = wificurrent;

    if (WiFi.isConnected()) {
      voice.say(sp2_CONNECT);
      voice.say(sp2_BRAVO);
    }

    uint8_t system_id = 1;
    uint8_t component_id = 191;
    uint8_t severity = 1;
    uint16_t id = 0;
    uint8_t chunk_seq = 0;

    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    mavlink_msg_statustext_pack(system_id, component_id, &msg, 0, "WIFI Reconnect", id, chunk_seq);
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    Serial2.write(buf, len);
  }
}

void sleepcheck() {

  Serial.println(MAINBATT);
  telnet.println("AWAKE");
  if (SLEEPMODE == 40) {
    if (MOTPOWER == 10) {
      if (FCPOWER == 10) {

        telnet.println("Going to sleep now waiting for RADARS");

        telnet.println("Going to sleep now");
        telnet.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
        telnet.println(MAINBATT);

        talkiesleep();
        mcp.digitalWrite(1, LOW);
        mcp.digitalWrite(2, LOW);
        mcp.digitalWrite(3, LOW);
        mcp.digitalWrite(4, LOW);
        mcp.digitalWrite(5, LOW);
        mcp.digitalWrite(6, LOW);
        mcp.digitalWrite(7, LOW);
        mcp.digitalWrite(8, LOW);
        delay(2000);
        Serial.flush();
        esp_deep_sleep_start();
      }
    }
  }
}


void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case 1:
      Serial.println("Wakeup caused by external signal using RTC_IO");
      talkieradarwake();
      break;
    case 2:
      Serial.println("Wakeup caused by external signal using RTC_CNTL");
      talkieradarwake();
      break;
    case 3:
      Serial.println("Wakeup caused by timer");
      break;
      talkierstartuptime();
    case 4: Serial.println("Wakeup caused by touchpad"); break;
    case 5: Serial.println("Wakeup caused by ULP program"); break;
    default:
      Serial.println("Wakeup was not caused by deep sleep");
      talkierstartup();
      break;
  }
}


void FCHBC() {
  //telnet.print("FCHB ");
  //telnet.println(FCHB);
  if (FCHB > 1) {
    telnet.print("Rover ");
    telnet.print(FCHB);
    telnet.println("Beats ");
    FCHB = 0;
  }
  if (FCHB <= 1) {
    telnet.print("NO FLIGHT CONTROLLER ");
    telnet.println(FCHB);
  }
}





void HBWATCH() {
  FCHB++;
  telnet.print("tick");
}
