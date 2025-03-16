# esp32-nginxtemp
IoT sensor using ESP32 with Dallas temperature sensor and reading Nginx access logs.  
No internal network access, exposed API or VPN required. Just internet connection and a web server.

# Getting started
1. Clone repository, run bash script as service or cron job on your nginx server.  
Change variables on line 2-3 for your log file and output file if different.
2. Connect Dallas temperature sensor to your ESP32. (3.3V, GND and D2)
3. Change variables at line 8-10 for your Wi-Fi ssid, password and your server address. (For example: yourwebserver.com)
4. Confirm that the temperature is recieved in your nginx access log by running grep like below:
````
grep "badtemp=" logs/access.log
````
5. ESP32 will send temperature data every 10 seconds.
