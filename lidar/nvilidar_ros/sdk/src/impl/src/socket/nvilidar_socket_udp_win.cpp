#if defined(_WIN32)
#include "socket/nvilidar_socket_udp_win.h"
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <sys/stat.h>
#include <io.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <ws2def.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>

#pragma comment(lib, "ws2_32.lib")


namespace nvilidar_socket
{ 
	Nvilidar_Socket_UDP::Nvilidar_Socket_UDP()
    {
    }
	Nvilidar_Socket_UDP::~Nvilidar_Socket_UDP()
    {
    }

    // 初始化 
    bool Nvilidar_Socket_UDP::udpInit(const char *addr, unsigned short port)
    {
		m_SocketConnect = false;

        // socket版本号 
        memset(&m_hWSAData, 0, sizeof(m_hWSAData));
		int err = WSAStartup(MAKEWORD(2, 2), &m_hWSAData);
		if (err != 0)
		{
			//printf("socket version error!\n");
			return false;
		}

        // 创建设备类型 本雷达需要 IPV4,STREAM,TCP方式  
        m_SocketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if(m_SocketHandle == INVALID_SOCKET)
		{
			m_SocketConnect = false;
			//printf("invalid socket!\n");
			return false;
		}

        // 保存ip 端口等信息
        m_SocketPara.sin_family =  AF_INET;
        m_SocketPara.sin_port =  htons(port);
		m_SocketPara.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//inet_addr(addr);

		if(SOCKET_ERROR == bind(m_SocketHandle, (sockaddr*)&m_SocketPara, sizeof(m_SocketPara)))
		{
			//printf("socket bind fail!\n");
			return false;
		}

		//发送 
		m_SocketSndPara.sin_family = AF_INET;
		m_SocketSndPara.sin_port = htons(port);
		m_SocketSndPara.sin_addr.S_un.S_addr = inet_addr(addr);

		//set socket opt 
		int opt_state = 1;
		if (SOCKET_ERROR == setsockopt(m_SocketHandle, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt_state, sizeof(opt_state)))
		{
			return false;
		}

		m_SocketConnect = true;

		return true;
    }

    // 判断有没有连接  
    bool Nvilidar_Socket_UDP::isudpOpen()
    {
        return m_SocketConnect;
    }

    //关闭socket  
    void Nvilidar_Socket_UDP::udpClose()
    {
        if(m_SocketConnect)
        {
            m_SocketConnect = false;     
            closesocket(m_SocketHandle);
			WSACleanup();
        }
    }

     // 读可读字节的长度   未用此项 
    int Nvilidar_Socket_UDP::udpReadAvaliable()
    {
        return 8192;
    }

    // 读socket数据  
    int Nvilidar_Socket_UDP::udpReadData(const uint8_t *data,int len)
    {
		if (!isudpOpen())
		{
			return -1;
		}

		int server_addr_len = sizeof(sockaddr_in);
		int ret = recvfrom(m_SocketHandle, (char *)data, len, 0, (sockaddr*)&m_SocketPara, &server_addr_len);

        return ret;
    }

    // 写socket数据  
    int Nvilidar_Socket_UDP::udpWriteData(const uint8_t *data,int len)
    {
		if (!isudpOpen())
		{
			return -1;
		}

        int ret = sendto(m_SocketHandle,(char *)data,len,0, (sockaddr*)&m_SocketSndPara,sizeof(m_SocketSndPara));
		if (0 == ret)
		{
			ret = -1;
		}
        return ret;
    }
}

#endif

