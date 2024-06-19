import packet;

packet NeighborDiscoveryPacket extends Packet{
    int LnkIndex;
    int neighborIndex;
}