#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    printf(1, "Testing Energy Tracker...\n");
    int my_pid = getpid();
    
    int start_e = get_energy(my_pid);
    
    // Burn some CPU cycles aggressively
    volatile int i;
    for(i = 0; i < 2000000; i++) {}
    
    int end_e = get_energy(my_pid);
    printf(1, "Energy ticks consumed: %d\n", end_e - start_e);
    
    if(end_e > start_e) {
        printf(1, "SUCCESS: Phase 2 Complete!\n");
    } else {
        printf(1, "FAILED: Hardware timer did not charge process.\n");
    }
    
    exit();
}
