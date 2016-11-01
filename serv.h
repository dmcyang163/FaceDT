#ifndef _SERV_H_
#define _SERV_H_

#include "zhelpers.h"

class CServ
{
public:
	CServ();
	~CServ();

	void SendBuf(char* buf);
	int SendBuf(char* buf, int len);
	int SendMsg(zmq_msg_t* msg);

private:
	void* context;
	void* publisher;

	/* data */
};

#endif