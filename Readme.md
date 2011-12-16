# PanicAR Framework

by doPanic - for sales and support contact azeitler@dopanic.com

## Information

Check API Reference
http://docs.dopanic.com/panicar

Check the wiki for tipps and guides on how to implement:
https://github.com/doPanic/PanicAR/wiki/

For common build errors and other issues check:
https://github.com/doPanic/PanicAR/wiki/Troubleshooting

## Demo Project

### Structure

**MyARViewControll** is a subclass of ARViewController and handles all the AR functionality.
The ViewController is embedded into a TabBarController and uses a NavigationController to add a Title Bar to the view.

### Configurations

**Debug**

- uses Debug Build of the Framework
- displays Button to switch Console on and off
- has additional debug output

**Release**

- uses Release build of the Framework
- highly optimized, no uneccessary UI and debug information