```tefcha

start

if      Sensor\nconfigurado
    if     Sensor\nconectado
        - Alimenta salida \n- Manda comando\n- Recibe respuesta\n- Desalimenta salida

        if Respuesta\n     válida
            Procesar info y armar json
            
            if Enviado
                Chequea mediciones guardadas
                if Enviado
                    Borra de la SD
                else 
                    if Mandado \n   más de \n  3 veces
                        Borra de la SD

                Chequea configuración pendiente
                if Enviado
                    Borra configuración\n        pendiente
            else 
                Guarda en SD

end

```