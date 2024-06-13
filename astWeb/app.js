const WebSocket = require('ws');
const express = require('express');
const http = require('http');
const path = require('path');
const fs = require('fs');
const { spawn } = require('child_process');

const {SerialPort} = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline')
const Readline = require('@serialport/parser-readline');

// Crear una instancia de la aplicación Express
const app = express();

// Crear un servidor HTTP utilizando Express
const server = http.createServer(app);


  const puertoSerial = new SerialPort({
  path: "/dev/ttyACM0",
  baudRate:115200
});



// Escuchar datos del puerto serial
/*puertoSerial.on('data', function(data) {
  console.log('Datos recibidos:', data.toString());
});*/

const wsData = new WebSocket.Server({ noServer: true });
const wsvideo = new WebSocket.Server({ noServer: true });

server.on('upgrade', function upgrade(request, socket, head) {
  const pathname = new URL(request.url, `http://${request.headers.host}`).pathname;

  if (pathname === '/video') {
    wsvideo.handleUpgrade(request, socket, head, function done(ws) {
      wsvideo.emit('connection', ws, request);
    });
  } else if (pathname === '/data') {
    wsData.handleUpgrade(request, socket, head, function done(ws) {
      wsData.emit('connection', ws, request);
    });
  } else {
    socket.destroy();
  }
});


// Variables de control
let speed = 0;
let direcccion = 0;
let steer = 0;
let arm = 0;
let cam1 = 0;
let cam2 = 0;

const parser = puertoSerial.pipe(new ReadlineParser({ delimiter: '\r\n' }))


function startStreaming(ws) {
  const ffmpeg = spawn('ffmpeg.exe', [
    '-f', 'dshow',                       // Formato de captura de vídeo para dispositivos DirectShow en Windows
    '-i', 'video=OBS Virtual Camera',    // Especificar el dispositivo de entrada
    '-f', 'mjpeg',                       // Formato de salida MJPEG
    '-q:v', '5',                         // Calidad del vídeo
    '-s', '640x480',                     // Resolución del vídeo
    '-r', '30',                          // Framerate de 30 fps
    '-rtbufsize', '5000000',             // Tamaño del buffer en tiempo real
    '-'                                  // Envía el output a stdout
], {
      stdio: ['ignore', 'pipe', 'ignore']
  });

  ffmpeg.stdout.on('data', (data) => {
      // Enviar datos de vídeo al cliente mediante WebSocket
      ws.send(data, { binary: true });
  });

  ws.on('close', () => {
      // Terminar el proceso de FFmpeg cuando el cliente se desconecte
      ffmpeg.kill('SIGINT');
  });
}


wsvideo.on('connection', function connection(ws){
  startStreaming(ws);
});

// Manejar la conexión WebSocket entrante
wsData.on('connection', function connection(ws) {
  console.log('Cliente conectado');
  

  // Manejar los mensajes entrantes desde el cliente
  ws.on('message', function incoming(message) {
    
    //console.log('Mensaje recibido desde el cliente:', message);
    let data;
    try {
      data = JSON.parse(message);

      // Actualizar variables según los valores recibidos
      if (data.hasOwnProperty('speed')) {
        speed = data.speed;
        if(speed<0){
          speed=-speed;
          direcccion=1;
        } else{
          direcccion=0;
        }
      }
      if (data.hasOwnProperty('steer')) {
        steer = data.steer;
        steer+=100;
      }
      if (data.hasOwnProperty('arm')) {
        arm = data.arm;
      }
      if (data.hasOwnProperty('cam1')) {
        cam1 = data.cam1;
      }
      if (data.hasOwnProperty('cam2')) {
        cam2 = data.cam2;
      }

      
      console.log('speed:', speed);
      console.log('steer:', steer);
      console.log('arm:', arm);
      console.log('cam1:', cam1);
      console.log('cam2:', cam2);
      let send_serial=`${speed}-${direcccion}-${steer}`;  //String para enviar al arduino

    } catch (error) {
      console.error('Error al analizar el mensaje:', error);
    }
    // Escribir el mensaje en el puerto serial
    puertoSerial.write(send_serial, (err) => {
      if (err) {
        return console.log('Error al escribir en el puerto serial:', err.message);
      }
      console.log('Datos enviados al puerto serial:', message);
    });
  });

  /* ------------------- DESCOMENTAR ------------------------
  parser.on('data', data => {
    console.log('Datos recibidos del puerto serial:', data);
      // Enviar datos al cliente
    ws.send(JSON.stringify({ battery: data }));
  });
  -----------------------------------------------------------*/



  // Manejar el cierre de la conexión WebSocket
  ws.on('close', function close() {
    console.log('Cliente desconectado');
  });
});

// Servir archivos estáticos desde el directorio 'public'
app.use(express.static('public'));

// Servir Bootstrap desde una ruta específica
app.use('/bootstrap', express.static(path.join(__dirname, 'node_modules', 'bootstrap', 'dist')));
// Servir chart desde una ruta específica
app.use('/chart', express.static(path.join(__dirname, 'node_modules', 'chart.js', 'dist')));


// Iniciar el servidor HTTP
const PORT = process.env.PORT || 8080;
server.listen(PORT, () => {
  console.log(`Servidor HTTP escuchando en el puerto ${PORT}`);
});
