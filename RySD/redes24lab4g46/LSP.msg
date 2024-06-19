import packet;

packet LSPPacket extends Packet {
    int node;
    int neighborList[];
}