#ifndef APP
#define APP

#include <string.h>
#include <omnetpp.h>
#include <packet_m.h>

using namespace omnetpp;

class App : public cSimpleModule
{
private:
    cMessage *sendMsgEvent;
    cStdDev delayStats;
    cOutVector delayVector;

    cStdDev hopStats;
    cOutVector hopVector;

public:
    App();
    virtual ~App();

protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(App);

#endif /* APP */

App::App()
{
}

App::~App()
{
}

void App::initialize()
{

    if (par("interArrivalTime").doubleValue() != 0)
    {
        sendMsgEvent = new cMessage("sendEvent");
        scheduleAt(par("interArrivalTime"), sendMsgEvent);
    }

    delayStats.setName("TotalDelay");
    delayVector.setName("Delay");

    hopStats.setName("TotalHopCount");
    hopVector.setName("HopCount");
}

void App::finish()
{
    recordScalar("Average delay", delayStats.getMean());
    recordScalar("Number of packets", delayStats.getCount());

    recordScalar("Average hop count", hopStats.getMean());
    recordScalar("Number of hops", hopStats.getCount());
}

void App::handleMessage(cMessage *msg)
{

    if (msg == sendMsgEvent)
    {
        Packet *pkt = new Packet("packet", this->getParentModule()->getIndex());
        pkt->setByteLength(par("packetByteSize"));
        pkt->setSource(this->getParentModule()->getIndex());
        pkt->setDestination(par("destination"));

        pkt->setHopCount(0);

        send(pkt, "toNet$o");

        simtime_t departureTime = simTime() + par("interArrivalTime");
        scheduleAt(departureTime, sendMsgEvent);
    }
    else
    {
        Packet *pkt = check_and_cast<Packet *>(msg);
        simtime_t delay = simTime() - pkt->getCreationTime();
        delayStats.collect(delay);
        delayVector.record(delay);

        hopStats.collect(pkt->getHopCount());
        hopVector.record(pkt->getHopCount());

        delete (msg);
    }
}
