void Calculate_Sun_Position(int hour, int minute, int second, int day, int month, int year) {

  float Lon = (nemalon * DEG_TO_RAD);
  float Lat = (nemalat * DEG_TO_RAD);
  float T, JDate_frac, L0, M, e, C, L_true, f, R, GrHrAngle, Obl, RA, Decl, HrAngle;
  long JDate, JDx;
  int zone = 0;  //Unused variable but retained for continuity
  JDate = JulianDate(year, month, day);
  JDate_frac = (hour + minute / 60. + second / 3600.0) / 24.0 - 0.5;
  T = JDate - 2451545;
  T = (T + JDate_frac) / 36525.0;
  L0 = DEG_TO_RAD * fmod(280.46645 + 36000.76983 * T, 360);
  M = DEG_TO_RAD * fmod(357.5291 + 35999.0503 * T, 360);
  e = 0.016708617 - 0.000042037 * T;
  C = DEG_TO_RAD * ((1.9146 - 0.004847 * T) * sin(M) + (0.019993 - 0.000101 * T) * sin(2 * M) + 0.00029 * sin(3 * M));
  f = M + C;
  Obl = DEG_TO_RAD * (23 + 26 / 60.0 + 21.448 / 3600. - 46.815 / 3600 * T);
  JDx = JDate - 2451545;
  GrHrAngle = 280.46061837 + (360 * JDx) % 360 + 0.98564736629 * JDx + 360.98564736629 * JDate_frac;
  GrHrAngle = fmod(GrHrAngle, 360.0);
  L_true = fmod(C + L0, 2 * PI);
  R = 1.000001018 * (1 - e * e) / (1 + e * cos(f));
  RA = atan2(sin(L_true) * cos(Obl), cos(L_true));
  Decl = asin(sin(Obl) * sin(L_true));
  HrAngle = DEG_TO_RAD * GrHrAngle + Lon - RA;
  elevation = asin(sin(Lat) * sin(Decl) + cos(Lat) * (cos(Decl) * cos(HrAngle)));
  azimuth = PI + atan2(sin(HrAngle), cos(HrAngle) * sin(Lat) - tan(Decl) * cos(Lat));  // Azimuth measured east from north, so 0 degrees is North
  sun_azimuth = azimuth / DEG_TO_RAD;
  sun_elevation = elevation / DEG_TO_RAD;
 
  telnet.println(String(elevation / DEG_TO_RAD, 0) + "\t\t" + String(azimuth / DEG_TO_RAD, 0));
}

long JulianDate(int year, int month, int day) {
  long JDate;
  int A, B;
  if (month <= 2) {
    year--;
    month += 12;
  }
  A = year / 100;
  B = 2 - A + A / 4;
  JDate = (long)(365.25 * (year + 4716)) + (int)(30.6001 * (month + 1)) + day + B - 1524;
  return JDate;
}

void Calculate_Moon_Position() {
  getLocalTime( &timeinfo );
  telnet.print( asctime( &timeinfo ) );

  moon = moonPhase.getPhase();

  telnet.print( "Moon phase angle: " );
  telnet.print( moon.angle );                       // angle is a integer between 0-360
  telnet.print( " degrees. Moon surface lit: " );
  telnet.printf( "%f%%\n", moon.percentLit * 100 ); // percentLit is a real between 0-1
  telnet.println();
  delay(1000);
}


void TIDE(){
    dst = rss.finds(String("High Tide"));
    if (!dst.length()) ;
    telnet.printf("[s%]\n", dst.c_str());
  
  telnet.printf("<== End rssRead(%d)\n", rss.tagCnt());
}
