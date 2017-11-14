#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdlib.h>

static const char send_data[] = "TCP Server from RT-Thread.";  
int main(int argc,char*argv[])
{
   int port = 8000;
   int count=0;
   char *recv_data;  
   uint32_t sin_size;
   int sock, connected, bytes_received;
   struct sockaddr_in server_addr, client_addr;
   bool stop = false;  
   if (argc!=2)
	return -2;
    port =atoi(argv[1]);
   

   recv_data = (char *)malloc(1024);  
   if (recv_data == NULL)
   {
       printf("No memory\n");
       return -1;
   }

    
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
   {
       
       printf("Socket error\n");

        
       free(recv_data);
       return -2;
   }

    
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(port);  
   server_addr.sin_addr.s_addr = INADDR_ANY;
   memset(&(server_addr.sin_zero), 8, sizeof(server_addr.sin_zero));

    
   if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
   {
       
       printf("Unable to bind\n");


       
       free(recv_data);
       return -3;
   }

   
   if (listen(sock, 5) == -1)
   {
       printf("Listen error\n");

       /* release recv buffer */
       free(recv_data);
       return -4;
   }

   printf("\nTCPServer Waiting for client on port:%d...\r\n", port);
   while(stop != true)
   {
       sin_size = sizeof(struct sockaddr_in);

       
       connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
        

       
       printf("Got Connection from (%s , %d)\n",
                  inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

       
       while (1)
       {
#if 0
            
           send(connected, send_data, strlen(send_data), 0);
#endif
            
           bytes_received = recv(connected,recv_data, 27, 0);
           if (bytes_received <= 0)
           {
               
               close(connected);
			   printf("recv() ret %d, return accept()\n", bytes_received);
               break;
           }
            
           recv_data[bytes_received] = '\0';
				if (bytes_received > 0) {
				    
				   printf("RECEIVED DATA = %d \n" , ++count);
			   }
       }
   }

    
   close(sock);

    
   free(recv_data);

   return 0;
}
