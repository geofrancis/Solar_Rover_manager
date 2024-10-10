void setup() {

  //Serial2.begin(115200, SERIAL_8N1, 5, 4);  //RXTX from Pixhawk (Port 19,18 Arduino Mega)
  Serial.begin(115200);                      //Main serial port for console output
//  Serial1.begin(115200, SERIAL_8N1, 23, 5);  
  Serial2.begin(38400, SERIAL_8N1, 18, 19);//GPS+AIS

  Wire.begin();  //22 SCL  21 SDA

  SLEEPWAKE();
  GPIOSETUP();
  WIFICONNECT();
  INA228SETUP();
  MCPSETUP();
  OTASETUP();
  configTime(1 * 60 * 60, 3600, "uk.pool.ntp.org");
  setupTelnet();
  delay(2000);

  BME680GASSETUP();
  AS3935SETUP();
  ArduinoOTA.begin();
  lightMeter.begin();
  PINGSERVER();
  request_datastream();
inputString.reserve(200);
 myPID.SetMode(AUTOMATIC);

 // rss.begin();
//  rss.axs(url);

Serial.println("STARTUP.........................................................................");
    sendBOOT();
  delay(1000);
}