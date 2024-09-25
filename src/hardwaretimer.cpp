#include "hardwaretimer.h"

// Alarm interrupt handler
static volatile bool elapsed;

static void hardware_timer_handler(void) {
    // Clear the alarm irq
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_NUM);

    // Assume alarm 0 has fired
    //printf("Alarm IRQ fired\n");
    elapsed = true;
}

void timer_us_initialize(uint32_t delay_us) {
    // Alarm interrupt handler
    elapsed = false;

    // Enable the interrupt for our alarm (the timer outputs 4 alarm irqs)
    hw_set_bits(&timer_hw->inte, 1u << TIMER_NUM);
    // Set irq handler for alarm irq
    irq_set_exclusive_handler(TIMER_IRQ_0, hardware_timer_handler);
    // Enable the alarm irq
    irq_set_enabled(TIMER_IRQ_0, true);
    // Enable interrupt in block and at processor

    // Alarm is only 32 bits so if trying to delay more
    // than that need to be careful and keep track of the upper
    // bits
    uint64_t target = timer_hw->timerawl + delay_us;

    // Write the lower 32 bits of the target time to the alarm which
    // will arm it
    timer_hw->alarm[TIMER_NUM] = (uint32_t) target;
}

bool timer_us_elapsed(){
    return elapsed;
}
