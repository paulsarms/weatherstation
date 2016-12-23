var serialport = require("serialport");
var SerialPort = serialport;
var fs = require('fs');

var serialPort = new SerialPort("COM6", {
  baudrate: 9600,
  parser: serialport.parsers.readline("\n")
});

serialPort.on("open", function () {
  console.log('open');
  serialPort.on('data', function(data) {
    console.log(data);
  });
});

fs.writeFile("test.txt", "Hey there!", function(err) {
    if(err) {
        return console.log(err);
    }

    console.log("The file was saved!");
});

fs.appendFile('test.txt', 'data to append', (err) => {
  if(err) {
      return console.log(err);
  }
  console.log('The "data to append" was appended to file!');
});
