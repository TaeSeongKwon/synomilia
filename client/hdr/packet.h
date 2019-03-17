#ifndef __PACKET_H__
#define __PACKET_H__

#include<memory>
#include<tuple>

enum class TYPE : char
{
    REQUEST,
    RESPONSE
};

enum class METHOD : char
{
    DEFAULT = 0,
    LOGIN = 1,
    LOGOUT,
    MESSAGE,
    INVITE,
    CREATE,
    NOTIFY,
    PUBLISH,
    REGISTER
};

class Packet
{
private:
    TYPE type_;
    METHOD method_;
    int index_;
    int identity_;
    char* payload_;
    int lenOfData_;
    bool endFlag_;

public:
    static const int HEADER_SIZE = 7;
    Packet();
    ~Packet();

    /* getter */
    TYPE getType();
    METHOD getMethod();
    int getIdentity();
    int getIndex();
    std::tuple<char*, int> getPayload();
    bool getEndFlag();

    /* setter */
    bool setType(int type);    
    bool setMethod(int method);
    bool setIdentity(int identity);
    bool setIndex(int index);
    bool setPayload(char* data, int length);
    bool setEndFlag(int flag);

    /* stati API */
    static bool fromBytes(char* buff, int length, std::unique_ptr<Packet> &ptr);
    static char* toBytes(Packet& packet);
};

#endif
