# Serial Data Plotter

Serial Data Plotter is a graphical user interface (GUI) application for visualizing and analyzing serial data. It provides real-time plotting capabilities for multiple data channels received from a serial port.

## Features

- Read and plot data from a specified serial port
- Support for custom frame format and counter mode
- Adjustable baud rate and data types
- Real-time updating of plots as data is received
- Pause and resume functionality
- Checksum verification for data integrity

## Requirements

- Python 3.6 or higher
- PyQt5 library
- pyqtgraph library
- pyserial library

## Usage
1. Connect serial device to the computer.
2. Open the terminal and navigate to the directory where the Serial Plot files are located.
3. Run the serial_plot python file
4. Configure the desired settings such as baud rate, number of channels, frame format, etc.
5. Click the "Start" button to begin reading and plotting the data.
6. Use the "Pause" button to temporarily pause data acquisition.
7. Use the "Resume" button to resume data acquisition after pausing.
8. Close the application by clicking the "Close" button or pressing the close button on the window.
9. To save the gui settings, click the "File" -> "Save"

## Customization
To change the checksum formula: Edit checksum_processing()

## Note
- Max Frame start length is 8 bits
- Total Frame Start Size Sent (bytes) includes the framestart byte, frame and checksum byte
- Change file path for saving settings: file_path = '~/config.ini', QSettings.IniFormat (the file will be created if does not exist)
- Change file path for saving recordings: self.directory = self.settings.value('directory', "~/directoy_file", type=str) 

## Acknowledgments

The Serial Data Plotter application is built using PyQt5, pyserial and pyqtgraph libraries, 
which provide powerful GUI and plotting capabilities for Python.
