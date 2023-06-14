#pragma once
//#include<winsock2.h>
#include<sys/socket.h>
#ifndef _RESPOND_H_
#define _RESPOND_H_


void solve_01(SOCKET clntSock, byte request[], byte coil[]);
void solve_02(SOCKET clntSock, byte request[], byte relay[]);
void solve_03(SOCKET clntSock, byte request[], byte holding_reg[]);
void solve_04(SOCKET clntSock, byte request[], byte input_reg[]);


void solve_all(SOCKET clnSock, byte request[]);  


#endif
