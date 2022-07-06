#include "AT_command.h"

AT_TypeDef AT;

char check_module[] = "AT\r\n";								
char checking_module[]= "Checking Module Sim\r\n";
char check_module_[]= "Module Ready\r\n";

char check_sim[] = "AT+CPIN?\r\n";			
char checking_sim[]= "KT sim OK\r\n";

char check_tin_hieu[] = "AT+CSQ\r\n";		
char checking_tin_hieu[]= "KT cuong do OK\r\n";

char check_dang_ky[] = "AT+CREG?\r\n";				
char checking_dang_ky[]= "KT dang ky OK\r\n";

char check_GPRS[] = "AT+CGATT?\r\n";				
char checking_GPRS[]= "KT GPRS OK\r\n";

char set_timeout[] = "AT+CIPTIMEOUT=30000,20000,40000,50000\r\n";   
char setting_timeout[]= "Set timeout  OK\r\n";

char set_transmit[] = "AT+CIPMODE=0\r\n";     
char setting_transmit[]= "Set transmit OK\r\n";

char check_net[] ="AT+NETOPEN\r\n";           
char checking_net[]= "KT NET OK\r\n";

char check_ip[] ="AT+IPADDR\r\n";						
char checking_ip[]= "KT IP OK\r\n";

char set_receive[] = "AT+CIPRXGET=0,1\r\n";	
char setting_receive[]= "KT receive OK\r\n";

char send_data_to_TCP[] = "AT+CIPSEND=1,,,,";

char get_time[] = "AT+CCLK?\r\n";

char connect_tcp[50];
char connect_tcp_code_first[] ={'A','T','+','C','I','P','O','P','E','N','=','1',',','"','T','C','P','"',',','"','\0'};
char connect_tcp_IP[20];
char connect_tcp_code_between[] ={'"',',','\0'};
char connect_tcp_Port[20];
char connect_tcp_code_final[] ={',','0', 0x0D, 0x0A,'\0'};

char connect_tcp_ok[] ="CONNECT IP OK\r\n";
									
char check_connect[] = "AT+CIPOPQUERY?\r\n";
//char check_connect[] = "AT+CIPOPQUERY=1\r\n";
char check_connect_ok[] = "CONNECT_OK\r\n";

char close_connect_ip[] = "AT+CIPCLOSE=1";
char close_net[] = "AT+NETCLOSE";

void AT_init(char IP_Address[], char Port[]){
    
    // to connect TCP server, install in order number
    memcpy(AT.AT, check_module, strlen(check_module));                       // 1
    memcpy(AT.CPIN, check_sim, strlen(check_sim));                           // 2
    memcpy(AT.CSQ, check_tin_hieu, strlen(check_tin_hieu));                  // 3
    memcpy(AT.CREG, check_dang_ky, strlen(check_dang_ky));                   // 4
    memcpy(AT.CGATT, check_GPRS, strlen(check_GPRS));                        // 5
    memcpy(AT.CIPTIMEOUT, set_timeout, strlen(set_timeout));                 // 6
    memcpy(AT.CIPMODE, set_transmit, strlen(set_transmit));                  // 7
    memcpy(AT.NETOPEN, check_net, strlen(check_net));                        // 8
    memcpy(AT.IPADDR, check_ip, strlen(check_ip));                           // 9
    memcpy(AT.CIPRXGET, set_receive, strlen(set_receive));                   // 10

    memcpy(AT.CIPSEND_DATA, send_data_to_TCP, strlen(send_data_to_TCP));
    memcpy(AT.CCLK, get_time, strlen(get_time));
    memcpy(AT.CIPCLOSE, close_connect_ip, strlen(close_connect_ip));
    memcpy(AT.NETCLOSE, close_net, strlen(close_net));

    // set TCP server with IP and Port
    memcpy(connect_tcp_IP,IP_Address, strlen(IP_Address));
    memcpy(connect_tcp_Port,Port, strlen(Port));
    memcpy(connect_tcp + 0, connect_tcp_code_first, strlen(connect_tcp_code_first));
    memcpy(connect_tcp + strlen(connect_tcp), connect_tcp_IP, strlen(connect_tcp_IP));
    memcpy(connect_tcp + strlen(connect_tcp), connect_tcp_code_between, strlen(connect_tcp_code_between));
    memcpy(connect_tcp + strlen(connect_tcp), connect_tcp_Port, strlen(connect_tcp_Port));
    memcpy(connect_tcp + strlen(connect_tcp), connect_tcp_code_final, strlen(connect_tcp_code_final));

    // connect TCP server with IP and Port
    memcpy(AT.CIPOPEN, connect_tcp, strlen(connect_tcp));                    // 11
    memcpy(AT.CIPOPQUERY, check_connect, strlen(check_connect));             // 12

}

