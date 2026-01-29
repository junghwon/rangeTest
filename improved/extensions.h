#ifndef MICROWAVE_EXTENSIONS_H
#define MICROWAVE_EXTENSIONS_H

#include "types.h"

/* ============================================================================
   Extension Examples - Show how to extend the system
   ============================================================================ */

/* ============================================================================
   Feature: Food Type Auto Cooking
   ============================================================================ */

typedef enum {
    FOOD_TYPE_POPCORN,
    FOOD_TYPE_BEVERAGE,
    FOOD_TYPE_FROZEN,
    FOOD_TYPE_CUSTOM,
} FoodType;

typedef struct {
    uint32_t time_seconds;
    PowerLevel power;
} FoodRecipe;

/* Pure function: Get recipe for food type */
FoodRecipe get_recipe_for_food(FoodType type);

/* ============================================================================
   Feature: Defrost Mode
   ============================================================================ */

typedef enum {
    DEFROST_MODE_TIME,
    DEFROST_MODE_WEIGHT,
} DefrostMode;

typedef struct {
    DefrostMode mode;
    uint32_t parameter;  // time in seconds or weight in grams
} DefrostConfig;

/* Pure function: Calculate defrost cycles */
typedef struct {
    uint32_t on_seconds;
    uint32_t off_seconds;
    uint32_t total_cycles;
} DefrostSchedule;

DefrostSchedule calculate_defrost_schedule(DefrostConfig config);

/* ============================================================================
   Feature: Sensor Integration (Temperature/Humidity)
   ============================================================================ */

typedef struct {
    uint32_t temperature_celsius;
    uint32_t humidity_percent;
    bool sensor_error;
} SensorReading;

/* Pure function: Adjust power based on sensors */
PowerLevel adjust_power_from_sensors(
    PowerLevel initial_power,
    SensorReading reading
);

/* ============================================================================
   Feature: Energy Saving Mode
   ============================================================================ */

typedef struct {
    bool enabled;
    uint32_t idle_timeout_seconds;
    PowerLevel eco_power_limit;
} EnergySavingMode;

/* Pure function: Apply energy saving rules */
MicrowaveStatus apply_energy_saving(
    MicrowaveStatus current,
    EnergySavingMode mode
);

/* ============================================================================
   Feature: Cooking History and Statistics
   ============================================================================ */

typedef struct {
    uint32_t total_cooking_time;
    uint32_t total_sessions;
    uint32_t average_power_level;
    PowerLevel most_used_power;
    uint32_t last_cooking_time;
} CookingStatistics;

/* Pure function: Update statistics */
CookingStatistics update_statistics(
    CookingStatistics current,
    uint32_t session_time,
    PowerLevel power_used
);

#endif // MICROWAVE_EXTENSIONS_H
