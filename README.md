# Evaluación-de-medios-filtrantes-con-arduino

# Construcción de un sistema arduino medidor de vacio para la valución de medios filtrantes empleados en el beneficio de minerales.

## Este procyecto forma parte de mi trabajo de tesis de la carrera de ingeniería química metalúrgica de la Facultad de Química de la UNAM.

- Se diseño y construyó un equipo que permite medir el vacío en una prueba de filtración.

- El programa permite establecer la comunicación serial entre la placa y una hoja de cálculo en excel.

- Adicionalmente se construyo un equipo generador de vacio en conjunto con un sistema de filtrado.

## El sistema completo luce así:

![Equipo construido](/imgs/sistema_completo_verde.jpg)


Se empleó una tarjeta arduino UNO junto con un sensor de presión BMP180.
También se utilizó una pantalla LCD, un par de botones que inician y detienen el registro de los datos en la hoja de cálculo de Excel y un par de leds que indican si se esta o no efectuando el registro de datos.


# Componentes electrónicos
![Dispositivos electrónicos empleados](/imgs/dispositivos_electronicos_verde.jpg)


![Detalle protoboard](/imgs/proto_11.jpg)


# Diagrama del sistema de filtrado
![Diagrama sistema](/imgs/sistema_mason.png)

# Diagrama de conexiones
![Diagrama conexiones](/imgs/esquema_proyecto_bb.png)


# Comunicación Arduino-Excel
Para establecer la comunicación serial entre la tarjeta arduino y la hoja de cálculo, se empleo el programa Parallax Data Acquisition tool (PLX-DAQ) software add-in for Microsoft Excel. Este complemento se puede descargar en la [página oficial del software](https://www.parallax.com/package/plx-daq/). También se ha incluido el los archivos de este repositorio. 




