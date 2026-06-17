# 🚀 Proyecto de Medición y Control con Arduino

![HTML5](https://img.shields.io/badge/html5-%23E34F26.svg?style=for-the-badge&logo=html5&logoColor=white)
![CSS3](https://img.shields.io/badge/css3-%231572B6.svg?style=for-the-badge&logo=css3&logoColor=white)
![JavaScript](https://img.shields.io/badge/javascript-%23323330.svg?style=for-the-badge&logo=javascript&logoColor=%23F7DF1E)
![NodeJS](https://img.shields.io/badge/node.js-6DA55F?style=for-the-badge&logo=node.js&logoColor=white)
![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)

Un sistema interactivo para la **medición de datos, control de variables y visualización de desplazamiento horizontal** utilizando Arduino y tecnologías web. Este repositorio contiene la interfaz y la lógica de backend necesarias para procesar y presentar los datos capturados en el entorno físico.

## 📖 Descripción del Proyecto

Este sistema fue diseñado como parte de un proyecto integrador para la carrera de Ingeniería en Informática. Su objetivo principal es obtener medidas precisas de desplazamiento horizontal a través de la instrumentación con Arduino, procesar la información obtenida y desplegarla en una interfaz web amigable y fácil de interpretar. 

El proyecto abarca desde la construcción física y el control de variables en el entorno de medición, hasta el desarrollo de la arquitectura de software que maneja y formatea los datos generados (`datos.json`).

## ✨ Características Principales

- **Medición Precisa:** Captura y lectura de datos de desplazamiento horizontal.
- **Control de Variables:** Ajustes y calibración del entorno de pruebas.
- **Interfaz Web Interactiva:** Visualización clara de los resultados de las métricas mediante HTML, CSS y JavaScript.
- **Procesamiento de Datos:** Gestión y empaquetado de la información mediante un servidor en Node.js (`app.js`).
- **Arquitectura Modular:** Separación clara entre la lógica de recolección de hardware y la presentación web.

## 🛠️ Tecnologías y Estructura

El repositorio se compone de las siguientes tecnologías:
- **Frontend:** HTML5, CSS3, JavaScript puro.
- **Backend:** Node.js.
- **Gestión de Datos:** Almacenamiento estructurado en formato JSON.

### Estructura de archivos principal:
```text
📦 Proyecto-2-Arduino
 ┣ 📜 app.js              # Archivo principal del servidor y lógica
 ┣ 📜 index.html          # Interfaz gráfica de usuario principal
 ┣ 📜 style.css           # Hoja de estilos de la aplicación
 ┣ 📜 datos.json          # Archivo de almacenamiento de mediciones
 ┣ 📜 package.json        # Dependencias y configuración del proyecto
 ┗ 📜 package-lock.json   # Árbol de dependencias bloqueado
