<div align="center">
  <img src="https://your-logo-link-here" alt="AstroTracker logo" width="400"/>
  <h1>AstroTracker</h1>
</div>

AstroTracker is a sophisticated star tracker system that utilizes an Arduino microcontroller to command a 3-axis servo system. This allows for precise tracking of celestial bodies for the purpose of astronomical observation.

## Features

- Input the geographical coordinates of your current location.
- Specify the index of your target star.
- Set the tracking duration for your observation session.

## Star Database

AstroTracker uses the HYG Database version 3.0 for star data. The database is maintained by David Nash and can be found [here](https://github.com/astronexus/HYG-Database).

## Hardware Requirements

- Arduino microcontroller
- 3 Servo motors
- RTC DS3231 chip for real-time clock functionality
- A sturdy structure to mount your equipment, such as a tripod, robotic arm kit, or a custom-built structure.

## Software Requirements

The AstroTracker requires the following Arduino libraries:

- [Servo](https://www.arduino.cc/reference/en/libraries/servo/) (included in Arduino IDE)
- [Time](https://github.com/PaulStoffregen/Time)
- [RTClib](https://github.com/adafruit/RTClib)
- [VarSpeedServo](https://github.com/netlabtoolkit/VarSpeedServo)

## Getting Started

1. **Setup your Arduino environment**: Make sure you have the Arduino IDE installed and you are able to upload code to your Arduino board.
2. **Install the necessary libraries**: Follow the links provided above to install each of the necessary libraries.
3. **Download and upload the AstroTracker code**: Clone this repository and upload the AstroTracker code to your Arduino board.
4. **Setup your hardware**: Connect your servo motors and RTC DS3231 chip to your Arduino board, and mount the setup on your structure.

Enjoy tracking the stars!

## License

This project is licensed under the MIT License.

