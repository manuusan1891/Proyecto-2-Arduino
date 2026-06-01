const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const fs = require('fs');

// Ruta de almacenamiento
const RUTA_JSON = 'C:/proyecto_sensor/datos.json';

// ⚠️ MODIFICÁ ACÁ: Poné el puerto COM real que te dé el IDE de Arduino (ej: COM5)
const PUERTO_ARDUINO = 'COM5'; 

const port = new SerialPort({
  path: PUERTO_ARDUINO,
  baudRate: 9600,
});

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

console.log(`=== Servidor Node.js Iniciado ===`);
console.log(`Escuchando al Arduino en el puerto ${PUERTO_ARDUINO}...`);
console.log(`Guardando lecturas cada 5 minutos. No cierres esta ventana.\n`);

parser.on('data', (linea) => {
  try {
    // 1. Parsear el JSON enviado por el Arduino
    const datosArduino = JSON.parse(linea);

    // 2. Capturar la hora local del sistema
    const ahora = new Date();
    const horaFormateada = ahora.toLocaleTimeString('es-UY', { hour: '2-digit', minute: '2-digit' });

    // 3. Crear la estructura del registro
    const nuevoRegistro = {
      hora: horaFormateada,
      temperatura: datosArduino.temperatura,
      humSuelo: datosArduino.humSuelo,
      humAmbiente: datosArduino.humAmbiente
    };

    // 4. Leer el JSON, añadir el nuevo elemento y volver a escribir
    fs.readFile(RUTA_JSON, 'utf8', (err, contenido) => {
      let listaDatos = [];
      
      if (!err && contenido.trim()) {
        try {
          listaDatos = JSON.parse(contenido);
        } catch (e) {
          listaDatos = []; // Si el archivo está corrupto o vacío, inicia una lista limpia
        }
      }

      listaDatos.push(nuevoRegistro);

      // Deja un máximo de 30 registros en pantalla para mantener el histórico estético
      if (listaDatos.length > 30) listaDatos.shift();

      fs.writeFile(RUTA_JSON, JSON.stringify(listaDatos, null, 2), (err) => {
        if (err) {
          console.error("❌ Error al escribir en datos.json:", err.message);
        } else {
          console.log(`✅ ¡Dato Guardado! [${horaFormateada}] -> Temp: ${nuevoRegistro.temperatura}°C | Hum. Amb: ${nuevoRegistro.humAmbiente}% | Hum. Suelo: ${nuevoRegistro.humSuelo}%`);
        }
      });
    });

  } catch (error) {
    // Ignora interferencias o líneas incompletas al conectar el cable USB
  }
});