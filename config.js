// A file for storing config parameters

var config = {};

config.serialPort = "COM6"; //config for my windows machine
// config.serialPort = "/dev/ttyACM0";  //config for my linux machine
config.baudrate = 9600;

module.exports = config;
