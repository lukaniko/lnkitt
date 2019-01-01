# LN K.I.T.T. 
LN K.I.T.T. lights effects for nodeMCU (arduino IDE code) with effects and wifi android app
It's a project to recreate the Knight Rider K.I.T.T lights effect in front of the Supercar.

What do you need:<br>

1 - A nodeMCU ESP8266 or ESP12E<br>
2 - A breadboard or PCB<br>
3 - 8 Led<br>
4 - A 1000 Ohm resistor<br>
5 - Arduino IDE program with ESP8266 libraryes<br>
6 - USB cable<br>

How to proceed:<br>

1 - Prepare the nodeMCU on a breadboard or PCB and made the circuit. (see the circuit section)<br>
2 - Install the Arduino IDE, download here : https://www.arduino.cc/en/Main/Software <br>
3 - Follow the tutorial to install the ESP8266 libraryes : https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/<br>
4 - Connect the nodeMCU to the pc with the USB cable <br>
5 - Check and set the COM port where the nodeMCU is connected under TOOLS -> Port <br>
6 - Load the lnkitt-wifi-xxx.ino into the Arduino IDE program <br>
7 - Upload the Sketch to the nodeMCU <br>
8 - Now you can download and install the lnkitt-wifi-xxx.apk into your android smarthphone<br> (must remove the google apps restriction)<br>
9 - Turn on the smartphone wifi, scan and find the ESPxxxx access point and connect to this<br>
10 - Open the lnkitt app. you can find some type of effects and you can change the speed (N.B. lower value = speed faster)<br>

The Circuit:<br>

Led from 1 to 8,are connected to the pins D0,D1,D2,D3,D5,D6,D7,D8 intended like positive 3 volts <br>
Ground is common connected with a 1000 ohm resistor for all LED. <br>
In case 2 or more led are simultaneously turned on, we have an attenuation. To avoid this, you must use eight resistor,one for each led connected to the negative<br>


Roadmap:

1 - Add more effects <br>
2 - Add more features to the app <br>
3 - Made a circuit able to drive big led or lamps, using the 12 volts on car<br>

Special Thanks! <br>

Paolo Esposto for the great help to develope the code. <br>


<p align="center">
  <img src="https://github.com/lukaniko/lnkitt/blob/master/Android-APP-Screenshot-1.jpg" width="350" title="">
  <img src="https://github.com/lukaniko/lnkitt/blob/master/Android-APP-Screenshot-2.jpg" width="350" alt="">
</p>
