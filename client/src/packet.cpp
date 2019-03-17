#include "packet.h"
#include <cstring>

Packet::Packet()
{
    type_ = TYPE::REQUEST;
    method_ = METHOD::DEFAULT;
    payload_ = nullptr;
    lenOfData_ = 0;
    identity_ = -1;
    index_ = 0;
    endFlag_ = false;
}
Packet::~Packet()
{
    if(payload_ != nullptr)
    {
        delete payload_;
    }
}

TYPE Packet::getType()
{
    return type_;
}

METHOD Packet::getMethod()
{
    return method_; 
}
int Packet::getIdentity()
{
    return identity_;
}
int Packet::getIndex()
{
    return index_;
}
std::tuple<char*, int> Packet::getPayload()
{
    return std::make_tuple(payload_, lenOfData_);
}
bool Packet::getEndFlag()
{
    return endFlag_;
}

/* setter */
bool Packet::setType(int type)
{
    if(type == (int)TYPE::REQUEST) 
        type_ = TYPE::REQUEST;
    else if(type == (int)TYPE::RESPONSE) 
        type_ = TYPE::RESPONSE;
    else 
        return false;
    return true;
}
bool Packet::setMethod(int method)
{
    switch(method)
    {
    case (int)METHOD::LOGIN :
        method_ = METHOD::LOGIN;
        break;
    case (int)METHOD::LOGOUT :
        method_ = METHOD::LOGOUT;
        break;
    default :
        return false;
    }

    return true;
}
bool Packet::setIdentity(int identity)
{
    identity_ = identity;
    return true;
}
bool Packet::setIndex(int index)
{
    if(0 <= index && index <= 0xfff)
    {
        index_ = index;
        return true;
    }
    return false;

}
bool Packet::setPayload(char* data, int length)
{
    if(data == nullptr)
    {
        return false;
    }

    payload_ = data;
    lenOfData_ = length;
    return true;
}

bool Packet::setEndFlag(int flag)
{
    if(flag >= 0 && flag <= 1)
    {
        endFlag_ = (flag == 0) ? false : true;
        return true;
    }
    else
    {
        return false;
    }
}

/* static API */
bool Packet::fromBytes(char *buff, int length, std::unique_ptr<Packet> &ptr)
{
    // the length of packet is more or 7.
    if(length < Packet::HEADER_SIZE) 
    {
        return false;
    }

    // length is 0xfffff
    int totalLength = buff[1] & 0xff; 
    totalLength = (totalLength << 8) | (buff[2] & 0xff);
    totalLength = (totalLength << 5) | ((buff[3] & 0xf8) >> 5);

    // if totalLength is different with length, buff is invalid...
    if(totalLength != length)
    {
        return false;
    }

    // parse type and method from index 0
    int type = buff[0] & 0x80;              // bin(10000000)
    int method = buff[0] & 0x7f;            // bin(01111111)
    int endFlag = buff[3] & 0x07;           // bin(00000111)

    if(ptr->setType(type) != true) return false;
    if(ptr->setMethod(method) != true) return false;    
    if(ptr->setEndFlag(endFlag) != true) return false;

    // parse transection number and end flag from index 4 and 5
    int identity = (buff[4] & 0xff);
    identity = (identity << 4) | ((buff[5] & 0xf0)>>4);
    if(ptr->setIdentity(identity) != true) return false;

    // parse index of packet
    int index = buff[5] & 0x0f;
    index = (index<<8) | buff[6];
    if(ptr->setIndex(index) != true) return false;

    // Parse Payload
    int lenOfData = totalLength - Packet::HEADER_SIZE;
    char *data = buff+Packet::HEADER_SIZE;
    if(ptr->setPayload(data, lenOfData) != true) return false;

    return true;
}

char* Packet::toBytes(Packet& packet)
{
    char *data= nullptr;
    int length = 0;
    auto tp = packet.getPayload();   // tuple( char*, int)
    data = std::get<0>(tp);
    length = std::get<1>(tp);
    
    char *buff = new char[Packet::HEADER_SIZE + length];
    memset(buff, 0, sizeof(char) *(Packet::HEADER_SIZE + length));

    // encode type and method
    buff[0] = (char)(((int)packet.getType() << 7) | (int)packet.getMethod());

    // encode length
    int totalLength = Packet::HEADER_SIZE + length;
    buff[1] = totalLength & (0xff000<<1);
    buff[2] = totalLength & (0x00ff0<<1);
    buff[3] = totalLength & 0x1f;

    int endFlag = packet.getEndFlag() ? 1 : 0;
    buff[3] = (buff[3] << 3) | endFlag;

    // encode transection number
    int identity = packet.getIdentity();
    buff[4] = identity & 0xff0;
    buff[5] = identity & 0x00f;

    // encode index of packet
    int index = packet.getIndex();
    buff[5] = (buff[5] << 4) | ( (index & 0xf00) >>8 );
    buff[6] = index & 0x0ff;

    // encode payload
    for(int i = 7, j = 0; j<length; j++,i++)
        buff[i] = data[j];
    
    return buff;
}

