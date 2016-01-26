/**************************************************************************
    Souliss - Sleeping
    
    A battery operated node (Peer) is activated on press of a pushbutton and/or on
    time base, each time the node wake-ups it sends data to the gateway (that is always
    powered on).
    
    Run this code on one of the following boards:
      - Arduino with Nordic nRF24L01 or nRF24L01+
      
    As option you can run the same code on the following, just changing the
    relevant configuration file at begin of the sketch
      - Chibiduino v1
      - Moteino
      
***************************************************************************/

// Let the IDE point to the Souliss framework
#include "SoulissFramework.h"

// Configure the framework
#include "bconf/StandardArduino.h"          // Use a standard Arduino
#include "conf/ethW5100.h"                  // Ethernet through Wiznet W5100
#include "conf/nRF24L01.h"
#include "conf/Gateway.h"                   // The main node is the Gateway
#include "conf/DynamicAddressing.h"         // Use dynamic addressing

// Include framework code and libraries
#include <SPI.h>
#include <EEPROM.h>

/*** All configuration includes should be above this line ***/ 
#include "Souliss.h"

// Define the network configuration according to your router settings
uint8_t ip_address[4]  = {192, 168, 1, 77};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 1, 1};
#define myvNet_address  ip_address[3]       // The last byte of the IP address (77) is also the vNet address

void setup()
{   
    Initialize();
    
    // Set network parameters
    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);                          // Address on the Ethernet interface
    SetAsGateway(myvNet_address);                                                       // Set this node as gateway for SoulissApp  

    // Set networking parameters for the radio
    SetAddress(0x6501, 0xFF00, 0x0000);

	// List of peer nodes
	SetAsBatteryNode(0x6502, 1);
	SetAsBatteryNode(0x6503, 2);

}

void loop()
{   
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   
        
        // Here we process the communication
        FAST_GatewayComms();        
    }   
} 
