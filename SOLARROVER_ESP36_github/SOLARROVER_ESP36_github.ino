#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_MCP23X17.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <NetworkUdp.h>
#include <ArduinoOTA.h>
#include "ESPTelnet.h"
#include <ESP32Time.h>
#include <ESPping.h>
#include <moonPhase.h>
#include "INA228.h"
#include <BH1750.h>
#include "Zanshin_BME680.h"
#include "SparkFun_AS3935.h"
#include <DFRobot_ADS1115.h>
#include <TinyGPSPlus.h>
#include <AIS.h>
#include <Adafruit_HMC5883_U.h>
#include <PID.h>


//#include <time.h>  // Built-in


#include "mavlink/common/mavlink.h"
#include "mavlink/common/mavlink_msg_rc_channels.h"
#include "mavlink/common/mavlink_msg_mission_current.h"
#include "mavlink/common/mavlink_msg_command_long.h"


#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"
#include "Vocab_Soundbites.h"
#include "TalkieUtils.h"
#include "Vocab_Special.h"
#include "Vocab_US_Acorn.h"




/*
Value
Meaning
0 Manual
1Acro
3Steering
4Hold
5Loiter
6Follow
7Simple
8Dock
9Circle
10Auto
11RTL
12SmartRTL
15Guided

*/

// WiFi settings
const char ssid2[] = "SSID1";
const char password1[] = "password";
const char ssid1[] = "SSID2";
const char password2[] = "password";

//int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiClient client;  // or WiFiClientSecure for HTTPS
HTTPClient http;

char* message;
RTC_DATA_ATTR int bootCount = 0;

unsigned long previousMillis = 0;  // LOOP1
const long interval = 2000;

unsigned long previousMillis2 = 0;  // LOOP2
const long interval2 = 10000;
//const long interval2 = (1 * 60 * 1000);


unsigned long previousMillis4 = 0;  // LOOP2
const long GPSinterval = 200;

const long sleepinterval = 20000;  // inte
unsigned long sleeppreviousMillis = 0;
// domoticz

unsigned long wifimillis = 0;
unsigned long wifiinterval = 5000;

unsigned long counts;           //variable for GM Tube events
unsigned long previousMillis3;  //variable for time measurement
#define LOG_PERIOD 60000        // cetak tiap detik

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
int TIME_TO_SLEEP = 600;
int TIME_TO_SLEEPshort = 1200;
int TIME_TO_SLEEPlong = 2100;


#define BUTTON_PIN_BITMASK (1 << 15 | 1 << 2)


const char* domoticz_server = "yoursever.yourdomain.org";  //Domoticz port
int port = 9000;                                          //Domoticz port

int ADC1 = 0;
int ADC2 = 0;
int ADC3 = 0;
int RAD1 = 0;
int RAD2 = 0;
int RAD3 = 0;
int RAD4 = 0;
int RAD11 = 0;
int RAD22 = 0;
int RAD33 = 0;
int RAD44 = 0;


int RCIN = 1500;
int MODE = 0;
int ARM = 0;
int ARMSET = 0;
int BASEMODE = 0;
int WARNING = 0;
int SLEEPMODE = 0;
int NAVIMODE = 0;

double NAVLAT = 50.000000, NAVLON = -4.000000;

const char* RAINFALL;
const char* RAINRATE;
int WINDD;
const char* WINDS;
const char* WINDG;
const char* WINDSS;
const char* WINDGG;
float TEMP;
float CHILL;
const char* VISIBILITY;
const char* VISIBILITYY;
const char* CLOUD;
float rain;
float rainrate;
float winds;
float windg;
float visi;
float cloud;
const char* DAYLEGNTH;
const char* SUNRISE;
const char* SUNSET;

float DayLength;


int dom_thr;


float elevation;
float azimuth;


int sun_azimuth;
int sun_elevation;

String time_str, current_hour, current_minute, current_day, current_month, current_year;



int MAINBATTAVG;
float MAINBATT = 0;
float BATT1 = 0;
float BATT2 = 0;
RTC_DATA_ATTR float VOLTS = 0;
float AMPS = 0;
int flightmode = 0;
RTC_DATA_ATTR long GPSLAT = 0.1234567;
RTC_DATA_ATTR long GPSLON = 0.1234567;
int satelites = 0;
int comdroprate = 60;

RTC_DATA_ATTR float roll = 0;
RTC_DATA_ATTR float pitch = 0;
float yaw = 0;
float speed = 0;
RTC_DATA_ATTR float heading = 0;
int rangefinder1 = 0;
int rangefinder2 = 0;


float navbearing = 0;
float wpdist = 0;
float xtrackerror = 0;

int FCHB = 0;
int GSHB = 0;


int servo1 = 0;
int servo2 = 0;
int servo3 = 0;


mavlink_message_t         receivedMsg; 
mavlink_message_t         heartbeatMsg;
mavlink_message_t         gpsMsg;
mavlink_message_t         ahrsMsg;
mavlink_message_t         paramMsg;
mavlink_message_t         rc_overMsg;
mavlink_message_t         statMsg;
mavlink_message_t         msg;
mavlink_manual_control_t  manual_control;
mavlink_set_mode_t        modee;
mavlink_heartbeat_t       heartbeat;
mavlink_status_t          mav_status;
mavlink_status_t          _mstatus;
mavlink_message_t         misReq;
mavlink_mission_item_t    misItem;
mavlink_mission_count_t   misCount;
mavlink_command_long_t    cmd_long;


float position[6];

typedef struct local_param_set
{
  char param_id[17];  ///< Onboard parameter id, terminated by NULL if the length is less than 16 human-readable chars and WITHOUT null termination (NULL) byte if the length is exactly 16 chars - applications have to provide 16+1 bytes storage if the ID is stored as string
  uint8_t param_type; ///< Onboard parameter type: see the MAV_PARAM_TYPE enum for supported data types.
  float param_value;  ///< Onboard parameter value
} local_params_type;

 //     {"ARMING_REQUIRE" , MAV_PARAM_TYPE_UINT8  , 0    },
  //    {"INITIAL_MODE"   , MAV_PARAM_TYPE_UINT8  , 0    },
  //   {"ARMING_CHECK"   , MAV_PARAM_TYPE_UINT8  , 0    },

//Set up rover Parameters
uint8_t paramCount =  2;
local_params_type local_param[2] =
    { 
      {"CRUISE_SPEED"   , MAV_PARAM_TYPE_REAL32 , 5.0  },
      {"CRUISE_THROTTLE"   , MAV_PARAM_TYPE_REAL32 , 95.0  }
/*      {"FS_THR_VALUE"   , MAV_PARAM_TYPE_INT8 , 1  },
      {"NAVL1_DAMPING"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"NAVL1_PERIOD"   , MAV_PARAM_TYPE_INT8 , 1  },
      {"SONAR_DEBOUNCE"   , MAV_PARAM_TYPE_INT8 , 1  },
      {"SONAR_TRIGGER_CM"   , MAV_PARAM_TYPE_INT8 , 1  },
      {"SONAR_TRIGGER_CM"   , MAV_PARAM_TYPE_INT8 , 1  },
      {"SONAR_TURN_TIME"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"SPEED2THR_D"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"SPEED2THR_I"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"SPEED2THR_IMAX"   , MAV_PARAM_TYPE_UINT16 , 1  },
      {"SPEED2THR_P"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"SPEED_TURN_DIST"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"SPEED_TURN_GAIN"   , MAV_PARAM_TYPE_INT8 , 1  },
      {"STEER2SRV_D"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"STEER2SRV_I"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"SPEED2THR_I"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"STEER2SRV_IMAX"   , MAV_PARAM_TYPE_UINT16 , 1  },
      {"STEER2SRV_P"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"THR_MIN"   , MAV_PARAM_TYPE_REAL32 , 1  },
      {"WP_RADIUS"   , MAV_PARAM_TYPE_REAL32 , 1  }
      */
    };


//Waypoints from GCS.
struct waypoints
{
  uint8_t wpcount;
  double lat; 
  double lon;
  double alt;
  uint8_t auto_cont;
} wpm[20];

uint8_t wpm_count = 0;
uint8_t wpm_rcvd = 0;

uint8_t wp_count;

mavlink_system_t mavlink_system;
uint8_t bufTx[MAVLINK_MAX_PACKET_LEN];
uint8_t bufRx[MAVLINK_MAX_PACKET_LEN];

#define MAV_SYS_STATUS_SENSOR_3D_GYRO 1
#define MAV_SYS_STATUS_SENSOR_3D_ACCEL 2
#define MAV_SYS_STATUS_SENSOR_3D_MAG 4
#define MAV_SYS_STATUS_GPS 32
#define MAV_SYS_STATUS_AHRS 2097152

#define MAVLINK_SENSOR_PRESENT_DEFAULT (MAV_SYS_STATUS_SENSOR_3D_GYRO | MAV_SYS_STATUS_SENSOR_3D_ACCEL | MAV_SYS_STATUS_SENSOR_3D_MAG | MAV_SYS_STATUS_AHRS | MAV_SYS_STATUS_GPS)


RTC_DATA_ATTR int wp_number;
int wp_numberold;
int wp_total;
int mission_state;
int mission_mode;

int armed;

float HDOP;
//MODE CHANGE
int mode;
int fcmode;
int fcmodein;
int fcmodeinold;

uint8_t gps_Fix = 0;
int32_t gps_Lat = 0;
int32_t gps_Long = 0;
uint16_t gps_Vel = 0;
uint16_t gps_Head = 0;
uint16_t sys_Bat = 0;
uint16_t sys_Bcur = 0;
int8_t sys_Brem = 0;

//relay control
int powerselect = 0;
int FCPOWER = 0;
int AUXPOWER = 0;
int WIFICAM = 0;
int LIDAR = 0;
int RADAR = 0;
int MAINPOWER = 0;
int MOTPOWER = 0;
int LIGHTS = 0;
int INDICATOR = 0;
int HORN = 0;
int SENSORR = 0;

//wifireconnect

DynamicJsonDocument doc(2048);


Talkie voice;
void sayNumber(long n);
Adafruit_MCP23X17 mcp;

//ESP32Time rtc;
ESP32Time rtc(-3600);  // offset in seconds GMT+1

ESPTelnet telnet;
IPAddress ip;
uint16_t ports = 23;


moonPhase moonPhase;
moonData_t moon;
char modename;
struct tm timeinfo = { 0 };

#define radpin 15

int CPM = 0;

#include "rssRead.hpp"
static rssRead rss;
const char* url = "https://www.tidetimes.co.uk/rss/ardrossan-tide-times";


String dst;

INA228 INA1(0x45);
INA228 INA2(0x44);


BH1750 lightMeter;

BME680_Class BME680;
float altitude(const int32_t press, const float seaLevel = 1013.25);


#define AS3935_ADDR 0x03
#define INDOOR 0x12
#define OUTDOOR 0xE
#define LIGHTNING_INT 0x08
#define DISTURBER_INT 0x04
#define NOISE_INT 0x01

SparkFun_AS3935 lightning(AS3935_ADDR);

byte noiseFloor = 2;
byte watchDogVal = 2;
byte spike = 2;
byte lightningThresh = 1;

// This variable holds the number representing the lightning or non-lightning
// event issued by the lightning detector.
byte intVal = 0;


DFRobot_ADS1115 ads(&Wire);


char inChar;

static const uint32_t GPSBaud = 38400;

// The TinyGPSPlus object
TinyGPSPlus gps;
unsigned long last = 0UL;



String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete



/* Coming from util.h */
#define htonl(x) (((x) << 24 & 0xFF000000UL) | ((x) << 8 & 0x00FF0000UL) | ((x) >> 8 & 0x0000FF00UL) | ((x) >> 24 & 0x000000FFUL))
#define htons(x) (((x) << 8) | (((x) >> 8) & 0xFF))

char aismsg[] = "inputString";

RTC_DATA_ATTR double nemalat;
RTC_DATA_ATTR double nemalon;
float nmeaspeed;
float nmeacourse;
int nmeasats;
float hdop;
double WPdistance;
double WPcourse;
float WPerror;
float Steering;
float WPyaw;
float PIDyaw;



static const float Xoffset = 0, Yoffset = 0;  // offsets for magnetometer readings
static float declinationAngle = -13.2;        //magnetic declination angle

Adafruit_HMC5883_Unified compass = Adafruit_HMC5883_Unified(12345);  // compass object; ID is random
float magheading;
float Kp = 0.5;      // coefficient  for proportional steering




//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp=0.2, aggKi=0.1, aggKd=0.1;
double consKp=0.01, consKi=0.05, consKd=0.1;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
