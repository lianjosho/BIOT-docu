Comunicación con la APP
#######################

.. sectnum:: 
   :suffix: .-
   :start: 5
   :depth: 2

.. contents::

Cuando el celular está conectado al equipo, éste puede 
atender las siguientes peticiones:

[enlace](variables/archivo.wsd)

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
   es por eso que se sincroniza con el RTC externo cada vez 
   que se despierta.


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

   "{json_app}"

Donde ``{json_app}`` es el json que el ESP32 usa para 
configurar el equipo. El ``{json_app}`` tiene la forma:

.. literalinclude:: variables/json_app.json
   :language: json

En el ejemplo las salidas tienen los siguientes sensores:

- Salida 1: sensor THE.
- Salida 2: sensor NPK.
- Salida 3: sensor de nivel.
- Salida 4: sensor Stevens.

La trama tiene a lo sumo 4 elementos, numerados del 0 al 3, que 
corresponden a cada una de las salidas configuradas.

.. literalinclude:: variables/json_app.json
   :language: json
   :emphasize-lines: 2, 5, 9, 12

Cada salida tiene a su vez elementos numerados del 0 al 9 a lo
sumo, que corresponden a los comandos que se le debe enviar al 
sensor en dicha salida.

.. literalinclude:: variables/json_app.json
   :language: json
   :emphasize-lines: 3, 6-7, 10, 13-15

Estos comandos tienen como campo un array que tiene la forma:

.. code-block:: console
   :class: centered

   [<type>, <command>, <max>, <power>, <response>]

- ``type``: es el tipo de variable del contenido del comando. 
  Puede ser ``hex`` o ``ascii``.
- ``command``: es el comando en sí.
- ``max``: es el número de caracteres que se debe esperar como 
  respuesta del sensor. Si es 0, significa que no se espera 
  respuesta.
- ``power``: es el tiempo que hay que esperar después de 
  haber alimentado la salida antes de mandarle un comando.
- ``response``: es el tiempo límite que se debe esperar la 
  respuesta. De nuevo, si es 0 es que no se espera respuesta. 
  Si ``max = 0`` entonces ``response = 0`` también.

.. note:: 
   Para más información de estos parámetros, 
   ver ::ref:`array_param`

.. note:: 
  Los dos últimos parámetros podrían llevar el nombre de 
  ``timeout`` al principio, pero la librería ``Preferences.h`` 
  limita la longitud del nombre de la llave para guardar un valor 
  en la eeprom. En realidad, deberían llamarse 
  ``timeout_power`` y ``timeout_response``.

Con esta información, el equipo chequea si los sensores de ese
json están en las salidas correspondientes y si coinciden en
el tipo.

El HTTP response es un json con las respuestas que devolvieron 
las salidas a cada uno de los parámetros pasados. 

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   {
      "0": {
        "0": "010306012C02921D4CECA6"
      },
      "1": {
        "0": "010306012C02921D4CECA6",
        "1": "010306012C02921D4CECA6"
      },
      "2": {
        "0": "010306012C02921D4CECA6"
      },
      "3": {
        "0": "",
        "1": "062+0.535,+0.060,+29.2,+84.6,+0.064,+42.952,+23.095,+44.388,+21.661\r\n",
        "2": "062+0.535,+0.060,+29.2\r\n",
      }
   }

.. warning:: 

    El equipo no verifica la trama de respuesta (longitud, tiempo 
    de respuesta, caracteres válidos, etc.) de cada parámetros, 
    simplemente devuelve lo que respondió. La app se tiene que 
    encargar de verificar si cada trama de respuesta es coherente 
    con su comando. 
    
Los casos en que haya un posible fallo en la configuración son:

1. No hay sensor conectado.
2. No hay respuesta a un comando.
3. Se cuela ruido en la respuesta a un comando.
 
No hay sensor conectado
=======================

Si en el caso del ejemplo el sensor de la salida 1 está 
desconectado, entonces el json de respuesta es como sigue:

.. code-block:: bash
   :emphasize-lines: 9-10

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   {
      "0": {
        "0": "010306012C02921D4CECA6"
      },
      "1": {
        "0": "",
        "1": ""
      },
      "2": {
        "0": "010306012C02921D4CECA6"
      },
      "3": {
        "0": "",
        "1": "062+0.535,+0.060,+29.2,+84.6,+0.064,+42.952,+23.095,+44.388,+21.661\r\n",
        "2": "062+0.535,+0.060,+29.2\r\n",
      }
   }

En donde las líneas resaltadas tienen tramas de respuesta nulas 
porque no hay sensor que responda. Como el parámetro ``<max>`` 
no es 0, esto se interpreta como un error y los comandos para 
esta salida **NO** van a ser guardados en la configuración. El 
resto de las salidas sí se van a guardar.

No hay respuesta a un comando
=============================

Si ahora en la salida 1 se tiene conectado un sensor THE y la 
app manda comandos para un sensor NPK, el sensor THE sólo
responderá al primer comando, como sigue.

.. code-block:: bash
   :emphasize-lines: 10

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   {
      "0": {
        "0": "010306012C02921D4CECA6"
      },
      "1": {
        "0": "010306012C02921D4CECA6",
        "1": ""
      },
      "2": {
        "0": "010306012C02921D4CECA6"
      },
      "3": {
        "0": "",
        "1": "062+0.535,+0.060,+29.2,+84.6,+0.064,+42.952,+23.095,+44.388,+21.661\r\n",
        "2": "062+0.535,+0.060,+29.2\r\n",
      }
   }

En donde la línea resaltada representa la respuesta del sensor 
al segundo comando. En este caso pasa como en el caso anterior:
**NO** se guarda la configuración para esta salida.

Se cuela ruido en la respuesta a un comando
===========================================

Ha sucedido un caso en una placa en que el sensor responde con 
unos bytes aleatorios antes de responder la trama esperada. 
Siguiendo con el ejemplo anterior, se esperan 11 bytes

.. code-block:: bash
    
    0   1   2   3   4   5   6   7   8   9   10
    ------------------------------------------
    01  03  06  01  2C  02  92  1D  4C  EC  A6

Pero en su lugar, se reciben 4 bytes antes de la respuesta 
esperada:

.. code-block:: bash
    
    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
    ----------------------------------------------------------
    00  00  00  00  01  03  06  01  2C  02  92  1D  4C  EC  A6

En donde los bytes 0 al 3 son basura o respuesta inálida, ya 
que la trama de respuesta debería comenzar con 01, que es la 
dirección por defecto de los sensores chinos. Como ``max=11``, 
el equipo espera 11 bytes y corta ahí la respuesta, por lo que 
lo devuelto a la app sería: 

.. code-block:: bash
    
    0   1   2   3   4   5   6   7   8   9   10
    ------------------------------------------
    00  00  00  00  01  03  06  01  2C  02  92

Lo cual no tiene sentido y si se le aplica CRC no lo va a cumplir, 
pero el equipo no está configurado para hacer esta tarea, de eso
se tiene que encargar la app. Lo que sí va a pasar es que se van 
a guardar los comandos para esa salida y lo que se devuelve a 
la app es lo siguiente:

.. code-block:: bash
   :emphasize-lines: 10

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   {
      "0": {
        "0": "010306012C02921D4CECA6"
      },
      "1": {
        "0": "010306012C02921D4CECA6",
        "1": "00000000010306012C0292"
      },
      "2": {
        "0": "010306012C02921D4CECA6"
      },
      "3": {
        "0": "",
        "1": "062+0.535,+0.060,+29.2,+84.6,+0.064,+42.952,+23.095,+44.388,+21.661\r\n",
        "2": "062+0.535,+0.060,+29.2\r\n",
      }
   }

Donde la línea resaltada es la respuesta inválida del sensor.

Palabras clave
**************

El http request es:

.. code-block:: http

   POST /keyword HTTP/1.1
   content-type: plain/text
   content-length: 158
   host: 192.168.4.1

   "{json_key}"

Donde el json_key tiene la forma:

.. literalinclude:: variables/json_key.json
   :language: json

Y el campo ``<keyword>`` es la palabra clave, que puede ser:

erase
===== 
Borra la configuración del equipo, excepto:

- ``mac``;
- ``firm_vers``;
- ``volt_coeff`` y 
- ``unix_time``.
  
Devuelve la siguiente HTTP response:

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   Se borró toda la configuración, excepto:
	 - MAC
	 - Versión de firmware
	 - Unix time
	 - Coeficiente de voltaje

eeprom
======

Devuelve un json con la configuración de la eeprom.

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   {
      "0": {
        "0": ["hex", "010300060003E5CA", 30, 1, 4]
      },
      "1": {
        "0": ["hex", "010300060003E5CA", 30, 1, 4],
        "1": ["hex", "010300060003E5CA", 30, 1, 4]
      },
      "2": {
        "0": ["hex", "01040000000271CB", 30, 12, 1]
      },
      "3": {
        "0": ["ascii", "///TR\r\n", 1, 1, 5],
        "1": ["ascii", "///T0\r\n", 80, 1, 1],
        "2": ["ascii", "///T1\r\n", 80, 1, 1]
      },
      "other": {
        "mac": "7BF4",
        "fv": "V6.1.0",
        "unix time": 0,
        "volt. coeff.": 0.00,
        "modo_12": false,
        "offline": false 
      }
   }

Donde el json devuelto es igual al ``json_pp``, excepto que 
a los campos de las salidas se le agrega un campo llamado
``other`` que contiene información adicional. El tiempo que 
demora la respuesta es **258 ms** aproximadamente.

check
=====

Hace un chequeo de los módulos RTC externo y SD y las 
salidas. Luego le envía a la app un mensaje con el 
resultado del chequeo.

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

    {
        "0": {
            "0": "01030608D500880000ADC5"
        },
        "1": {
            "0": "",
            "1": "062+0.000,+0.001,+22.4,+72.3,+0.001,+0.697,+0.354,+0.708,+0.368\r\n",
            "2": "062+22.4,+72.3,+0.508\r\n"
        },
        "other": {
            "sdcard": true,
            "rtc": true
        }
    }
   

voltaje,<volt>
==============

Configura el coeficiente de voltaje, donde <volt> es el 
valor de voltaje de la batería en ese momento. La HTTP response es:

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   Coeficiente de voltaje seteado en:
    - 1.00

modo12
======

Activa o desactiva el modo 12.

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   Modo 12: des/activado

offline
=======

Activa o desactiva el modo offline.

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   Modo offline: des/activado

bat
===

Devuelve a la app el archivo ``battery.txt``.

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   [
      json_bat_0,   
      json_bat_1,   
      json_bat_2,
      ...   
      json_bat_n   
   ]

regall
======

Devuelve a la app el archivo ``regall.txt``.

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   [
      json_regall_0,   
      json_regall_1,   
      json_regall_2,
      ...   
      json_regall_n   
   ]

activity
========

Devuelve a la app el archivo ``activity.txt``.

.. warning:: 
   Con las 3 últimas palabras se debe hacer la petición con 
   Packet Sender o programa similar, pues los archivos son 
   muy extensos para que la app los muestre.

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

La HTTP response es:

.. code-block:: bash

   HTTP/1.1 200 OK
   Content-Type:text/plain;charset=UTF-8

   [ json_measure_0, json_measure_1, json_measure_2, json_measure_3 ] 

Donde cada ``json_measure`` es:

.. literalinclude:: variables/json_measure.json
   :language: json
   :lines: 1-8

Si los elementos del campo ``value`` están vacíos, significa que 
no se pudo medir.

Si el campo ``number_sent`` tiene valor 0, significa que no se ha 
podido enviar.

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

   [ json_measure_0, json_measure_1, ... ]   

El ESP32 manda un json cada vez porque tiene un límite de 
alrededor de 1400 caracteres por envío al cliente.

.. note:: 
   Después de descargar los datos, el archivo ``register.txt``
   no se elimina, sólo lo hará en la medida en que el equipo
   pueda mandar con éxito dichas mediciones o se hayan 
   intentado mandar 3 veces sin éxito.