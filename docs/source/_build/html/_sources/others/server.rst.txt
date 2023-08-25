Comunicación con el servidor
############################

.. sectnum::
   :depth: 1
   :suffix: .-
   :start: 7

.. contents:: 

Funcionamiento
**************

Una vez que los paquetes de mediciones están hechas, los paquetes 
se mandan al servidor cuya dirección es:

.. code-block:: console
   
   https://us-central1-briste-biot.cloudfunctions.net/updateProduct

Se hace una petición POST con cada paquete con el módulo 
SIM808 como el del siguiente ejemplo:

.. code-block:: http

   POST /updateProduct HTTP/1.1
   Host: us-central1-briste-biot.cloudfunctions.net
   Content-Type: text/plain
   Content-Length: <length>

   {
      "enabled": true,
      "id": "L-7BF4",
      "product": "THSST",
      "timestamp": "2023-04-20-12-18-42",
      "location": {
         "latitude": -31.39167023,
         "longitude": -64.22102356
      },
      "value": {
         "sn": "00000000001",
         "humidity": 0.00,
         "temperature": 22.08,
         "location_name": "BIOT-",
         "tag_depth": 10,
         "loss_tangent": 0.00,
         "electrical_conductivity": 0,
         "electrical_conductivity_tc": 0.00,
         "real_dielectric_permittivity": 0.00,
         "real_dielectric_permittivity_tc": 0.00,
         "imag_dielectric_permittivity": 0.00,
         "imag_dielectric_permittivity_tc": 0.00,
         "level_bat": 0.000
      },
      "verFirm": "V1.0.15",
      "verHard": "V1.0.0",
      "number_sent": 0
      }

El servidor puede contestar con los siguientes códigos de 
error.

200: Petición ok
****************

Petición procesada exitosamente. Si se le envía el ``http 
request`` del ejemplo, entonces el servidor responde:

.. code-block:: http

   HTTP/1.1 200 OK
   Content-Type: application/json
   Content-Length: <length>

   {
      "message": "Se actualizaron los datos de L-7BF4",
      "timestamp": "2023-07-16T23:26:06"
   }

400: Problema con el JSON
=========================

El paquete json entero posiblemente esté mal formado. Si 
se le envía el ``http request`` del ejemplo con algún error, 
entonces el servidor responde:

.. code-block:: http

   HTTP/1.1 400 Bad Request
   Content-Type: application/json
   Content-Length: <length>

   {
    "message": "Error al parsear el body: {\r\n  
    \"enabled\": true,\r\n  \r\n  \"product\": \"THSST\",
    \r\n  \"timestamp\": \"2023-04-20-12-18-42\",\r\n  
    \"location\": {\r\n    \"latitude\": -31.39167023,\r\n
   \"longitude\": -64.22102356\r\n  },\r\n  
   \"value\": {\r\n    \"sn\": \"00000000001\",\r\n
   \"humidity\": 0.00,\r\n    \"temperature\": 
   22.08,\r\n    \"location_name\": \"BIOT-\",\r\n
   \"tag_depth\": 10,\r\n    \"loss_tangent\": 0.00,\r\n
   \"electrical_conductivity\": 0,\r\n    
   \"electrical_conductivity_tc\": 0.00,\r\n    
   \"real_dielectric_permittivity\": 0.00,\r\n    
   \"real_dielectric_permittivity_tc\": 0.00,\r\n    
   \"imag_dielectric_permittivity\": 0.00,\r\n    
   \"imag_dielectric_permittivity_tc\": 0.00,\r\n    
   \"level_bat\": 0.000\r\n  },\r\n  \"verFirm\": 
   \"V1.0.15\",\r\n  \"verHard\": \"V1.0.0\",\r\n  
   \"number_sent\": 0\r\n}"
   }

404: Problema con PRODUCT
=========================

El campo ``product`` no es válido. Si se le envía el 
mismo ``http request`` del ejemplo, pero con el siguiente 
campo modificado:

.. code-block:: json

   "product": "dsTHSST",

El servidor responde:

.. code-block:: http

   HTTP/1.1 404 Not Found
   Content-Type: application/json
   Content-Length: <length>

   {
      "message": "Error PRODUCT: dsTHSST no válido."
   }

405: Problema con ID
====================

Problemas con el campo ``id``, no es válido. Si se le 
envía el mismo ``http request`` del ejemplo, pero con el 
siguiente campo modificado:

.. code-block:: json

   "id": "",

El servidor responde:

.. code-block:: http

   HTTP/1.1 405 Method Not Allowed
   Content-Type: application/json
   Content-Length: <length>

   {
      "message": "Error ID no valido"
   }

406: Problema con SN
====================

Problemas con el campo ``sn``, la longitud es menor a 
4 caracteres. Si se le envía el mismo ``http request`` 
del ejemplo, pero con el siguiente campo modificado:

.. code-block:: json

   "sn": "01",

El servidor responde:

.. code-block:: http

   HTTP/1.1 406 Not Acceptable
   Content-Type: application/json
   Content-Length: <length>

   {
      "message": "Error SN no valido"
   }

407: Problema con LOCATION
==========================

enviados son [0,0]

408: Problema con el TAG_DEPTH  
==============================

no es válido. Fuera del  rango [000, 9999]

460: Problema con la LATITUDE
=============================

feura de  rango de [-90, 90]

461: Problema con LONGITUDE 
====================================

fuera del  rango de [-180, 180]

462: Problema con LOCATION  
==========================

Revisar los  campos "latitude" & "longitude"

463: Problema con el TIMESTAMP
==============================

mal formado,  debe seguir con el formato YYYY-MM-DD-HH-MM-SS. Por 
ejemplo: 2021-10-15-12-06-18

464: Problema con el TIMESTAMP
==============================

fuera de rango 

500: Problema del servidor 
==========================

Problema interno del servidor a la hora de guardar los datos




