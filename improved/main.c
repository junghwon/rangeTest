#include "application.h"
#include <stdio.h>

int main(void) {
    printf("=== Microwave Control System ===\n");
    printf("Functional Programming Implementation\n\n");

    MicrowaveApp app = app_create();
    app_run(&app);
    app_destroy(&app);

    printf("\nMicrowave shutdown complete.\n");
    return 0;
}
