# kryzerbrewery
Control system for temperature in Kryzer Brewery

Code used for running a small ESP8266 or Arduino microcontroller specificanlly to display temperatures in a home brew cycle. 

##Features

In the beginning there were three temperature sensors of type xxx.  These are read using the Dallas semiconductor library

A display, likely a 4 row 20 character model, will be connected.

Power is delivered via a +5V power supply, either a wall plug or a battery.

## Roadmap

A roadmap feature will be to embed a output control mechanism to engage a heating element that can control the temperature using a PWM signal.  Most likely a SCR or solid state relay will be used to control a simple resistive heating element.

