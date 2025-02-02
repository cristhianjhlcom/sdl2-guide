#include "common.h"

// Functions definitions.
void timer_init(timer_t *t) {
    t->start_ticks = 0;
    t->paused_ticks = 0;
    t->paused = false;
    t->started = false;
}
// Various clock actions.
void timer_start(timer_t *t) {
    t->started = true;
    t->paused = false;
    t->start_ticks = SDL_GetTicks();
    t->paused_ticks = 0;
}
void timer_stop(timer_t *t) {
    t->started = false;
    t->paused = true;
    t->start_ticks = 0;
    t->paused_ticks = 0;
}
void timer_pause(timer_t *t) {
    // If the timer is running and isn't already paused.
    if (t->started && !t->paused) {
        // Pause the timer.
        t->paused = true;
        // Calculate the paused ticks.
        t->paused_ticks = SDL_GetTicks() - t->start_ticks;
        t->start_ticks = 0;
    }
}
void timer_unpause(timer_t *t) {
    // If the timer is running and paused.
    if (t->started && t->paused) {
        // Unpause the timer.
        t->paused = false;
        // Reset the starting ticks.
        t->start_ticks = SDL_GetTicks() - t->paused_ticks;
        t->paused_ticks = 0;
    }
}
// Gets timer's time.
Uint32 timer_get_ticks(timer_t *t) {
    // The actual timer time.
    Uint32 time = 0;
    // If the timer is running.
    if (t->started) {
        if (t->paused) {
            // Return the number of ticks when the timer was paused.
            time = t->paused_ticks;
        } else {
            // Return the current time minus the start time.
            time = SDL_GetTicks() - t->start_ticks;
        }
    }

    return time;
}
// Checks the status of the timer.
bool timer_is_started(timer_t *t) {
    return t->started;
}
bool timer_is_paused(timer_t *t) {
    return t->paused;
}
