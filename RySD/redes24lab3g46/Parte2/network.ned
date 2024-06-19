simple Generator
{
    parameters:
        volatile double generationInterval; // sec
        int packetByteSize; // byte
        @display("i=block/source");
    gates:
        output out;
}

simple Queue
{
    parameters:
        volatile double serviceTime; // sec
        int bufferSize; // byte
        @display("i=block/queue;q=buffer");
    gates:
        input in;
        output out;
}

simple Sink
{
    parameters:
        @display("i=block/sink");
    gates:
        input in;
}


simple TransportTx
{
    parameters:
        int bufferSize;
        @display("i=block/queue;q=buffer");
    gates:
        input toApp;    // Recibe paquetes desde el generador
        inout toOut;    // Bidireccional, manda paquetes a TransportRx
}


simple TransportRx
{
    parameters:
        int bufferSize;
        @display("i=block/queue;q=buffer");
    gates:
        output toApp;   //Envia los paquetes procesados a Sink
        inout toOut;    //Bidireccional, envia paquetes a TransportTx
}


module NodeTx
{
    parameters:
        @display("i=block/routing");
    gates:
        output out;
        input in;
    submodules:
        gen: Generator {
            parameters:
                @display("p=75,50");
        }

        TrTx: TransportTx {
            parameters:
                @display("p=75,190");
        }
    connections:
        in --> TrTx.toOut$i;          //Recibe paquetes desde TransportRx
        gen.out --> TrTx.toApp;       //La conexión gen.out --> TrTx.toApp envía los paquetes generados por Generator hacia TransportTx.
        TrTx.toOut$o --> out;         //Envía paquetes desde TransportTx hacia la red
}

module NodeRx
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
        output out;
    submodules:
        sink: Sink {
            parameters:
                @display("p=75,50");
        }
        TrRx: TransportRx {
            parameters:
                @display("p=75,190");
        }
    connections:
        in --> TrRx.toOut$i;          //Permite que se reciban paquetes desde la red
        TrRx.toOut$o --> out;         //Envía paquetes desde TransportRx hacia la red
        // Case 1
        TrRx.toApp --> {datarate = 0.5Mbps;} --> sink.in;   //Envía paquetes desde TransportRx hacia Sink
        // Case 2
        //TrRx.toApp --> {datarate = 1Mbps;} --> sink.in;
}

network Network
{
    @display("bgl=2");
    submodules:
        nodeTx: NodeTx {
            @display("p=30,30");
        }
        queue_1: Queue{
            @display("p=130,30");
        }
        queue_2: Queue{
            @display("p=130,100");
        }
        nodeRx: NodeRx {
            @display("p=230,30");
        }
    connections:
        nodeTx.out--> {datarate = 1Mbps; delay = 100us;} --> queue_1.in;
        // Case 1
        queue_1.out --> {datarate = 1Mbps; delay = 100us;} --> nodeRx.in;
        // Case 2
        //queue_1.out --> {datarate = 0.5Mbps; delay = 100us;} --> nodeRx.in;

        nodeRx.out --> {datarate = 1Mbps; delay = 100us;} --> queue_2.in;
        queue_2.out --> {datarate = 1Mbps; delay = 100us;} --> nodeTx.in;

}

