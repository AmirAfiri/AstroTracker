# AstroTracker
AstroTracker is a star tracker using an Arduino chip to command a 3 axis servo system to track stars for observation.

It takes as input the location of the system as coordinates, the target star index and the tracking duration.

The database of stellar objects is provided by the HYG Database version 3.0 provided by David Nash. (https://github.com/astronexus/HYG-Database)


List of components :

- Arduino chip
- 3 servo motors
- RTC DS3231 chip (clock)
- Tripod or Robotic arm kit or custom built structure


Necessary libraries (Arduino) :

- Servo library (included in Arduino IDE)
- Time library (https://github.com/PaulStoffregen/Time)
- RTC library (https://github.com/adafruit/RTClib)
- VarSpeedServo (https://github.com/netlabtoolkit/VarSpeedServo)
