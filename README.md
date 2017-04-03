# Arduino Based DIY climate station
Please note, this repo and readme is a work in progress and will be modified as the project progresses to make building a DIY climate station more accessible and user friendly. 
    
## How to use
##### 1. Make sure you have node.js
This a Node.js application. To use it you must first download and install node.js from:
https://nodejs.org/en/download/

##### 2. Download/clone the repo
After cloning this repository you might have to edit the config.js file to change the COM port or serial baudrate. 

##### 3. Start the app
Finally, from your terminal, run this command to start the app:
`node /[path_to_your_clone]/app.js`

A data.csv file will be created in /public (if it's not already there) and all incoming serial port data will be prefixed with a timestamp and appended to the data.csv file. 


