
void request_datastream() {
  //Request Data from Pixhawk
  uint8_t _system_id = 255;       // id of computer which is sending the command (ground control software has id of 255)
  uint8_t _component_id = 2;      // seems like it can be any # except the number of what Pixhawk sys_id is
  uint8_t _target_system = 1;     // Id # of Pixhawk (should be 1)
  uint8_t _target_component = 0;  // Target component, 0 = all (seems to work with 0 or 1
  uint8_t _req_stream_id = MAV_DATA_STREAM_ALL;
  uint16_t _req_message_rate = 0x08;  //number of times per second to request the data in hex
  uint8_t _start_stop = 1;            //1 = start, 0 = stop



  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_request_data_stream_pack(_system_id, _component_id, &msg, _target_system, _target_component, _req_stream_id, _req_message_rate, _start_stop);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);  // Send the message (.write sends as bytes)

  Serial.write(buf, len);  //Write data to serial port
}

void MAVLINK_HB() {
     if (FCHB > 1) {
  uint8_t autopilot_type = MAV_TYPE_ONBOARD_CONTROLLER;
  uint8_t system_mode = MAV_MODE_PREFLIGHT;  ///< Booting up
  uint32_t custom_mode = 0;                  ///< Custom mode, can be defined by user/adopter
  uint8_t system_state = MAV_STATE_STANDBY;  ///< System ready for flight
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  int type = MAV_TYPE_GROUND_ROVER;
  // Pack the message

  mavlink_msg_heartbeat_pack(1, 191, &msg, type, autopilot_type, system_mode, custom_mode, system_state);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);
}
}

void MAVLINK_GPS() {
     if (FCHB > 1) {
  uint8_t autopilot_type = MAV_TYPE_ONBOARD_CONTROLLER;
  uint8_t system_mode = MAV_MODE_PREFLIGHT;  ///< Booting up
  uint32_t custom_mode = 0;                  ///< Custom mode, can be defined by user/adopter
  uint8_t system_state = MAV_STATE_STANDBY;  ///< System ready for flight
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  int type = MAV_TYPE_GROUND_ROVER;
  // Pack the message
     


  int32_t LATT = (gps.location.lat() * 10000000);
  int32_t LONN = (gps.location.lng() * 10000000);
  Serial.println("");
  Serial.println(LATT);
  Serial.println(LONN);
  Serial.println(gps.location.lat());
  Serial.println(gps.location.lng());
  mavlink_msg_gps_input_pack(1, 191, &msg, millis(), 0, 0, 0, 1, 3, LATT, LONN, gps.altitude.meters(), gps.hdop.hdop(), 0.01, 0, 0, 0, 0.1, 0.1, 0.1, gps.satellites.value(), gps.course.deg());
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);
}
}


void MAVLINK_SPEED() {
     if (FCHB > 1) {
  uint8_t autopilot_type = MAV_TYPE_ONBOARD_CONTROLLER;
  uint8_t system_mode = MAV_MODE_PREFLIGHT;  ///< Booting up
  uint32_t custom_mode = 0;                  ///< Custom mode, can be defined by user/adopter
  uint8_t system_state = MAV_STATE_STANDBY;  ///< System ready for flight
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  int type = MAV_TYPE_GROUND_ROVER;
  // Pack the message

  mavlink_msg_command_ack_pack(1, 191, &msg, 1, -1, dom_thr, 0, 0, 0);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);
  confirmspeedchange();
}
}

void sendtext() {


  uint8_t system_id = 1;
  uint8_t component_id = 2;
  uint8_t severity = 1;
  uint16_t id = 0;
  uint8_t chunk_seq = 0;
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  mavlink_msg_statustext_pack(system_id, component_id, &msg, 0, "TEST", id, chunk_seq);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial.write(buf, len);
}

void send_status(){
    memset(bufTx, 0xFF, sizeof(bufTx));
    mavlink_msg_sys_status_pack(mavlink_system.sysid, mavlink_system.compid, &statMsg,
      MAVLINK_SENSOR_PRESENT_DEFAULT, MAVLINK_SENSOR_PRESENT_DEFAULT, 
      MAVLINK_SENSOR_PRESENT_DEFAULT, 500,7400,330,50,0,0,0,0,0,0);
    
    /// Copy the message to send buffer
    uint16_t len = mavlink_msg_to_send_buffer(bufTx, &statMsg);

     //Write Message    
    Serial.write(bufTx, len);  
}

void send_parameters(){

  for(uint8_t i = 0; i < paramCount; i++){
    memset(bufTx, 0xFF, sizeof(bufTx));
    mavlink_msg_param_value_pack(mavlink_system.sysid, mavlink_system.compid,
      &paramMsg, local_param[i].param_id, local_param[i].param_value, 
      local_param[i].param_type, paramCount, i);
    /// Copy the message to send buffer
    uint16_t len = mavlink_msg_to_send_buffer(bufTx, &paramMsg);
    //Write Message    
    Serial.write(bufTx, len);
  }
   /*
    memset(bufTx, 0xFF, sizeof(bufTx));
    mavlink_msg_rc_channels_override_pack(mavlink_system.sysid, mavlink_system.compid, 
      &rc_overMsg, 1, 0, UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, 
      UINT16_MAX, UINT16_MAX, UINT16_MAX);
    /// Copy the message to send buffer
    uint16_t len = mavlink_msg_to_send_buffer(bufTx, &rc_overMsg);
    //Write Message    
    telem.write(bufTx, len);
    cout.println("Disabled RC INPUT");
*/
}

void send_mission_ack(){
    memset(bufTx, 0xFF, sizeof(bufTx));
    mavlink_msg_mission_ack_pack(mavlink_system.sysid, mavlink_system.compid,&msg, mavlink_system.sysid, mavlink_system.compid, MAV_RESULT_ACCEPTED,0);
    /// Copy the message to send buffer
    uint16_t len = mavlink_msg_to_send_buffer(bufTx, &msg);
    //Write Message    
    Serial.write(bufTx, len);
}

void send_mission_req(){
  for(uint16_t i = 0; i < wp_count; i++){
    memset(bufTx, 0xFF, sizeof(bufTx));
    mavlink_msg_mission_request_pack(mavlink_system.sysid, mavlink_system.compid,&misReq, mavlink_system.sysid, mavlink_system.compid, i,i);
    /// Copy the message to send buffer
    uint16_t len = mavlink_msg_to_send_buffer(bufTx, &misReq);
    //Write Message    
    Serial.write(bufTx, len);
  }
}


/*
void send_gps_msg(){
    // As long as we have a fix, proceed with packing and sending GPS data
    if(2 > 2)
    {
        memset(bufTx, 0xFF, sizeof(bufTx));
        mavlink_msg_gps_raw_int_pack(mavlink_system.sysid, mavlink_system.compid, &gpsMsg,
                   Microseconds, rtk.fixType, Latitude, Longitude, Altitude, rtk.pDOP, 
                   0, Velocity, rtk.heading*100, rtk.numSV); 
  
        /// Copy the message to send buffer
        uint16_t len = mavlink_msg_to_send_buffer(bufTx, &gpsMsg);

         //Write Message       
        telem.write(bufTx, len);  
     }
}
*/
/*
void send_ahrs_msg(){
    memset(bufTx, 0xFF, sizeof(bufTx));
    mavlink_msg_attitude_pack(mavlink_system.sysid, mavlink_system.compid, &ahrsMsg,
      bootTime, ahrs.roll, ahrs.pitch, ahrs.yaw,
      ahrs.rotx, ahrs.roty, ahrs.rotz);
    
    /// Copy the message to send buffer
    uint16_t len = mavlink_msg_to_send_buffer(bufTx, &ahrsMsg);

     //Write Message    
    telem.write(bufTx, len);  
}
*/