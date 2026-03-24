#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    printf(1, "Testing Environment Syscalls...\n");
    int pol = get_env(0);
    printf(1, "Zone 0 initial pollution: %d\n", pol);
    
    printf(1, "Adding 50 pollution to Zone 0...\n");
    update_env(0, 50);
    
    pol = get_env(0);
    printf(1, "Zone 0 new pollution: %d\n", pol);
    
    if (pol == 50) {
        printf(1, "SUCCESS: Phase 1 Complete!\n");
    } else {
        printf(1, "FAILED: Kernel state did not update properly.\n");
    }
    
    exit();
}
