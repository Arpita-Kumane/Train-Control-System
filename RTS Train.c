//
// serial.c / serial.cpp
// A simple serial port writing example
// Written by Ted Burke - last updated 13-2-2013
//
// To compile with MinGW:
//
//      gcc -o serial.exe serial.c
//
// To compile with cl, the Microsoft compiler:
//
//      cl serial.cpp
//
// To run:
//
//      serial.exe
//
 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


int main()
{
	
    // Define the five bytes to send ("hello")
    char bytes_to_send[3];
	char menu_option;
	
/*  bytes_to_send[0] = 254;
    bytes_to_send[1] = 11;
    bytes_to_send[2] = 157; */
    
	

    printf("**************Train Control System*******************\n");
    printf("------------------------------------------\n");
	printf("------------------------------------------\n");
	printf("------------------------------------------\n");
	
    do{
		printf("Main Menu\n");
		printf("0. Forward direction.\n");
		printf("1. Start.\n");
		printf("2. Accelerate.\n");
		printf("3. Decelerate.\n");
		printf("4. Stop.\n");
		printf("5. Ring the Bell.\n");
		printf("6. Reverse direction.\n");
		printf("7. Exit. \n");
		printf(" Please enter an option from the main menu:\n");
		printf("------------------------------------------\n");
		printf("------------------------------------------\n");
		scanf("%c",&menu_option);
		



    switch(menu_option)
	{
    case '0':
	    bytes_to_send[0] = 254;
		bytes_to_send[1] = 11;
		bytes_to_send[2] = 128;
        break;

    case '1':
		bytes_to_send[0] = 254;
		bytes_to_send[1] = 11;
		bytes_to_send[2] = 198;
        break;
		
    case '2':
		bytes_to_send[0] = 254;
		bytes_to_send[1] = 11;
		bytes_to_send[2] = 232;
        break;
		
    case'3':
        bytes_to_send[0] = 254;
		bytes_to_send[1] = 11;
		bytes_to_send[2] = 196;
        break;
		
    case'4':
		bytes_to_send[0] = 254;
		bytes_to_send[1] = 11;
		bytes_to_send[2] = 192;
        break;
		
    case'5':
		bytes_to_send[0] = 254;
		bytes_to_send[1] = 11;
		bytes_to_send[2] = 157;
        break;
		
	case'6':
	    bytes_to_send[0] = 254;
		bytes_to_send[1] = 11;
		bytes_to_send[2] = 131;
		break;
		
	case '7':
	    break;

	}

	// } while(menu_option !='f');
 
	/* int i;
	for(i=0;i<3;i++)
	{
		char c = bytes_to_send[i];
		int j;
		for(j = 0; j < 8; j++){
			printf("%d",!!((c<<j)&0x80));
		}
	} */
	
	//printf("\n");
	//printf("Char Array:%c\r\n",(char*)bytes_to_send);
	//while(1) { }
 
    // Declare variables and structures
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
         
    // Open the highest available serial port number
   // fprintf(stderr, "Opening serial port...\n");
    hSerial = CreateFile(
                "\\\\.\\COM1", GENERIC_READ|GENERIC_WRITE, 0, NULL,
                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
    if (hSerial == INVALID_HANDLE_VALUE)
    {
            fprintf(stderr, "Error\n");
            return 1;
    }
    // else fprintf(stderr, "OK\n");
     
    // Set device parameters (38400 baud, 1 start bit,
    // 1 stop bit, no parity)
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (GetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error getting device state\n");
        CloseHandle(hSerial);
        return 1;
    }
     
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if(SetCommState(hSerial, &dcbSerialParams) == 0)
    {
        fprintf(stderr, "Error setting device parameters\n");
        CloseHandle(hSerial);
        return 1;
    }
 
    // Set COM port timeout settings
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if(SetCommTimeouts(hSerial, &timeouts) == 0)
    {
        fprintf(stderr, "Error setting timeouts\n");
        CloseHandle(hSerial);
        return 1;
    }
 
    // Send specified text (remaining command line arguments)
    DWORD bytes_written, total_bytes_written = 0;
   // fprintf(stderr, "Sending bytes...\n");
    if(!WriteFile(hSerial, bytes_to_send, 3, &bytes_written, NULL))
    {
        fprintf(stderr, "Error\n");
        CloseHandle(hSerial);
        return 1;
    }   
  //  fprintf(stderr, "%d bytes written\n", bytes_written);
     
    // Close serial port
   // fprintf(stderr, "Closing serial port...\n");
    if (CloseHandle(hSerial) == 0)
    {
        fprintf(stderr, "Error\n");
        return 1;
    }
   // fprintf(stderr, "OK\n");
	
	//while(1) { }
 
    // exit normally
} while(menu_option !='7');
	getch ();
    return 0;
	
}