#include <Servo.h>
#include <TimeLib.h>
#include <RTClib.h>
#include <math.h>
#include "star_data.h"
#include <Wire.h>
#include <RTClib.h>
#include <VarSpeedServo.h>

// RTC_DS3231 (Time module) instance creation
RTC_DS3231 rtc;

time_t getUnixTime() {
  DateTime now = rtc.now();
  return now.unixtime();
}

// Define servo motors with VarSpeedServo library
VarSpeedServo motor1;
VarSpeedServo motor2;
VarSpeedServo motor3;

// Define pins
const int motor1Pin = 9;
const int motor2Pin = 10;
const int motor3Pin = 11;

// Observer location
const float observerLatitude = 45.0956;
const float observerLongitude = -72.6093;

// Track for 1 hour (3600 seconds)
const int trackingDuration = 3600;

// Function to convert equatorial coordinates to servo angles
void equatorialToServo(float rightAscension, float declination, int& motor1Angle, int& motor2Angle) {
  // Get local sidereal time
  time_t currentTime = now();
  float localSiderealTime = (observerLongitude / 15.0) + (currentTime % 86400) * (360.0 / 86400.0);

  // Calculate hour angle
  float hourAngle = localSiderealTime - rightAscension;

  // Convert to radians
  float latitudeRad = radians(observerLatitude);
  float declinationRad = radians(declination);
  float hourAngleRad = radians(hourAngle);

  // Calculate altitude and azimuth
  float altitude = asin(sin(latitudeRad) * sin(declinationRad) + cos(latitudeRad) * cos(declinationRad) * cos(hourAngleRad));
  float azimuth = acos((sin(declinationRad) - sin(latitudeRad) * sin(altitude)) / (cos(latitudeRad) * cos(altitude)));

  // Convert altitude and azimuth to servo angles
  motor1Angle = map(altitude, -1.57, 1.57, 0, 180);
  motor2Angle = map(azimuth, 0, 6.28, 0, 360);
}

void setup() {

  // Set up serial communication
  Serial.begin(9600);

  // Initialize servos
  motor1.attach(motor1Pin);
  motor2.attach(motor2Pin);
  motor3.attach(motor3Pin);

  // Initialize the I2C bus (Wire library)
  Wire.begin();

  // Initialize the RTC module
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Check if the RTC is running, if not, set the time
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // rtc.adjust(DateTime(2023, 4, 2, 12, 0, 0)); // Eventual manual set the date and time to April 2, 2023, 12:00:00

  // Set the Time library's time provider to use the RTC module
  setSyncProvider(getUnixTime);
  setSyncInterval(300); // Sync every 5 minutes (300 seconds)

  // Set initial servo positions
  motor1.write(90);
  motor2.write(90);
  motor3.write(90);
}

void loop() {

  // Get current date and time
  time_t currentTime = now();

  // Check if data is available from the serial connection
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int separatorIndex1 = data.indexOf(",");
    int separatorIndex2 = data.indexOf(",", separatorIndex1 + 1);
    int separatorIndex3 = data.indexOf(",", separatorIndex2 + 1);

    observerLatitude = data.substring(0, separatorIndex1).toFloat();
    observerLongitude = data.substring(separatorIndex1 + 1, separatorIndex2).toFloat();
    targetStarIndex = data.substring(separatorIndex2 + 1, separatorIndex3).toInt();
    trackingDuration = data.substring(separatorIndex3 + 1).toInt();
  }


  // Check if it's time to start tracking the target star
  if (!isTracking && currentTime >= DateTime(trackingStartYear, trackingStartMonth, trackingStartDay, trackingStartHour, trackingStartMinute, trackingStartSecond).unixtime()) {
    isTracking = true;
  } else if (isTracking && currentTime >= DateTime(trackingStartYear, trackingStartMonth, trackingStartDay, trackingStartHour, trackingStartMinute, trackingStartSecond).unixtime() + trackingDuration) {
    isTracking = false;
  }

  // If not tracking, return early
  if (!isTracking) {
    return;
  }

  // Get target star coordinates
  float rightAscension = stars[targetStarIndex].rightAscension;
  float declination = stars[targetStarIndex].declination;

  // Convert equatorial coordinates to servo angles
  int motor1Angle, motor2Angle;
  equatorialToServo(rightAscension, declination, motor1Angle, motor2Angle);

  // Move servos to the calculated angles
  int servo_speed = 30; // Adjust this value to control the servo speed
  bool smooth_movement = true;
  motor1.write(motor1Angle, servo_speed, smooth_movement);
  motor2.write(motor2Angle, servo_speed, smooth_movement);
}
