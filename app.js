var express = require('express');
var app = express();
var fs = require('fs');
var moment = require('moment');
var serialport = require("serialport");
var SerialPort = serialport;
var config = require('./config');
var logger = require('./logger');
var path = require('path');
var appDir = path.dirname(require.main.filename);

process.chdir(appDir);
//public files
app.use(express.static('public'));
// Start the Server
app.get('/', function (req, res) {
   res.sendFile( __dirname + "/" + "index.htm" );
})
app.get('/test', function (req, res) {
   res.sendFile( __dirname + "/" + "test.htm" );
})
app.get('/test2', function (req, res) {
   res.sendFile( __dirname + "/" + "test2.htm" );
})

var server = app.listen(8081, function () {
   var host = server.address().address
   var port = server.address().port

   console.log("Example app listening at http://%s:%s", host, port)
})

logger.start_logger();
