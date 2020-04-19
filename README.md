Smart Traffic light system
=========
## Functions:
>* Remain basic traffic light functions
>* Control the time of traffic lights according to traffic flow to improve traffic conditions
\<br> 
## System constructure
Sensors feed back data to the Raspberry Pi, and then control the running status of traffic lights through the Raspberry Pi. <br>
![system](https://github.com/UoGTeam21/TrafficLight/blob/master/images/system.jpg "system schematic diagram")
<br>
## Hardware
>* Infrared transmitter *4
>* Infrared receiver *4
>* Main road traffic lights（red light *4    ,green light *4    ,yellow light *4) 
>* Sidewalk traffic lights ( red light *4    ,green light *4) 
>* Button *4
>* RaspberryPi
## Software
>* VS
## Flowchart
The whole system follow the steps of the flow chart below: <br>
![flowchart](https://github.com/UoGTeam21/TrafficLight/blob/master/images/flowchart.jpg "system flow chart")
## Contributors
Hanzhi Zhang(2434486H): project analysis, unit test (button test, sensor test), hardware test; <br>
Xinhui Zheng(2417363Z): hardware design, PCB design, and main program; <br>
Qingxia Lee(2510350L): Entire code integration,  main program and multi-threads design.
