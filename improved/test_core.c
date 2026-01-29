#include <assert.h>
#include <stdio.h>
#include "../types.h"
#include "../core.h"

/* ============================================================================
   Unit Tests for Core Logic
   ============================================================================ */

void test_calculate_remaining_time(void) {
    printf("Test: calculate_remaining_time\n");
    
    assert(calculate_remaining_time(60, 1) == 59);
    assert(calculate_remaining_time(10, 5) == 5);
    assert(calculate_remaining_time(5, 5) == 0);
    assert(calculate_remaining_time(0, 1) == 0);  // Underflow protection
    
    printf("  ✓ All tests passed\n");
}

void test_next_power_level(void) {
    printf("Test: next_power_level\n");
    
    assert(next_power_level(POWER_500W) == POWER_400W);
    assert(next_power_level(POWER_400W) == POWER_300W);
    assert(next_power_level(POWER_300W) == POWER_200W);
    assert(next_power_level(POWER_200W) == POWER_100W);
    assert(next_power_level(POWER_100W) == POWER_500W);  // Wrap around
    
    printf("  ✓ All tests passed\n");
}

void test_next_cooking_time(void) {
    printf("Test: next_cooking_time\n");
    
    assert(next_cooking_time(0) == 10);
    assert(next_cooking_time(10) == 20);
    assert(next_cooking_time(20) == 30);
    assert(next_cooking_time(60) == 0);  // Wrap around
    
    printf("  ✓ All tests passed\n");
}

void test_get_magnetron_cycle(void) {
    printf("Test: get_magnetron_cycle\n");
    
    MagnetronCycle cycle_500w = get_magnetron_cycle(POWER_500W);
    assert(cycle_500w.on_ms == 100);
    assert(cycle_500w.off_ms == 0);
    
    MagnetronCycle cycle_300w = get_magnetron_cycle(POWER_300W);
    assert(cycle_300w.on_ms == 60);
    assert(cycle_300w.off_ms == 40);
    
    MagnetronCycle cycle_100w = get_magnetron_cycle(POWER_100W);
    assert(cycle_100w.on_ms == 20);
    assert(cycle_100w.off_ms == 80);
    
    printf("  ✓ All tests passed\n");
}

void test_validate_cooking_config(void) {
    printf("Test: validate_cooking_config\n");
    
    CookingConfig valid = {30, POWER_500W};
    Result result1 = validate_cooking_config(valid);
    assert(result1.success);
    
    CookingConfig zero_time = {0, POWER_500W};
    Result result2 = validate_cooking_config(zero_time);
    assert(!result2.success);
    
    CookingConfig too_long = {3601, POWER_500W};
    Result result3 = validate_cooking_config(too_long);
    assert(!result3.success);
    
    printf("  ✓ All tests passed\n");
}

void test_apply_event_start_cooking(void) {
    printf("Test: apply_event - START_COOKING\n");
    
    MicrowaveStatus state = create_initial_state();
    state.remaining_time = 30;  // Set time first
    
    Event event = {.type = EVENT_START_COOKING};
    MicrowaveStatus new_state = apply_event(state, event);
    
    assert(new_state.state == STATE_COOKING);
    assert(new_state.magnetron_state == MAGNETRON_ON);
    assert(new_state.relay_state == RELAY_ON);
    
    printf("  ✓ All tests passed\n");
}

void test_apply_event_timer_tick(void) {
    printf("Test: apply_event - TIMER_TICK\n");
    
    MicrowaveStatus state = create_initial_state();
    state.state = STATE_COOKING;
    state.remaining_time = 30;
    
    Event event = {.type = EVENT_TIMER_TICK};
    MicrowaveStatus new_state = apply_event(state, event);
    
    assert(new_state.remaining_time == 29);
    assert(new_state.elapsed_time == 1);
    assert(new_state.state == STATE_COOKING);  // Still cooking
    
    printf("  ✓ All tests passed\n");
}

void test_apply_event_timer_complete(void) {
    printf("Test: apply_event - TIMER_COMPLETE\n");
    
    MicrowaveStatus state = create_initial_state();
    state.state = STATE_COOKING;
    state.remaining_time = 1;
    
    Event event = {.type = EVENT_TIMER_TICK};
    MicrowaveStatus new_state = apply_event(state, event);
    
    assert(new_state.remaining_time == 0);
    assert(new_state.state == STATE_COMPLETED);
    assert(new_state.magnetron_state == MAGNETRON_OFF);
    assert(new_state.relay_state == RELAY_OFF);
    
    printf("  ✓ All tests passed\n");
}

void test_apply_event_pause_resume(void) {
    printf("Test: apply_event - PAUSE/RESUME\n");
    
    MicrowaveStatus state = create_initial_state();
    state.state = STATE_COOKING;
    state.magnetron_state = MAGNETRON_ON;
    
    // Pause
    Event pause_event = {.type = EVENT_PAUSE};
    MicrowaveStatus paused = apply_event(state, pause_event);
    assert(paused.state == STATE_PAUSED);
    assert(paused.magnetron_state == MAGNETRON_OFF);
    
    // Resume
    Event resume_event = {.type = EVENT_RESUME};
    MicrowaveStatus resumed = apply_event(paused, resume_event);
    assert(resumed.state == STATE_COOKING);
    assert(resumed.magnetron_state == MAGNETRON_ON);
    
    printf("  ✓ All tests passed\n");
}

void test_create_initial_state(void) {
    printf("Test: create_initial_state\n");
    
    MicrowaveStatus state = create_initial_state();
    
    assert(state.state == STATE_STANDBY);
    assert(state.remaining_time == 0);
    assert(state.current_power == POWER_500W);
    assert(state.magnetron_state == MAGNETRON_OFF);
    assert(state.relay_state == RELAY_OFF);
    assert(state.elapsed_time == 0);
    
    printf("  ✓ All tests passed\n");
}

void test_status_to_display(void) {
    printf("Test: status_to_display\n");
    
    MicrowaveStatus state = create_initial_state();
    state.state = STATE_COOKING;
    state.remaining_time = 30;
    
    DisplayData display = status_to_display(state);
    
    assert(display.time_display == 30);
    assert(display.power_display == POWER_500W);
    assert(display.state_label != NULL);
    
    printf("  ✓ All tests passed\n");
}

int main(void) {
    printf("=== Microwave Core Logic Unit Tests ===\n\n");
    
    test_calculate_remaining_time();
    test_next_power_level();
    test_next_cooking_time();
    test_get_magnetron_cycle();
    test_validate_cooking_config();
    test_apply_event_start_cooking();
    test_apply_event_timer_tick();
    test_apply_event_timer_complete();
    test_apply_event_pause_resume();
    test_create_initial_state();
    test_status_to_display();
    
    printf("\n=== All tests passed! ✓ ===\n");
    
    return 0;
}
