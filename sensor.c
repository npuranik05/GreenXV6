#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf(1, "Usage: sensor [zone_id]\n");
        exit();
    }
    
    int zone = atoi(argv[1]);
    set_zone(zone, 0); // Not a mitigator
    
    printf(1, "Sensor started for Zone %d\n", zone);
    
    while(1) {
        sleep(50);
        update_env(zone, 20); // Add 20 pollution every 50 ticks
    }
    
    exit();
}
