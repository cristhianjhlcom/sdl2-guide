#pragma once

#include "common.h"

typedef struct Timer timer_t;
typedef struct Timer {
    // The clock time when the timer started.
    Uint32 start_ticks;
    // The ticks stored when the timer was paused.
    Uint32 paused_ticks;
    // The timer status.
    bool paused;
    bool started;
} timer_t;

// Functions definitions.
void timer_init(timer_t *t);
// Various clock actions.
void timer_start(timer_t *t);
void timer_stop(timer_t *t);
void timer_pause(timer_t *t);
void timer_unpause(timer_t *t);
// Gets timer's time.
Uint32 timer_get_ticks(timer_t *t);
// Checks the status of the timer.
bool timer_is_started(timer_t *t);
bool timer_is_paused(timer_t *t);

extern timer_t timer;
