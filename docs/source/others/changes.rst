Cambios o propuestas de mejora
##############################

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

   "{\"soil_type\": \"Arcillo arenoso\", \"location_name\": \"holas\", \"sensors\": {\"Salida1(o1)\": {\"type\": \"the\", \"tag_depth\": 10 }}, \"location\": {\"latitude\": -31.4402331, \"longitude\": -64.2040826}}"

Si todo sale bien, entonces el http response es:

.. code-block:: http
    
    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
      "id": "L-E620",
      "offline": false,
      "sensors": {
        "1": true,
        "2": false,
        "3": false,
        "4": false
      },
      "save": true,
      "connection": true,
      "server": true
    }

Donde: 

- ``<id>``: identificador del equipo.
- ``<offline>``: indica si el modo offline está des/activado.
- ``<sensors>``: resultado de la configuración de los sensores.
    - **false**: hubo un problema con algún sensor y no se configuró.
    - **true**: los sensores se configurarion correctamente.
- ``<save>``: resultado del guardado de la configuración.
    - **false**: no se guardó la configuración.
    - **true**: se guardó la configuración.
- ``<sent>``: resultado del envío de la configuración.
    - **0**: módulo offline activado, no se envía la configuración.
    - **1**: la configuración se envió correctamente.
    - **2**: el módulo SIM no responde.
    - **3**: no se pudo obtener conexión a internet.
    - **4**: el servidor no respondió con 200 ok.





.. Donde ``{json_app}`` es el json que el ESP32 usa para 
.. configurar el equipo. El ``{json_app}`` tiene la forma:

.. .. literalinclude:: variables/json_app.json
..    :language: json

.. En el ejemplo las salidas tienen los siguientes sensores:

.. - Salida 1: sensor THE.
.. - Salida 2: sensor NPK.
.. - Salida 3: sensor de nivel.
.. - Salida 4: sensor Stevens.

.. La trama tiene a lo sumo 4 elementos, numerados del 0 al 3, que 
.. corresponden a cada una de las salidas configuradas.

.. .. literalinclude:: variables/json_app.json
..    :language: json
..    :emphasize-lines: 2, 5, 9, 12

.. Cada salida tiene a su vez elementos numerados del 0 al 9 a lo
.. sumo, que corresponden a los comandos que se le debe enviar al 
.. sensor en dicha salida.

.. .. literalinclude:: variables/json_app.json
..    :language: json
..    :emphasize-lines: 3, 6-7, 10, 13-15

.. Estos comandos tienen como campo un array que tiene la forma:

.. .. code-block:: console
..    :class: centered

..    [<type>, <command>, <max>, <power>, <response>]

.. - ``type``: es el tipo de variable del contenido del comando. 
..   Puede ser ``hex`` o ``ascii``.
.. - ``command``: es el comando en sí.
.. - ``max``: es el número de caracteres que se debe esperar como 
..   respuesta del sensor. Si es 0, significa que no se espera 
..   respuesta.
.. - ``power``: es el tiempo que hay que esperar después de 
..   haber alimentado la salida antes de mandarle un comando.
.. - ``response``: es el tiempo límite que se debe esperar la 
..   respuesta. De nuevo, si es 0 es que no se espera respuesta. 
..   Si ``max = 0`` entonces ``response = 0`` también.

.. .. note:: 
..    Para más información de estos parámetros, 
..    ver ::ref:`array_param`

.. .. note:: 
..   Los dos últimos parámetros podrían llevar el nombre de 
..   ``timeout`` al principio, pero la librería ``Preferences.h`` 
..   limita la longitud del nombre de la llave para guardar un valor 
..   en la eeprom. En realidad, deberían llamarse 
..   ``timeout_power`` y ``timeout_response``.

.. Con esta información, el equipo chequea si los sensores de ese
.. json están en las salidas correspondientes y si coinciden en
.. el tipo.

.. El HTTP response es un json con las respuestas que devolvieron 
.. las salidas a cada uno de los parámetros pasados. 

.. .. code-block:: bash

..    HTTP/1.1 200 OK
..    Content-Type:text/plain;charset=UTF-8

..    {
..       "0": {
..         "0": "010306012C02921D4CECA6"
..       },
..       "1": {
..         "0": "010306012C02921D4CECA6",
..         "1": "010306012C02921D4CECA6"
..       },
..       "2": {
..         "0": "010306012C02921D4CECA6"
..       },
..       "3": {
..         "0": "",
..         "1": "062+0.535,+0.060,+29.2,+84.6,+0.064,+42.952,+23.095,+44.388,+21.661\r\n",
..         "2": "062+0.535,+0.060,+29.2\r\n",
..       }
..    }

.. .. warning:: 

..     El equipo no verifica la trama de respuesta (longitud, tiempo 
..     de respuesta, caracteres válidos, etc.) de cada parámetros, 
..     simplemente devuelve lo que respondió. La app se tiene que 
..     encargar de verificar si cada trama de respuesta es coherente 
..     con su comando. 
    
.. Los casos en que haya un posible fallo en la configuración son:

.. 1. No hay sensor conectado.
.. 2. No hay respuesta a un comando.
.. 3. Se cuela ruido en la respuesta a un comando.
 
.. No hay sensor conectado
.. =======================

.. Si en el caso del ejemplo el sensor de la salida 1 está 
.. desconectado, entonces el json de respuesta es como sigue:

.. .. code-block:: bash
..    :emphasize-lines: 9-10

..    HTTP/1.1 200 OK
..    Content-Type:text/plain;charset=UTF-8

..    {
..       "0": {
..         "0": "010306012C02921D4CECA6"
..       },
..       "1": {
..         "0": "",
..         "1": ""
..       },
..       "2": {
..         "0": "010306012C02921D4CECA6"
..       },
..       "3": {
..         "0": "",
..         "1": "062+0.535,+0.060,+29.2,+84.6,+0.064,+42.952,+23.095,+44.388,+21.661\r\n",
..         "2": "062+0.535,+0.060,+29.2\r\n",
..       }
..    }

.. En donde las líneas resaltadas tienen tramas de respuesta nulas 
.. porque no hay sensor que responda. Como el parámetro ``<max>`` 
.. no es 0, esto se interpreta como un error y los comandos para 
.. esta salida **NO** van a ser guardados en la configuración. El 
.. resto de las salidas sí se van a guardar.

.. No hay respuesta a un comando
.. =============================

.. Si ahora en la salida 1 se tiene conectado un sensor THE y la 
.. app manda comandos para un sensor NPK, el sensor THE sólo
.. responderá al primer comando, como sigue.

.. .. code-block:: bash
..    :emphasize-lines: 10

..    HTTP/1.1 200 OK
..    Content-Type:text/plain;charset=UTF-8

..    {
..       "0": {
..         "0": "010306012C02921D4CECA6"
..       },
..       "1": {
..         "0": "010306012C02921D4CECA6",
..         "1": ""
..       },
..       "2": {
..         "0": "010306012C02921D4CECA6"
..       },
..       "3": {
..         "0": "",
..         "1": "062+0.535,+0.060,+29.2,+84.6,+0.064,+42.952,+23.095,+44.388,+21.661\r\n",
..         "2": "062+0.535,+0.060,+29.2\r\n",
..       }
..    }

.. En donde la línea resaltada representa la respuesta del sensor 
.. al segundo comando. En este caso pasa como en el caso anterior:
.. **NO** se guarda la configuración para esta salida.

.. Se cuela ruido en la respuesta a un comando
.. ===========================================

.. Ha sucedido un caso en una placa en que el sensor responde con 
.. unos bytes aleatorios antes de responder la trama esperada. 
.. Siguiendo con el ejemplo anterior, se esperan 11 bytes

.. .. code-block:: bash
    
..     0   1   2   3   4   5   6   7   8   9   10
..     ------------------------------------------
..     01  03  06  01  2C  02  92  1D  4C  EC  A6

.. Pero en su lugar, se reciben 4 bytes antes de la respuesta 
.. esperada:

.. .. code-block:: bash
    
..     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
..     ----------------------------------------------------------
..     00  00  00  00  01  03  06  01  2C  02  92  1D  4C  EC  A6

.. En donde los bytes 0 al 3 son basura o respuesta inálida, ya 
.. que la trama de respuesta debería comenzar con 01, que es la 
.. dirección por defecto de los sensores chinos. Como ``max=11``, 
.. el equipo espera 11 bytes y corta ahí la respuesta, por lo que 
.. lo devuelto a la app sería: 

.. .. code-block:: bash
    
..     0   1   2   3   4   5   6   7   8   9   10
..     ------------------------------------------
..     00  00  00  00  01  03  06  01  2C  02  92

.. Lo cual no tiene sentido y si se le aplica CRC no lo va a cumplir, 
.. pero el equipo no está configurado para hacer esta tarea, de eso
.. se tiene que encargar la app. Lo que sí va a pasar es que se van 
.. a guardar los comandos para esa salida y lo que se devuelve a 
.. la app es lo siguiente:

.. .. code-block:: bash
..    :emphasize-lines: 10

..    HTTP/1.1 200 OK
..    Content-Type:text/plain;charset=UTF-8

..    {
..       "0": {
..         "0": "010306012C02921D4CECA6"
..       },
..       "1": {
..         "0": "010306012C02921D4CECA6",
..         "1": "00000000010306012C0292"
..       },
..       "2": {
..         "0": "010306012C02921D4CECA6"
..       },
..       "3": {
..         "0": "",
..         "1": "062+0.535,+0.060,+29.2,+84.6,+0.064,+42.952,+23.095,+44.388,+21.661\r\n",
..         "2": "062+0.535,+0.060,+29.2\r\n",
..       }
..    }

.. Donde la línea resaltada es la respuesta inválida del sensor.

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

    {
        "message": "La configuración ha sido borrada"
    }

eeprom
======

Devuelve un json con la configuración del equipo en 
formato json.

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
      "id": "L-7BF4",
      "product": "THSST",
      "soil_type": "",
      "location_name": "",
      "location": {
        "latitude": 0,
        "longitude": 0
      },
      "sensors": {},
      "otro": {
        "apn": "",
        "user": "",
        "pwd": "",
        "pending_config": false,
        "offline": true,
        "modo 12": true
      }
    }

Donde el json devuelto es igual al ``json_pp``, excepto que 
a los campos de las salidas se le agrega un campo llamado
``other`` que contiene información adicional. El tiempo que 
demora la respuesta es **258 ms** aproximadamente.

chequeo
=======

Hace un chequeo de los módulos RTC externo y SD y las 
salidas. Luego le envía a la app un mensaje con el 
resultado del chequeo.

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
      "SD card": true,
      "extern RTC": true,
      "SIM module": true,
      "sensors": {
        "1": true,
        "1": false
      },
      "others": {
        "offline": false,
        "modo 12": false,
        "json in SD": 3
      }
    }
   
- ``SD card``: instala el módulo SD y crea las carpetas necesarias para trabajar si no estaban creadas.
    - false: no se pudo obtener respuesta.
    - true: chequeo ok.
- ``extern RTC``: instala el módulo DS3231. Si no responde a la primera llamada, se desalimenta, se espera 100 ms, se vuelve a alimentar y se chequea de nuevo
    - false: no se pudo obtener respuesta.
    - true: chequeo ok.
- ``SIM module``: se alimenta el módulo SIM y se intenta mandar un paquete al server.
    - false: no se pudo enviar el paquete.
    - true: paquete enviado.
- ``sensors``: json que contiene los sensores configurados.
    - false: no se obtuvo respuesta del sensor.
    - true: chequeo ok.
- ``others``: json que contiene otras configuraciones.
    - ``offline``: false si el modo offline está desactivado, true si está activado.
    - ``modo 12``: ídem para el modo 12.
    - ``json in SD``: cantidad de paquetes guardados en la SD.



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
        "message": "modo 12",
        "measures": "c/1 hs",
        "send": "00:00 y 12:00"
    }

Si se vuelve a mandar la palabra clave, entonces el 
``http_response`` es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
        "message": "modo normal",
        "measures": "12:00",
        "send": "12:00"
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

Suponiendo la siguiente configuración:

- Salida 1: sensor THE;
- Salida 2: sensor NPK;
- Salida 3: sensor LEVEL;
- Salida 4: sensor PH;

la ``HTTP_response`` es:

.. code-block:: http

    HTTP/1.1 200 OK
    Content-Type:text/plain;charset=UTF-8

    {
      "offline": true,
      "sensors": {
        "1": {
          "status": true,
          "T": 20.50,
          "H": 0.11,
          "E": 0,
          "sent": false,
          "save": true
        },
        "2": {
          "status": true,
          "T": 20.50,
          "H": 0.11,
          "E": 0,
          "N": 0,
          "P": 0,
          "K": 0,
          "sent": false,
          "save": true
        },
        "3": {
          "status": true,
          "L": 0.798,
          "sent": false,
          "save": true
        },
        "4": {
          "status": true,
          "T": 20.50,
          "H": 0.11,
          "E": 0,
          "N": 5,
          "P": 42,
          "K": 56,
          "PH": 7.52
          "sent": false,
          "save": true
        },
      },
      "sent_from_sd": 0,
      "rest_on_sd": 16
    }

Donde :

- ``offline``: indica si el modo offline está activado o no.
- ``Sensors``: contiene json de los sensores configurados.
    - ``status``: indica si la medición se hizo o falló.
    - ``T, H, E``: parámetros del sensor THE. 
    - ``T, H, E, N, P, K``: parámetros del sensor NPK. 
    - ``L``: parámetros del sensor LEVEL. 
    - ``sent``: indica si el paquete se envió con éxito al server. 
    - ``save``: indica si el paquete se guardó con éxito si el envío falló. 
- ``sent_from_sd``: número de paquetes enviados desde la sd.
- ``rest_on_sd``: número de paquetes que quedan en la sd.

.. warning:: 

    Los paquetes en la SD con más de 3 envíos fallidos se 
    borrarán de la misma.

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