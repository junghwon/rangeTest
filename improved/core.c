#include "core.h"

/* ============================================================================
   Pure Functions - Core Logic (No Side Effects)
   ============================================================================ */

const PowerLevel POWER_LEVELS[] = {500, 400, 300, 200, 100};
const int POWER_LEVELS_COUNT = 5;

const uint32_t COOKING_TIMES[] = {0, 10, 20, 30, 40, 50, 60};
const int COOKING_TIMES_COUNT = 7;

/* Magnetron PWM cycles based on power level */
const MagnetronCycle MAGNETRON_CYCLES[] = {
    {100, 0},    // 500W - always on
    {80, 20},    // 400W - 80% duty cycle
    {60, 40},    // 300W - 60% duty cycle
    {40, 60},    // 200W - 40% duty cycle
    {20, 80},    // 100W - 20% duty cycle
};

/*
 * Pure: Calculate remaining time
 */
uint32_t calculate_remaining_time(uint32_t current, uint32_t tick_seconds) {
    return current > tick_seconds ? current - tick_seconds : 0;
}

/*
 * Pure: Get magnetron cycle from power
 */
MagnetronCycle get_magnetron_cycle(PowerLevel power) {
    switch (power) {
        case POWER_500W: return MAGNETRON_CYCLES[0];
        case POWER_400W: return MAGNETRON_CYCLES[1];
        case POWER_300W: return MAGNETRON_CYCLES[2];
        case POWER_200W: return MAGNETRON_CYCLES[3];
        case POWER_100W: return MAGNETRON_CYCLES[4];
        default: return MAGNETRON_CYCLES[0];
    }
}

/*
 * Pure: Validate configuration
 */
Result validate_cooking_config(CookingConfig config) {
    if (config.cooking_time_seconds > 3600) {
        return (Result){false, 1, "Cooking time exceeds 1 hour"};
    }
    if (config.cooking_time_seconds == 0) {
        return (Result){false, 2, "Cooking time must be greater than 0"};
    }
    return (Result){true, 0, "OK"};
}

/*
 * Pure: Create initial state
 */
MicrowaveStatus create_initial_state(void) {
    return (MicrowaveStatus){
        .state = STATE_STANDBY,
        .remaining_time = 0,
        .current_power = POWER_500W,
        .magnetron_state = MAGNETRON_OFF,
        .relay_state = RELAY_OFF,
        .elapsed_time = 0,
    };
}

/*
 * Pure: Transform status to display data
 */
DisplayData status_to_display(MicrowaveStatus status) {
    const char* state_labels[] = {
        "STANDBY", "COOKING", "PAUSED", "COMPLETED", "ERROR"
    };

    return (DisplayData){
        .state_label = state_labels[status.state],
        .time_display = status.remaining_time,
        .power_display = status.current_power,
        .message = "Ready",
    };
}

/*
 * Pure: Cycle to next power level
 */
PowerLevel next_power_level(PowerLevel current) {
    for (int i = 0; i < POWER_LEVELS_COUNT - 1; i++) {
        if (POWER_LEVELS[i] == current) {
            return POWER_LEVELS[i + 1];
        }
    }
    return POWER_LEVELS[0];  // Wrap around
}

/*
 * Pure: Cycle to next cooking time
 */
uint32_t next_cooking_time(uint32_t current_seconds) {
    for (int i = 0; i < COOKING_TIMES_COUNT - 1; i++) {
        if (COOKING_TIMES[i] == current_seconds) {
            return COOKING_TIMES[i + 1];
        }
    }
    return COOKING_TIMES[0];  // Wrap around
}

/*
 * Pure: State transition logic - the heart of the microwave FSM
 */
MicrowaveStatus apply_event(MicrowaveStatus current, Event event) {
    MicrowaveStatus next = current;

    switch (event.type) {
        case EVENT_START_COOKING:
            if (current.state == STATE_STANDBY && current.remaining_time > 0) {
                next.state = STATE_COOKING;
                next.magnetron_state = MAGNETRON_ON;
                next.relay_state = RELAY_ON;
            }
            break;

        case EVENT_PAUSE:
            if (current.state == STATE_COOKING) {
                next.state = STATE_PAUSED;
                next.magnetron_state = MAGNETRON_OFF;
                next.relay_state = RELAY_OFF;
            }
            break;

        case EVENT_RESUME:
            if (current.state == STATE_PAUSED) {
                next.state = STATE_COOKING;
                next.magnetron_state = MAGNETRON_ON;
                next.relay_state = RELAY_ON;
            }
            break;

        case EVENT_TIMER_TICK:
            if (current.state == STATE_COOKING) {
                next.elapsed_time = current.elapsed_time + 1;
                next.remaining_time = calculate_remaining_time(
                    current.remaining_time, 1);
                
                if (next.remaining_time == 0) {
                    next.state = STATE_COMPLETED;
                    next.magnetron_state = MAGNETRON_OFF;
                    next.relay_state = RELAY_OFF;
                }
            }
            break;

        case EVENT_STOP:
            next.state = STATE_STANDBY;
            next.magnetron_state = MAGNETRON_OFF;
            next.relay_state = RELAY_OFF;
            next.elapsed_time = 0;
            break;

        case EVENT_CONFIG_CHANGED:
            // Configuration change only allowed in STANDBY
            if (current.state == STATE_STANDBY) {
                if (event.data) {
                    CookingConfig* config = (CookingConfig*)event.data;
                    next.remaining_time = config->cooking_time_seconds;
                    next.current_power = config->power_level;
                }
            }
            break;

        default:
            break;
    }

    return next;
}
