#ifndef TRANSPORT_TX
#define TRANSPORT_TX

#include <string.h>
#include <omnetpp.h>

#include "FeedbackPkt_m.h"

using namespace omnetpp;

class TransportTx : public cSimpleModule
{
private:
    cOutVector Queue_BufferSize; // max amount of packets in the buffer
    cOutVector Queue_PacketDrop; // amount of packets dropped
    cQueue buffer;               // buffer

    cMessage *endServiceEvent;
    cMessage *endFeedBackEvent;
    simtime_t serviceTime;

    float rate;

public:
    TransportTx();
    virtual ~TransportTx();

protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(TransportTx);

TransportTx::TransportTx()
{
    endServiceEvent = NULL;
    endFeedBackEvent = NULL;
}

TransportTx::~TransportTx()
{
    cancelAndDelete(endServiceEvent);
    cancelAndDelete(endFeedBackEvent);
}

void TransportTx::initialize()
{
    buffer.setName("buffer");
    Queue_BufferSize.setName("Queue_BufferSize");
    Queue_PacketDrop.setName("Queue_PacketDrop");

    Queue_PacketDrop.record(0);

    endServiceEvent = new cMessage("endService");

    endFeedBackEvent = new cMessage("feedback");
    rate = 0.1;
}

void TransportTx::finish()
{
}

void TransportTx::handleMessage(cMessage *msg)
{
    EV << "msg: " << msg->getKind() << endl;
    if (msg == endServiceEvent)
    {
        EV << "EndServiceEvent" << endl;
        if (!buffer.isEmpty())
        {
            cPacket *pkt = (cPacket *)buffer.pop();
            if (gate("toOut$o")->getTransmissionChannel()->isBusy())
            {
                buffer.insert(pkt);
                scheduleAt(gate("toOut$o")->getTransmissionChannel()->getTransmissionFinishTime(), endServiceEvent);
            }
            else
            {
                send(pkt, "toOut$o");
                serviceTime = pkt->getDuration();
                scheduleAt(simTime() + serviceTime * rate, endServiceEvent);
            }
        }
    }
    else
    {
        if (buffer.getLength() >= par("bufferSize").intValue())
        {
            delete (msg);
            this->bubble("packet-dropped");
            Queue_PacketDrop.record(1);
        }
        else
        {
            if (msg->getKind() == 2)
            {
                EV << "rate: " << rate << endl;
                rate = rate + 0.1;
                delete (msg);
            }
            else if (dynamic_cast<FeedbackPkt *>(msg) == nullptr)
            {
                // show msg type
                EV << "msg type: " << msg->getClassName() << endl;
                buffer.insert(msg);
                Queue_BufferSize.record(buffer.getLength());
                if (!endServiceEvent->isScheduled())
                {
                    // start the service
                    scheduleAt(simTime() + 0, endServiceEvent);
                }
            }
        }
    }
}

#endif