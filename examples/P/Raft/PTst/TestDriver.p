machine TestDriverRaftAsync {
    start state Init {
        entry {
            var servers: set[Server];
            var emptyset: set[Server];
            var s5, s6 : Server;
            var i, n: int;
            var log: Log;

            // Servers
            n = 4;

            i = 0;
            while (i < n) {
                servers += (new Server());
                i=i+1;
            }

            log = default(Log);
            log += (sizeof(log), servers);

            i = 0;
            while (i < n) {
                send servers[i], InitMessage, (log=log, servers=servers);
                i=i+1;
            }

        }
    }
}
