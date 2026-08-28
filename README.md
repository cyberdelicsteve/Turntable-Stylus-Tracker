<h1>Turntable Stylus Tracker</h1>

 ### [YouTube Demonstration](Coming Soon)

<h2>Description</h2>
This is a turntable stylus tracker that I have designed to track hours used on a cartridge. This projects aims to be a beginnner DIY project that anyone can build for about $20 since there are currently no commercially available options.
<br />


<h2>Utilities Used</h2>

- <b>Arduino IDE</b> 

<h2>Parts Used </h2>
These are NOT affiliate links, just a link to where I purchased each part.<br />
Feel free to find your own, but check the dimensions and compatability, you assume the risk of making your own edits. <br />

- <b>[Arduino Nano](https://www.ebay.com/itm/196416785218)</b>
- <b>[SSD1306 1" OLED display](https://www.amazon.com/dp/B0F5WPZJ92)</b>
- <b>[2x Momentary Push Buttons (12mm diameter)](https://www.ebay.com/itm/389467741599)</b>
- <b>22AWG Wire (x4)</b>
- <b>5v USB-C cable</b>

<h2>Project walk-through:</h2>

<p align="center">
Initial setup <br />
Plug in the Arduino Nano to a computer via USB, and using the Arduino IDE, copy the code to the Arduino.
<br />
<br />
Wiring diagram:  <br/>
Solder the following connections:<br />
Arduino Side > OLED Side<br />
 5v > VCC<br />
 GND > GND<br />
 A4 > SDA<br />
 A5 > SCL<br />
<br />
Arduino Side > Buttons<br />
 GND > Both Negatives(-) on buttons<br />
 D2 > Button 1 Positive(+)<br />
 D3 > Button 2 Positive(+)<br />
<br />
<br />
Visual Wiring Diagram: <br/>
<img src="https://github.com/cyberdelicsteve/Turntable-Stylus-Tracker/blob/main/stylus-timer-wiring-diagram.jpg" height="80%" width="80%" alt="Wiring-Diagram"/>
<br />
<br />
 <h2>Troubleshooting</h2>
 <h3>Arduino Nano does not power on.</h3>
 Check to make sure your power supply and USB cable are working properly.<br />
 Ensure that the USB cable is seated properly, the Arduino should have a red status LED.<br />
 If you are sure it is getting power, it could be a bad board, or you could have bridged one of the joints with solder. Check all connections with a meter, and if it is indeed the board, contact the seller for a refund.<br />
 <br />
 <h3>Arduino Powers on, but nothing on the OLED display</h3>
 This is one of the more tricky ones. The first time I prototyped this, I actually had a DOA OLED display and did a lot of troubleshooting, so I know most of the things to check.<br />
 To rule out any wiring issues, check to make sure none of your connections are bridged, and there are no cold joints. Meter for continuity across the connections.<br />
 Check to make sure there is voltage suplied to the VCC and GND, it should show about 5v (I get about 5.2v on mine).<br />
 Make sure SDA and SCL are not crossed, sometimes these OLEDS are manufactured differently, so always check the printed labels on the board.<br />
 On the back of the board there should be a resistor that bridges the pads for 0x3C, make sure it is set to that, and not 0x3D otherwise you will have to edit the code.<br />
 There is an included screen test code in the files, if you are not able to get visuals on the OLED, upload the screen test code instead, run it, and see what the console says. It will check for the presence of I2C devices, and if it sees it, then you have an issue elsewhere. If it can't see it, then you might have a dead board or crossed wires.<br />
 <br />
 There are many errors that could arise, start by checking your wiring. Ensure that all solder connections are solid and  there is no joints touching.<br />
 I have a list of possible issues, but I will organize them before adding them here, please wait.<br />
</p>

<!--
 ```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```
--!>
