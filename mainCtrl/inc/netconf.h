/*!
    \file  netconf.h
    \brief the header file of netconf 
*/

/*
    Copyright (C) 2017 GigaDevice

    2014-12-26, V1.0.0, demo for GD32F10x
    2017-06-30, V2.0.0, demo for GD32F10x
*/

#ifndef NETCONF_H
#define NETCONF_H

/* function declarations */
/* initializes the LwIP stack */
void lwip_stack_init(void);
/* dhcp_task */
void dhcp_task(void * pvParameters);

#endif /* NETCONF_H */
