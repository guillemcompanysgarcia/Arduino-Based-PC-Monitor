# Stat_Screen_Monitor
DIY Arduino Project with Python to Display your PC's stats (CPU temp, CPU load, GPU temp and GPU load)

TLDR: this project uses a 3,5" LCD screen to Display the PC basic stats. This project only needs an LCD screen for Arduino (like this one: https://www.aliexpress.com/item/2251832844810030.html?spm=a2g0o.order_list.0.0.48cc194dkSCymg&gatewayAdapt=4itemAdaptan) and an Arduino Uno (or a compatible board with the screen).
This project uses the UTFTGLUE library (you probably will need to install it). The Arduino code is quite simple and it's pretty modifiable.
To connect your PC with the board I use the Serial Communication Port and a Python Script. The script gets the data I want to display and it is sent to the board.
To run the script (script.pyw) you need to create a batch script to call it( Run_Script). To avoid the cmd window you need to run this last script with the launch_bat file.
To run the script in the Startup of your PC, modify OpenHardwareMonitor to open silently at Startup.
Then move the launch_bat.vbs script to the Start folder (Windows+R and type shell:startup).

To power off the screen when your PC is off change bios settings and enable (S4+S5 Erp).
If you have any concerns or doubts about this project don't mind to message me.

Thanks!
