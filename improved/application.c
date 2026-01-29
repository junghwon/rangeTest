#include "application.h"
#include <stdlib.h>
#include <stdio.h>

/* ============================================================================
   Application Implementation
   ============================================================================ */

/*
 * Pure function: Convert key input to event
 * This maintains separation between I/O and business logic
 */
Event handle_user_input(char key_code) {
    Event event = {
        .type = EVENT_TIMER_TICK,
        .timestamp = 0,
        .data = NULL,
    };

    switch (key_code) {
        case 's':
        case 'S':
            event.type = EVENT_START_COOKING;
            break;
        case 'p':
        case 'P':
            event.type = EVENT_PAUSE;
            break;
        case 'r':
        case 'R':
            event.type = EVENT_RESUME;
            break;
        case 'c':
        case 'C':
            event.type = EVENT_STOP;
            break;
        case 't':
        case 'T':
            // Time adjustment
            event.type = EVENT_CONFIG_CHANGED;
            break;
        case 'w':
        case 'W':
            // Power adjustment
            event.type = EVENT_CONFIG_CHANGED;
            break;
        default:
            break;
    }

    return event;
}

/*
 * Apply state transition and synchronize hardware
 */
void apply_state_transition(MicrowaveApp* app, Event event) {
    // Pure state transition
    MicrowaveStatus new_state = apply_event(app->current_state, event);

    // Synchronize hardware based on state change
    if (new_state.relay_state != app->current_state.relay_state) {
        app->io.hardware.set_relay(new_state.relay_state);
    }

    if (new_state.magnetron_state != app->current_state.magnetron_state) {
        app->io.hardware.set_magnetron(new_state.magnetron_state);
    }

    app->current_state = new_state;
}

/*
 * Render UI - transform state to display
 */
void render_ui(MicrowaveApp* app) {
    DisplayData display = status_to_display(app->current_state);
    app->io.display.clear_screen();
    app->io.display.print_status(display);

    printf("Commands:\n");
    printf("  s - Start cooking\n");
    printf("  p - Pause\n");
    printf("  r - Resume\n");
    printf("  c - Cancel\n");
    printf("  t - Set time\n");
    printf("  w - Set power\n");
    printf("  q - Quit\n\n");
}

/*
 * Application factory
 */
MicrowaveApp app_create(void) {
    MicrowaveApp app = {
        .io = create_io_context(),
        .current_state = create_initial_state(),
        .config = {
            .cooking_time_seconds = 10,
            .power_level = POWER_500W,
        },
        .running = true,
    };

    // Enable non-blocking input
    app.io.input.non_blocking_mode(true);

    return app;
}

void app_destroy(MicrowaveApp* app) {
    // Ensure hardware is safe
    app->io.hardware.set_relay(RELAY_OFF);
    app->io.hardware.set_magnetron(MAGNETRON_OFF);

    // Restore terminal mode
    app->io.input.non_blocking_mode(false);
}

/*
 * Main event loop - reactive programming pattern
 */
void app_run(MicrowaveApp* app) {
    uint32_t last_tick = app->io.timer.get_time_ms();
    const uint32_t TICK_INTERVAL_MS = 1000;  // Timer tick every second

    render_ui(app);

    while (app->running) {
        uint32_t current_time = app->io.timer.get_time_ms();
        uint32_t elapsed = current_time - last_tick;

        // Timer tick event every second
        if (elapsed >= TICK_INTERVAL_MS) {
            Event tick_event = {
                .type = EVENT_TIMER_TICK,
                .timestamp = current_time,
                .data = NULL,
            };
            apply_state_transition(app, tick_event);
            last_tick = current_time;

            // Re-render after state change
            render_ui(app);
        }

        // User input handling
        char key = app->io.input.read_key();
        if (key != '\0') {
            if (key == 'q' || key == 'Q') {
                app->running = false;
            } else if (key == 't' || key == 'T') {
                // Cycle through cooking times
                uint32_t new_time = next_cooking_time(
                    app->current_state.remaining_time);
                app->config.cooking_time_seconds = new_time;

                Event config_event = {
                    .type = EVENT_CONFIG_CHANGED,
                    .timestamp = current_time,
                    .data = &app->config,
                };
                apply_state_transition(app, config_event);
                render_ui(app);
            } else if (key == 'w' || key == 'W') {
                // Cycle through power levels
                PowerLevel new_power = next_power_level(app->config.power_level);
                app->config.power_level = new_power;

                Event config_event = {
                    .type = EVENT_CONFIG_CHANGED,
                    .timestamp = current_time,
                    .data = &app->config,
                };
                apply_state_transition(app, config_event);
                render_ui(app);
            } else {
                Event user_event = handle_user_input(key);
                apply_state_transition(app, user_event);
                render_ui(app);
            }
        }

        // Yield to prevent busy-waiting
        app->io.timer.sleep_ms(50);
    }
}
