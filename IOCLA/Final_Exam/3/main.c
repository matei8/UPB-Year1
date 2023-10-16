#include <stdio.h>
#include <stdlib.h>

#include "dns.h"

void task3() {
    // TODO: call secret function with correct arguments
    magik(0, 0x7a69);
}

void main() {
    struct dns_entry entries[] = {
        [0].ip = 2169504010,
        [0].hostname = "google.com",
        [1].ip = 2169504012,
        [1].hostname = "facebook.com",
        [2].ip = 2169504002,
        [2].hostname = "curs.upb.ro",
        [3].ip = 2169504004,
        [3].hostname = "ocw.cs.pub.ro",
        [4].ip = 2169504006,
        [4].hostname = "fep.grid.pub.ro",
        [5].ip = 2169504008,
        [5].hostname = "youtube.com",
    };

    int target_ip = 3232235521; // 192.168.0.1

    task2(entries, 6, target_ip);
    task3();
}
