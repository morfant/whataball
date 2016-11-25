n = NetAddr("127.0.0.1",  8000); // local machine

(
fork {
    inf.do {
        var r = 1.0.rand;
        var chStr = "/ch" ++ (3.rand);
        // var chStr = "/ch" ++ (8.rand);
        // var chStr = "/ch" ++ (0.rand);
        n.sendMsg(chStr, r);
        ("random value: " + r).postln;
        0.05.wait;
    }
}
)
