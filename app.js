var express = require('express');
var app = express();
var fs = require('fs');
var moment = require('moment');
var serialport = require("serialport");
var SerialPort = serialport;
var config = require('./config');
var path = require('path');
var appDir = path.dirname(require.main.filename);
//public files
app.use(express.static('public'));
// Start the Server
app.get('/', function (req, res) {
   res.sendFile( __dirname + "/" + "index.htm" );
})
app.get('/test', function (req, res) {
   res.sendFile( __dirname + "/" + "test.htm" );
})

var server = app.listen(8081, function () {
   var host = server.address().address
   var port = server.address().port

   console.log("Example app listening at http://%s:%s", host, port)
})

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
    // Append new data from serialport to the CSV
    var data=moment().format() + "," + data + "\n";
    fs.appendFile(appDir + '/public/data.csv', data, (err) => {
      if(err) {
          return console.log(err);
      }
      console.log('The data was appended to file!');
    });
  });
});
