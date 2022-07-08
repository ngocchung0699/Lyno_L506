#include "AT_command.h"

//* List AT command, return check, check ok, check error


char AT_Send_Check_Module[]             =           "AT\r\n";				            // 1		OK		
char send_Checking_Module[]             =           "Checking Module Sim\r\n";
char send_Check_Module_Error[]          =           "Check Module Error\r\n";
char send_Check_Module_Ok[]             =           "Check Module Ok\r\n";

char AT_Send_Check_Sim[]                =           "AT+CPIN?\r\n";			            // 2        OK
char send_Checking_Sim[]                =           "Checking Sim\r\n";
char send_Check_Sim_Error[]             =           "Check Sim Error\r\n";
char send_Check_Sim_Ok[]                =           "Check Sim Ok\r\n";

char AT_Send_Check_Signal[]             =           "AT+CSQ\r\n";		                // 2        OK
char send_Checking_Signal[]             =           "Checking Signal\r\n";
char send_Check_Signal_Error[]          =           "Check Signal Error\r\n";
char send_Check_Signal_Ok[]             =           "Check Signal Ok\r\n";

char AT_Send_Check_Subscribe[]          =           "AT+CREG?\r\n";				        //2         OK
char send_Checking_Subscribe[]          =           "Checking Subscribe\r\n";
char send_Check_Subscribe_Error[]       =           "Check Subscribe Error\r\n";
char send_Check_Subscribe_Ok[]          =           "Check Subscribe Ok\r\n";

char AT_Send_Check_GPRS[]               =           "AT+CGATT?\r\n";				    //2        OK
char send_Checking_GPRS[]               =           "Checking GPRS\r\n";
char send_Check_GPRS_Error[]            =           "Check GPRS Error\r\n";
char send_Check_GPRS_Ok[]               =           "Check GPRS Ok\r\n";

char AT_Send_Set_Timeout[]              =           "AT+CIPTIMEOUT=30000,20000,40000,50000\r\n";   // 1   OK
char send_Setting_Timeout[]             =           "Setting Timeout\r\n";
char send_Set_Timeout_Error[]           =           "Set Timeout Error\r\n";
char send_Set_Timeout_Ok[]              =           "Set Timeout Ok\r\n";

char AT_Send_Set_Transmit_Mode[]        =           "AT+CIPMODE=0\r\n";             // 1   OK
char send_Setting_Transmit_Mode[]       =           "Setting Transmit Mode\r\n";
char send_Set_Transmit_Mode_Error[]     =           "Set Transmit Mode Error\r\n";
char send_Set_Transmit_Mode_Ok[]        =           "Set Transmit Mode Ok\r\n";

char AT_Send_Check_Net_Open[]           =           "AT+NETOPEN\r\n";               //2       SUCCESS
char send_Checking_Net_Open[]           =           "Checking Internet\r\n";
char send_Check_Net_Open_Error[]        =           "Check Internet Error\r\n";
char send_Check_Net_Open_Ok[]           =           "Check Internet Ok\r\n";

char AT_Send_Check_IP[]                 =           "AT+IPADDR\r\n";				 //2		 OK
char send_Checking_IP[]                 =           "Checking IP\r\n";
char send_Check_IP_Error[]              =           "Check IP Error\r\n";
char send_Check_IP_Ok[]                 =           "Check IP Ok\r\n";

char AT_Send_Set_Receive_Mode[]         =           "AT+CIPRXGET=0,1\r\n";	    //1         OK
char send_Setting_Receive_Mode[]        =           "Setting Receive Mode\r\n";
char send_Set_Receive_Mode_Error[]      =           "Set Receive Mode Error\r\n";
char send_Set_Receive_Mode_Ok[]         =           "Set Receive Mode Ok\r\n";

char AT_Send_Transmit_Data_To_TCP[]     =           "AT+CIPSEND=1,,,,";       // 1  +CIPSEND:SUCCESS,1,1,1<\r><\n>

char send_Transmiting_Data_To_TCP[]     =           "Transmiting Data To TCP\r\n";
char send_Transmit_Data_To_TCP_Error[]  =           "Transmit Data To TCP Error\r\n";
char send_Transmit_Data_To_TCP_Ok[]     =           "Transmit Data To Ok\r\n";

char AT_Send_Get_Current_Time[]         =           "AT+CCLK?\r\n";  //2   +CCLK: "22/07/08,15:20:19+28"<\r><\n>


char set_Connect_TCP[50];
char code_TCP_First[] = {'A','T','+','C','I','P','O','P','E','N','=','1',',','"','T','C','P','"',',','"','\0'};
char code_TCP_IP[20];
char code_TCP_Center[] = {'"',',','\0'};
char code_TCP_Port[20];
char code_TCP_Final[] = {',','0', 0x0D, 0x0A,'\0'};

char AT_Send_Connect_TCP_Server[50];      //2  WAIT      AT+CIPOPEN=1,"TCP","117.6.163.177",7577,0        +CIPOPEN:SUCCESS,1<\r><\n>

char send_Connecting_TCP_Server[] = "Connecting TCP Server\r\n";
char send_Connect_TCP_Server_Error[] = "Connect TCP Server Error\r\n";
char send_Connect_TCP_Server_Ok[] = "Connect TCP Server Ok\r\n";      
									
char AT_Send_Check_Connect_TCP[] = "AT+CIPOPQUERY?\r\n";  //2      +CIPOPQUERY:0,1,0,0,0,0,0,0,0,0<\r><\n><\r><\n>OK<\r><\n>
char send_Checking_Connect_TCP[] = "Checking Conect TCP\r\n";
char send_Check_Connect_TCP_Error[] = "Check Conect TCP Error\r\n";
char send_Check_Connect_TCP_Ok[] = "Ready To Communicate With TCP\r\n";

char AT_Send_Close_Connect_TCP_Server[] = "AT+CIPCLOSE=1\r\n";  //2 OK +CIPCLOSE:SUCCESS,1<\r><\n>
char send_Close_Connect_TCP_Server[] = "Clossing Connect TCP Server\r\n";
char send_Close_Connect_TCP_Server_Error[] = "Close Connect TCP Server Error\r\n";
char send_Close_Connect_TCP_Server_Ok[] = "Close Connect TCP Server Ok\r\n";

char AT_Send_Set_Net_Close[] = "AT+NETCLOSE\r\n";  //2       
char send_Setting_Net_Close[] = "Clossing Connect Internet\r\n";
char send_Set_Net_Close_Error[] = "Close Connect Internet Error\r\n";
char send_Set_Net_Close_Ok[] = "Close Connect Internet Ok\r\n";


void AT_Init(char IP_Address[], char Port[]){
    
    extern AT_Command_HandleTypeDef AT_Check_Module;
    memcpy(AT_Check_Module.Send, AT_Send_Check_Module, strlen(AT_Send_Check_Module));
    memcpy(AT_Check_Module.Checking, send_Checking_Module, strlen(send_Checking_Module));
    memcpy(AT_Check_Module.Error, send_Check_Module_Error, strlen(send_Check_Module_Error));
    memcpy(AT_Check_Module.Ready, send_Check_Module_Ok, strlen(send_Check_Module_Ok));
    AT_Check_Module.Number_Get_Data = 1;

    extern AT_Command_HandleTypeDef AT_Check_Sim;
    memcpy(AT_Check_Sim.Send, AT_Send_Check_Sim, strlen(AT_Send_Check_Sim));
    memcpy(AT_Check_Sim.Checking, send_Checking_Sim, strlen(send_Checking_Sim));
    memcpy(AT_Check_Sim.Error, send_Check_Sim_Error, strlen(send_Check_Sim_Error));
    memcpy(AT_Check_Sim.Ready, send_Check_Sim_Ok, strlen(send_Check_Sim_Ok));
    AT_Check_Sim.Number_Get_Data = 2;

    extern AT_Command_HandleTypeDef AT_Check_Signal;
    memcpy(AT_Check_Signal.Send, AT_Send_Check_Signal, strlen(AT_Send_Check_Signal));
    memcpy(AT_Check_Signal.Checking, send_Checking_Signal, strlen(send_Checking_Signal));
    memcpy(AT_Check_Signal.Error, send_Check_Signal_Error, strlen(send_Check_Signal_Error));
    memcpy(AT_Check_Signal.Ready, send_Check_Signal_Ok, strlen(send_Check_Signal_Ok));
    AT_Check_Signal.Number_Get_Data = 2;

    extern AT_Command_HandleTypeDef AT_Check_Subscribe;
    memcpy(AT_Check_Subscribe.Send, AT_Send_Check_Subscribe, strlen(AT_Send_Check_Subscribe));
    memcpy(AT_Check_Subscribe.Checking, send_Checking_Subscribe, strlen(send_Checking_Subscribe));
    memcpy(AT_Check_Subscribe.Error, send_Check_Subscribe_Error, strlen(send_Check_Subscribe_Error));
    memcpy(AT_Check_Subscribe.Ready, send_Check_Subscribe_Ok, strlen(send_Check_Subscribe_Ok));
    AT_Check_Subscribe.Number_Get_Data = 2;

    extern AT_Command_HandleTypeDef AT_Check_GPRS;
    memcpy(AT_Check_GPRS.Send, AT_Send_Check_GPRS, strlen(AT_Send_Check_GPRS));
    memcpy(AT_Check_GPRS.Checking, send_Checking_GPRS, strlen(send_Checking_GPRS));
    memcpy(AT_Check_GPRS.Error, send_Check_GPRS_Error, strlen(send_Check_GPRS_Error));
    memcpy(AT_Check_GPRS.Ready, send_Check_GPRS_Ok, strlen(send_Check_GPRS_Ok));
    AT_Check_GPRS.Number_Get_Data = 2;

    extern AT_Command_HandleTypeDef AT_Set_Timeout;
    memcpy(AT_Set_Timeout.Send, AT_Send_Set_Timeout, strlen(AT_Send_Set_Timeout));
    memcpy(AT_Set_Timeout.Checking, send_Setting_Timeout, strlen(send_Setting_Timeout));
    memcpy(AT_Set_Timeout.Error, send_Set_Timeout_Error, strlen(send_Set_Timeout_Error));
    memcpy(AT_Set_Timeout.Ready, send_Set_Timeout_Ok, strlen(send_Set_Timeout_Ok));
    AT_Set_Timeout.Number_Get_Data = 1;

    extern AT_Command_HandleTypeDef AT_Set_Transmit_Mode;
    memcpy(AT_Set_Transmit_Mode.Send, AT_Send_Set_Transmit_Mode, strlen(AT_Send_Set_Transmit_Mode));
    memcpy(AT_Set_Transmit_Mode.Checking, send_Setting_Transmit_Mode, strlen(send_Setting_Transmit_Mode));
    memcpy(AT_Set_Transmit_Mode.Error, send_Set_Transmit_Mode_Error, strlen(send_Set_Transmit_Mode_Error));
    memcpy(AT_Set_Transmit_Mode.Ready, send_Set_Transmit_Mode_Ok, strlen(send_Set_Transmit_Mode_Ok));
    AT_Set_Transmit_Mode.Number_Get_Data = 1;

    extern AT_Command_HandleTypeDef AT_Check_Net_Open;
    memcpy(AT_Check_Net_Open.Send, AT_Send_Check_Net_Open, strlen(AT_Send_Check_Net_Open));
    memcpy(AT_Check_Net_Open.Checking, send_Checking_Net_Open, strlen(send_Checking_Net_Open));
    memcpy(AT_Check_Net_Open.Error, send_Check_Net_Open_Error, strlen(send_Check_Net_Open_Error));
    memcpy(AT_Check_Net_Open.Ready, send_Check_Net_Open_Ok, strlen(send_Check_Net_Open_Ok));
    AT_Check_Net_Open.Number_Get_Data = 2;
    
    extern AT_Command_HandleTypeDef AT_Check_IP;
    memcpy(AT_Check_IP.Send, AT_Send_Check_IP, strlen(AT_Send_Check_IP));
    memcpy(AT_Check_IP.Checking, send_Checking_IP, strlen(send_Checking_IP));
    memcpy(AT_Check_IP.Error, send_Check_IP_Error, strlen(send_Check_IP_Error));
    memcpy(AT_Check_IP.Ready, send_Check_IP_Ok, strlen(send_Check_IP_Ok));
    AT_Check_IP.Number_Get_Data = 2;

    extern AT_Command_HandleTypeDef AT_Set_Receive_Mode;
    memcpy(AT_Set_Receive_Mode.Send, AT_Send_Set_Receive_Mode, strlen(AT_Send_Set_Receive_Mode));
    memcpy(AT_Set_Receive_Mode.Checking, send_Setting_Receive_Mode, strlen(send_Setting_Receive_Mode));
    memcpy(AT_Set_Receive_Mode.Error, send_Set_Receive_Mode_Error, strlen(send_Set_Receive_Mode_Error));
    memcpy(AT_Set_Receive_Mode.Ready, send_Set_Receive_Mode_Ok, strlen(send_Set_Receive_Mode_Ok));
    AT_Set_Receive_Mode.Number_Get_Data = 1;

    extern AT_Command_HandleTypeDef AT_Transmit_Data_To_TCP;
    memcpy(AT_Transmit_Data_To_TCP.Send, AT_Send_Transmit_Data_To_TCP, strlen(AT_Send_Transmit_Data_To_TCP));
    memcpy(AT_Transmit_Data_To_TCP.Checking, send_Transmiting_Data_To_TCP, strlen(send_Transmiting_Data_To_TCP));
    memcpy(AT_Transmit_Data_To_TCP.Error, send_Transmit_Data_To_TCP_Error, strlen(send_Transmit_Data_To_TCP_Error));
    memcpy(AT_Transmit_Data_To_TCP.Ready, send_Transmit_Data_To_TCP_Ok, strlen(send_Transmit_Data_To_TCP_Ok));
    AT_Transmit_Data_To_TCP.Number_Get_Data = 1;

    extern AT_Command_HandleTypeDef AT_Get_Current_Time;
    memcpy(AT_Get_Current_Time.Send, AT_Send_Get_Current_Time, strlen(AT_Send_Get_Current_Time));
    AT_Get_Current_Time.Number_Get_Data = 2;         //


    memcpy(code_TCP_IP, IP_Address, strlen(IP_Address));
    memcpy(code_TCP_Port,Port, strlen(Port));
    memcpy(set_Connect_TCP + 0, code_TCP_First, strlen(code_TCP_First));
    memcpy(set_Connect_TCP + strlen(set_Connect_TCP), code_TCP_IP, strlen(code_TCP_IP));
    memcpy(set_Connect_TCP + strlen(set_Connect_TCP), code_TCP_Center, strlen(code_TCP_Center));
    memcpy(set_Connect_TCP + strlen(set_Connect_TCP), code_TCP_Port, strlen(code_TCP_Port));
    memcpy(set_Connect_TCP + strlen(set_Connect_TCP), code_TCP_Final, strlen(code_TCP_Final));
    memcpy(AT_Send_Connect_TCP_Server, set_Connect_TCP, strlen(set_Connect_TCP));  

    extern AT_Command_HandleTypeDef AT_Connect_TCP_Server;
    memcpy(AT_Connect_TCP_Server.Send, AT_Send_Connect_TCP_Server, strlen(AT_Send_Connect_TCP_Server));
    memcpy(AT_Connect_TCP_Server.Checking, send_Connecting_TCP_Server, strlen(send_Connecting_TCP_Server));
    memcpy(AT_Connect_TCP_Server.Error, send_Connect_TCP_Server_Error, strlen(send_Connect_TCP_Server_Error));
    memcpy(AT_Connect_TCP_Server.Ready, send_Connect_TCP_Server_Ok, strlen(send_Connect_TCP_Server_Ok));
    AT_Connect_TCP_Server.Number_Get_Data = 2;       //

    extern AT_Command_HandleTypeDef AT_Check_Connect_TCP;
    memcpy(AT_Check_Connect_TCP.Send, AT_Send_Check_Connect_TCP, strlen(AT_Send_Check_Connect_TCP));
    memcpy(AT_Check_Connect_TCP.Checking, send_Checking_Connect_TCP, strlen(send_Checking_Connect_TCP));
    memcpy(AT_Check_Connect_TCP.Error, send_Check_Connect_TCP_Error, strlen(send_Check_Connect_TCP_Error));
    memcpy(AT_Check_Connect_TCP.Ready, send_Check_Connect_TCP_Ok, strlen(send_Check_Connect_TCP_Ok));
    AT_Check_Connect_TCP.Number_Get_Data = 2;

    extern AT_Command_HandleTypeDef AT_Close_Connect_TCP_Server;
    memcpy(AT_Close_Connect_TCP_Server.Send, AT_Send_Close_Connect_TCP_Server, strlen(AT_Send_Close_Connect_TCP_Server));
    memcpy(AT_Close_Connect_TCP_Server.Checking, send_Close_Connect_TCP_Server, strlen(send_Close_Connect_TCP_Server));
    memcpy(AT_Close_Connect_TCP_Server.Error, send_Close_Connect_TCP_Server_Error, strlen(send_Close_Connect_TCP_Server_Error));
    memcpy(AT_Close_Connect_TCP_Server.Ready, send_Close_Connect_TCP_Server_Ok, strlen(send_Close_Connect_TCP_Server_Ok));
    AT_Close_Connect_TCP_Server.Number_Get_Data = 2;

    extern AT_Command_HandleTypeDef AT_Set_Net_Close;
    memcpy(AT_Set_Net_Close.Send, AT_Send_Set_Net_Close, strlen(AT_Send_Set_Net_Close));
    memcpy(AT_Set_Net_Close.Checking, send_Setting_Net_Close, strlen(send_Setting_Net_Close));
    memcpy(AT_Set_Net_Close.Error, send_Set_Net_Close_Error, strlen(send_Set_Net_Close_Error));
    memcpy(AT_Set_Net_Close.Ready, send_Set_Net_Close_Ok, strlen(send_Set_Net_Close_Ok));
    AT_Set_Net_Close.Number_Get_Data = 2;

}



