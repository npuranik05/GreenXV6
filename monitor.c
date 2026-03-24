#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    printf(1, "Starting Campus Monitor...\n");
    
    while(1) {
        printf(1, "\n--- Western Campus Environment Status ---\n");
        for(int i = 0; i < 5; i++) {
            int pol = get_env(i);
            printf(1, "Zone %d Pollution Level: %d %s\n", i, pol, pol > 100 ? "[CRITICAL]" : "");
        }
        sleep(200); // UI Refresh rate
    }
    
    exit();
}
