let serial;
let latestData = "Waiting for data..."; 
let brightness = 0;
let mode = 0;

function setup() {
    createCanvas(600, 400);
    serial = new p5.SerialPort();
    serial.list();
    serial.open('/dev/ttyUSB0');

    serial.on('connected', serverConnected);
    serial.on('data', serialEvent);
}

function serverConnected() {
    console.log("Connected to Arduino!");
}

function serialEvent() {
    let data = serial.readLine();
    if (data.length > 0) {
        latestData = data;
        let values = split(data, ',');
        if (values.length >= 2) {
            mode = int(values[0].split(': ')[1]);
            brightness = int(values[1].split(': ')[1]);
        }
    }
}

function draw() {
    background(220);
    
    textSize(16);
    textAlign(LEFT);
    text("LED 밝기: " + brightness, 20, 30);
    
    let r = mode === 1 ? brightness : 0;
    let y = mode === 2 ? brightness : 0;
    let g = mode === 3 ? brightness : 0;

    fill(255, 0, 0, r);
    ellipse(100, 100, 50, 50);
    fill(255, 255, 0, y);
    ellipse(100, 160, 50, 50);
    fill(0, 255, 0, g);
    ellipse(100, 220, 50, 50);

    text("Mode: " + mode, 20, 300);
}