

void flightmodein() {
  // READ FLIGHT MODE

  DOMOTICZ_CONNECT();
  client.println("324");
  DOMOTICZ_AUTHENTICATE();
  mode = doc["result"][0]["Level"];
  //telnet.ptint("dmmode ");
  //telnet.ptintln(mode);
  http.end();
}


void setMODE() {

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

    //  telnet.print("MODE ");
    //  telnet.println(mode);
    // telnet.print("mode ");
    //   telnet.println(mode);
    // telnet.print("fc mode ");
    // telnet.println(fcmode);
    //  telnet.print("fc modein ");
    //  telnet.println(fcmodein);


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



void arming() {


  if (ARM > 1) {
    telnet.println("ARMING change");


    if (ARM == 20) {
      arm();
    }


    if (ARM == 10) {
      disarm();
    }
  }
}



void arm() {
  // if (armed ==0){

  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  int type = MAV_TYPE_GROUND_ROVER;
  // Pack the message
  mavlink_msg_command_long_pack(0xFF, 0xBE, &msg, 1, 1, 400, 1, 1.0, 0, 0, 0, 0, 0, 0);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);
  confirmmarm();

  // }
}


void disarm() {
  //   if (armed ==1){
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  int type = MAV_TYPE_GROUND_ROVER;
  // Pack the message
  mavlink_msg_command_long_pack(0xFF, 0xBE, &msg, 1, 1, 400, 1, 0.0, 0, 0, 0, 0, 0, 0);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);
  confirmmdisarm();

  //}
}


void confirmmarm() {

  if (BASEMODE == 193) {
    talkiearmed();
    domoticzoutconnect();
    client.print(441);
    client.print("&nvalue=0&svalue=");
    client.print(0);
    domoticzoutauthenticate();
  }
}



void confirmmdisarm() {

  if (BASEMODE == 65) {
    talkiedisarmed();
    domoticzoutconnect();
    client.print(441);
    client.print("&nvalue=0&svalue=");
    client.print(0);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(domoticz_server);
    domoticzoutauthenticate();
  }
}



void sendflightmode() {
  domoticzoutconnect();
  client.print(397);
  client.print("&nvalue=0&svalue=");
  client.print(fcmodein);
  domoticzoutauthenticate();
}


void confirmmodechange() {

  domoticzoutconnect();
  client.print(324);
  client.print("&nvalue=0&svalue=");
  client.print(0);
  domoticzoutauthenticate();
}
