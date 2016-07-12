package newnet;
network mynet
{
    int countactive=default(0);
    @display("bgb=120,120;bgs=75,m");
    submodules:
        sink: MadeSink {
            @display("p=0,0");
        }
        node[100]: Node {
            @display("i=misc/node_vs");
        }
}
