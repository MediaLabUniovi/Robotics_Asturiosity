
// --------------------------------------------------------- WEBSOCKET ---------------------------------------------------------

// Crear una instancia de WebSocket
const socket = new WebSocket('ws://localhost:8080');

// Manejar la apertura de la conexión WebSocket
socket.addEventListener('open', function (event) {
  console.log('Conexión WebSocket establecida');
});

// Manejar errores de WebSocket
socket.addEventListener('error', function (event) {
  console.error('Error en la conexión WebSocket:', event);
});

// Manejar cierre de la conexión WebSocket
socket.addEventListener('close', function (event) {
  console.log('Conexión WebSocket cerrada');
});

// --------------------------------------------------------- MENSAJES WEBSOCKET ENTRANTES ---------------------------------------------------------

socket.onmessage = function (event) {
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
      left: '25%'
    },
    mode: "static",   // 'dynamic', 'static' or 'semi'
    color: "white"
};

// Crear el joystick usando NippleJS
var opCamera = {
    zone: document.getElementById('joyCamera'),
    position: {       // preset position for 'static' mode
      top: '65%',
      left: '75%'
    },
    mode: "static",   // 'dynamic', 'static' or 'semi'
    color: "white",
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
    socket.send(message);
});
// Escuchar el evento 'end' del joystick
joyMove.on('end', (evt, data) => {
    const message = JSON.stringify({ speed: 0, steer: 0 });
    socket.send(message);
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
    socket.send(message);
});

// Escuchar el evento 'end' del joystick
joyCamera.on('end', (evt, data) => {
    const message = JSON.stringify({ cam1: 0, cam2: 0 });
    socket.send(message);
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
  socket.send(message);
  armBtn.style.display = 'none';

});

// Agrega un controlador de eventos de clic al botón
disarmBtn.addEventListener('click', () => {
    
    armBtn.style.display = 'block';
    const message = JSON.stringify({
      arm: 0,
      });
  
    // Envía el mensaje a través del WebSocket
    socket.send(message);
    disarmBtn.style.display = 'none';
  
  });



