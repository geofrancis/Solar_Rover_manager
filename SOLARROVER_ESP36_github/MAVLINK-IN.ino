
void FetchMavlink() {
  mavlink_message_t msg;
  mavlink_status_t status;

  while (Serial.available()) {
    uint8_t c = Serial.read();

    //Get new message
    if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {

      //Handle new message from autopilot
      switch (msg.msgid) {

        case MAVLINK_MSG_ID_GPS_RAW_INT:
          {
            mavlink_gps_raw_int_t packet;
            mavlink_msg_gps_raw_int_decode(&msg, &packet);

            mavlink_gps_raw_int_t datagps;
            mavlink_msg_gps_raw_int_decode(&msg, &datagps);
            //telnet.println("PX HB");
            // telnet.println("GPS Data ");
            //  telnet.print("time usec: ");
            // telnet.println(datagps.time_usec);
            //  telnet.print("lat: ");
            //     telnet.println(datagps.lat);
            GPSLAT = (datagps.lat);
            //telnet.print("lon: ");
            //telnet.println(datagps.lon);
            GPSLON = (datagps.lon);
            //  telnet.print("alt: ");
            //   telnet.println(datagps.alt);
            //telnet.print("Sattelite visible: ");
            //  telnet.println(datagps.satellites_visible);
            satelites = (datagps.satellites_visible);
            //   telnet.println(datagps.eph);
            HDOP = (datagps.eph);
            //telnet.println(datagps.epv);
          }
          break;

        case MAVLINK_MSG_ID_SYS_STATUS:  // #1: SYS_STATUS
          {
            //mavlink_message_t* msg;
            mavlink_sys_status_t sys_status;
            mavlink_msg_sys_status_decode(&msg, &sys_status);
            //   telnet.print("PX SYS STATUS: ");
            //   telnet.print("[Bat (V): ");
            //    telnet.print(sys_status.voltage_battery);
            VOLTS = (sys_status.voltage_battery);
            // telnet.print(sys_status.voltage_battery / 1000);
            //   telnet.print("], [Bat (A): ");
            //   telnet.print(sys_status.current_battery);
            AMPS = (sys_status.current_battery);
            //  telnet.print("], [Comms loss (%): ");
            //  telnet.print(sys_status.drop_rate_comm);
            //comdroprate = (sys_status.drop_rate_comm);
            //      telnet.println("]");
          }


          break;

        case MAVLINK_MSG_ID_ATTITUDE:  // #30
          {

            mavlink_attitude_t attitude;
            mavlink_msg_attitude_decode(&msg, &attitude);
            //    telnet.println("PX ATTITUDE");
            //     telnet.println(attitude.roll);
            roll = (attitude.roll);
            pitch = (attitude.pitch);
            yaw = (attitude.yaw);
            //if (attitude.roll > 1) leds_modo = 0;
            //else if (attitude.roll < -1) leds_modo = 2;
            //else leds_modo = 1;
          }

          break;

        case MAVLINK_MSG_ID_RC_CHANNELS_RAW:  // #35
          {
            mavlink_rc_channels_raw_t chs;
            mavlink_msg_rc_channels_raw_decode(&msg, &chs);
            //   telnet.print("Chanel 6 (3-Kanal Schalter): ");
            //    telnet.println(chs.chan6_raw);
          }

          break;

        case MAVLINK_MSG_ID_RC_CHANNELS_SCALED:  // #35
          {
            mavlink_rc_channels_scaled_t RCCHANNEL;
            mavlink_msg_rc_channels_scaled_decode(&msg, &RCCHANNEL);
            //  telnet.print("Chanel 6 (3-Kanal Schalter): ");
            // int RAW_SERVO = RCCHANNEL.chan6_scaled;
            // telnet.println(RAW_SERVO);
            // telnet.print("Chanel 5 (Schub): ");
            //  telnet.println(RCCHANNEL.chan5_scaled);
            //  telnet.print("Drei Kanal: ");
            //  telnet.println(mavlink_msg_rc_channels_scaled_get_chan6_scaled(&msg));
            //  telnet.print("Schub: ");
            //  telnet.println(mavlink_msg_rc_channels_scaled_get_chan5_scaled(&msg));
          }

          break;

        case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:  // #30
          {
            mavlink_global_position_int_t Position;
            //mavlink_msg_attitude_decode(&msg, &attitude);
            mavlink_msg_global_position_int_decode(&msg, &Position);
          }
          break;

        case MAVLINK_MSG_ID_HEARTBEAT:  // #0: Heartbeat
          {

            mavlink_heartbeat_t hb;
            mavlink_msg_heartbeat_decode(&msg, &hb);
            // telnet.print("Flight Mode: ");
            //  telnet.println(hb.custom_mode);
            //  telnet.print("Type: ");
            //   telnet.println(hb.type);
            // telnet.print("Autopilot: ");
            // telnet.println(hb.autopilot);
            telnet.print("Base Mode: ");
            telnet.println(hb.base_mode);
            BASEMODE = (hb.base_mode);
            fcmodein = (hb.custom_mode);
            telnet.println("ROVER HB");
            HBWATCH();
            



            // telnet.println("fcmodein ");
            // telnet.println(fcmodein);
            //telnet.print("System Status: ");
            //telnet.println(hb.system_status);
            //     telnet.print("Mavlink Version: ");
            //     telnet.println(hb.mavlink_version);
            //telnet.println();
          }
          break;


        case MAVLINK_MSG_ID_RC_CHANNELS:  // #35
          {
            mavlink_rc_channels_t chs;
            mavlink_msg_rc_channels_decode(&msg, &chs);
            //       telnet.print("Chanel 8: ");
            RCIN = (chs.chan8_raw);
            //      telnet.println(chs.chan1_raw);
          }
          break;
        case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:  // #35
          {
            mavlink_servo_output_raw_t SERVOCHANNEL;
            mavlink_msg_servo_output_raw_decode(&msg, &SERVOCHANNEL);
            //  telnet.println(SERVOCHANNEL.servo1_raw);
            //  telnet.println(SERVOCHANNEL.servo2_raw);
            //  telnet.println(SERVOCHANNEL.servo3_raw);
            //  telnet.print("Chanel 1 (raw): ");
          }
          break;

        case MAVLINK_MSG_ID_MISSION_CURRENT:
          {
            mavlink_mission_current_t RPNUM;
            mavlink_msg_mission_current_decode(&msg, &RPNUM);
            wp_number = (RPNUM.seq);
            // telnet.print("wp_number ");
            //  telnet.println(wp_number);
            break;

            case MAVLINK_MSG_ID_VFR_HUD:
              {
                mavlink_vfr_hud_t vfrhud;
                mavlink_msg_vfr_hud_decode(&msg, &vfrhud);
                // telnet.print("Ground Speed: ");
                //  telnet.println(vfrhud.groundspeed);
                ////  telnet.print("Heading ");
                //   telnet.println(vfrhud.heading);
                gps_Vel = vfrhud.groundspeed;
                gps_Head = vfrhud.heading;
              }


            case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
              {
                mavlink_nav_controller_output_t navout;
                mavlink_msg_nav_controller_output_decode(&msg, &navout);
                navbearing = navout.target_bearing;
                wpdist = navout.wp_dist;
                xtrackerror = navout.xtrack_error;
                telnet.print("navbearing: ");
                telnet.println(navout.nav_bearing);
                telnet.print("wpdist ");
                telnet.println(navout.wp_dist);
                telnet.print("xtrackerror ");
                telnet.println(navout.xtrack_error);
              }




            case MAVLINK_MSG_ID_STATUSTEXT:  //  #253  https://mavlink.io/en/messages/common.html#STATUSTEXT
              {
                mavlink_statustext_t packet;
                mavlink_msg_statustext_decode(&msg, &packet);
                //        telnet.print("=STATUSTEXT");
                //         telnet.print(" severity:");
                //        telnet.print(packet.severity);
                //         telnet.print(" text:");
                //         telnet.print(packet.text);
                message = (packet.text);
                break;
              }

         case MAVLINK_MSG_ID_MANUAL_CONTROL: // #69: Joystick data
                //[IMPORTANT: TEMPORARY FIX EXPLAINED BELOW]
              //  mavlink_msg_manual_control_decode(&msg, &manual_control);
                //Serial.println("Received Manual Message");
              //  joyStick_control();
                break;
                
          case MAVLINK_MSG_ID_SET_MODE:            //Get new base mode
              //killMotors();                        //Get bot ready for new mode
              mavlink_msg_set_mode_decode(&msg, &modee);
              //heartbeat.base_mode = modee.base_mode;
             // heartbeat.custom_mode = modee.custom_mode;
    //          print_setMode();
              break;
        

           case MAVLINK_MSG_ID_PARAM_REQUEST_LIST: //#21  
               send_parameters();
               break;

           case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
               send_parameters();
               break;

           case MAVLINK_MSG_ID_MISSION_ITEM:
                mavlink_msg_mission_item_decode(&msg, &misItem);
      //          print_mission_item();
      //          save_waypoints();
                send_mission_ack();
                break;

           case MAVLINK_MSG_ID_MISSION_COUNT:
               mavlink_msg_mission_count_decode(&msg, &misCount);
               wp_count = misCount.count;
               if(wp_count > 100 || wp_count == 0) {
                  wp_count = 0;
                  break;
               } else {
                 send_mission_req();
               }
               break;
               
          case MAVLINK_MSG_ID_PARAM_SET:  
             //Serial.println("GOT PARAM_SET");
             mavlink_param_set_t packet;
             mavlink_msg_param_set_decode(&paramMsg, &packet);
             //Serial.print("Received set parameter: "); 
             //Serial.print(packet.param_id[0]); Serial.print(",  ");
             //Serial.println(packet.param_value);
             send_mission_ack();
             
             break;

          case MAVLINK_MSG_ID_PARAM_VALUE:
   //          cout.println("GOT PARAM_VALUE");
             mavlink_param_set_t packet1;
             mavlink_msg_param_set_decode(&paramMsg, &packet1);
          //   cout.print("Received set parameter: ");
          ////   cout.print(packet1.param_id[0],HEX); Serial.print(",  ");
          //   cout.println(packet1.param_value);
             break;

          case MAVLINK_MSG_ID_COMMAND_LONG:
            mavlink_msg_command_long_decode(&msg, &cmd_long);
  /*          cout.print("\tTarget Component: "); Serial.println(cmd_long.target_component);
            cout.print("\tCommand: "); Serial.println(cmd_long.command);
            cout.print("\tParam1: "); Serial.println(cmd_long.param1);
            cout.print("\tParam2: "); Serial.println(cmd_long.param2);
            cout.print("\tParam3: "); Serial.println(cmd_long.param3);
            cout.print("\tParam4: "); Serial.println(cmd_long.param4);
            cout.print("\tParam5: "); Serial.println(cmd_long.param5);
            cout.print("\tParam6: "); Serial.println(cmd_long.param6);
            cout.print("\tParam7: "); Serial.println(cmd_long.param7);           
    */
            send_mission_ack();
          break;




          }
      }
    }
  }
}










/*








              /*
case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:  // #35
  {
    mavlink_servo_output_raw_t SERVOCHANNEL;
    mavlink_msg_servo_output_raw_decode(&msg, &SERVOCHANNEL);
    telnet.println(SERVOCHANNEL.servo1_raw);
    telnet.println(SERVOCHANNEL.servo2_raw);
    telnet.println(SERVOCHANNEL.servo3_raw);
    servo1 = (SERVOCHANNEL.servo1_raw);
    servo2 = (SERVOCHANNEL.servo2_raw);
    servo3 = (SERVOCHANNEL.servo3_raw);
    telnet.print("Chanel 1 (raw): ");
  }

*/

/*
case MAVLINK_MSG_ID_RANGEFINDER:  // #17
  {
    mavlink_rangefinder_t packet;
    mavlink_msg_rangefinder_get_distance(&msg, &packet);
    telnet.println(packet.distance);
    telnet.print("packet distance ");
  }
  



              void pixhawk_Watchdog()  //Request Pixhawk to send HeartBeats and check for response
              {
                unsigned long current_hb_Millis = millis();

                if (pixhawk_Watchdog_switch == 1 && pixhawk_HBsatswitch == 1) {

                  //Non-blocking timer function
                  if (current_hb_Millis - previous_hb_Millis >= HB_Interval) {
                    previous_hb_Millis = current_hb_Millis;  // save the last time you collected data

                    //Check for Pixhawk heartbeats
                    telnet.println("\nChecking for Pixhawk Heartbeats... ");
                    hb_collection_flag = 1;
                    mavLinkHB_switch = 1;
                  }

                  //Non-blocking timer function
                  //Turn off watchdog routine according to HB_Turnoff_interval variable
                  if (((current_hb_Millis - previous_hb_Millis) >= hb_Turnoff_interval) && (hb_collection_flag == 1)) {
                    telnet.println("\nEnding HB watchdog... ");
                    hb_collection_flag = 0;
                    mavLinkHB_switch = 0;

                    //check to see if HB collected is more than 0
                    if (px4_Hb > 0) {
                      telnet.print("\nHBs received: ");
                      telnet.println(px4_Hb);
                      px4_Hb = 0;
                      HBwatchdog_Counter = 0;  //reset watchdog reset counter
                    }

                    else {
                      HBwatchdog_Counter++;
                      telnet.println("\nNO HBs received setting counter: ");
                      telnet.println(HBwatchdog_Counter);

                      //If havent received HBs 3x then POWER CYLE Relay
                      if (HBwatchdog_Counter >= 3) {
                        telnet.println("\nPower cycling Pixhawk and resetting counter");
                        HBwatchdog_Counter = 0;

                        //Begin Pixhawk and Servo power cycle
                        previous_pixhawk_servo_Millis = millis();
                        digitalWrite(19, LOW);  //Turn off power to pixhawk
                        pixhawk_servo_Switch = 1;
                        telnet.println("Pixhawk and Servo Power Off");

                        px4_Resetcounter++;
                        telnet.print("\nIncrementing Total number of HB Failures: ");
                        telnet.println(px4_Resetcounter);

                        //Reset global variable to 0 if too large (sent via modem)
                        if (px4_Resetcounter >= 99) {
                          telnet.println("\nresetting global HB failure counter");
                          px4_Resetcounter = 0;
                        }
                      }
                    }
                  }
                }
              }


*/