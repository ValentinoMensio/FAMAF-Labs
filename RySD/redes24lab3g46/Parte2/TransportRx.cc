#ifndef TRANSPORT_RX
#define TRANSPORT_RX

#include <string.h>
#include <omnetpp.h>

#include "FeedbackPkt_m.h"

using namespace omnetpp;

class TransportRx : public cSimpleModule
{

private:
    cOutVector Queue_BufferSize; // max amount of packets in the buffer
    cOutVector Queue_PacketDrop; // amount of packets dropped
    cQueue buffer;               // buffer

    cMessage *endFeedBackEvent; // feedback event
    cMessage *endServiceEvent;
    simtime_t serviceTime;

public:
    TransportRx();
    virtual ~TransportRx();

protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
    void sendFeedbackMax();
};

Define_Module(TransportRx);

TransportRx::TransportRx()
{
    endServiceEvent = NULL;
    endFeedBackEvent = NULL;
}

TransportRx::~TransportRx()
{
    cancelAndDelete(endServiceEvent);
    cancelAndDelete(endFeedBackEvent);
}

void TransportRx::initialize()
{
    buffer.setName("buffer");
    Queue_BufferSize.setName("Queue_BufferSize");
    Queue_PacketDrop.setName("Queue_PacketDrop");

    Queue_PacketDrop.record(0);

    endServiceEvent = new cMessage("endService");
    endFeedBackEvent = new cMessage("endFeedback");
}

void TransportRx::finish()
{
}

void TransportRx::handleMessage(cMessage *msg)
{

    if (msg == endServiceEvent)
    {
        if (!buffer.isEmpty())
        {
            cPacket *msg = (cPacket *)buffer.pop(); // dequeue packet
            send(msg, "toApp");

            serviceTime = msg->getDuration();
            scheduleAt(simTime() + serviceTime, endServiceEvent);
        }
    }
    else if (msg->getKind() == 2)
    {
        sendFeedbackMax();
        delete msg;
    }
    else
    {
        if (buffer.getLength() >= par("bufferSize").intValue())
        {
            // drop the packet
            delete msg;
            this->bubble("PacketDropped");
            Queue_PacketDrop.record(1);
        }
        else
        {
            const int max_rate = 0.9 * par("bufferSize").intValue();

            if (buffer.getLength() >= max_rate)
            {
                sendFeedbackMax();
            }

            // enqueue the packet
            buffer.insert(msg);
            // new packet in buffer
            Queue_BufferSize.record(buffer.getLength());

            // if the server is idle
            if (!endServiceEvent->isScheduled())
            {
                // start the service
                scheduleAt(simTime(), endServiceEvent);
            }
        }
    }
}

void TransportRx::sendFeedbackMax()
{
    FeedbackPkt *feedbackPkt = new FeedbackPkt("feedback");
    feedbackPkt->setByteLength(20);
    feedbackPkt->setKind(2);
    feedbackPkt->setRemainingBuffer(buffer.getLength());
    send(feedbackPkt, "toOut$o");
}

#endif