.. V6.3.0 - 08/08/2023
.. ===================

.. - **HTTP response de keyword "check"**: antes era:
  
.. .. code-block:: bash
   
..     HTTP/1.1 200 OK
..     Content-Type:text/plain;charset=UTF-8

..     Chequeo:
..     ========
..     - Memoria SD: ok
..     - Módulo de hora: ok
..     - Sensores: ok


.. y ahora es:

.. .. code-block:: bash

..     HTTP/1.1 200 OK
..     Content-Type:text/plain;charset=UTF-8

..     {
..         "0": {
..             "0": "01030608D500880000ADC5"
..         },
..         "1": {
..             "0": "",
..             "1": "062+0.000,+0.001,+22.4,+72.3,+0.001,+0.697,+0.354,+0.708,+0.368\r\n",
..             "2": "062+22.4,+72.3,+0.508\r\n"
..         },
..         "other": {
..             "sdcard": true,
..             "rtc": true
..         }
..     }

.. V6.2.0 - 28/07/2023
.. ===================

.. Changed
.. -------

.. - **HTTP response de configuración**: antes era:

.. .. code-block:: bash

..    HTTP/1.1 200 OK
..    Content-Type:text/plain;charset=UTF-8

..    Equipo configurado:
..    ===================
..    1) 10 cm (the)
..    2) 20 cm (npk)
..    3) No configurado 
..    4) No configurado

.. y ahora es:

.. .. code-block:: bash

..    HTTP/1.1 200 OK
..    Content-Type:text/plain;charset=UTF-8

..    Configuración hecha

.. V6.1.1 - 28/07/2023
.. ===================

.. Fixed
.. -----

.. - **Problema de sensor tipo hex no conectado**: cuando el sensor 
..   tipo hex no está conectado, no devuelve respuesta. Esa respuesta 
..   se estaba guardando en un array nulo que después se convertía en 
..   un String "000..."; cuando en realidad debería ser "". Corregido.

.. V6.1.0 - 26/07/2023
.. ===================

.. Added
.. -----

.. - **Funcionalidad keyword: erase**: se atiende la petición POST 
..   de palabra clave que pide borrar la configuración.  

.. - **Funcionalidad keyword: eeprom**: se atiende la petición POST 
..   que pide la configuración guardada. 

.. - **Funcionalidad keyword: check**: chequea los módulos del equipo. 

.. - **Funcionalidad keyword: voltaje**: setea el coeficiente de 
..   voltaje. 

.. - **Funcionalidad keyword: modo12**: des/activa el modo 12. 

.. - **Funcionalidad keyword: offline**: des/activa el modo offline. 

.. - **Funcionalidad keyword: bat**: devuelve el archivo "battery.txt". 

.. - **Funcionalidad keyword: regall**: devuelve el archivo 
..   "regall.txt". 

.. V6.0.0 - 14/07/2023
.. ===================

.. Changed
.. -------

.. - **Cambios en el json_app**: se cambió el json que manda la app 
..   para configurar el equipo. Antes era:

.. .. code-block:: json

..    {
..       "soil_type": "Arcilloso",
..       "location_name": "Hola",
..       "sensors": {
..          "Salida 2 (o2)": {
..             "type": "nivel",
..             "tag_depth": 20
..          }
..       },
..       "location": {
..       "latitude": -31.4403103,
..       "longitude": -64.2040562
..       }
..    }

.. Y ahora es:

.. .. code-block:: json

..    {
..       "0": {
..          "0": ["hex", "010300060003E5CA", 30, 1, 4]
..       },
..       "1": {
..          "0": ["hex", "010300060003E5CA", 30, 1, 4],
..          "1": ["hex", "010300060003E5CA", 30, 1, 4]
..       },
..       "2": {
..          "0": ["hex", "01040000000271CB", 30, 12, 1]
..       },
..       "3": {
..          "0": ["ascii", "///TR\r\n", 1, 1, 5],
..          "1": ["ascii", "///T0\r\n", 80, 1, 1],
..          "2": ["ascii", "///T1\r\n", 80, 1, 1]
..       }
..    }

.. - **Cambios en el json_measure**: se cambió el paquete json de 
..   de medición. Antes era:

.. .. code-block:: json

..    {
..       "enabled": true,
..       "id": "L-7BF4",
..       "product": "THSST",
..       "timestamp": "2023-04-20-12-18-42",
..       "location": {
..          "latitude": -31.39167023,
..          "longitude": -64.22102356
..       },
..       "value": {
..          "sn": "00000000001",
..          "humidity": 0.00,
..          "temperature": 22.08,
..          "location_name": "BIOT-",
..          "tag_depth": 10,
..          "loss_tangent": 0.00,
..          "electrical_conductivity": 0,
..          "electrical_conductivity_tc": 0.00,
..          "real_dielectric_permittivity": 0.00,
..          "real_dielectric_permittivity_tc": 0.00,
..          "imag_dielectric_permittivity": 0.00,
..          "imag_dielectric_permittivity_tc": 0.00,
..          "level_bat": 0.000
..       },
..       "verFirm": "V1.0.15",
..       "verHard": "V1.0.0",
..       "number_sent": 0
..    }

.. Y ahora es: 

.. .. code-block:: json

..    {
..       "id": "L-1234",
..       "timestamp": "2022-12-23-21-58-08",
..       "level_bat": 10.2,
..       "sn": 1,
..       "number_sent": 2,
..       "value": "value"
..    }

.. Donde el campo ``value`` es depende del tipo de sensor.

.. Para un sensor tipo THE: 

.. .. code-block:: json

..    "value": ["010325657455548"]

.. Para un sensor tipo NPK:

.. .. code-block:: json
  
..    "value": ["010325657455548", "010325657455548"]

.. Para un sensor tipo LEVEL:

.. .. code-block:: json
  
..    "value": ["010325657455548"]

.. Para un sensor tipo STEVENS:

.. .. code-block:: json
  
..    "value": [
..       "062+0.535,+0.060,+29.2,+84.6,+0.064,+42.952,+23.095,+44.388,+21.661",
..       "062+28.9,+84.0,+0.517"
..    ]