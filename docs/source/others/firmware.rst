Información sobre el firmware
#############################

.. sectnum::
   :suffix: .-
   :start: 3
   :depth: 3

.. contents:: 

Almacenamiento no volatil
*************************

.. cpp:function:: void Eeprom1::setup(int argtumento)

   :param type: description of the first parameter.
   :param nitems: description of the second parameter.
   :returns: a result.
   :retval NULL: under some conditions.
   :retval NULL: under some otjnhmjnhmmmher conditions as well.


El nombre de los archivos de cabereca son ``EEPROM1.h`` y 
``EEPROM1.cpp`` porque cuando se comenzó a hacer el firmware 
se usó la librería ``EEPROM.h``. La librería que se usa a 
partir de la versión V4.0.0 es la ``Preferences.h``, que 
administra mejor el almacenamiento no volatil.

.. note:: 
   En este peoyecto se usan las palabras ``Eeprom`` y 
   ``Almacenamiento no volátil`` como sinónimos, aunque no lo 
   sean. Se da a entender que se refiere al espacio que 
   destina el ESP32 para usarlo como una memoria EEPROM.

Estructura
==========



A partir de la versión V6.0.0, la estructura que se usa para 
escribir en la eeprom es:

.. literalinclude:: variables/estructura.cpp
   :language: cpp
   :tab-width: 2


Funciones
=========

.. function:: int sumar(int num1, int num2)

    Esta función toma dos números enteros como entrada y devuelve su suma.

    :param num1: El primer número a sumar.
    :param num2: El segundo número a sumar.
    :return: La suma de los dos números.

    :Example:

    >>> resultado = sumar(5, 7)
    >>> print("El resultado es:", resultado)

    .. note::

        Puedes encontrar más información sobre la función en la sección
        `Funciones de Matemáticas <enlace-a-documentacion>`_.



