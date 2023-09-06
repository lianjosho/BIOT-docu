Testing
#######

.. sectnum::
   :suffix: .-
   :start: 9
   :depth: 2

.. contents:: 

Configuración
*************

### Requerimientos

* Sin sensores conectados 

### Pasos

1. En el menú de la app, apretar "Configurar equipo"
2. Rellenar con los siguientes campos:
    - Nombre de la central: _&lt;cualquiera&gt;_
    - Textura del suelo: _&lt;cualquiera&gt;_
3. Apretar en "Agregar sensor" y rellenar:
    - Salida del sensor: Salida1(o1)
    - Tipo de sensor: the
    - Profundidad del sensor: _&lt;cualquiera&gt;_
4. Apretar "Guardar"
4. En el menú "configuraciones", apretar "Guardar"

### Resultado esperado
Aparece un pop-up con el siguiente mensaje:

    Problemas con la salida 1. Revise conexión


1 salida 
    Configuración con sensor desconectado
    Configuración con otro tipo de sensor
    Configuración con sensor
    Configuración sin chip
    Medición manual con sensor 
    Medición manual sin chip 
    Pedidio de historial 
    Medición manual sin sensor

4 salidas
    


Testing cases para configurar el equipo, deben hacerse con 
sensores THE, NPK y de nivel.

* En cada salida
* En las 4 salidas
* En las 4 salidas con salida 2 desconectada
* En una salida con sensor desconectado
* En una salida sin chip

En cada salida
==============

+---------------------------------------+
|                Results                |
+-------------+-------------------------+
|             |        Contestant       |
| Competition +-------+--------+--------+
|             |  John | Andrea | Robert |
+-------------+-------+--------+--------+
| Swimming    |  1:30 |   2:05 |   1:15 |
+-------------+-------+--------+--------+
| Running     | 15:30 |  14:10 |  15:45 |
+-------------+-------+--------+--------+


+-----------------------------------------------+
|                 Requerimientos                |
+===============================================+
| 1. Sensor conectado a una salida              |
| 2. Chip instalado y con datos                 |
| 3. Cel sin datos y conectado a red del equipo |
| 4. App abierta en menú principal              |
+-----------------------------------------------+


+-------------------------------------------------------------------------+
| Requerimientos                                                          |
+=========================================================================+
| * Sensor conectado en una salida                                        |
| * Chip instalado y con datos                                            |
| * Celular sin datos móviles activados y conectado a red wifi del equipo |
| * App abierta en el menú principal                                      |
+-------------------------------------------------------------------------+

.. csv-table:: Steps
    :header: Step, Description, Expected result, Actual result, Status
    :widths: 3, 30, 10, 10, 10
    :align: center

    1, Apretar "Configuración", Se abre el menú de configuración, ,
    1, Rellenar los campos: 
    dsa, , ,

.. list-table:: Frozen Delights!
   :widths: 15 10 30
   :header-rows: 1

   * - Treat
     - Quantity
     - Description
   * - Albatross
     - 2.99
     - On a stick!
   * -  Crunchy Frog
     - 1.49\n
       * historial\n
       * asfd 
     - If we took the bones out, it wouldn't be
       crunchy, now would it?
   * - Gannet Ripple
     - 1.99
     - On a stick!




En las 4 salidas
================



En las 4 salidas con salida 2 desconectada
==========================================



En una salida con sensor desconectado
=====================================



En una salida sin chip
======================






Medición manual
***************

* En una salida
* En una salida con sensor desconectado 
* En una salida sin chip 

Pedido de historial
*******************

* En una salida
* En las 4 salidas 





