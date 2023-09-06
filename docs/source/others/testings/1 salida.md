# 1 salida

Estos test cases se deben hacer eligiendo uno de los 3 tipos de sensores que soporta el equipo y conectarlo a una salida aleatoria "x". Se deben repetir con los otros 2 tipos de sensores.

| Nro | Nombre | Sensor | Chip |
|:---:|:---|:---:|:---:|
| 1 | Configuración con otro tipo de sensor |  |  |
| 2 | Configuración sin sensor | - | - |
| 3 | Configuración sin chip | ✓ | - |
| 4 | Configuración normal | ✓ | ✓ |
| 5 | Medición manual normal | ✓ | ✓ |
| 6 | Medición manual con sensor y sin chip | ✓ | - |
| 7 | Medición manual sin sensor | - | - |
| 8 | Pedido de historial |  |  |

## 1. Configuración con otro tipo de sensor

### Requerimientos

* Sensor de tipo _&lt;type&gt;_ en salida _&lt;x&gt;_

### Pasos

1. En el menú de la app, apretar "Configurar equipo"
2. Rellenar con los siguientes campos:
    - Nombre de la central: _&lt;cualquiera&gt;_
    - Textura del suelo: _&lt;cualquiera&gt;_
3. Apretar en "Agregar sensor" y rellenar:
    - Salida del sensor: Salida _&lt;x&gt;_
    - Tipo de sensor: distinto de _&lt;type&gt;_
    - Profundidad del sensor: _&lt;cualquiera&gt;_
4. Apretar "Guardar"
4. En el menú "Configuraciones", apretar "Guardar"

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Problemas con la salida <x>. Revise conexión

## 2. Configuración sin sensor ni chip

### Requerimientos

* Sin sensores conectados 

### Pasos

1. En el menú de la app, apretar "Configurar equipo"
2. Rellenar con los siguientes campos:
    - Nombre de la central: _&lt;cualquiera&gt;_
    - Textura del suelo: _&lt;cualquiera&gt;_
3. Apretar en "Agregar sensor" y rellenar:
    - Salida del sensor: Salida _&lt;x&gt;_
    - Tipo de sensor: ≠ _&lt;type&gt;_
    - Profundidad del sensor: _&lt;cualquiera&gt;_
4. Apretar "Guardar"
4. En el menú "configuraciones", apretar "Guardar"

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Problemas con la salida <x>. Revise conexión

## 3. Configuración con sensor y sin chip

### Requerimientos

- Sensor conectado en una salida _&lt;x&gt;_
- Chip NO instalado

### Pasos

1. Repetir los pasos para configurar equipo

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Problemas de conexión: chip mal conectado o sin datos.
    La configuración hecha, pero no enviada
    Configuración
    =============
     · 1) No configurado
     · 2) No configurado
     · 3) 30.00 cm (the)
     · 4) No configurado

Aquí _&lt;x&gt; = 3_

## 4. Configuración normal

### Requerimientos

- Sensor conectado en una salida _&lt;x&gt;_
- Chip instalado

### Pasos

1. Repetir los pasos para configurar equipo

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Configuración
    =============
     · 1) No configurado
     · 2) No configurado
     · 3) 30.00 cm (the)
     · 4) No configurado

Aquí _&lt;x&gt; = 3_

## 5. Medición manual normal

### Requerimientos

- Equipo configurado en salida _&lt;x&gt;_
- Chip instalado

### Pasos

1. En el menú principal de la app, apretar "Realizar medición"

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Resultado
    =========
    · 1) --- No config. ---
    · 2) --- No config. ---
    · 3) Sensor the
        T = 19.68°C
        H = 0.34%RH
        EC = 0uS/cm
        Enviado: ok
    · 4) --- No config. ---

Aquí _&lt;x&gt; = 3_

## 6. Medición manual con sensor y sin chip

### Requerimientos

- Equipo configurado en salida _&lt;x&gt;_
- Chip NO instalado

### Pasos

1. En el menú de la app, apretar "Realizar medición"
2. Repetir 4 veces el paso anterior para tener 5 paquetes guardados 

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Resultado
    =========
    · 1) --- No config. ---
    · 2) --- No config. ---
    · 3) Sensor the
        T = 19.81°C
        H = 0.45%RH
        EC = 0uS/cm
        Envío: FALLÓ
        Guardado: ok
    · 4) --- No config. ---

Aquí _&lt;x&gt; = 3_

## 7. Medición manual sin sensor

### Requerimientos

- Equipo configurado en salida _&lt;x&gt;_
- Sensor NO conectado en salida _&lt;x&gt;_
- Chip NO instalado

### Pasos

1. En el menú de la app, apretar "Realizar medición"

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    Resultado
    =========
    · 1) --- No config. ---
    · 2) --- No config. ---
    · 3) Sensor the
        FALLA de sensor
    · 4) --- No config. ---

Aquí _&lt;x&gt; = 3_

## 8 | Pedido de historial

### Requerimientos

- Equipo con _&lt;x&gt;_ mediciones guardadas 

### Pasos

1. En el menú de la app, apretar "Descargar historial local"

### Resultado esperado

Aparece un pop-up con el siguiente mensaje:

    [5] datos fueron guardados de manera local. Cuando se conecte a una red con acceso a internet, los datos se subirán a la nube.


