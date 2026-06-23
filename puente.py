import serial
import time
import requests

# CONFIGURACIÓN: Reemplazá con tu puerto COM y tu link de Firebase
# (En Windows te fijás en el Arduino IDE si es COM3, COM4, etc.)
PUERTO_SERIAL = 'COM5' 
BAUDIOS = 9600
FIREBASE_URL= "https://proyecto-arduino-11833-default-rtdb.firebaseio.com/sensores.json"

try:
    # Abrimos la comunicación con el Arduino a través del USB
    arduino = serial.Serial(PUERTO_SERIAL, BAUDIOS, timeout=1)
    time.sleep(2) # Esperamos a que el Arduino se reinicie correctamente
    print("Conectado exitosamente al Arduino en el puerto", PUERTO_SERIAL)
    
    while True:
        if arduino.in_waiting > 0:
            # Leemos la línea que manda el Arduino (el JSON)
            linea = arduino.readline().decode('utf-8').strip()
            
            # Verificamos que parezca un JSON válido
            if linea.startswith("{") and linea.endswith("}"):
                print(f"Datos recibidos del Arduino: {linea}")
                
                try:
                    # Enviamos el JSON directo a Firebase usando un PATCH HTTP
                    respuesta = requests.patch(FIREBASE_URL, data=linea)
                    if respuesta.status_code == 200:
                        print("¡Datos subidos a Firebase correctamente!")
                    else:
                        print(f"Error en Firebase: {respuesta.status_code}")
                except Exception as e:
                    print(f"Error de conexión a internet: {e}")
                    
        time.sleep(0.1) # Pausa mínima para no saturar el procesador

except KeyboardInterrupt:
    print("\nPrograma pausado por el usuario.")
except Exception as e:
    print(f"Error: No se pudo abrir el puerto {PUERTO_SERIAL}. ¿Está el Monitor Serie de Arduino abierto? Cerralo e intentalo de nuevo. Detalles: {e}")