# Developing a ESP8266 Web Server

To breefly explain, this little project is an example of how to develop a web server with an external Arduino wifi module. <br />
Everything you need to know is written down below.

## Project explanation

I've always been interested in understanding how to create/build a home automation system for home lights on my own and i quickly realized that Arduino was the perfect solution. <br />
The way the code I am presenting you works can be summarized in this two steps: <br />
1. The ESP8266 makes itself an access point and thus creates a network that we can connect to with our phone. <br />
2. Once we are connected to the network, we just need to type the IP address of the ESP8266 (you can find it into the code) in a web browser to have access to the control panel of the lights. <br />
Keep in mind this is a really basic example and its only purpose is to understand how to create a domotic system. That is also why the web page I created is so simple and static. <br />
Feel free to modify the code as you like in order to add new features to the page. For example a control panel for a temperature and humidity sensor. <br />

## Get Started and References

If you don't know what Arduino is: https://docs.arduino.cc/ <br />
This is a simple and effective guide I followed that helped me a lot to get everything working: https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/ <br />
For reference, my ESP8266 was recognized by the Arduino IDE as "NodeMCU (ESP-12E Module)".