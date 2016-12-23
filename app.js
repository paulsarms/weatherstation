var express = require('express');
var app = express();
var fs = require('fs');
var moment = require('moment');

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
// timestamp, temperature
if (fs.existsSync('public/data.csv')==false){
  fs.writeFile('public/data.csv', 'timestamp,temperature\n', (err) => {
  if (err) throw err;
    console.log('CSV file created');
  });
}

// Append new data from serialport to the CSV
var data=moment().format() + "," + "49\n";
fs.appendFile('public/data.csv', data, (err) => {
  if(err) {
      return console.log(err);
  }
  console.log('The data was appended to file!');
});
