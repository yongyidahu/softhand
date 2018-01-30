/*!
    \file  readme.txt
    \brief description of the enet demo
*/

/*
    Copyright (C) 2017 GigaDevice

    2014-12-26, V1.0.0, demo for GD32F10x
    2017-06-30, V2.0.0, demo for GD32F10x
*/

  This demo is based on the GD32107C-EVAL-V1.0 board, it shows how to configure the 
enet peripherals to send and receive frames in normal mode and use lwip tcp/ip 
stack to realize ping, telnet and tcp server functions. 

  JP4,JP13,JP18 and JP19 must be fitted. JP5,JP6 jump to Usart.

  It is configured in RMII mode, and 25MHz oscillator is used, the system clock 
is configured to 108MHz. Users should configure ip address, mask and gw of GD32107C-EVAL-V1.0 
board according to the actual net situation from the private defines in main.h.

  This demo realize three applications:
  1) Telnet application, the eval board acts as tcp server. Users can link 
the client with the eval board server, using 8000 port. Users can see the reply from the 
server, and can send the name(should input enter key) to server.

  2) tcp client application, the eval board acts as tcp client. Users can link 
the eval board client with the server, using 1026 port. Users can send information from server 
to client, then the client will send back the information.
 
  3) udp application. Users can link the eval board with another station, using 1025 port.
Users can send information from station to board, then the board will send back the information. 
  
  If users need dhcp function, it can be configured from the private defines in main.h.
This function is closed by default.

