#ifndef MICROWAVE_APPLICATION_H
#define MICROWAVE_APPLICATION_H

#include "types.h"
#include "core.h"
#include "io.h"

/* ============================================================================
   Application Layer - Orchestration and Coordination
   ============================================================================ */

/* Application context containing all dependencies */
typedef struct {
    IOContext io;
    MicrowaveStatus current_state;
    CookingConfig config;
    bool running;
} MicrowaveApp;

/* Application lifecycle functions */
MicrowaveApp app_create(void);
void app_destroy(MicrowaveApp* app);
void app_run(MicrowaveApp* app);

/* Input handling (pure function that produces an event) */
Event handle_user_input(char key_code);

/* State management (applies event and updates hardware) */
void apply_state_transition(MicrowaveApp* app, Event event);

/* UI rendering (transforms state to display) */
void render_ui(MicrowaveApp* app);

#endif // MICROWAVE_APPLICATION_H
