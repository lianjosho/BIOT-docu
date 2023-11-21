Pruebas varias
##############

.. sectnum:: 
   :suffix: .-
   :start: 9
   :depth: 2

.. contents::

Sensor PH Gemho
***************

Se realizó la siguiente prueba para ver cómo funciona el sensor PH:

- Se aliemnta el sensor.
- Se manda la trama 01 03 00 06 00 07 E4 09 cada 2 segundos apox.
- Se recolecta la respuesata y analiza.

.. role:: gbg

.. raw:: html

   <style>
      .gbg {background-color:#00ff00;} 
   </style>

.. csv-table:: Prueba sensor PH
    :header: Intento, Trama de respuesta, Tiempo (seg.)
    :widths: 2, 4, 1

    1, 01 03 0E 00 00 00 00 00 00 02 F7 00 00 00 00 00 00 E8 03, 2
    2, 01 03 0E 00 00 00 00 00 00 03 16 00 00 00 00 00 00 D8 C1, 4
    3, 01 03 0E :gbg:`08 31 0B B0 01 A1` 03 19 :gbg:`00 0D 00 3C 00 46` 16 0C, 6
    4, 01 03 0E :gbg:`08 34 0B C9 01 8E` 03 19 :gbg:`00 0C 00 38 00 43` FA 67, 8

**Conclusión**: se puede ver que después de ser alimentado, tiene que pasar 
aproximadamente 6 segundos antes de que el sensor devuelva una trama con los 
parámetros THE y NPK no nulos. 

Promediado de las mediciones
****************************

Se tomó un sensor ph y se extrajeron varios valores de los 7 
parámetros para tomar su promedio.

.. csv-table:: Valores de sensor PH
    :header: Intento, T, H, E, PH, N, P, K
    :widths: 3, 3, 3, 3, 3, 3, 3, 3 

    0, 0, 0, 7.04, 0, 0, 0
    1, 23.04, 100.00, 417, 7.32, 13, 60, 70
    2, 23.04, 100.00, 394, 7.32, 11, 56, 66
    3, 23.07, 100.00, 394, 7.32, 11, 56, 66
    4, 23.10, 100.00, 392, 7.32, 11, 55, 66
    5, 23.07, 100.00, 391, 7.32, 11, 55, 65
    6, 23.07, 100.00, 393, 7.32, 11, 55, 66
    7, 23.07, 100.00, 393, 7.32, 11, 55, 66
    8, 23.07, 100.00, 392, 7.32, 11, 55, 66
    9, 23.07, 100.00, 393, 7.32, 11, 55, 66
    10, 23.13, 100.00, 395, 7.32, 11, 56, 66
    11, 23.07, 100.00, 393, 7.32, 11, 55, 66

**Conclusión:** se toman distintas mediciones y se ve que los valores 
se quedan dentro de las tolerancias especificadas por la hoja de 
datos del sensor PH. Por lo tanto, no se necesita tomar varias
mediciones para promediarlas después. 

**Nota:** lo que sí sucede es que cuando se toman mediciones desde 
distintos sensores en un mismo entorno, las mediciones no 
coiciden y se alejan de las tolerancias.




