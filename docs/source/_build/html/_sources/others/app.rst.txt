Comunicación con la APP
#######################

.. sectnum:: 
   :suffix: .-
   :start: 5
   :depth: 2

.. contents::

Cuando el celular está conectado al equipo, éste puede 
atender las siguientes peticiones:

- Actualización del RTC interno
- Configuración del equipo
- Palabras clave
- Medición manual
- Pedido del historial

Actualización del RTC interno
*****************************

El HTTP request es el siguiente:

.. code-block:: http
      
   POST /updateDate HTTP/1.1
   user-agent: Dart/2.16 (dart:io)
   content-type: text/plain; charset=utf-8
   accept-encoding: gzip
   content-length: 36
   host: 192.168.4.1


   "{date: 2022-12-13T21:07:33.803604}"

Con esta información, se actualiza el RTC externo y se pone
en hora también el RTC interno. Después de esto, le manda a
la app el siguiente HTTP response:

.. code-block:: http
   
   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   V5.0.1

Donde va la información de la versión del firmware.

.. note:: 
   
   Cada vez que el ESP32 se queda sin suministro eléctrico, 
   el RTC vuelve al epoch time (1 de enero de 1970 a las 0hs), 
   es por eso que se sincroniza con el RTC externo (DS3231) 
   cada vez que se despierta.

Configuración del equipo
************************

El HTTP request es el siguiente:


.. code-block:: http
   
    POST /setConfig HTTP/1.1
    user-agent: Dart/2.16 (dart:io)
    content-type: application/json; charset=utf-8
    accept-encoding: gzip
    content-length: 158
    host: 192.168.4.1

    {
      "soil_type": "Arcillo arenoso",
      "location_name": "holas",
      "sensors": {
        "Salida1(o1)": {
          "type": "the",
          "tag_depth": 10
        }
      },
      "location": {
        "latitude": -31.4402331,
        "longitude": -64.2040826
      }
    }

Si todo sale bien, entonces el http response es:

.. code-block:: http
    
    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    Configuración
    =============
    id: L-378C
    RTC ref.:
      2023-11-28-12-00-00
    RTC int.:
      2023-11-28-14-06-54
    RTC ext.:
      2023-11-28-14-06-54
    Salidas:
     · 1: ok
     · 2: -
     · 3: -
     · 4: -
     · 5: -
    Firm. Vers.: V7.6.0
    Offline: Sí
    Guardado: ok
    Subido: -

Donde: 

- ``id``: identificador del equipo.
- ``RTC ref.``: es la hora de referencia guardada en la eeprom del equipo: 
    - *Con modo 12*: es la fecha con la hora en punto anterior.
    - *Con modo normal*: es la fecha con la hora en 00 o 12 anterior.
- ``RTC int.``: es la hora con la que se carga el equipo; si sale todo 
  ok, coincide con la RTC ext.
- ``RTC ext.``: es la hora que se recupera del RTC externo (DS3231).
  Si esta hora no coincide con la fecha en que se esté haciendo la 
  configuración, entonces el RTC externo no se inicializó correctamente.
- ``Salidas:``: es el resultado del chequeo de cada salida. Está conformado con el número de salida (que va desde 1 a 5) y lo siguiente:
    - **ok**: el sensor respondió como debe ser.
    - **-**: el sensor no respondió o no está configurado.
- ``Firm. Vers.``: versión del firmware.
- ``offline``: indica si el modo offline está des/activado.
- ``Guardado``: indica si la configuración se guardó en el equipo.
- ``Subido``: indica si la configuración se subió al servidor; si 
  el equipo está en modo offline: entonces .

Palabras clave
**************

Si el campo ``location_name`` tiene alguna de las siguientes 
palabras reservadas, entonces el equipo no hace la
configuración y atiende ese caso especial.

- erase 
- eeprom 
- chequeo 
- voltaje,<bat_level>
- modo12
- offline
- modulo
- reset
- invalid sn
- invalid time
- log
- apn,<valor de apn>
- user,<valor de user>
- pwd,<valor de pwd>
- erase cred
- erase log

erase 
=====

Borra la configuración del equipo, excepto:

- ``mac``;
- ``firm_vers``;
- ``volt_coeff`` y 
- ``unix_time``.

El http_response es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    La configuración ha sido borrada

eeprom
======

Devuelve la configuración del equipo. Es la misma respuesta que en el
caso de una configuración bien hecha.

.. code-block:: http
    
    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    Configuración
    =============
    id: L-378C
    RTC ref.:
      2023-11-28-12-00-00
    RTC int.:
      2023-11-28-14-06-54
    RTC ext.:
      2023-11-28-14-06-54
    Salidas:
     · 1: ok
     · 2: -
     · 3: -
     · 4: -
     · 5: -
    Firm. Vers.: V7.6.0
    Offline: Sí
    Guardado: ok
    Subido: -

chequeo
=======

Hace un chequeo de los módulos RTC externo y SD y las 
salidas. Luego le envía a la app un mensaje con el 
resultado del chequeo.

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    Chequeo:
    ========
    - Tarjeta SD: Ok
    - RTC externo: Ok
    - Módulo SIM: No
      se chequea. Modo offline activado
    - Salidas:
       · 1: Ok
    - Paquetes en SD: 0
   
Donde:

- ``Tarjeta SD``: instala el módulo SD y crea los archivos necesarios para trabajar si no estaban creados.
    - **ok**: la tarjeta responde bien.
    - **falla**: la tarjeta no responde.
- ``RTC externo``: instala el módulo DS3231. Si no responde a la primera llamada, se desalimenta, se espera 100 ms, se vuelve a alimentar y se chequea de nuevo:
    - **ok**: el DS3231 responde bien.
    - **falla**: el módulo no responde.
- ``Módulo SIM``: se alimenta el módulo SIM y se intenta mandar un paquete al server.
    - **No se chequea. Modo offline activado**: no se hace el chequeo porque el equipo está en modo offline.
    - **ok**: el módulo SIM responde bien.
    - **falla**: el módulo no responde.
- ``Salidas``: chequeo de las salidas (las salidas no configuradas NO se muestran):
    - **ok**: el sensor responde bien.
    - **falla**: el sensor no responde.
- ``Paquetes en SD``: cantidad de paquetes guardados en la SD que no se puedieron enviar.

voltaje,<volt>
==============

Configura el coeficiente de voltaje, donde <volt> es el 
valor de voltaje de la batería en ese momento. La HTTP response es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "Coeficiente de voltaje seteado en 1.00"
    }

modo12
======

Activa o desactiva el modo 12. Si el modo 12 estaba desactivado, el 
``http_response`` es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
      "message": "modo normal",
      "measures": "12:00",
      "send": "12:00",
      "unix_eeprom": "2023-11-21-12-00-00",
      "timeStamp RTC externo": "2023-11-21-13-10-23",
      "timestamp equipo": "2023-11-21-13-10-23"
    }

Si se vuelve a mandar la palabra clave, entonces el 
``http_response`` es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
      "message": "modo 12",
      "measures": "c/1 hs",
      "send": "00:00 y 12:00",
      "unix_eeprom": "2023-11-21-13-00-00",
      "timeStamp RTC externo": "2023-11-21-13-15-51",
      "timestamp equipo": "2023-11-21-13-15-51"
    }

offline
=======

Des/activa modo offline. Si el equipo estaba con el modo offline 
desactivado, lo activa y devuelve:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "Modo offline ACTIVADO"
    }

Si se vuelve a enviar la palabra clave, entonces responde:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "Modo offline desactivado"
    }

modulo 
======

Borra el contenido del archivo ``register.txt``, que es en donde se 
guardan las mediciones fallidas. El http_response es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "Memoria SD formateada. Mediciones guardadas eliminadas"
    }

reset
=====

Reinicia el equipo. El esp32 se apaga y se vuelve a encender. 

.. warning:: 
    
    Para seguir configurando el equipo, se debe volver a generar la red wifi.

invalid sn
==========

Se quita los 0 en el campo "sn" del json de medición que se va a 
enviar al servidor. Esto se hace para testear la respuesta del 
mismo a un json formado con un sn inválido.

El http_response es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "json_measure con SN inválido"
    }

Y si se vuelve a mandar la palabra clave, devuelve:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "json_measure normal"
    }

invalid time
============

Se manda un timestamp con el año 2025 en el json de medición que 
se va a enviar al servidor. Esto se hace para testear la respuesta
del mismo a un json formado con un timestamp inválido.

El http_response es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "json_measure con timestamp inválido"
    }

Y si se vuelve a mandar la palabra clave, devuelve:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "json_measure normal"
    }

log
===

Devuelve a la app el archivo ``activity.txt``.

.. warning:: 
   
   Con esta palabra se debe hacer la petición con Packet Sender o 
   programa similar, pues el archivo es muy extensos para que la 
   app los muestre.

apn,<valor de apn>
==================

Configura la APN que va a usar el equipo para conectarse a 
internet. El `http_response` es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "APN configurado",
        "apn": "<valor de apn>",
        "user": "<valor de user>",
        "pwd": "<valor de pwd>"
    }

.. warning:: 

    El valor de apn se debe ingresar sin los símbolos <>;
    así, si APN es igual a `datos.personal.com`, entonces
    la palabra clave a usar es:

    .. code-block:: console

        apn,datos.personal.com

    Lo mismo sucede con USER y PWD.

user,<valor de user>
====================

Configura el USER que va a usar el equipo para conectarse a 
internet. El ``http_response`` es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "APN configurado",
        "apn": "<valor de apn>",
        "user": "<valor de user>",
        "pwd": "<valor de pwd>"
    }

pwd,<valor de pwd>
==================

Configura el PWD que va a usar el equipo para conectarse a 
internet. El ``http_response`` es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "PWD configurado",
        "apn": "<valor de apn>",
        "user": "<valor de user>",
        "pwd": "<valor de pwd>"
    }

erase cred
==========

Borra la APN, USER y PWD que están guardados. El 
``http_response`` es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "Credenciales borradas",
        "apn": "<valor de apn>",
        "user": "<valor de user>",
        "pwd": "<valor de pwd>"
    }

.. note:: 

    Cuando no hay credenciales configuradas, el equipo
    consulta al módulo SIM800 para saber a qué prestadora 
    de servicio de internet permenece el chip insertado y
    coloca las credenciales guardadas por defecto. 

erase log 
=========

Borra el archivo ``/activity.txt`` y lo vuelve a crear. El 
``http_response`` es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "Archivo "/activity.txt" borrado"
    }

Medición manual
***************

La HTTP request es:

.. code-block:: http

   POST /requestMeasuring HTTP/1.1  
   user-agent: Dart/2.16 (dart:io)  
   content-type: application/json; charset=utf-8
   accept-encoding: gzip
   content-length: 2
   host: 192.168.4.1


   {}

la ``http_response`` es:

.. code-block:: http
  
    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    [
        {json_measure_0},
        {json_measure_1},
        {json_measure_2},
        {json_measure_3},
        {json_measure_4}
    ]

Donde cada json_measure es:

  .. code-block:: json

    {
      "enabled": true,
      "id": "L-1004",
      "product": "THSST",
      "timestamp": "2022-12-31-21-00-00",
      "location": {
          "latitude": -31.39164543,
          "longitude": -64.22100067
      },
      "value": {
        "sn": "00000000001",
        "humidity": 1.59,
        "temperature": 24.98,
        "location_name": "BRISTE",
        "tag_depth": 200,
        "loss_tangent": 0.000,
        "electrical_conductivity": 0,
        "electrical_conductivity_tc": 0,
        "real_dielectric_permittivity": 0,
        "real_dielectric_permittivity_tc": 0,
        "imag_dielectric_permittivity": 0.00,
        "imag_dielectric_permittivity_tc": 0.00,
        "ph": 0.00,
        "level_bat": 6.643
      },
      "verFirm": "V5.1.0",
      "verHard": "V1.0.0",
      "number_sent": 0
    }


.. .. code-block:: http

..     HTTP/1.1 200 OK
..     Content-Type:text/plain;charset=UTF-8

..     {
..       "offline": true,
..       "sensors": {
..         "1": {
..           "status": true,
..           "T": 20.50,
..           "H": 0.11,
..           "E": 0,
..           "sent": false,
..           "save": true
..         },
..         "2": {
..           "status": true,
..           "T": 20.50,
..           "H": 0.11,
..           "E": 0,
..           "N": 0,
..           "P": 0,
..           "K": 0,
..           "sent": false,
..           "save": true
..         },
..         "3": {
..           "status": true,
..           "L": 0.798,
..           "sent": false,
..           "save": true
..         },
..         "4": {
..           "status": true,
..           "T": 20.50,
..           "H": 0.11,
..           "E": 0,
..           "N": 5,
..           "P": 42,
..           "K": 56,
..           "PH": 7.52
..           "sent": false,
..           "save": true
..         },
..       },
..       "sent_from_sd": 0,
..       "rest_on_sd": 16
..     }

.. Donde :

.. - ``offline``: indica si el modo offline está activado o no.
.. - ``Sensors``: contiene json de los sensores configurados.
..     - ``status``: indica si la medición se hizo o falló.
..     - ``T, H, E``: parámetros del sensor THE. 
..     - ``T, H, E, N, P, K``: parámetros del sensor NPK. 
..     - ``L``: parámetros del sensor LEVEL. 
..     - ``sent``: indica si el paquete se envió con éxito al server. 
..     - ``save``: indica si el paquete se guardó con éxito si el envío falló. 
.. - ``sent_from_sd``: número de paquetes enviados desde la sd.
.. - ``rest_on_sd``: número de paquetes que quedan en la sd.

.. .. warning:: 

..     Los paquetes en la SD con más de 3 envíos fallidos se 
..     borrarán de la misma.

Pedido del historial
********************

El HTTP request es:

.. code-block:: http

    POST /getHistory HTTP/1.1  
    user-agent: Dart/2.16 (dart:io)  
    content-type: application/json; charset=utf-8
    accept-encoding: gzip
    content-length: 2
    host: 192.168.4.1


    {}

Y la HTTP response es un array de json:

.. code-block:: bash

    HTTP/1.1 200 OK
    Content-type: application/json

    [
      json_measure_0, 
      json_measure_1, 
      ...,
      json_measure_n 
    ]   

El ESP32 manda un json cada vez porque tiene un límite de 
alrededor de 1400 caracteres por envío al cliente.

.. note:: 
    
    Después de descargar los datos, el archivo ``register.txt``
    no se elimina, sólo lo hará cuando el equipo pueda mandar 
    con éxito dichas mediciones vía sim800 o se hayan 
    intentado mandar 3 veces sin éxito.