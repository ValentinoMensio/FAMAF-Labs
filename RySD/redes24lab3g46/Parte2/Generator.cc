#ifndef GENERATOR
#define GENERATOR

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Generator : public cSimpleModule
{
private:
    cMessage *sendMsgEvent;
    cStdDev transmissionStats;

    unsigned int totalTransmissions;   // total number of transmissions
    cOutVector generatedPacketsVector; // vector to store the total number of packets

public:
    Generator();
    virtual ~Generator();

protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};
Define_Module(Generator);

Generator::Generator()
{
    sendMsgEvent = NULL;
}

Generator::~Generator()
{
    cancelAndDelete(sendMsgEvent);
}

void Generator::initialize()
{
    transmissionStats.setName("TotalTransmissions");

    // initialize the total number of transmissions
    totalTransmissions = 0;
    generatedPacketsVector.setName("generatedPackets");

    // create the send packet
    sendMsgEvent = new cMessage("sendEvent");
    // schedule the first event at random time
    scheduleAt(par("generationInterval"), sendMsgEvent);
}

void Generator::finish()
{
    // record the total number of transmissions
    recordScalar("TotalTransmissions", totalTransmissions);
}

void Generator::handleMessage(cMessage *msg)
{

    // create new packet
    cPacket *pkt = new cPacket("packet");
    // set the packet length
    pkt->setByteLength(par("packetByteSize"));

    // increment the counter for generated packets
    totalTransmissions++;
    // update the vector
    generatedPacketsVector.record(totalTransmissions);
    // update the stats
    transmissionStats.collect(pkt->getByteLength());

    // send to the output
    send(pkt, "out");

    // compute the new departure time
    simtime_t departureTime = simTime() + par("generationInterval");
    // schedule the new packet generation
    scheduleAt(departureTime, sendMsgEvent);
}

#endif /* GENERATOR */
