# esp32-nginxtemp
IoT sensor using ESP32 with Dallas temperature sensor and reading Nginx access logs.  
No internal network access, exposed API or VPN required. Just internet connection and a web server.

# Getting started
1. Clone repository, run bash script as service or cron job on your nginx server.  
Change variables on line 2-3 for your log file and output file if different.
2. Connect Dallas temperature sensor to your ESP32, see wiring diagram below under images. (3.3V, GND, D2 and 4.7K ohm resistor between 3.3V and D2)
3. Change variables at line 8-10 for your Wi-Fi ssid, password and your server address. (For example: yourwebserver.com)
4. Confirm that the temperature is recieved in your nginx access log by running grep like below:
````
grep "badtemp=" logs/access.log
````
5. Add index.html to your Nginx server or just use parts of the <script></script> for your own site,  
just remember to edit the getElementById as needed or adding elements with same id like temperature and footer divs.
6. ESP32 will send temperature data every 10 seconds.

## Images:
- Website:  
![example](https://github.com/user-attachments/assets/2b0d75cf-b3ae-482d-8584-b52aef73b36a)
- Hardware:  
![New Project (10)](https://github.com/user-attachments/assets/7070934d-0c15-4341-a849-02a82ba061e7)
- Wiring:  
![test](https://github.com/user-attachments/assets/2d71e6e5-caaa-49bf-95a8-22ba4aa8fa5c)
