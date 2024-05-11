Wireless NMEA0183 Battery monitor
=================

The idea of the project is to build a battery charge monitor that can be installed into the power system without the need to change the existing electrical wiring. The monitor shunt is installed directly on the negative terminal of the battery and has a second pin for connecting the usual negative terminal. Thus, to install the monitor, you simply need to remove the negative terminal, install the device and return the terminal to the shunt pin.
The device transmits measured current and voltage data using the NMEA018 protocol via WiFi. This data can be displayed in any device or application that supports XDR message, such as Navmonitor or OpenCPN. A built-in web page is also implemented, which displays the current battery parameters


This data can be displayed, for example, as a widget on the Android screen. Average battery performance statistics are collected per minute and per hour. Averaged data is stored for 7 days and displayed in the form of graphs via a web page - this functionality needs improvement!

The project code is based on the code of the following projects:
https://github.com/alvra/nmea-bridge - read the annotation to understand all the capabilities of the device.
https://github.com/ttlappalainen/NMEA0183 - XDR message processing has been additionally implemented

Components:
1. Battery terminals

2. Pins for terminals

3. 100A shunt

4. ESP8266 WeMos D1 Mini V2 (ESP-12)
5. INA226 CJMCU-226 board
6. Power converter TZT MH-MINI-360
7. 3x7 breadboard, terminal block, wires

Assembling the device
  * The INA226 board has an address selection pad that must be pre-soldered. The current version of the program is configured to use address 0x45, i.e. it is necessary to solder A0 and A1 to the VCC pin. See the INA226 board datasheet for details. It is also necessary to remove resistor R100 from the board since an external shunt is used instead. The current configured board parameters are:
  * shunt 100A / voltage drop across shunt 0.75v, board address 0x45
  * The 3x7 breadboard is secured with screws directly to the shunt; simply drill holes on the board to a diameter of 4mm

Connection diagram here
https://oshwlab.com/aleck1/Nmea-Wreless-Battery-Monitor

TODO
It is necessary to completely rewrite the send_graph_page_response() function, which is responsible for displaying a web page with graphs. Now it's terrible. Charts should not use external libraries and require Internet access to display.


NMEA Wi-Fi Bridge
=================

This project allows the ESP8266 microcontroller
to be connected to your NMEA 0183 device to
broadcast NMEA sentences over Wi-Fi.

You can use it, for example, on your boat to connect your AIS
receiver to your chart plotter wirelessly.

<table>
<tr>
<td valign="top"><img src="preview/info.png"></td>
<td valign="top"><img src="preview/config.png"></td>
<td valign="top"><img src="preview/log.png"></td>
</tr>
</table>

Features

  * Almost completely configurable over Wi-Fi.
    Upload the code once; then configure away.
  * Connect to an existing Wi-Fi network
    or set up its own station.
  * Receive NMEA sentences over UDP,
    or view them live from your browser over websockets.
  * Send back NMEA sentences over UDP,
    or send them from your browser.
  * Choose the UDP transmission ip address mode;
    unicast, multicast, or broadcast.
    [Read more](#transmit-mode).
  * Features a captive portal to easily access the website.
    (Only possible when it provides Wi-Fi network itself.)
  * Allows setting a mDNS hostname
    to reach the device by name
    instead of only by ip address.
  * Uses a separate hardware serial TX port for debug output.
    By default, the one connected to usb is used for easy debugging.
  * The onboard LED signals the Wi-Fi status
    so you have an idea what's going on.


Quickstart
----------

This project was designed to require no configuration in software
for the ESP8266, just flash it and connect to the NMEA device.
Other devices require you first define the serial (UART) pins.
All further configuration (including network settings)
can be updated at any time over Wi-Fi using your browser.


### Wiring

The bridge connects to your NMEA device
using a hardware UART (serial) port.
The ESP8266 has two such ports (`Serial` and `Serial1` in the code),
although the second one only supports sending — not receiving.
By default, the first one is used to
receive NMEA data to be sent to the NMEA device
and send out debug output,
while the second port is used to receive sentences from the NMEA device.
Note that the first serial port is usually connected via USB.
The use of ports can be changed in the code.

|Device     | Receive NMEA | Send NMEA | Send debug |
|-----------|--------------|-----------|------------|
|ESP8266    | UART1 Tx 1   | UART0 Rx  | UART0 Tx   |
|NodeMCU v3 | D4           | RX        | TX         |

Most NMEA devices output RS-422 serial
with two lines per unidirectional connection
(For example: Tx- and Tx+).
Although you might be able to safely interface
directly with a microcontroller operating at TTL voltages
in some cases
([details](https://electronics.stackexchange.com/questions/405825/connect-rs422-interface-with-arduino-uno)),
the best solution is undoubtably to go through a logic level converter.

An inexpensive converter based on the MAX490 chip has been found to work well.
Connect it as follows to the microcontroller running the bridge
on one side and the NMEA device on the other.

| MAX490 |   bridge |
|--------|----------|
| RSD    |  receive |
| TXD    | transmit |

| MAX490 | NMEA device |
|--------|-------------|
|      B | Tx+         |
|      A | Tx-         |
|      Z | Rx+         |
|      Y | Rx-         |


### Uploading

When uploading the software to the microcontroller,
by default the flash memory that contains the configuration is erased.
If you're uploading for the first time, this is a good thing
because it causes the default configuration to be used.
However, if you've change the configuration later on,
you might want to disable erasure to retain your changes
(Arduino IDE: Tools > Erase Flash > Only Sketch).

If you're not erasing the flash on the first upload,
you might end up with random settings bases on what was stored previously.
This can prevent you from connecting to the device
because, for example, the Wi-Fi password is some unknown value.

In this case, you can reset the configuration
back to default by holding the reset-button after startup.
The onboard LED will start to blink rapidly.
After one second, the LED wil stay solidly on.
You can release the botton now
as the config has been successfully reset.


### Connecting

Assuming the default settings have been loaded
by one of the above described methods,
the bridge will create a Wi-Fi network
named "NMEA Bridge" with password "nmeabridgeesp8266".

If you connect to this Wi-Fi network,
your browser will hopefully notice the captive portal
and ask you to "sign in" to the Wi-Fi network.
This will guide you to the configuration page.

Otherwise, you can reach the page using the mDNS hostname
[nmea_bridge.local](http://nmea_bridge.local/) or by ip address
[10.1.1.1](http://10.1.1.1/).


### Configuring

The main page gives an overview of the configuration
that it's currently using.
The config page list all settings and their currently stored values.
Most changes here go live immediately.
Only changes to the Wi-Fi settings or ip address requires a restart.
In this case, a notice on the overview page will remind you
why the values displayed there are different from the current config.

Use the log page to check if NMEA sentences are correctly received.
For example, if the log shows some unintellible text being received
you might need to update the receive baudrate setting.
Consult the documentation for the NMEA device to find
what value to use.


Configuration
=============

Below is a description of each configuration setting
and the meaning of its values.


Wi-Fi mode
----------

Choose "Station" to connect to an existing Wi-Fi network,
or "Access Point" to create a new Wi-Fi network.


Wi-Fi SSID & Password
---------------------

Enter the name and password of the Wi-Fi network.
In station mode, this is the name and password of the Wi-Fi network
that the bridge should connect to.
In access point mode, this will be of the new network that is created.


IP Adress
---------

Enter a static IP address for the bridge,
so you always know what address to reach it at.

Leave this empty to get an address through DHCP
in station mode.
Note that, in this case, reaching the bridge over UDP
requires using either mDNS or a broadcast mode other than unicast.


mDNS Hostname
-------------

Enter a name for your bridge to reach it using mDNS.
For example, set it to "my_nmea_bridge" to access it
in the local network at "my_nmea_bridge.local"
on devices that support mDNS.

Leave this empty to disable mDNS support.


Transmit Mode
-------------

This setting allows you to specify how
sentences received from the NMEA device
are transmitted on the network.


### Unicast

Send sentences to a single IP address.

Since this means only a single device will receive the data
and requires it's IP address to be a known constant,
its the least flexible option.
It is however the simplest option that should be supported
on all platforms that can receive NMEA sentences over UDP.


### Multicast

Send sentences to a multicast address.

A multicast address is a special type of IP address
that devices can subscribe to in order to receive
*all* messages sent to the address.
As such, it allows a single sender (ie. the nmea bridge)
to transmit sentences to any number of recipients.

If you want to receive the data on multiple devices
that all support multicast, this is an excellent option
to avoid the need for a relay.

This option also solves the issue of having to hardcode
the recipient IP address.
You still need to choose a constant multicast address,
but the recipient's address becomes a variable.

Again, use of this option will depend
on the recipients support for it.


### Broadcast

Send sentences on the local networks broadcast address.

A broadcast address is a single address
on the local network to which all connected devices
are subscribed.

This option is simliar to multicast mode
in that it avoids the need for known constant
ip addresses
and enables multiple recipients.

Although it seems to be somewhat better supported that multicast mode,
it might be less efficient since it requires transmission
to all devices in the local network.


UDP Transmit Address
--------------------

The IP address to transmit NMEA sentences too.
The interpretation of this setting
depends on the transmit mode.

In unicast mode, its the IP address
of the single recipient of data.

In multicast mode,
it must be a valid multicast IP address
(224.0.0.0 through 239.255.255.255,
 although some addresses are reserved).
Recipients must subscribe to this same address
to receive the data.

In broadcast mode,
the special value of 255.255.255.255
indicates the use of this address;
the local network broadcast address.
Any other value is ignored,
and causes the subnet specific broadcast address to be used.

Note that this mode does not support IPv6.



UDP Transmit Port
-----------------

The UDP port to transmit NMEA sentences to.


UDP Receive Port
----------------

The UDP port that the bridge will listen at for UDP sentences.


Receive Baudrate
----------------

The baudrate for the UART (serial) port
at which NMEA sentences are received.

Refer to the NMEA device's documentation
for the exact value to use.
Typically 4800 is used,
although many AIS devices use 38400.

If the wrong value is set,
unintellible data is received.


Transmit Baudrate
-----------------

The baudrate for the UART (serial) port
at which NMEA sentences are transmitted.

Refer to the NMEA device's documentation
for the exact value to use.
Typically 4800 is used.

If the wrong value is set,
unintellible data is received.
