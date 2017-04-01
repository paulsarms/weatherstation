var fs = require('fs');
var config = require('./config');
var path = require('path');
var appDir = path.dirname(require.main.filename);
var Regex = require("regex");

var lineReader = require('readline').createInterface({
  input: require('fs').createReadStream('data.csv')
});

lineReader.on('line', function (line) {
  console.log(line);
  var re = new RegExp(/-?\d{1,2}[.]\d\d[,]-?\d{1,2}[.]\d\d[,]\d{1,2}[.]\d\d[,]\d{5,6}[.]\d\d[,]?\d{1,7}[,]?\d{1,7}[,]?\d{1,6}[.]\d\d[,]\d{1,2}/g);
  if (re.test(line)) {
    console.log("it's grand sure");
    // Data is valid, append it to the CSV
    fs.appendFile(appDir + '/public/scrubbed.csv', line + "\n", (err) => {
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
