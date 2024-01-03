Desarrollador
#############

.. sectnum::
   :suffix: .-
   :start: 5
   :depth: 2

.. contents:: 

Interrupción
************



Órdenes por terminal
********************

Si se conecta un cable microUSB al ESP32, se puede enviar
(siempre que el WiFi siga activo) **órdenes por consola** para 
que el equipo haga determinadas acciones. Es como las palabras
clave pero por consola. Las órdenes son:

eeprom
======

Muestra en consola la configuración guardada en la eeprom o en el 
NVS.

.. code-block:: console

    ======================== EEPROM ========================
    Salida	Max	Power	Resp.	Tipo	Comando
    --------------------------------------------------------
    0	    11	    1	4	    hex	    010300060003E5CA
    --------------------------------------------------------
    1	    0	    1	3	    ascii  	///TR\r\n
            80	    1	1	    ascii	///T0\r\n
            60	    1	1	    ascii	///T1\r\n
    --------------------------------------------------------
    2
    --------------------------------------------------------
    3
    --------------------------------------------------------
    Mac: 7BF4           FV: V6.1.0	Unix time: 4294967226
    volt. coeff.: 1.00	Modo 12: 1	Modo offline: 0
    ========================================================

.. note:: 

	Los caracteres invisibles ``<CR>`` y ``<LF>`` se visualizan 
	como ``\r`` y ``\n``, respectivamente.

register
========

Muestra el archivo ``register.txt``, que son los paquetes 
``json_measure`` que no se mandaron.

.. code-block:: console

	Lectura desde "register.txt": 
	[
	{"enabled":true,"id":"L-7BF4","product":"THSST","timestamp":"2023-07-08-13-00-01","location":{"latitude":-31.39164543,"longitude":-64.22102356},"value":{"sn":"00000000001","humidity":1.13,"temperature":17.62,"location_name":"holas","tag_depth":10,"loss_tangent":0.000,"electrical_conductivity":0,"electrical_conductivity_tc":0,"real_dielectric_permittivity":0,"real_dielectric_permittivity_tc":0,"imag_dielectric_permittivity":0.00,"imag_dielectric_permittivity_tc":0.00,"level_bat":0.000},"verFirm":"V6.0.0","verHard":"V1.0.0","number_sent":0},
	{"enabled":true,"id":"L-7BF4","product":"THSST","timestamp":"2023-07-08-14-00-02","location":{"latitude":-31.39164543,"longitude":-64.22102356},"value":{"sn":"00000000001","humidity":1.36,"temperature":18.31,"location_name":"holas","tag_depth":10,"loss_tangent":0.000,"electrical_conductivity":0,"electrical_conductivity_tc":0,"real_dielectric_permittivity":0,"real_dielectric_permittivity_tc":0,"imag_dielectric_permittivity":0.00,"imag_dielectric_permittivity_tc":0.00,"level_bat":0.000},"verFirm":"V6.0.0","verHard":"V1.0.0","number_sent":0},
	{"enabled":true,"id":"L-7BF4","product":"THSST","timestamp":"2023-07-09-12-00-01","location":{},"value":{"sn":"00000000001","humidity":0.00,"temperature":0.00,"loss_tangent":0.000,"electrical_conductivity":0,"electrical_conductivity_tc":0,"real_dielectric_permittivity":0,"real_dielectric_permittivity_tc":0,"imag_dielectric_permittivity":0.00,"imag_dielectric_permittivity_tc":0.00,"level_bat":0.000},"verFirm":"V6.0.0","verHard":"V1.0.0","number_sent":0},
	{"enabled":true,"id":"L-7BF4","product":"THSST","timestamp":"2023-07-09-12-00-01","location":{},"value":{"sn":"00000000002","humidity":0.00,"temperature":0.00,"loss_tangent":0.000,"electrical_conductivity":0,"electrical_conductivity_tc":0,"real_dielectric_permittivity":0,"real_dielectric_permittivity_tc":0,"imag_dielectric_permittivity":0.00,"imag_dielectric_permittivity_tc":0.00,"level_bat":0.000},"verFirm":"V6.0.0","verHard":"V1.0.0","number_sent":0},
	{"enabled":true,"id":"L-7BF4","product":"THSST","timestamp":"2023-07-09-12-00-01","location":{},"value":{"sn":"00000000003","humidity":0.00,"temperature":0.00,"loss_tangent":0.000,"electrical_conductivity":0,"electrical_conductivity_tc":0,"real_dielectric_permittivity":0,"real_dielectric_permittivity_tc":0,"imag_dielectric_permittivity":0.00,"imag_dielectric_permittivity_tc":0.00,"level_bat":0.000},"verFirm":"V6.0.0","verHard":"V1.0.0","number_sent":0},
	{"enabled":true,"id":"L-7BF4","product":"THSST","timestamp":"2023-07-09-12-00-01","location":{},"value":{"sn":"00000000004","humidity":0.00,"temperature":0.00,"loss_tangent":0.000,"electrical_conductivity":0,"electrical_conductivity_tc":0,"real_dielectric_permittivity":0,"real_dielectric_permittivity_tc":0,"imag_dielectric_permittivity":0.00,"imag_dielectric_permittivity_tc":0.00,"level_bat":0.000},"verFirm":"V6.0.0","verHard":"V1.0.0","number_sent":0}
	]
	Número de json guardados = 6

.. note:: 

	Los corchetes [] están para copiar todo el contenido 
	incluyéndolos y pegarlo en un una página de edición de json, 
	como `Editor json 
	<https://jsoneditoronline.org/#left=local.dahuwa&right=local.cowiwe>`_.

sim
===

Enciende el módulo SIM808 durante 1 minuto para enviar comandos AT.


chino0
======

Enciende la salida 0 para interactuar durante 1 minuto con un 
sensor chino tipo THE. Enviando cualquier caracter, se le mandará
la trama ``THE_request``. Esto se hace para mover de lugar el sensor 
y pedirle que mida varias veces.

chino1
======

Ídem para salida 1 con sensor NPK. 


chino2
======

Ídem para salida 2 con sensor de nivel. 

rtc
===

Muestra el tiempo que tienen los RTC externo e interno.

.. code-block:: console

	rtc interno: 2023-07-14-22-51-39
	rtc externo: 2023-07-14T22:51:39

recrear
=======

Borra y vuelve a crear los archivos ``battery.txt`` y 
``register.txt``.

at command
==========

Des/activa la impresión en consola de los comandos AT enviados al 
SIM808 y su respuesta.

erase nvs 
=========

Borra de la los valores resaltados en amarillo: 

.. literalinclude:: variables/estructura.cpp
	:language: cpp
	:emphasize-lines: 2-5, 12-14

erase all
=========

Borra toda la eeprom.

voltaje,12.05
=============

Establece el coeficiente de voltaje, donde ``12.05`` es el voltaje 
de la batería en ese momento.

bat
===

Muestra el contenido de ``battery.txt``.

.. code-block:: console

	{"timeStamp":"2023-07-05-12-53-30","dur":26.775,"volts":0.028205128,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":true,"med":{"1":"OK","2":"-","3":"-","4":"-"},"antes":0,"envi":0}}, 
	{"timeStamp":"2023-07-05-14-00-01","dur":0.653,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":0,"envi":0}}, 
	{"timeStamp":"2023-07-05-15-00-02","dur":0.62,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":1,"envi":0}}, 
	{"timeStamp":"2023-07-05-16-00-01","dur":0.659,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":2,"envi":0}}, 
	{"timeStamp":"2023-07-07-15-00-00","dur":0.709,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":3,"envi":0}}, 
	{"timeStamp":"2023-07-07-16-00-01","dur":0.723,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":4,"envi":0}}, 
	{"timeStamp":"2023-07-08-10-00-02","dur":0.74,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":5,"envi":0}}, 
	{"timeStamp":"2023-07-08-11-00-01","dur":0.747,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":6,"envi":0}}, 
	{"timeStamp":"2023-07-08-12-00-01","dur":58.495,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":true,"med":{"1":"OK","2":"-","3":"-","4":"-"},"antes":7,"envi":7}}, 
	{"timeStamp":"2023-07-08-13-00-01","dur":0.652,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":0,"envi":0}}, 
	{"timeStamp":"2023-07-08-14-00-02","dur":0.656,"volts":0,"med":{"1":"OK","2":"-","3":"-","4":"-"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":1,"envi":0}}, 
	{"timeStamp":"2023-07-09-12-00-01","dur":12.808,"volts":0,"med":{"1":"error","2":"error","3":"error","4":"error"},"env":{"int":false,"med":{"1":"-","2":"-","3":"-","4":"-"},"antes":2,"envi":0}}, 
	Nro de meustras = 12

Para pegar en el editor json, se debe:

1. Copiar los paquetes.
2. Abrir el editor json online.
3. Poner corchetes [].
4. Dentro de los corchetes, pegar el contenido copiado.
5. Borrar la última coma después del último paquete.

regall
======

Muestra el contenido de ``regall.txt``, que es en donde están 
todas las mediciones hechas, enviadas o no.

Parámetros del proyecto
***********************






