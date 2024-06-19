#ifndef QUEUE
#define QUEUE

#include <string.h>
#include <omnetpp.h>

#include "FeedbackPkt_m.h"

using namespace omnetpp;

class Queue : public cSimpleModule
{
private:
    cOutVector bufferSizeVector; // amount of packets in the buffer
    cOutVector packetDropVector; // amount of packets dropped

    cQueue buffer;
    cMessage *endServiceEvent;
    cMessage *endFeedBackEvent;
    simtime_t serviceTime;

public:
    Queue();
    virtual ~Queue();

protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Queue);

Queue::Queue()
{
    endServiceEvent = nullptr;
    endFeedBackEvent = nullptr;
}

Queue::~Queue()
{
    cancelAndDelete(endServiceEvent);
    cancelAndDelete(endFeedBackEvent);
}

void Queue::initialize()
{
    buffer.setName("buffer");
    endServiceEvent = new cMessage("endService");
    endFeedBackEvent = new cMessage("endFeedback");

    bufferSizeVector.setName("bufferSize");
    packetDropVector.setName("packetDrop");

    packetDropVector.record(0);
}

void Queue::finish()
{
}

void Queue::handleMessage(cMessage *msg)
{
    // if msg is signaling an endServiceEvent
    if (msg == endServiceEvent)
    {
        // if packet in buffer, send next one
        if (!buffer.isEmpty())
        {
            cPacket *pkt = (cPacket *)buffer.pop();
            if (gate("out")->getTransmissionChannel()->isBusy())
            {
                buffer.insert(pkt);
                scheduleAt(gate("out")->getTransmissionChannel()->getTransmissionFinishTime(), endServiceEvent);
            }
            else
            {
                // send packet
                send(pkt, "out");
                // start new service
                serviceTime = pkt->getDuration();
                scheduleAt(simTime() + serviceTime, endServiceEvent);
            }
        }
    }
    else if (msg == endFeedBackEvent)
    {
        // Feedback message handling
        if (!gate("out")->getTransmissionChannel()->isBusy())
        {
            send(endFeedBackEvent, "out");
        }
        else
        {
            // Reschedule the feedback event if the channel is busy
            scheduleAt(gate("out")->getTransmissionChannel()->getTransmissionFinishTime(), endFeedBackEvent);
        }
    }
    else
    {
        // if msg is a data packet
        if (buffer.getLength() >= par("bufferSize").intValue())
        {
            // drop the packet
            delete msg;
            this->bubble("PacketDropped");
            packetDropVector.record(1);
        }
        else
        {
            if (msg != endFeedBackEvent)
            {
                const int max_rate = 0.8 * par("bufferSize").intValue();

                if (buffer.getLength() >= max_rate && !endFeedBackEvent->isScheduled())
                {
                    FeedbackPkt *feedbackPkt = new FeedbackPkt("Feedback");
                    feedbackPkt->setByteLength(20);
                    feedbackPkt->setKind(2);
                    feedbackPkt->setRemainingBuffer(buffer.getLength());

                    if (gate("out")->getTransmissionChannel()->isBusy())
                    {
                        scheduleAt(gate("out")->getTransmissionChannel()->getTransmissionFinishTime(), endFeedBackEvent);
                    }
                    else
                    {
                        send(feedbackPkt, "out");
                    }
                }

                // enqueue the packet
                buffer.insert(msg);
                // new packet in buffer
                bufferSizeVector.record(buffer.getLength());

                // if the server is idle
                if (!endServiceEvent->isScheduled())
                {
                    // start the service
                    scheduleAt(simTime(), endServiceEvent);
                }
            }
            else
            {
                if (gate("out")->getTransmissionChannel()->isBusy())
                {
                    buffer.insertBefore(buffer.front(), msg);
                    scheduleAt(gate("out")->getTransmissionChannel()->getTransmissionFinishTime(), endFeedBackEvent);
                }
                else
                {
                    send(msg, "out");
                }
            }
        }
    }
}

#endif /* QUEUE */
