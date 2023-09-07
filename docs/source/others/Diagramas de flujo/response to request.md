```tefcha

start

switch   HTTP\nrequest
    case updateTime
        Pone en hora el ds3231
    
    case setConfig
        if keyword
            Procesa\nkeyword
        else 
            Configura\n   equipo

    case requestMeasuring
        Realiza\nmedición\n manual

    case getHistory
        Pide\nhistorial\nen SD

end

```