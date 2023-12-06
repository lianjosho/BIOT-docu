Comunicación con el servidor
############################

.. sectnum::
   :depth: 1
   :suffix: .-
   :start: 7

.. contents:: 

Dada de alta de un punto
************************

Para configurar un punto, el equipo manda a la siguiente dirección:

.. code-block:: console

    https://us-central1-briste-biot.cloudfunctions.net/setMetadata

el siguiente metadata en una HTTP POST request: 

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

Si está todo ok, el servidor responde lo siguiente:

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

Entonces el equipo no pone el bool ``pending_config`` en alto y 
le responde a la app que la configuración se realizó 
exitosamente.

Actualización de las mediciones
*******************************

Una vez que los paquetes de mediciones están hechas, se mandan al 
servidor cuya dirección es:

.. code-block:: console
   
   https://us-central1-briste-biot.cloudfunctions.net/updateProduct

Se hace una petición POST con cada paquete con el módulo 
SIM808 como el del siguiente ejemplo:

.. code-block:: http

    POST /updateProduct HTTP/1.1
    Content-Type: text/plain
    User-Agent: Insomnia/2023.5.7
    Host: us-central1-briste-biot.cloudfunctions.net
    Content-Length: 679

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

El servidor puede contestar con los siguientes códigos de 
error.

200: Petición ok
================

Petición procesada exitosamente. Si se le envía el ``http 
request`` del ejemplo, entonces el servidor responde:

.. code-block:: http

    HTTP/2 200 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327ufhdlkwk
    x-cloud-trace-context: 979ccf0190118773a1eea5b3ecf09a2d
    date: Fri, 29 Sep 2023 14:24:35 GMT
    server: Google Frontend
    content-length: 83
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000

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

    HTTP/2 400 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327ad9l5bl2
    x-cloud-trace-context: d6c3aacad50eff5163d7da9a5951f2ea;o=1
    date: Fri, 29 Sep 2023 14:25:07 GMT
    server: Google Frontend
    content-length: 691
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000

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

El campo ``product`` no es válido. Si se le envía el mismo 
``http request`` del ejemplo, pero con el siguiente campo 
modificado:

.. code-block:: console

   "product": "TdddHSST"

El servidor responde:

.. code-block:: http

    HTTP/2 404 
    content-type: application/json; charset=utf-8
    function-execution-id: 43276bbpevjg
    x-cloud-trace-context: 0dd0a36ff048bebced564210d3b47720;o=1
    date: Fri, 29 Sep 2023 14:26:16 GMT
    server: Google Frontend
    content-length: 49
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000

    {
        "message": "Error PRODUCT: TdddHSST no válido."
    }

405: Problema con ID
====================

Problemas con el campo ``id``, no es válido. Si se le 
envía el mismo ``http request`` del ejemplo, pero con el 
siguiente campo modificado:

.. code-block:: console

    "id": "",

El servidor responde:

.. code-block:: http

    HTTP/2 405 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327iobihsgs
    x-cloud-trace-context: 38fcb81db56be11f4755c004f82af3d5;o=1
    date: Fri, 29 Sep 2023 14:27:08 GMT
    server: Google Frontend
    content-length: 32
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000

    {
        "message": "Error ID no valido"
    }

406: Problema con SN
====================

Problemas con el campo ``sn``, la longitud es menor a 
4 caracteres. Si se le envía el mismo ``http request`` 
del ejemplo, pero con el siguiente campo modificado:

.. code-block:: console

    "sn": "01",

El servidor responde:

.. code-block:: http

    HTTP/2 406 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327phq6x3pu
    x-cloud-trace-context: 4bda6dc1b80f87f11d724dee1aafe24c;o=1
    date: Fri, 29 Sep 2023 14:29:09 GMT
    server: Google Frontend
    content-length: 32
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000

    {
        "message": "Error SN no valido"
    }

407: Problema con LOCATION
==========================

Problemas con el campo ``location``, tiene valores nulos. Si se 
le envía el mismo ``http request`` del ejemplo, pero con el 
siguiente campo modificado:

.. code-block:: console

    "location": {
        "latitude": 0,
        "longitude": 0
    }

El servidor responde:

.. code-block:: http

    HTTP/2 407 
    content-type: application/json; charset=utf-8
    function-execution-id: 43275yhfqgp3
    x-cloud-trace-context: 0f1e3a8038c542871411b216cdcb6420;o=1
    date: Fri, 29 Sep 2023 14:30:16 GMT
    server: Google Frontend
    content-length: 38
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000

    {
    	"message": "Error LOCATION no valido"
    }

408: Problema con el TAG_DEPTH  
==============================

Problemas con el campo ``tag_depth``, está fuera de rango. Si se 
le envía el mismo ``http request`` del ejemplo, pero con el 
siguiente campo modificado:

.. code-block:: console

    "tag_depth": -1 (o 1001)

El servidor responde:

.. code-block:: http

    HTTP/2 408 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327fjv706qh
    x-cloud-trace-context: c073c93c7b38e7fd887ca80b5567ebdf
    date: Fri, 29 Sep 2023 14:31:18 GMT
    server: Google Frontend
    content-length: 60
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000

    {
    	"message": "Error TAG_DEPTH fuera de rango en cm. [0,1000]"
    }

460: Problema con la LATITUDE
=============================

Problemas con el campo ``latitude``, está fuera del rango 
[-90; 90]. Si se envía el mismo ``http request`` del ejemplo, 
pero con el siguiente campo modificado:

.. code-block:: console

    "latitude": -121.39164543

El servidor responde:

.. code-block:: http

    HTTP/2 460 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327styqcgqb
    x-cloud-trace-context: 0cef79a5a2f24ce400d58f2711933b53;o=1
    date: Fri, 29 Sep 2023 13:58:02 GMT
    server: Google Frontend
    content-length: 70
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000

    {
        "message": "Error LATITUDE: -121.39164543 fuera del rango [-90, 90]."
    }

461: Problema con LONGITUDE 
===========================

Problemas con el campo ``latitude``, está fuera del rango 
[-180; 180]. Si se envía el mismo ``http request`` del ejemplo, 
pero con el siguiente campo modificado:

.. code-block:: console

    "longitude": -264.22100067

El servidor responde:

.. code-block:: http

    HTTP/2 461 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327ypc89obe
    x-cloud-trace-context: 02409f5d3ff5c00d0db21e2abdd20452;o=1
    date: Fri, 29 Sep 2023 14:04:12 GMT
    server: Google Frontend
    content-length: 73
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000
    
    {
        "message": "Error LONGITUDE: -264.22100067 fuera del rango [-180, 180]."
    }

462: Problema con LOCATION  
==========================

Problemas con el campo ``location``, está mal formado. Si se 
envía el mismo ``http request`` del ejemplo, pero con el 
siguiente campo modificado:

.. code-block:: console

    "location": {
        "le": -31.39164543,
        "longitude": -64.22100067
    }

El servidor responde:

.. code-block:: http

    HTTP/2 462 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327uzdwybk9
    x-cloud-trace-context: c0b28411578ea5badab2d2867b5fb1ba;o=1
    date: Fri, 29 Sep 2023 14:06:45 GMT
    server: Google Frontend
    content-length: 45
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000
    
    {
        "message": "Error al convertir la location."
    }

463: Problema con el TIMESTAMP (mal formado)
============================================

Problemas con el campo ``timestamp``, está mal formado, debe 
seguir con el formato YYYY-mm-DD-HH-MM-SS. Si se envía el 
mismo ``http request`` del ejemplo, pero con el siguiente campo 
modificado:

.. code-block:: console
    
    "timestamp": "2023-08-31T14:10:36",

El servidor responde:

.. code-block:: http

    HTTP/2 463 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327qpic95yf
    x-cloud-trace-context: 2f668064b1d64e371a0053a0363ee908;o=1
    date: Fri, 29 Sep 2023 14:09:08 GMT
    server: Google Frontend
    content-length: 43
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000
    
    {
        "message": "Error al convertir timestamp."
    }

464: Problema con el TIMESTAMP (fuera de rango)
===============================================

Problemas con el campo ``timestamp``, está fuera de rango.

- Valor mínimo: 2021-12-31-21-00-00
- Valor máximo: la hora actual del servidor

Si se envía el mismo ``http request`` del ejemplo, pero con el 
siguiente campo modificado:

.. code-block:: console
    
    "timestamp": "2024-08-31T14:10:36",

El servidor responde:

.. code-block:: http

    HTTP/2 464 
    content-type: application/json; charset=utf-8
    function-execution-id: 4327wilgms5n
    x-cloud-trace-context: f931fa672659f33450be1d334dd1697c;o=1
    date: Fri, 29 Sep 2023 14:22:11 GMT
    server: Google Frontend
    content-length: 76
    alt-svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000
    
    {
        "message": "Error fecha fuera de rango.",
        "timestamp": "29/09/2023, 11:22:11"
    }

500: Problema del servidor 
==========================

Problema interno del servidor a la hora de guardar los datos. No 
se muestra un ejemplo de lo que responde el servidor porque al 
momento de ahcer esta documentación no se ha podido simular esa 
falla.




