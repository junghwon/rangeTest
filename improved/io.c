#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

/* ============================================================================
   Console Display Implementation
   ============================================================================ */

void console_clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void console_print_line(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}

void console_print_status(DisplayData data) {
    printf("\n=== Microwave Status ===\n");
    printf("State:  %s\n", data.state_label);
    printf("Time:   %d seconds\n", data.time_display);
    printf("Power:  %d W\n", data.power_display);
    printf("Note:   %s\n", data.message);
    printf("========================\n");
}

DisplayInterface create_console_display(void) {
    return (DisplayInterface){
        .clear_screen = console_clear_screen,
        .print_line = console_print_line,
        .print_status = console_print_status,
    };
}

/* ============================================================================
   Console Input Implementation
   ============================================================================ */

#ifdef _WIN32
static char windows_read_key(void) {
    if (_kbhit()) {
        return _getch();
    }
    return '\0';
}

static void windows_non_blocking_mode(bool enabled) {
    // Windows console is already non-blocking with _kbhit()
    (void)enabled;
}
#else
static struct termios original_termios;

static void enable_raw_mode(void) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &original_termios);
    raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

static void disable_raw_mode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

static char unix_read_key(void) {
    char c;
    if (read(STDIN_FILENO, &c, 1) > 0) {
        return c;
    }
    return '\0';
}

static void unix_non_blocking_mode(bool enabled) {
    if (enabled) {
        enable_raw_mode();
    } else {
        disable_raw_mode();
    }
}
#endif

InputInterface create_console_input(void) {
#ifdef _WIN32
    return (InputInterface){
        .read_key = windows_read_key,
        .non_blocking_mode = windows_non_blocking_mode,
    };
#else
    return (InputInterface){
        .read_key = unix_read_key,
        .non_blocking_mode = unix_non_blocking_mode,
    };
#endif
}

/* ============================================================================
   Mock Hardware Implementation (for testing/simulation)
   ============================================================================ */

void mock_relay_control(RelayState state) {
    printf("[HARDWARE] Relay: %s\n", state == RELAY_ON ? "ON" : "OFF");
}

void mock_magnetron_control(MagnetronState state) {
    printf("[HARDWARE] Magnetron: %s\n", state == MAGNETRON_ON ? "ON" : "OFF");
}

HardwareInterface create_mock_hardware(void) {
    return (HardwareInterface){
        .set_relay = mock_relay_control,
        .set_magnetron = mock_magnetron_control,
    };
}

/* ============================================================================
   System Timer Implementation
   ============================================================================ */

static uint32_t system_get_time_ms(void) {
#ifdef _WIN32
    return (uint32_t)GetTickCount();
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif
}

static void system_sleep_ms(uint32_t ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

TimerInterface create_system_timer(void) {
    return (TimerInterface){
        .get_time_ms = system_get_time_ms,
        .sleep_ms = system_sleep_ms,
    };
}

/* ============================================================================
   I/O Context Factory
   ============================================================================ */

IOContext create_io_context(void) {
    return (IOContext){
        .display = create_console_display(),
        .input = create_console_input(),
        .hardware = create_mock_hardware(),
        .timer = create_system_timer(),
    };
}
