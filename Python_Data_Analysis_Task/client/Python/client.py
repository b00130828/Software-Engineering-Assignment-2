import numpy as np
import urllib.request
import xml.etree.ElementTree as etree
import matplotlib.pyplot as plot 

response = urllib.request.urlopen("http://localhost:8080/")
Temperature = []
Time = []
data = response.read().decode()
root = etree.fromstring(data.strip("\n"))

for reading in root.findall('reading'):
    time = reading.find('time').text
    Time.append(time[time.find(' '):])
    Temperature.append(int(reading.find('temperature').text))
    
plot.style.use('ggplot')
title_obj = plot.title("Temperature Vs Time")
plot.xlabel("Time")
plot.ylabel("Temperature")
plot.setp(title_obj,fontsize="14")
plot.plot(Time, Temperature, 'ro-')
plot.show()



