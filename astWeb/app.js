const WebSocket = require('ws');
const express = require('express');
const http = require('http');
const path = require('path');
const fs = require('fs');

// const SerialPort = require('serialport');

// Crear una instancia de la aplicación Express
const app = express();

// Crear un servidor HTTP utilizando Express
const server = http.createServer(app);

// const port = new SerialPort('com0com/CNCA0', { baudRate: 9600 });
const wss = new WebSocket.Server({ server });

// Variables de control
let speed = 0;
let steer = 0;
let arm = 0;
let cam1 = 0;
let cam2 = 0;

// Manejar la conexión WebSocket entrante
wss.on('connection', function connection(ws) {
  console.log('Cliente conectado');

  // Manejar los mensajes entrantes desde el cliente
  ws.on('message', function incoming(message) {
    
    //console.log('Mensaje recibido desde el cliente:', message);

    try {
      const data = JSON.parse(message);

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
    /*port.write(message, (err) => {
      if (err) {
        return console.log('Error al escribir en el puerto serial:', err.message);
      }
      console.log('Datos enviados al puerto serial:', message);
    });*/
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
