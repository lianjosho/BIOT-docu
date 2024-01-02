Cambios o propuestas de mejora
##############################

.. sectnum:: 
   :suffix: .-
   :start: 7
   :depth: 2

.. contents::

Actualización del ``json_meta``
*******************************

Se propone cambiar el ``json_measure`` de la siguiente manera. Que 
pase de ser:

.. code-block:: json

  {
    "id": "L-7BF4",
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

a ser:

.. code-block:: json

  {
    "id": "L-7BF4",
    "soil": "Franco arcillo arenoso",
    "name": "hola",
    "verFirm": "7.4.1",
    "verHard": "1.1.0",
    "location": {
      "lat": -31.39163971,
      "long": -64.22101593
    },
    "outs": {
      "1": {
        "type": "the",
        "depth": "10.00"
      }
    },
    "cred": {
      "apn": "datos.personal.com",
      "user": "datos",
      "pwd": "datos"
    }
  }

Los cambios son:

- El campo ``soil_type`` pasa a llamarse ``soil``.
- El campo ``location_name`` pasa a llamarse ``name``.
- Los campos ``latitude`` y ``longitude`` pasan a llamarse ``lat`` y 
  ``long``, respectivamente.
- El campo ``tag_depth`` con valor decimal pasa a llamarse ``depth`` con 
  valor entero (debe dividirse por 100 para procesamiento).
- Los campos de salida ``0000000000x`` pasan a tener de nombre sin ceros,
  así ocupan menos caracteres.
- Se agregan los campos ``verFirm`` y ``verHard``.

**Nota:** estos últimos campos se agrega aquí y se quitan del 
``json_measure`` porque cuando se cambia la placa (cambio de hardware), se 
debe hacer una configuración nueva. Lo mismo sucede cuando se carga un nuevo
firmware.

Actualización del ``json_measure``
**********************************

Se propone cambiar el ``json_measure`` de la siguiente manera. Que 
pase de ser:

.. code-block:: json

  {
    "enabled": true,
    "id": "L-7BF4",
    "product": "THSST",
    "timestamp": "2024-08-31-14-10-36",
    "location": {
      "latitude": -31.44023323,
      "longitude": -64.2040863
    },
    "value": {
      "sn": "00000000001",
      "humidity": 0.79,
      "temperature": 23.65,
      "location_name": "hola",
      "tag_depth": 10,
      "loss_tangent": 0.000,
      "electrical_conductivity": 0,
      "electrical_conductivity_tc": 0,
      "real_dielectric_permittivity": 0,
      "real_dielectric_permittivity_tc": 0,
      "imag_dielectric_permittivity": 0.00,
      "imag_dielectric_permittivity_tc": 0.00,
      "level_bat": 0.013,
      "ph": 7.16
    },
    "verFirm": "V5.2.1",
    "verHard": "V1.0.0",
    "number_sent": 0
  }

por el siguiente:

.. code-block:: json

  {
    "id": "L-7BF4",
    "timeStamp": "2024-08-31-14-10-36",
    "out": 1,
    "bat": 1205,
    "number_sent": 2,
    "data": {
      "T": 2365,
      "H": 79,
      "E": 256,
      "N": 10,
      "P": 20,
      "K": 30,
      "L": 562,
      "PH": 756
    }
  }

En donde se proponen los siguientes cambios:

- Se eliminan los campos ``enabled``, ``product``, 
  ``location``, ``location_name``, ``verFirm`` y 
  ``verHard``; los cuales ocupan espacio y no se usan en 
  ningún lado del proyecto.
  En el caso de ``location``, no es necesario mandarlo 
  aquí porque ya se lo envía en el ``json_meta``.
- El campo ``sn`` que es un String con varios cero pasa 
  a llamarse ``out`` y es un entero; así ocupa menos 
  caracteres.
- Los campos dentro de ``value`` se cambian de nombre por 
  una letra (a lo sumo 2), así ocupan menos caracteres. 
- Los campos de la temperatura (T), humedad (H), distancia
  (L), valor de ph (PH) y nivel de batería (bat) pasan de 
  ser decimales a ser enteros. Con esto se espera que se 
  solucione el tema de valores NULL y de que haya muchos 
  decimales a la hora de crear el json. 

**Nota**: los campos T, H, PH y bat se deben dividir por 
100 para mostrarlos o procesarlos, y a L se lo debe 
dividir por 1000.
