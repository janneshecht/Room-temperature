# Room-temperature
Smashing Widget to display the current room-temperature and humidity

## Preview
[![Room-temperature-Widget.png](https://i.postimg.cc/QdLkKtCk/Room-temperature-Widget.png)](https://postimg.cc/Xp8yTnwp)

## Description
This project is using a Wemos D1 Mini with an DHT22-Sensor to update the current temperature and humidity in the room on a Smashing io Dashboard

## Set-up Smashing
1. Copy the roomtemperature-directory to your widgets
2. Add the following lines to your Dashboard to include the widget
```html
<li data-row="1" data-col="1" data-sizex="1" data-sizey="1">
  <div data-id="roomtemperature" data-view="Roomtemperature" data-title="Wohnzimmer" ></div>
</li>
```
3. Set the name of the Widget in the lines you added in step 2 (Value: data-title)
4. Set a AUTH_Token in the config.ru-file of your Dashboard

## Set-up Wemos D1 Mini
1. Connect the DHT22 to your Wemos D1 Mini (used Pins are defined in the INO-Sketch)
2. Download the Sketch and change the following values:
 - Wifi-name
 - Wifi-password
 - AUTH_Token (set up in step 4 by setting up Smashing)
 - URL to your Dashboard
3. Upload the Sketch to your Wemos D1 Mini
