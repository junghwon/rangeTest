#include "extensions.h"

/* ============================================================================
   Extension Implementations
   ============================================================================ */

/* Auto Cooking Recipes */
const FoodRecipe RECIPES[] = {
    [FOOD_TYPE_POPCORN] = {180, POWER_500W},    // 3 min at full power
    [FOOD_TYPE_BEVERAGE] = {120, POWER_300W},  // 2 min at 60% power
    [FOOD_TYPE_FROZEN] = {600, POWER_200W},    // 10 min at 40% power
};

FoodRecipe get_recipe_for_food(FoodType type) {
    if (type >= FOOD_TYPE_CUSTOM) {
        return (FoodRecipe){0, POWER_500W};  // Default
    }
    return RECIPES[type];
}

/* Defrost Mode Calculation */
DefrostSchedule calculate_defrost_schedule(DefrostConfig config) {
    if (config.mode == DEFROST_MODE_WEIGHT) {
        // 50g per minute at 30% power
        uint32_t total_time = (config.parameter / 50) * 60;
        return (DefrostSchedule){
            .on_seconds = 10,
            .off_seconds = 20,
            .total_cycles = total_time / 30,
        };
    } else {
        // DEFROST_MODE_TIME
        return (DefrostSchedule){
            .on_seconds = 10,
            .off_seconds = 20,
            .total_cycles = config.parameter / 30,
        };
    }
}

/* Sensor Integration */
PowerLevel adjust_power_from_sensors(
    PowerLevel initial_power,
    SensorReading reading
) {
    if (reading.sensor_error) {
        return initial_power;  // Use default if sensor fails
    }

    // If temperature is already high, reduce power
    if (reading.temperature_celsius > 60) {
        if (initial_power > POWER_200W) {
            return initial_power - 100;  // Decrease by one level
        }
    }

    // If humidity is too high, reduce power to prevent overheating
    if (reading.humidity_percent > 80) {
        if (initial_power > POWER_100W) {
            return initial_power - 100;
        }
    }

    return initial_power;
}

/* Energy Saving */
MicrowaveStatus apply_energy_saving(
    MicrowaveStatus current,
    EnergySavingMode mode
) {
    if (!mode.enabled) {
        return current;
    }

    // Limit power in eco mode
    if (current.current_power > mode.eco_power_limit) {
        MicrowaveStatus adjusted = current;
        adjusted.current_power = mode.eco_power_limit;
        return adjusted;
    }

    return current;
}

/* Cooking Statistics */
CookingStatistics update_statistics(
    CookingStatistics current,
    uint32_t session_time,
    PowerLevel power_used
) {
    CookingStatistics updated = current;
    
    updated.total_cooking_time += session_time;
    updated.total_sessions += 1;
    updated.last_cooking_time = session_time;
    
    // Update average (simplified)
    updated.average_power_level = 
        (current.average_power_level + power_used) / 2;
    
    // Track most used power
    if (updated.total_sessions == 1 || power_used > current.average_power_level) {
        updated.most_used_power = power_used;
    }
    
    return updated;
}
