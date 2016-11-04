#ifndef _SERV_H_
#define _SERV_H_

#include "zhelpers.h"
#include "mongo/bson/bson.h"


class CServ
{
public:
	CServ();
	~CServ();

	void SendBuf(char* buf);
	int SendBuf(char* buf, int len);
	int SendMsg(zmq_msg_t* msg);
	int SendBson(mongo::BSONObjBuilder* b);

	void BsonObjBuilderAppendIp(mongo::BSONObjBuilder* b);


private:
	void* context;
	void* publisher;

	/* data */
};

#endif