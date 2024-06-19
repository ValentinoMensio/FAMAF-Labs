#ifndef NET
#define NET

#include <string.h>
#include <omnetpp.h>
#include <packet_m.h>
#include <NeighborDiscoveryPacket_m.h>
#include <LSP_m.h>

#include <map>
#include <vector>
#include <queue>

using namespace omnetpp;

class Net : public cSimpleModule
{
private:
    static const int cntNeighbor = 2;
    int neighborReached;
    int neighbor[cntNeighbor];
    std::vector<std::pair<int, int>> neighborList;
    std::vector<std::pair<int, int>> graph;
    int cntNodesGraph;
    std::vector<bool> LSPVis;
    int cntLSPVis;
    std::vector<int> lnkToSend;

public:
    Net();
    virtual ~Net();

protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);

    void askNeighborInfo();
    void actualizeNeighborInfo(NeighborDiscoveryPacket *pkt);
    bool isNeighborInfo(cMessage *msg);

    void sendLSP();
    void actualizeGraphRepresentation(LSPPacket *pkt);
    bool isLSPInfo(cMessage *msg);

    void constructRoutingTable();
    int getLnkToSend(int nodeName);
};

Define_Module(Net);

Net::Net()
{
}

Net::~Net()
{
}

void Net::initialize()
{
    cntNodesGraph = 8;
    neighborReached = 0;
    cntLSPVis = 0;

    for (int i = 0; i < cntNeighbor; i++)
    {
        neighbor[i] = -1;
    }
    graph.resize(cntNodesGraph, std::make_pair(-1, -1));
    LSPVis.resize(cntNodesGraph, false);

    askNeighborInfo();

    cMessage *actualizeGraphRepresentation = new cMessage("actualizeGraphRepresentation");
    scheduleAt(simTime(), actualizeGraphRepresentation);
}

void Net::finish()
{
}

void Net::askNeighborInfo()
{
    for (int i = 0; i < cntNeighbor; i++)
    {
        NeighborDiscoveryPacket *pkt = new NeighborDiscoveryPacket("NeighborDiscoveryPacket");
        pkt->setLnkIndex(i);
        pkt->setNeighborIndex(-1);
        send(pkt, "toLnk$o", i);
    }
}

void Net::actualizeNeighborInfo(NeighborDiscoveryPacket *pkt)
{
    int lnkIndex = pkt->getLnkIndex();
    int neighborIndex = pkt->getNeighborIndex();

    if (neighborReached < cntNeighbor)
    {
        neighborList.push_back(std::make_pair(lnkIndex, neighborIndex));
        neighborReached++;
        if (neighborReached == cntNeighbor)
        {
            sendLSP();
        }
    }
}

bool Net::isNeighborInfo(cMessage *msg)
{
    NeighborDiscoveryPacket *pkt = dynamic_cast<NeighborDiscoveryPacket *>(msg);
    return pkt != nullptr;
}

void Net::sendLSP()
{
    LSPPacket *pkt = new LSPPacket("LSPPacket");

    pkt->setNode(getParentModule()->getIndex());
    pkt->setNeighborListArraySize(cntNeighbor);
    pkt->setHopCount(0);
    pkt->setDuration(0);
    pkt->setSource(getParentModule()->getIndex());

    for (int i = 0; i < cntNeighbor; i++)
    {
        pkt->setNeighborList(i, neighborList[i].second);
    }

    if (cntNeighbor == neighborReached)
    {
        for (int i = 0; i < cntNeighbor; i++)
        {
            send(pkt->dup(), "toLnk$o", i);
        }
    }
}

void Net::actualizeGraphRepresentation(LSPPacket *pkt)
{
    int source = pkt->getNode();
    std::vector<int> pktNeighbors;

    for (int i = 0; i < pkt->getNeighborListArraySize(); i++)
    {
        pktNeighbors.push_back(pkt->getNeighborList(i));
    }

    graph[source] = std::make_pair(pktNeighbors[0], pktNeighbors[1]);

    if (!LSPVis[source])
    {
        LSPVis[source] = true;
        cntLSPVis++;
        if (cntLSPVis == cntNodesGraph)
        {
            constructRoutingTable();
        }
        else
        {
            for (int i = 0; i < cntNeighbor; i++)
            {
                send(pkt->dup(), "toLnk$o", i);
            }
        }
    }
    else
    {
        delete pkt;
    }
}

bool Net::isLSPInfo(cMessage *msg)
{
    LSPPacket *pkt = dynamic_cast<LSPPacket *>(msg);
    return pkt && pkt->getNeighborListArraySize() == cntNeighbor;
}

void Net::constructRoutingTable()
{
    lnkToSend.resize(cntNodesGraph, -1);
    std::queue<std::pair<int, int>> q;

    q.push(std::make_pair(graph[getParentModule()->getIndex()].first, 0));
    q.push(std::make_pair(graph[getParentModule()->getIndex()].second, 1));

    while (!q.empty())
    {
        std::pair<int, int> actNode = q.front();
        q.pop();

        int nodeIndex = actNode.first;
        int linkIndex = actNode.second;

        if (lnkToSend[nodeIndex] == -1)
        {
            lnkToSend[nodeIndex] = linkIndex;

            if (graph[nodeIndex].first != -1 && lnkToSend[graph[nodeIndex].first] == -1)
            {
                q.push(std::make_pair(graph[nodeIndex].first, linkIndex));
            }
            if (graph[nodeIndex].second != -1 && lnkToSend[graph[nodeIndex].second] == -1)
            {
                q.push(std::make_pair(graph[nodeIndex].second, linkIndex));
            }
        }
    }
}

int Net::getLnkToSend(int nodeName)
{
    return lnkToSend[nodeName];
}

void Net::handleMessage(cMessage *msg)
{
    if (isNeighborInfo(msg))
    {
        NeighborDiscoveryPacket *pkt = check_and_cast<NeighborDiscoveryPacket *>(msg);
        if (pkt->getNeighborIndex() == -1)
        {
            pkt->setNeighborIndex(getParentModule()->getIndex());
            send(pkt, "toLnk$o", pkt->getLnkIndex() == 0 ? 1 : 0);
        }
        else
        {
            actualizeNeighborInfo(pkt);
            delete pkt;
        }
    }
    else if (isLSPInfo(msg))
    {
        LSPPacket *pkt = check_and_cast<LSPPacket *>(msg);
        actualizeGraphRepresentation(pkt);
    }
    else if (dynamic_cast<Packet *>(msg))
    {
        Packet *pkt = check_and_cast<Packet *>(msg);
        if (pkt->getDestination() == getParentModule()->getIndex())
        {
            send(pkt, "toApp$o");
        }
        else
        {
            int lnkToSendIndex = getLnkToSend(pkt->getDestination());
            if (lnkToSendIndex != -1)
            {
                send(pkt, "toLnk$o", lnkToSendIndex);
            }
            else
            {
                delete pkt;
            }
        }
    }
    else
    {
        delete msg;
    }
}

#endif
