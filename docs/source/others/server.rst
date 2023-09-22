Comunicación con el servidor
############################

.. sectnum::
   :depth: 1
   :suffix: .-
   :start: 7

.. contents:: 

setMetadata
***********

Para configurar un punto, el equipo le manda al servidor el 
siguiente ``http_request``: 

.. code-block:: http

    POST /setMetadata HTTP/1.1
    Content-Type: text/plain
    User-Agent: Insomnia/2023.5.7
    Host: us-central1-briste-biot.cloudfunctions.net
    Content-Length: 354

    {
        "id": "L-7BF4",
        "product": "THSST",
        "soil_type": "Franco arcillo arenoso",
        "location_name": "hola",
        "location": {
            "latitude": -31.39163971,
            "longitude": -64.22101593
        },
        "sensors": {
            "00000000001": {
                "type": "the",
                "tag_depth": "10.00"
            }
        },
        "cred": {
            "apn": "datos.personal.com",
            "user": "datos",
            "pwd": "datos"
        }
    }

.. code-block:: http
   
    HTTP/2 200 
    content-type: application/json; charset=utf-8
    function-execution-id: xlnu4p0lt2ec
    x-cloud-trace-context: 8f5c53493268a963fecda8353c1d7583;o=1
    date: Thu, 21 Sep 2023 14:00:12 GMT
    server: Google Frontend
    content-length: 49
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000

    {
        "message": "Se actualizaron los datos de L-7BF4"
    }



updateProduct
*************

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

Problemas con el campo ``location``, tiene valores nulos. Si se 
le envía el mismo ``http request`` del ejemplo, pero con el 
siguiente campo modificado:

.. code-block:: json

    "location": {
        "latitude": 0,
        "longitude": 0
    }

El servidor responde:

.. code-block:: http

    HTTP/1.1 406 Not Acceptable
    Content-Type: application/json
    Content-Length: <length>

    {
    	"message": "Error LOCATION no valido"
    }

408: Problema con el TAG_DEPTH  
==============================

Problemas con el campo ``tag_depth``, está fuera de rango. Si se 
le envía el mismo ``http request`` del ejemplo, pero con el 
siguiente campo modificado:

.. code-block:: json

    "tag_depth": -1 (o 1001)

El servidor responde:

.. code-block:: http

    HTTP/1.1 406 Not Acceptable
    Content-Type: application/json
    Content-Length: <length>

    {
    	"message": "Error TAG_DEPTH fuera de rango en cm. [0,1000]"
    }

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




