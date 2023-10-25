# Window Shutters Controller with ESP8266

This project aims to control window shutters using an ESP8266, allowing the shutters to move up or down through a simple web interface.
I bought a standard add-on shutter winder, opend it up and added a couple of wires to the controler buttons. When short-circuiting those wires the butten is "pressed". These cables are then wired through a relay which is controlled using an ESP 12E over a webserver.  

[instagram.com/unitech.yoco](www.instagram.com/unitech.yoco)


<!-- ![Project Image](/images/shutterandesp.jpg?raw=true)   Replace 'your_image_link_here' with the link to your project's image. -->
<img src="/images/shutterandesp.jpg" alt="drawing" width="300"/>


## Description

The code provided sets up a local web server on the ESP8266 which, when accessed, provides two buttons: **UP** and **DOWN**. When pressed, these buttons control the movement of the shutters by interfacing with two relay modules. The relay modules act as switches to close the circuit for the shutter controller.

This project is based on [this guide](https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/html-buttons).

## What you need:
* 1 Automatic Tape Winder for Manual Operated Roller Shutters 
* 1 ESP [exmple](https://www.instructables.com/id/Programming-ESP8266-ESP-12E-NodeMCU-Using-Arduino-/)
* 2 Arduion Relays [example](https://arduinogetstarted.com/tutorials/arduino-relay)

## Setup

1. Connect the UP relay to the GPIO pin 14 of the ESP8266.
2. Connect the DOWN relay to the GPIO pin 12 of the ESP8266.
3. Replace `"WiFi Name"` and `"Password"` in the code with your WiFi credentials.
4. Flash the provided code to the ESP8266 using your preferred method.
5. Once the ESP8266 is powered on and running the provided code, you can access the web interface using the IP address displayed in the serial monitor.

## Style Guide

For the code style:

- The project uses the [SublimeAStyleFormatter](https://packagecontrol.io/packages/SublimeAStyleFormatter) with Sublime Text for formatting.
- The main style guide followed is based on the [UMD C Style Guide](http://www.cs.umd.edu/~nelson/classes/resources/cstyleguide/).

## Contributions

This is a beginner project, and feedback or contributions to improve the code or functionality are highly appreciated. Please feel free to suggest improvements or submit pull requests.

## License

This project is open-source and available to anyone. Use it, modify it, and distribute it as you see fit.

---

**Note**: Make sure to replace 'your_image_link_here' with the actual link or path to your project's image. If you're hosting the image directly on GitHub, you can use relative paths.
