#ifndef MICROWAVE_CORE_H
#define MICROWAVE_CORE_H

#include "types.h"

/* ============================================================================
   Pure Functions for Core Logic
   ============================================================================ */

/* State transition logic - completely pure */
typedef Result (*StateTransition)(MicrowaveStatus current, Event event);

/* 
 * Pure function: Get next state after an event
 * No side effects, deterministic
 */
MicrowaveStatus apply_event(MicrowaveStatus current, Event event);

/*
 * Pure function: Calculate remaining time after tick
 * No side effects, deterministic
 */
uint32_t calculate_remaining_time(uint32_t current, uint32_t tick_seconds);

/*
 * Pure function: Determine magnetron cycle from power level
 * Returns {on_time_ms, off_time_ms}
 */
typedef struct {
    uint32_t on_ms;
    uint32_t off_ms;
} MagnetronCycle;

MagnetronCycle get_magnetron_cycle(PowerLevel power);

/*
 * Pure function: Validate cooking configuration
 */
Result validate_cooking_config(CookingConfig config);

/*
 * Pure function: Create initial microwave state
 */
MicrowaveStatus create_initial_state(void);

/*
 * Pure function: Transform status into display data
 */
DisplayData status_to_display(MicrowaveStatus status);

/*
 * Pure function: Generate next power level (cycling)
 */
PowerLevel next_power_level(PowerLevel current);

/*
 * Pure function: Generate next cooking time (cycling)
 */
uint32_t next_cooking_time(uint32_t current_seconds);

#endif // MICROWAVE_CORE_H
