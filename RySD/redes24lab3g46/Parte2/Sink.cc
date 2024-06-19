#ifndef SINK
#define SINK

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Sink : public cSimpleModule
{
private:
    cStdDev delayStats;
    cOutVector delayVector;

    cOutVector receivedPacketsVector; // vector to store the total number of packets
    unsigned int numReceivedPackets;  // variable to track the number of received packets

public:
    Sink();
    virtual ~Sink();

protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Sink);

Sink::Sink()
{
}

Sink::~Sink()
{
}

void Sink::initialize()
{
    // stats and vector names
    delayStats.setName("TotalDelay");
    delayVector.setName("Delay");

    receivedPacketsVector.setName("receivedPackets");
    numReceivedPackets = 0;
}

void Sink::finish()
{
    // stats record at the end of simulation
    recordScalar("AvgDelay", delayStats.getMean()); // record the average delay
}

void Sink::handleMessage(cMessage *msg)
{
    // compute queuing delay
    simtime_t delay = simTime() - msg->getCreationTime();
    // update stats
    delayStats.collect(delay);
    delayVector.record(delay);

    // increment the counter for received packets
    numReceivedPackets++;
    // increment the counter for received packets
    receivedPacketsVector.record(numReceivedPackets);
    // delete msg
    delete (msg);
}

#endif /* SINK */
