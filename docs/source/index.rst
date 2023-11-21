Bienvenido a la documentación de BIOT
#####################################

El equipo **BIOT** se distingue por las siguientes características:

1. ``Núcleo basado en ESP32:`` el equipo está equipado con un 
   microcontrolador ESP32 de alto rendimiento como su componente 
   principal. Esta potente plataforma ofrece capacidades de procesamiento 
   avanzadas y soporte para una amplia gama de aplicaciones.

2. ``Conexión de múltiples tipos de sensores:`` el equipo BIOT es 
   compatible con tres tipos de sensores: de temperatura, humedad y 
   de nivel (the), de nutrientes (NPK) y de nivel. Estos sensores 
   se pueden conectar de forma simultánea, lo que permite una 
   monitorización integral y precisa de diversos parámetros ambientales.

3. ``Hasta 4 sensores simultáneos:`` el equipo BIOT tiene la capacidad de 
   conectar hasta cuatro sensores al mismo tiempo. Esto brinda 
   flexibilidad y versatilidad al permitir la adquisición de datos 
   de múltiples fuentes de manera simultánea.

4. ``Comunicación mediante protocolo RS485:`` el equipo BIOT utiliza el 
   protocolo RS485 para la comunicación de datos. Este protocolo 
   robusto y confiable permite una transferencia eficiente de 
   información entre el equipo y otros dispositivos compatibles.

5. ``Transmisión de datos a través de módulo SIM808:`` los datos 
   recopilados por el equipo BIOT se envían a un servidor remoto 
   mediante un módulo SIM808. Esta conexión facilita la transmisión 
   continua de datos en tiempo real, lo que permite un monitoreo 
   remoto y un análisis en tiempo real de las mediciones realizadas.

6. ``Almacenamiento de datos en tarjeta SD:`` en caso de que no sea posible
   la transmisión de datos al servidor, el equipo BIOT cuenta con la 
   capacidad de almacenar los datos en una tarjeta SD. Esto garantiza 
   que no se pierdan las mediciones y se puedan recuperar 
   posteriormente para su análisis.

7. ``Aplicación para configuración y control:`` el equipo BIOT cuenta con 
   una aplicación móvil dedicada que permite configurar y controlar 
   el equipo de manera sencilla. Mediante esta aplicación, es posible 
   ajustar los parámetros de funcionamiento, solicitar el registro 
   de mediciones no enviadas y realizar mediciones manuales según sea 
   necesario.

8. ``Mediciones automáticas:`` el equipo BIOT está diseñado para realizar 
   mediciones de manera automática. Esto significa que, una vez 
   configurado, el equipo adquiere y registra los datos de los 
   sensores de forma periódica y continua, brindando una 
   monitorización constante y precisa del entorno.

En resumen, el equipo BIOT ofrece un conjunto completo de 
características que lo convierten en una solución integral para la 
adquisición de datos y el monitoreo ambiental. Con su capacidad de 
conectar múltiples sensores, opciones de comunicación versátiles y 
funcionalidades adicionales como almacenamiento local y una 
aplicación de control, el equipo BIOT es una herramienta confiable 
y eficiente para diversas aplicaciones en el campo de la 
monitorización y la investigación científica.

Contenido
#########

.. figure:: others/images/logo.png
   :align: center
   :width: 400px
   :alt: Descripción de la imagen

.. toctree::
   :maxdepth: 2

   others/description
   others/components
   others/firmware
   others/sensors
   others/app
   others/sd
   others/server
   others/developer
   others/misc_test
   others/bugs
   others/changelog



.. # with overline, for parts
.. * with overline, for chapters
.. = for sections
.. - for subsections
.. ^ for subsubsections
.. " for paragraphs