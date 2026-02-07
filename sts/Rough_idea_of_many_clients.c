// Online C compiler to run C program online
#include <stdio.h>

pthread_t t[100];
int i =0;
int master_sock_tcp_fd = 0;

void * handler(comm_socket_fd,client_addr)
{
            if(comm_socket_fd < 0){

                /* if accept failed to return a socket descriptor, display error and exit */
                printf("accept error : errno = %d\n", errno);
                exit(0);
            }   
    
            while(1){
                printf("Server ready to service client msgs.\n");
                /*Drain to store client info (ip and port) when data arrives from client, sometimes, server would want to find the identity of the client sending msgs*/
                memset(data_buffer, 0, sizeof(data_buffer));

                /*Step 8: Server recieving the data from client. Client IP and PORT no will be stored in client_addr
                 * by the kernel. Server will use this client_addr info to reply back to client*/

                /*Like in client case, this is also a blocking system call, meaning, server process halts here untill
                 * data arrives on this comm_socket_fd from client whose connection request has been accepted via accept()*/
                /* state Machine state 3*/
                sent_recv_bytes = recvfrom(comm_socket_fd, (char *)data_buffer, sizeof(data_buffer), 0,
                        (struct sockaddr *)&client_addr, &addr_len);

                /* state Machine state 4*/
                printf("Server recvd %d bytes from client %s:%u\n", sent_recv_bytes, 
                        inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

                if(sent_recv_bytes == 0){
                /*If server recvs empty msg from client, server may close the connection and wait
                 * for fresh new connection from client - same or different*/
                close(comm_socket_fd);
                break; /*goto step 5*/

                }

                test_struct_t *client_data = (test_struct_t *)data_buffer;
                
                /* If the client sends a special msg to server, then server close the client connection
                 * for forever*/
                /*Step 9 */
                if(client_data->a == 0 && client_data->b ==0){

                    close(comm_socket_fd);
                    printf("Server closes connection with client : %s:%u\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                    /*Goto state machine State 1*/
                    break;/*Get out of inner while loop, server is done with this client, time to check for new connection request by executing selct()*/
                }

                result_struct_t result;
                result.c = client_data->a + client_data->b;

                /* Server replying back to client now*/
                sent_recv_bytes = sendto(comm_socket_fd, (char *)&result, sizeof(result_struct_t), 0,
                        (struct sockaddr *)&client_addr, sizeof(struct sockaddr));

                printf("Server sent %d bytes in reply to client\n", sent_recv_bytes);
                /*Goto state machine State 3*/
            }  
    
    
}



int main() {
    // Write C code here
    printf("Try programiz.pro");
    FD_SET(master_sock_tcp_fd, &readfds);  /*Add the socket to this set on which our server is running*/
    while(1)
    {
        select(master_sock_tcp_fd + 1, &readfds, NULL, NULL, NULL)
        i++;
        comm_socket_fd = accept(master_sock_tcp_fd, (struct sockaddr *)&client_addr, &addr_len);
        pthread_create(&t[i],handler,comm_socket_fd,client_addr);
        
    }
            
    
    
    
    

    return 0;
}
