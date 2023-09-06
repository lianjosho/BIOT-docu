# Palabras clave

| Nro | Palabra | Descripción |
|:---:|:---|:---|
| 1 | erase | Borra la configuración del equipo | 
| 2 | eeprom | Devuelve la configuración del equipo | 
| 3 | chequeo | Hace un chequeo de las salidas, la SD y el RTC | 
| 4 | regall | Devuelve el archivo "regall.txt" | 
| 5 | voltaje,12.05 | Setea el coeficiente de voltaje con el voltaje de la batería a 12.05 | 
| 6 | modo12 | Des/activa el modo 12 | 
| 7 | offline | Des/activa el modo offline | 
| 8 | modulo | Elimina las mediciones guardadas en la SD | 

## Requerimientos

* Equipo encendido 
* Wifi activado 
* Celular sin datos activados 
* Celular conectado a la red wifi generada por el equipo 
* App de BIOT abierta en el menú principal

## 1. Palabra clave "erase"

### Pasos

1. En el menú de la app, apretar "Configurar equipo"
2. Rellenar con los siguientes campos:
    - Nombre de la central: **erase**
    - El resto de los campos rellenar con cualquier valor
3. En el menú "configuraciones", apretar "Guardar"

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    La configuración ha sido borrada
    Configuración
    =============
    · 1) --- No config. ---
    · 2) --- No config. ---
    · 3) --- No config. ---
    · 4) --- No config. ---

## 2. Palabra clave "eeprom"

### Pasos

1. En el menú de la app, apretar "Configurar equipo"
2. Rellenar con los siguientes campos:
    - Nombre de la central: **eeprom**
    - El resto de los campos rellenar con cualquier valor
3. En el menú "configuraciones", apretar "Guardar"

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    {
      "id": "L-7BF4",
      "product": "THSST",
      "soil_type": "Arcilloso",
      "location_name": "hola",
      "location": {
        "latitude": -31.44027328,
        "longitude": -64.20404816
      },
      "sensors": {
        "00000000001": {
          "type": "the",
          "tag_depth": "10.00"
        }
      }
    }

## 3. Palabra clave "eeprom"

### Requerimientos

### Pasos

1. En el menú de la app, apretar "Configurar equipo"
2. Rellenar con los siguientes campos:
    - Nombre de la central: **eeprom**
    - El resto de los campos rellenar con cualquier valor
3. En el menú "configuraciones", apretar "Guardar"

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    {
      "id": "L-7BF4",
      "product": "THSST",
      "soil_type": "Arcilloso",
      "location_name": "hola",
      "location": {
        "latitude": -31.44027328,
        "longitude": -64.20404816
      },
      "sensors": {
        "00000000001": {
          "type": "the",
          "tag_depth": "10.00"
        }
      }
    }

## 4. Palabra clave "chequeo"

### Pasos

1. Repetir paso anterior con:
    - Nombre de la central: **chequeo**

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Chequeo:
    ========
    - Tarjeta SD: ok
    - Reloj externo: ok
    - Salidas:
     · 1) ok
     · 2) FALLÓ
     · 3) No configurado
     · 4) No configurado
    - Modo 12: Sí
    - Modo offline: Sí
    - Mediciones guardadas: 5

## 4. Palabra clave "regall"

### Pasos

1. Repetir paso anterior con:
    - Nombre de la central: **regall**

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    [
        {json_measure_0},
        {json_measure_1},
        {json_measure_2},
        ...,
        {json_measure_n-1}
    ]
 
_Nota_: esta prueba se la debe hacer con un programa como el Packet Sender o el Insomnia, porque el pop-up de la app no alcanza a mostrar un archivo tan grande.

## 5. Palabra clave "voltaje",12.05" 

### Pasos

1. Repetir paso anterior con:
    - Nombre de la central: **voltaje,12.05**

Nota: 12,05 es el voltaje de batería medido del equipo.

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Coeficiente de voltaje seteado en <x>
 
Donde _&lt;x&gt;_ es el valor del coeficiente de voltaje que tiene dos decimales.

## 6. Palabra clave "modo12"

### Pasos

1. Repetir paso anterior **2 veces** con:
    - Nombre de la central: **modo12**

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Modo 12:
     · Medición cada 1 hs
     · Envío cada 12 hs
     · Envíos a la 00:00 y 12:00 hs

La segunda vez aparece: 

    Modo normal:
     · Medición cada 24 hs
     · Envío cada 24 hs
     · Envíos a la 12:00 hs
 
_Nota:_ el orden de aparición de los pop-up puede alterarse dependiendo del estado del modo 12 al principio.

## 1. Palabra clave "offline"

### Pasos

1. Repetir paso anterior **2 veces** con:
    - Nombre de la central: **offline**

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Modo offline: las mediciones NO se envían, sólo se guardan

La segunda vez aparece: 

    Modo online: las mediciones se envían normalmente

_Nota:_ el orden de aparición de los pop-up puede alterarse dependiendo del estado del modo offline al principio.

## 8. Palabra clave "modulo"

### Pasos

1. Repetir paso anterior con:
    - Nombre de la central: **modulo**
2. Realizar una descarga de historial
   
### Resultado esperado

1. Aparece un pop-up con el siguiente mensaje:

    Memoria SD formateada. Mediciones guardadas eliminadas

2. Aparece un pop-up con el siguiente mensaje:

    [0] datos fueron guardados de manera local. Cuando se conecte a una red con acceso a internet, los datos se subirán a la nube.

