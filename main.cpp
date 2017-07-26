#include "mbed.h"
#include "TCPSocket.h"
#include "MXCHIPInterface.h"
#include "MbedJSONValue.h"
#include <string>
#define SIMPLE_POST_REQUEST1 \
    "POST /server_api HTTP/1.1\r\n" \
    "Host:vop.baidu.com\r\n" \
    "Content-Type:application/json;\r\n"\
    "Content-Length:153\r\n" \
    "\r\n" \
		
#define SIMPLE_GET_REQUEST \
"GET /text2audio?tex=%E7%99%BE%E5%BA%A6%E4%BD%A0%E5%A5%BD&lan=zh&cuid=33-10-B3-4A-D9-13&ctp=1&tok=24.5916fdcef5bfb89c6c8765fe940be503.2592000.1503541424.282335-9731315 HTTP/1.1\r\n" \
 "Host:tsn.baidu.com\r\n" \
"\r\n"
//string message="GET /text2audio?tex=%E7%99%BE%E5%BA%A6%E4%BD%A0%E5%A5%BD&lan=zh&cuid=33-10-B3-4A-D9-13&ctp=1&tok=24.5916fdcef5bfb89c6c8765fe940be503.2592000.1503541424.282335-9731315 HTTP/1.1\r\nHost:tsn.baidu.com\r\n\r\n";
MXCHIPInterface wifi(D1,D0);
DigitalOut led1(LED1); 
Serial pc(USBTX,USBRX);

int main( void )
{   
	
	  /****语音识别 ****/
	  
	  string s;
	  MbedJSONValue message;
	  char *speech_data="s";
    message["rate"]=8000;
    message["channel"] =1;
	  message["token"]="24.a5a620a33178a1e3c2cc2125d70b28a9.2592000.1503538431.282335-7842953";
	  message["cuid"]="30-10-B3-4A-D9-13" ;
	  message["len"]=1;
	  message["speech"]=speech_data;
    //serialize it into a JSON string
    s = message.serialize();
		const char *a=s.c_str();
  	// char req[500];
		int length=s.length();
	  printf("s=%s\r\n",s);
//	sprintf(req,SIMPLE_POST_REQUEST1,length);
		string b;
		b=SIMPLE_POST_REQUEST1+s;
	  const char *expr=b.c_str();
		char *sbuffer = new char[strlen(expr)+1];
    strcpy(sbuffer, expr);
		printf("sbuffere=%s\r\n",sbuffer);
	  int b_length=strlen(sbuffer);
		
		
		// strcat(req,a);
    // printf("json: %s\r\n", b);
		 //printf("length=%d\r\n",s.length());
		
		
    printf("NetworkSocketAPI Example\r\n");
    wifi.connect("wifi", "916754393");
    const char *ip = wifi.get_ip_address();
    const char *mac = wifi.get_mac_address();
    printf("IP address is: %s\r\n", ip ? ip : "No IP");
    printf("MAC address is: %s\r\n", mac ? mac : "No MAC");
  
    TCPSocket tcpsocket;
  //  printf("Sending HTTP request to www.arm.com...\r\n");
    // Open a socket on the network interface, and create a TCP connection to www.arm.com
    tcpsocket.open(&wifi);
    printf("finish open()\r\n");
     const char * host_ip=wifi.gethostbyname("vop.baidu.com");
	   wifi.addre=host_ip;
     pc.printf("wifi.address=%s",host_ip);
    int value=tcpsocket.connect(host_ip, 80);
    if(!value)
    	printf("connect to vop.baidu.com successfully!\r\n");
    // Send a simple http request
	  
		/********* 文字转语音接口  ***********/
		 /*
		 string b=SIMPLE_GET_REQUEST;
		const char * sbuffer=b.c_str();
		const char *expr=b.c_str();
		char *sbuffer = new char[strlen(expr)+1];
    strcpy(sbuffer, expr);
		printf("%s\r\n",sbuffer);
		int b_length=strlen(sbuffer);
		printf("b_length=%d\r\n",b_length);
		char sbuffer1[] = "GET /text2audio?tex=%E7%99%BE%E5%BA%A6%E4%BD%A0%E5%A5%BD&lan=zh&cuid=33-10-B3-4A-D9-13&ctp=1&tok=24.5916fdcef5bfb89c6c8765fe940be503.2592000.1503541424.282335-9731315 HTTP/1.1\r\nHost:tsn.baidu.com\r\n\r\n";
    int s_length= sizeof sbuffer1;
     */
	 
 	   int scount = tcpsocket.send(sbuffer, b_length);
		
     printf("sent %d [%.*s]\r\n", scount, strstr(sbuffer, "\r\n")-sbuffer, sbuffer);		
    // Recieve a simple http response and print out the response line
     char rbuffer[200];
     int rcount = tcpsocket.recv(rbuffer, sizeof rbuffer);
		 printf("rbuffer=%s\r\n",rbuffer);
	   printf("rcount=%d\r\n",rcount);
     printf("recv %d [%.*s]\r\n", rcount, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);

//    // Close the socket to return its memory and bring down the network interface
//    tcpsocket.close();

//    wifi.disconnect();

//    printf("Done\r\n");



}