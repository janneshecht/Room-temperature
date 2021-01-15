# Room-temperature
Smashing Widget to display the current room-temperature and humidity

## Preview

ToDo: adding screenshot of widget

## Description
This project is using a Wemos D1 Mini with an DHT22-Sensor to update the current temperature and humidity in the room on a Smashing io Dashboard

## Set-up Wemos D1 Mini
1. Connect the DHT22 to your Wemos D1 Mini (used Pins are defined in the INO-Sketch)
2. Upload the Sketch to your Wemos D1 Mini

## Set-up Smashing
1. Copy the roomtemperature-directory to your widgets
2. Add the following lines to your Dashboard to include the widget
```html
    <li data-row="1" data-col="1" data-sizex="1" data-sizey="1">
      <div data-id="roomtemperature" data-view="Roomtemperature" data-title="Room Temperature" ></div>
    </li>
```
