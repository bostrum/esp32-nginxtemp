# esp32-nginxtemp
IoT sensor using ESP32 with Dallas temperature sensor and reading Nginx access logs.  
No internal network access, exposed API or VPN required. Just internet connection and a web server.

The ESP32 sends HTTP request to your web server like below every 10 seconds. Which is then read by the bash script, exported to text file, read by javascript on the website and populated in elements with id footer and temperature.  
"https://yourserver.com/?temperature=12.3"

# Example
My self-hosted example, online unless power outage. Less ess downtime than Azure/O365 (O230) though.
https://badtunna.kstad.se

# Getting started
1. Clone repository, run bash script as service or cron job on your nginx server.  
Change variables on line [2-3](https://github.com/bostrum/esp32-nginxtemp/blob/994f1878b3333f46a34faba59b8e16189650c71c/nginx_temp.sh#L2-L3) for your log file and output file if different.
2. Connect Dallas temperature sensor to your ESP32, see wiring diagram below under images. (3.3V, GND, D2 and 4.7K ohm resistor between 3.3V and D2)
3. Edit variables at lines [8-10](https://github.com/bostrum/esp32-nginxtemp/blob/994f1878b3333f46a34faba59b8e16189650c71c/esp32_temp.ino#L8-L10) in 'esp32_temp.ino' for your Wi-Fi ssid, password and your server address. (For example: yourwebserver.com). PS. There is also the 'esp32_temp_battery.ino' using deep sleep, adjust SLEEP_TIME for longer sleep and better battery life.
4. Confirm that the temperature is recieved in your nginx access log by running grep like below:
````
grep "temperature=" logs/access.log
````
5. Add index.html to your Nginx server or just use parts of the <script></script> for your own site,  
just remember to edit the getElementById as needed or adding elements with same id like temperature and footer divs.
6. ESP32 will send temperature data every 10 seconds.

# Images:
- **Website:**  
Example site for displaying temperature uploaded as index.html in the repository.
![example](https://github.com/user-attachments/assets/2b0d75cf-b3ae-482d-8584-b52aef73b36a)
- **Hardware:**  
ESP32, DS18B20 Dallas waterproof temperature sensor and a electric junction box for outdoor use.  
Cable connector for sensor cable and soon another one for power as well.
![New Project (10)](https://github.com/user-attachments/assets/7070934d-0c15-4341-a849-02a82ba061e7)  
- **Wiring:**  
Please check so pinout is the same on your Arduino before connecting.
Don't forget connecting the 4.7K ohm resistor between 3.3V and D2. I just cut the cables and soldered it in between.
![test](https://github.com/user-attachments/assets/2d71e6e5-caaa-49bf-95a8-22ba4aa8fa5c)
