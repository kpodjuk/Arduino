var ledState = false;
var buttonEnable = false;
var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);

document.getElementById("blinkTime").addEventListener("keyup", handleBlinkTimeChange);


connection.onopen = function () {
    connection.send('Connect ' + new Date());
};
connection.onerror = function (error) {
    console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {  
    console.log("Received message: "+e.data);
    button(e.data);
};
connection.onclose = function(){
    console.log('WebSocket connection closed');
};


function ledStateChange(){
    ledState = ! ledState;
    if(ledState){
        connection.send(1);
        document.getElementById('buttonState').style.backgroundColor = '#00878F';
        document.getElementById('buttonState').innerText = 'ON';
    } else {
        connection.send(0);
        document.getElementById('buttonState').style.backgroundColor = '#999';
        document.getElementById('buttonState').innerText = 'OFF';
    }  
}

function button(message){

    if(message.includes("BUTTON:ON")){

        document.getElementById('buttonStatus').style.backgroundColor = '#00878F';
        document.getElementById('buttonStatus').innerText  = "ON";
    }
    if(message.includes("BUTTON:OFF")){
        document.getElementById('buttonStatus').style.backgroundColor = '#999';
        document.getElementById('buttonStatus').innerText = "OFF";


    }
}

function getAndSendBlinkTime(){
}

function turnOffBlink(){
    connection.send("BO");
    document.getElementById("blinkTime").value = "";
    handleBlinkTimeChange();
}

function handleBlinkTimeChange(){
    // console.log("Current blink time: "+document.getElementById("blinkTime").value);
    value = document.getElementById('blinkTime').value;
    connection.send("BS:"+value);

    if(value != 0){
        document.getElementById('buttonOffBlink').style.backgroundColor = '#00878F';
        document.getElementById('buttonOffBlink').disabled = false;
    } else {
        document.getElementById('buttonOffBlink').style.backgroundColor = '#999';
        document.getElementById('buttonOffBlink').disabled = true;
    }



}
