
void sensors() {

  ADC1 = analogRead(35);
  MAINBATT = map(ADC1, 1968, 2974, 380, 550);
  if (MAINBATT < 5) { MAINBATT = 0; }
  //telnet.println(ADC1);
  //telnet.println("MAINBATT");
  //telnet.println(MAINBATT/10);


  ADC2 = analogRead(34);
  BATT1 = map(ADC2, 0, 2385, 0, 415);
  //telnet.println(ADC2);
  //telnet.println(BATT1/100);


  ADC3 = analogRead(32);
  BATT2 = map(ADC3, 0, 2385, 0, 415);
  //telnet.println(ADC3);
  //telnet.println(BATT2/10);

  //radar1
  RAD1 = mcp.digitalRead(8);
  RAD2 = mcp.digitalRead(9);
  RAD3 = mcp.digitalRead(10);
  RAD4 = digitalRead(33);

  if (SENSORR == 20) {
    if (RAD1 != RAD11) {
      // if (RAD1 == 1) { talkieradarright(); }
    }
    if (RAD2 != RAD22) {
      // if (RAD2 == 1) { talkieradarleft(); }
    }
    if (RAD3 != RAD33) {
      //  if (RAD3 == 1) { talkieradarcentre(); }
    }
  }
  if (RAD4 != RAD44) {
    //  if (RAD4 == 1) { talkieradaromni(); }
  }
  RAD11 = RAD1;
  RAD22 = RAD2;
  RAD33 = RAD3;
  RAD44 = RAD4;


  //telnet.print("Radar 1 ");
  //telnet.println(RAD1);
  //radar2
  //telnet.print("Radar 2 ");
  //telnet.println(RAD2);
  //radar 3
  //telnet.print("Radar 3 ");
  //telnet.println(RAD3);
  //talkieradarcentre();
  //telnet.print("Radar 4 ");
  //telnet.println(RAD4);
}

 void RADS(){
 // telnet.print("CPM ");
 // telnet.println(counts);
  CPM = counts;
  counts = 0;
}

void impulse() {
  counts++;
   // telnet.print("tick");
}
 void INABATT(){

  telnet.println("\nBUS\tSHUNT\tCURRENT\tPOWER\tTEMP");
  for (int i = 0; i < 20; i++)
  {
    telnet.print(INA1.getBusVoltage(), 3);
    telnet.print("\t");
    telnet.print(INA1.getShuntVoltage_mV(), 3);
    telnet.print("\t");
    telnet.print(INA1.getCurrent_mA(), 3);
    telnet.print("\t");
    telnet.print(INA1.getPower_mW(), 3);
    telnet.print("\t");
    telnet.print(INA1.getTemperature(), 3);
    telnet.println();
    delay(1000);
  }

 }

  void INASOLAR(){

  telnet.println("\nBUS\tSHUNT\tCURRENT\tPOWER\tTEMP");
  for (int i = 0; i < 20; i++)
  {
    telnet.print(INA2.getBusVoltage(), 3);
    telnet.print("\t");
    telnet.print(INA2.getShuntVoltage_mV(), 3);
    telnet.print("\t");
    telnet.print(INA2.getCurrent_mA(), 3);
    telnet.print("\t");
    telnet.print(INA2.getPower_mW(), 3);
    telnet.print("\t");
    telnet.print(INA2.getTemperature(), 3);
    telnet.println();
    delay(1000);
  }

 }


void lightlevel(){

  float lux = lightMeter.readLightLevel();
  telnet.print("Light: ");
  telnet.print(lux);
  telnet.println(" lx");

}


void BME680GASSETUP(){


  BME680.setOversampling(TemperatureSensor, Oversample16);  // Use enumerated type values
  BME680.setOversampling(HumiditySensor, Oversample16);     // Use enumerated type values
  BME680.setOversampling(PressureSensor, Oversample16);     // Use enumerated type values
  Serial.print(F("- Setting IIR filter to a value of 4 samples\n"));
  BME680.setIIRFilter(IIR4);  // Use enumerated type values
  Serial.print(F("- Setting gas measurement to 320\xC2\xB0\x43 for 150ms\n"));  // "�C" symbols
  BME680.setGas(320, 150);  // 320�c for 150 milliseconds


}

void BME680GAS(){
  static int32_t  temp, humidity, pressure, gas;  // BME readings
  static char     buf[16];                        // sprintf text buffer
  static float    alt;                            // Temporary variable
  static uint16_t loopCounter = 0;                // Display iterations

  BME680.getSensorData(temp, humidity, pressure, gas);  // Get readings

  
  if (loopCounter++ != 0) {                             // Ignore first reading, might be incorrect
    sprintf(buf, "%4d %3d.%02d", (loopCounter - 1) % 9999,  // Clamp to 9999,
            (int8_t)(temp / 100), (uint8_t)(temp % 100));   // Temp in decidegrees
    Serial.print(buf);
    sprintf(buf, "%3d.%03d", (int8_t)(humidity / 1000),
            (uint16_t)(humidity % 1000));  // Humidity milli-pct
    Serial.print(buf);
    sprintf(buf, "%7d.%02d", (int16_t)(pressure / 100),
            (uint8_t)(pressure % 100));  // Pressure Pascals
    Serial.print(buf);
    alt = altitude(pressure);                                                // temp altitude
    sprintf(buf, "%5d.%02d", (int16_t)(alt), ((uint8_t)(alt * 100) % 100));  // Altitude meters
    Serial.print(buf);
    sprintf(buf, "%4d.%02d\n", (int16_t)(gas / 100), (uint8_t)(gas % 100));  // Resistance milliohms
    Serial.print(buf);
    delay(10000);  // Wait 10s
  }                // of ignore first reading


}

void AS3935SETUP(){

  if( !lightning.begin() ){ // Initialize the sensor. 
    Serial.println ("Lightning Detector did not start up, freezing!"); 
  }
  else
    Serial.println("Schmow-ZoW, Lightning Detector Ready!\n");
  // "Disturbers" are events that are false lightning events. If you find
  // yourself seeing a lot of disturbers you can have the chip not report those
  // events on the interrupt lines. 
  lightning.maskDisturber(true); 
  int maskVal = lightning.readMaskDisturber();
  Serial.print("Are disturbers being masked: "); 
  if (maskVal == 1)
    Serial.println("YES"); 
  else if (maskVal == 0)
    Serial.println("NO"); 

  // The lightning detector defaults to an indoor setting (less
  // gain/sensitivity), if you plan on using this outdoors 
  // uncomment the following line:
  lightning.setIndoorOutdoor(OUTDOOR); 
  int enviVal = lightning.readIndoorOutdoor();
  Serial.print("Are we set for indoor or outdoor: ");  
  if( enviVal == INDOOR )
    Serial.println("Indoor.");  
  else if( enviVal == OUTDOOR )
    Serial.println("Outdoor.");  
  else 
    Serial.println(enviVal, BIN); 
 
  // Noise floor setting from 1-7, one being the lowest. Default setting is
  // two. If you need to check the setting, the corresponding function for
  // reading the function follows.    

  lightning.setNoiseLevel(noiseFloor);  

  int noiseVal = lightning.readNoiseLevel();
  Serial.print("Noise Level is set at: ");
  Serial.println(noiseVal);

  // Watchdog threshold setting can be from 1-10, one being the lowest. Default setting is
  // two. If you need to check the setting, the corresponding function for
  // reading the function follows.    

  lightning.watchdogThreshold(watchDogVal); 

  int watchVal = lightning.readWatchdogThreshold();
  Serial.print("Watchdog Threshold is set to: ");
  Serial.println(watchVal);

  lightning.spikeRejection(spike); 
  int spikeVal = lightning.readSpikeRejection();
  Serial.print("Spike Rejection is set to: ");
  Serial.println(spikeVal);

}






void AS3935(){

    intVal = lightning.readInterruptReg();
    if(intVal == NOISE_INT){
      Serial.println("Noise."); 
    }
    else if(intVal == DISTURBER_INT){
      Serial.println("Disturber."); 
    }
    else if(intVal == LIGHTNING_INT){
      Serial.println("Lightning Strike Detected!"); 
      byte distance = lightning.distanceToStorm(); 
      Serial.print("Approximately: "); 
      Serial.print(distance); 
      Serial.println("km away!"); 
      long lightEnergy = lightning.lightningEnergy(); 
      Serial.print("Lightning Energy: "); 
      Serial.println(lightEnergy); 

    }
  }

void AMS1115setup(){
    ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS1);   // 0x48
    ads.setGain(eGAIN_TWOTHIRDS);   // 2/3x gain
    ads.setMode(eMODE_SINGLE);       // single-shot mode
    ads.setRate(eRATE_128);          // 128SPS (default)
    ads.setOSMode(eOSMODE_SINGLE);   // Set to start a single-conversion
    ads.init();

}

void AMD1115(){

 int16_t adc0, adc1, adc2, adc3;
        adc0 = ads.readVoltage(0);
        Serial.print("A0:");
        Serial.print(adc0);
        Serial.print("mV,  ");
        adc1 = ads.readVoltage(1);
        Serial.print("A1:");
        Serial.print(adc1);
        Serial.print("mV,  ");
        adc2 = ads.readVoltage(2);
        Serial.print("A2:");
        Serial.print(adc2);
        Serial.print("mV,  ");
        adc3 = ads.readVoltage(3);
        Serial.print("A3:");
        Serial.print(adc3);
        Serial.println("mV");

}


// Gets new heading info  from compass 
void getHeading() {
    sensors_event_t event; 
    compass.getEvent(&event);
    
    float X,Y;
    // Get x,y components of magnetic field vector; values are in micro-Tesla (uT))
    // and correct for offset 
    X=event.magnetic.x-Xoffset;
    Y=event.magnetic.y-Yoffset;
    float heading = atan2(-X, -Y) * 180/PI;
    //correct for declination angle 
    heading += declinationAngle;
    
    // correct as needed to guarantee that result is between 0 and 360
    if (heading < 0) heading += 360;
    if (heading > 360 ) heading -= 360;
  
}




