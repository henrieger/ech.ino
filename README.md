# `Echi.ino`: Arduino-based fish tank monitoring for LABPALEO-UFPR

This is a project that uses Arduino boards for monitoring fish tanks to aid in research of actualistic taphonomy for [LABPALEO-UFPR](www.labpaleo.ufpr.br/), a paleontology lab in Curitiba, Brazil.

The projects uses an array of different types of sensors connected to Arduinos, which in turn are connected to a server, to store and visualize data of fish tanks containing decaying ophiuroids in many distinct conditions. The goal of the study is to analyze how such conditions interfere in the preservation process of those animals in nature. The paper describing the complete experiment is yet to be published.

## Architecture

The basic architecture of this project is divided in 5 layers: the sensors, the Arduinos, a server used as interface between the boards and the database, the database itself and a visualization tool. All these layers, as well as their communications, can be visualized in the image below.

![Layer schema of the project](https://github.com/henrieger/echiino/blob/main/img/layer-schema.png?raw=true)

## Sensors

The idea of this project is for the system to be able to store information of many kinds of sensors. Currently, the following are supported:

- Temperature (model [DS18B20](https://pdf1.alldatasheet.com/datasheet-pdf/view/58557/DALLAS/DS18B20.html));
- Water Level (no info on model, but check [this tutorial](https://lastminuteengineers.com/water-level-sensor-arduino-tutorial/)).

More sensors are expected to be added soon. As explained in the next section, the code for the Arduino is programmed in such a way that adding other types of sensors shoud be relatively easy.

## Arduino

In the system, the Arduinos serve as interfaces between the sensors in a tank and the central computer where our database is. It should periodically collect, convert and send readings to the server, via some communication channel (like an USB cable, for example). The image below illustrates how one of these modules of Arduino and sensors can be assembled.

// Insert TinkerCAD image of assembled module

As the needs of each tank may be distinct, and the server might not be reachable with USB cable, the code must be versatile to switch between sensors and communication media. For this purpose, two main libraries are implemented and present in the directory `arduino/src` of this repository: `sensors` and `comms` (TODO).

The `sensors` library offers a basic interface for how a sensor should behave through the `Sensor` class, defined in `sensors.h`, with functions such as `begin` and `readInput`.

The `comms` library will provide a basic inteface for many communication media. It should be based in the `Serial` standard library for Arduino.

A more in depth documentation of the Arduino code can be found in the [Project Wiki](https://github.com/henrieger/pva-paleo/wiki).

## The Server

The purpose of the server is also as interface, but this time, between the Arduinos and the database where the sensors readings should be stored. It should be able to connect with many boards, each sending its sensors' data, and store these readings in the database file presented in the `db` directory of this repository. For this, a communication protocol had to be estabilished to ensure that all the boards could be served correctly. The documentation for the server code, as well as the communication protocol, can be found in the [Project Wiki](https://github.com/henrieger/pva-paleo/wiki).

## Database

The database is a very simple SQLite file with a table for each type of sensor. Each table has the following schema:

```
SensorType(tank_id, measurement, timestamp)
```

This way, it is possible to keep track of when measurements were taken in each fish tank, providing a history if measurements throughout the entire experiment.

## Visualization Tool

The visualization tool used for accessing the dataset is a [Metabase](https://metabase.com) local instance. Metabase is a Java application that allows the construction of charts, tables and full dashboards without direct writing SQL queries (though it allows the user to write custom queries). It is very easy to instantiate and use. The idea is to build a simple dashboard that shows each tank's measurements over time, as well as some graphs comparing the metrics in different tanks with different conditions. 
