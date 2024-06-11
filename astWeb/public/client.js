
// --------------------------------------------------------- WEBSOCKET ---------------------------------------------------------

// Crear una instancia de WebSocket
const wsdata = new WebSocket('ws://localhost:8080/data');
const wsvideo = new WebSocket('ws://localhost:8080/video');

// Manejar la apertura de la conexión WebSocket
wsdata.addEventListener('open', function (event) {
  console.log('Conexión WebSocket establecida');
});

// Manejar errores de WebSocket
wsdata.addEventListener('error', function (event) {
  console.error('Error en la conexión WebSocket:', event);
});

// Manejar cierre de la conexión WebSocket
wsdata.addEventListener('close', function (event) {
  console.log('Conexión WebSocket cerrada');
});

// --------------------------------------------------------- MENSAJES WEBSOCKET ENTRANTES ---------------------------------------------------------
const canvas = document.getElementById('videoCanvas');
const wc = document.getElementById('webcam');
const context = canvas.getContext('2d');

wsvideo.binaryType = 'blob';

wsvideo.onmessage = function (event) {
  console.log("ws received");
  const blob = event.data;
  const img = new Image();

  // Asignar el URL del objeto al src de la imagen
  const url = URL.createObjectURL(blob);
  img.src = url;

  // Establecer el manejador onload para la imagen
  img.onload = function() {
      // Ajustar el tamaño del canvas al de la imagen
      const scaleFactor = Math.min(canvas.parentElement.clientWidth / img.width, canvas.parentElement.clientHeight / img.height);
      canvas.width = canvas.parentElement.clientWidth
      canvas.height = canvas.parentElement.clientHeight
      
      // Dibujar la imagen en el canvas
      context.drawImage(img, 0, 0, canvas.width, canvas.height);

      // Liberar la URL del objeto una vez que la imagen se ha cargado
      URL.revokeObjectURL(url);
  };}

  wsdata.onmessage = function (event) {
    const data = JSON.parse(event.data);
    
    // Verificar si el mensaje contiene un valor de batería
    if (data.battery !== undefined) {
      // Obtener el elemento de la barra de progreso
      const progressBar = document.getElementById('battery');
  
      // Actualizar el valor del atributo aria-valuenow
      progressBar.setAttribute('aria-valuenow', data.battery);
  
      // Actualizar el ancho de la barra de progreso
      progressBar.style.width = `${data.battery}%`;
  
      // Actualizar el texto dentro de la barra de progreso
      progressBar.innerText = `${data.battery}%`;
  };
}

// --------------------------------------------------------- JOYSTICKS ---------------------------------------------------------

// Crear el joystick usando NippleJS
var opMove = {
    zone: document.getElementById('joyMove'),
    position: {       // preset position for 'static' mode
      top: '65%',
      left: '22%'
    },
    mode: "static",   // 'dynamic', 'static' or 'semi'
    color: "white",
    dynamicPage: true,
};

// Crear el joystick usando NippleJS
var opCamera = {
    zone: document.getElementById('joyCamera'),
    position: {       // preset position for 'static' mode
      top: '65%',
      left: '72%'
    },
    mode: "static",   // 'dynamic', 'static' or 'semi'
    color: "white",
    dynamicPage: true,
};

var joyMove = nipplejs.create(opMove);
var joyCamera = nipplejs.create(opCamera);

// Manejar eventos del joystick
joyMove.on('move', (evt, data) => {
    // Obtener el ángulo en radianes
    const angleRad = data.angle.radian;

    // Calcular las coordenadas speed y steer
    let speed = Math.cos(angleRad);
    console.log(speed);
    let steer = Math.sin(angleRad);
    console.log(steer);

    let force = data.force;

    if (force>2){
        force=2;
    }
    
    force = force*100/2;
    speed = speed * force;
    steer = steer * force;

    // Enviar las coordenadas speed y steer a través de WebSocket
    const message = JSON.stringify({
    speed: speed,
    steer: steer,
    });
    wsdata.send(message);
});
// Escuchar el evento 'end' del joystick
joyMove.on('end', (evt, data) => {
    const message = JSON.stringify({ speed: 0, steer: 0 });
    wsdata.send(message);
});

// Manejar eventos del joystick
joyCamera.on('move', (evt, data) => {
    // Obtener el ángulo en radianes
    const angleRad = data.angle.radian;

    // Calcular las coordenadas speed y steer
    let cam1 = Math.cos(angleRad);
    console.log(cam1);
    let cam2 = Math.sin(angleRad);
    console.log(cam2);

    let force = data.force;

    if (force>2){
        force=2;
    }
    
    force = force*100/2;
    cam1 = cam1 * force;
    cam2 = cam2 * force;

    // Enviar las coordenadas speed y steer a través de WebSocket
    const message = JSON.stringify({
    cam1: cam1,
    cam2: cam2,
    });
    wsdata.send(message);
});

// Escuchar el evento 'end' del joystick
joyCamera.on('end', (evt, data) => {
    const message = JSON.stringify({ cam1: 0, cam2: 0 });
    wsdata.send(message);
});

// --------------------------------------------------------- BOTONES ---------------------------------------------------------
// Selecciona el botón por su ID
const armBtn = document.getElementById('armBtn');
const disarmBtn = document.getElementById('disarmBtn');

// Agrega un controlador de eventos de clic al botón
armBtn.addEventListener('click', () => {
    
  disarmBtn.style.display = 'block';
  const message = JSON.stringify({
    arm: 1,
    });

  // Envía el mensaje a través del WebSocket
  wsdata.send(message);
  armBtn.style.display = 'none';

});

// Agrega un controlador de eventos de clic al botón
disarmBtn.addEventListener('click', () => {
    
    armBtn.style.display = 'block';
    const message = JSON.stringify({
      arm: 0,
      });
  
    // Envía el mensaje a través del WebSocket
    wsdata.send(message);
    disarmBtn.style.display = 'none';
  
  });

  

