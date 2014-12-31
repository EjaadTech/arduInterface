arduInterface
==============

a Qt based GUI to visualize data coming from an Arduino - cause SerialTerminal just wasn't enough

Features:
- Data items separated by COMMAs
- Different packets separated by lines (\r\n)
- Arduino Nano ATMEGA328p being used as Test Device
- Scans Serial Port and Opens at 9600
- Shows Analog Data 8 inputs on vertical Sliders
- Shows Serial Data in a PlainTextBox
- ~~Shows 1x Analog Data as a Waveform~~ NOT COMPLETE

Tested on: Linux Mint Debian 16 64-bit with Qt5.4.0 vanilla install

TODO:
- ~~Add Graphs of Analog Data~~ DONE
- Parameterize Baud Rate Selection
- Send an INTEGER to Arduino to control delay in loop()
- Add Timing Info and Control(Sampling time etc) to Scope Waveform
- Qwt Tutorial or procedure, how I did it..!

Commit 001 - 12-30-14: Basic Minimum Functionality App
- Added README
- Basic Functionality App

Commit 002 - 12-31-14: Basic Scope - Wave Plot of Analog Data
- Added Arduino Code in the folder
- Installed and Added Qwt for plotting waveforms
- Single Analog Channel Shown
