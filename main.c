#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Checks if systemd is running
    if(system("pidof systemd > /dev/null") == 0) {
        puts("Systemd");
        return 0;
    }

    // Checks the process name of init system
    FILE* fp = popen("ps -p 1 -o comm=", "r");
    char buf[32];
    if(fgets(buf, sizeof(buf), fp) == NULL) {
        puts("Failed to get init process name");
        return 1;
    }
    pclose(fp);

    if(strcmp(buf, "upstart\n") == 0) {
        puts("Upstart");
    } else if(strcmp(buf, "init\n") == 0) {
        puts("Sysvinit");
    } else {
        puts("Init unknown!");
    }

    return 0;
}
