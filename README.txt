Sound Detection Program version 1.0 28/12/2015

GENERAL USAGE NOTES
==========================
- This program record sound as 1-second long wave files with 16000 samples for
each second using the Raspberry Pi, an external soundcard and microphone. 
Afterward, it calculate the decibel values and display them in form of bars on 
the terminal screen.

- The web application in this project take the request from the client,
calculate the average value of the 8 sent data pieces for each second and display
it on the chart. When pointing the cursor to each second point on the graph,
the user  can see the exact decibel value at that time point. 

INSTALLATION REQUIREMENTS
==========================
- It is required that the system has cURL library installed for data transfering.

CONTRIBUTOR
==========================
Name : Nguyen Ha
ID   : e1500968
Email: nguyenthuha13101997@gmail.com


COPYRIGHT AND LICENSING INFORMATION
==========================
This project is unregisted and is not subjected to any copyright, trademark, patent
and/or other laws. The Google Chart portions of this page are modifications based 
on work created and shared by Google and used according to terms described in the 
Creative Commons 3.0 Attribution License, which can be found in the following link:
'http://creativecommons.org/licenses/by/3.0/'. 
