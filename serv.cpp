#include "serv.h"

#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif

#include "utils.h"

CServ::CServ()
{
	context = zmq_init (1);
	publisher = zmq_socket (context, ZMQ_PUB);
	zmq_bind (publisher, "tcp://*:5565");
}

CServ::~CServ()
{
	zmq_close (publisher);
	zmq_term (context);
}

void CServ::SendBuf(char* buf)
{
	s_send (publisher, buf);
	//usleep (10*1000);
}

int CServ::SendMsg(zmq_msg_t* msg)
{

	return zmq_msg_send (msg, publisher, 0);
}

int CServ::SendBuf(char* buf, int len)
{
	zmq_msg_t msg;
	int rc = zmq_msg_init_size (&msg, len);
	assert (rc == 0);

	memcpy (zmq_msg_data (&msg), buf, len);
	SendMsg(&msg);

	rc = zmq_msg_close (&msg);

	return rc;
}

int CServ::SendBson(mongo::BSONObjBuilder* b)
{
	mongo::BSONObj obj = b->obj();
	SendBuf( (char*)(obj.objdata()), obj.objsize());
}

void CServ::BsonObjBuilderAppendIp(mongo::BSONObjBuilder* b)
{
	string ip = CUtils::getIpAddress();
	b->append("ip", ip);

	//b->appendBinData("jpg", jpgLen, mongo::BinDataGeneral, buff);
}
