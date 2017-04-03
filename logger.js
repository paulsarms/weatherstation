var fs = require('fs');
var moment = require('moment');
var serialport = require("serialport");
var SerialPort = serialport;
var config = require('./config');
var path = require('path');
var appDir = path.dirname(require.main.filename);



module.exports = {
    start_logger: function (){
      // Make CSV file if it does exist. Use these headings:
      // timestamp, temperature... etc
      if (fs.existsSync(appDir + '/public/data.csv')==false){
        fs.writeFile(appDir + '/public/data.csv', 'timestamp,dht22_temp,bmp_180_temp,dht22_hum,bmp_180_presure\n', (err) => {
        if (err) throw err;
          console.log('CSV file created');
        });
      }
      //var serialPort = new SerialPort("/dev/ttyACM0", {
      var serialPort = new SerialPort(config.serialPort, {
        baudrate: config.baudrate,
        parser: serialport.parsers.readline("\n")
      });

      serialPort.on("open", function () {
        console.log('open');
        serialPort.on('data', function(data) {
          console.log(data);
          // for validating the data I'm using a regexp to check that:
              // temperature is between -99.99 and 99.99,
              // humidity is between 0.00 and 99.99,
              // pressure is between 5 and 6 digits for the Pascal value, with 2 decimal points
              // pm10 and pm25 between 1 and 7 digita
          var re = new RegExp("^-?\d{1,2}.\d\d,-?\d{1,2}.\d\d,\d{1,2}.\d\d,\d{5,6}.\d\d,?\d{1,7},?\d{1,7},?\d{1,6}.\d\d,?\d{1,2},");
          if (re.test(data)) {
            console.log("Data ok");
            // Data is valid, append it to the CSV
            var data=moment().format() + "," + data + "\n";
            fs.appendFile(appDir + '/public/data.csv', data, (err) => {
              if(err) {
                  return console.log(err);
              }
              console.log('The data was appended to file!');
            }); // Append new data from serialport to the CSV
          }
          else {
            // Data failed the regexp test
            console.log("Data is invalid, not saved")
            // do something... maybe email me the invalid data if it's invalid more than once in a row
          }
        });
      });
    }
};
