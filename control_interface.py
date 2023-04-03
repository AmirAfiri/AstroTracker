#Work with pyserial library
import serial
import time

# Configure your serial port settings
serial_port = 'COM3'  # Change this to your Arduino's serial port
baud_rate = 9600

# Connect to the Arduino
ser = serial.Serial(serial_port, baud_rate)
time.sleep(2)  # Wait for the serial connection to be established

# Get user input
observer_latitude = input("Enter observer's latitude: ")
observer_longitude = input("Enter observer's longitude: ")
target_star_index = input("Enter the target star index: ")
tracking_duration = input("Enter the tracking duration (seconds): ")

# Send the data to the Arduino
ser.write(f"{observer_latitude},{observer_longitude},{target_star_index},{tracking_duration}\n".encode())

ser.close()
