#ifndef MICROWAVE_IO_H
#define MICROWAVE_IO_H

#include "types.h"

/* ============================================================================
   I/O Abstractions - Platform Independence Layer
   ============================================================================ */

/* Display interface - abstract hardware dependency */
typedef struct {
    void (*clear_screen)(void);
    void (*print_line)(const char* format, ...);
    void (*print_status)(DisplayData data);
} DisplayInterface;

/* Input interface - abstract hardware dependency */
typedef struct {
    char (*read_key)(void);
    void (*non_blocking_mode)(bool enabled);
} InputInterface;

/* Hardware control interface - abstract hardware dependency */
typedef struct {
    void (*set_relay)(RelayState state);
    void (*set_magnetron)(MagnetronState state);
} HardwareInterface;

/* Timer interface - abstract time source */
typedef struct {
    uint32_t (*get_time_ms)(void);
    void (*sleep_ms)(uint32_t ms);
} TimerInterface;

/* Global I/O context - dependency injection pattern */
typedef struct {
    DisplayInterface display;
    InputInterface input;
    HardwareInterface hardware;
    TimerInterface timer;
} IOContext;

/* Platform-specific implementations */
DisplayInterface create_console_display(void);
InputInterface create_console_input(void);
HardwareInterface create_mock_hardware(void);
TimerInterface create_system_timer(void);

/* Create complete I/O context for a platform */
IOContext create_io_context(void);

#endif // MICROWAVE_IO_H
