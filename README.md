LINKS : <br>
<a href="https://easyeda.com/lukaniko/ln-kitt-master-p-e-s-p-te-c">EasyEda PCB and Circuit</a>
<br>
<a href="http://ai2.appinventor.mit.edu/#4705082274873344">MIT App Inventor</a>
<br>
# LN K.I.T.T. V1.70 <br>
LN K.I.T.T. lights effects for nodeMCU (arduino IDE code) with effects, wifi and android app.
It's a project to recreate the Knight Rider K.I.T.T lights effect in front of the Supercar.

What do you need:<br>

- Arduino IDE program with ESP8266 libraryes   <a href="https://www.arduino.cc/en/Main/Software">Download-Link</a><br>
- A USB cable<br>
- A nodeMCU ESP8266<br>
- A breadboard or PCB<br>
- 8 TIP31C (or NPN transistors suited to the power you want to handle)<br>
- 2 1K Ohm resistors<br>
- 7 220 Ohm resistors<br>
- 1 LM7805 voltage regulator<br>

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

Led from 1 to 8,are connected to the pins D0(GPIO16),D1(GPIO5),D2(GPIO4),D4(GPIO2),D5(GPIO14),D6(GPIO12),D7(GPIO13),D8(GPIO15) intended like positive 3 volts <br>
<img src="https://github.com/lukaniko/lnkitt/blob/master/nodemcu8266.png" width="200" alt=""><br>

Roadmap:

1 - Add more effects <br>
2 - Add more features to the app <br>
3 - Made a circuit able to drive big led or lamps, using the 12 volts on car /  <font color="red">DONE 25/05/2019</font><br>

Special Thanks! <br>
<font color="red">Paolo Esposto for the great help to develope code and hardware issues.</font><br>
Project developed by P.E.S.P.TE.C. Progettazione e sviluppo Progetti tecnologici condivisi<br><br>
<p align="center">
  <img src="https://github.com/lukaniko/lnkitt/blob/master/breadboard-1.jpg" width="300" alt="">
  <img src="https://github.com/lukaniko/lnkitt/blob/master/step1.jpg" width="300" alt="">
  <img src="https://github.com/lukaniko/lnkitt/blob/master/step2.jpg" width="300" alt=""><br>
  <img src="https://github.com/lukaniko/lnkitt/blob/master/step3.jpg" width="300" alt="">
  <img src="https://github.com/lukaniko/lnkitt/blob/master/step4.jpg" width="300" alt="">
  <img src="https://github.com/lukaniko/lnkitt/blob/master/Android-APP-Screenshot-1.jpg" width="300" title="">
  <img src="https://github.com/lukaniko/lnkitt/blob/master/Android-APP-Screenshot-2.jpg" width="300" alt="">
  <br>
</p>
