var fs = require('fs');
var moment = require('moment');

// timestamp, temperature
if (fs.existsSync('data.csv')==false){
  fs.writeFile('data.csv', 'timestamp,temperature\n', (err) => {
  if (err) throw err;
    console.log('CSV file created');
  });
}
var data=moment().format() + "," + "data to append\n";
fs.appendFile('data.csv', data, (err) => {
  if(err) {
      return console.log(err);
  }
  console.log('The data was appended to file!');
});
