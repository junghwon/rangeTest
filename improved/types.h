#ifndef MICROWAVE_TYPES_H
#define MICROWAVE_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/* ============================================================================
   Functional Types and Immutable Data Structures
   ============================================================================ */

/* Power levels (Watts) */
typedef enum {
    POWER_500W = 500,
    POWER_400W = 400,
    POWER_300W = 300,
    POWER_200W = 200,
    POWER_100W = 100,
} PowerLevel;

/* States of the microwave */
typedef enum {
    STATE_STANDBY,
    STATE_COOKING,
    STATE_PAUSED,
    STATE_COMPLETED,
    STATE_ERROR,
} MicrowaveState;

/* Relay states */
typedef enum {
    RELAY_OFF = 0,
    RELAY_ON = 1,
} RelayState;

/* Magnetron states */
typedef enum {
    MAGNETRON_OFF = 0,
    MAGNETRON_ON = 1,
} MagnetronState;

/* Immutable configuration */
typedef struct {
    uint32_t cooking_time_seconds;    // Total cooking time in seconds
    PowerLevel power_level;           // Microwave power level
} CookingConfig;

/* Immutable state snapshot */
typedef struct {
    MicrowaveState state;
    uint32_t remaining_time;          // Remaining cooking time in seconds
    PowerLevel current_power;
    MagnetronState magnetron_state;
    RelayState relay_state;
    uint32_t elapsed_time;            // Total elapsed time in seconds
} MicrowaveStatus;

/* Immutable display data */
typedef struct {
    const char* state_label;
    uint32_t time_display;
    uint32_t power_display;
    const char* message;
} DisplayData;

/* Event type for state transitions */
typedef enum {
    EVENT_START_COOKING,
    EVENT_PAUSE,
    EVENT_RESUME,
    EVENT_STOP,
    EVENT_TIMER_TICK,
    EVENT_COMPLETE,
    EVENT_CONFIG_CHANGED,
} EventType;

/* Immutable event */
typedef struct {
    EventType type;
    uint32_t timestamp;
    void* data;  // Event-specific data
} Event;

/* Result type for error handling (Rust-like Result) */
typedef struct {
    bool success;
    int error_code;
    const char* error_message;
} Result;

#endif // MICROWAVE_TYPES_H
