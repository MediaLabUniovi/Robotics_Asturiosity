const WebSocket = require('ws');
const express = require('express');
const http = require('http');
const path = require('path');
const fs = require('fs');

const {SerialPort} = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline')
const Readline = require('@serialport/parser-readline');

// Crear una instancia de la aplicación Express
const app = express();

// Crear un servidor HTTP utilizando Express
const server = http.createServer(app);

const puertoSerial = new SerialPort({
  path: "COM8",
  baudRate:9600
});



// Escuchar datos del puerto serial
/*puertoSerial.on('data', function(data) {
  console.log('Datos recibidos:', data.toString());
});*/

const wss = new WebSocket.Server({ server });

// Variables de control
let speed = 0;
let steer = 0;
let arm = 0;
let cam1 = 0;
let cam2 = 0;

const parser = puertoSerial.pipe(new ReadlineParser({ delimiter: '\r\n' }))

// Manejar la conexión WebSocket entrante
wss.on('connection', function connection(ws) {
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
      }
      if (data.hasOwnProperty('steer')) {
        steer = data.steer;
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

    } catch (error) {
      console.error('Error al analizar el mensaje:', error);
    }
    // Escribir el mensaje en el puerto serial
    puertoSerial.write("2", (err) => {
      if (err) {
        return console.log('Error al escribir en el puerto serial:', err.message);
      }
      console.log('Datos enviados al puerto serial:', message);
    });
  });

  parser.on('data', data => {
    console.log('Datos recibidos del puerto serial:', data);
      // Enviar datos al cliente
    ws.send(JSON.stringify({ battery: data }));
  });



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
