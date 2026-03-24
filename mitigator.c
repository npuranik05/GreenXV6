#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(1, "Usage: mitigator [zone_id]\n");
        exit();
    }
    
    int zone = atoi(argv[1]);
    set_zone(zone, 1); // Mark as mitigator so it never gets throttled!
    printf(1, "Mitigator ready for Zone %d\n", zone);
    
    while(1) {
        // Poll for danger
        int pol = get_env(zone);
        if(pol > 100) {
            printf(1, "[!] Mitigator cleaning Zone %d... (-50 pollution)\n", zone);
            update_env(zone, -50); 
            
            // Wait out the timer to simulate work
            sleep(20);
        } else {
            // Idle safely
            sleep(50);
        }
    }
    
    exit();
}
