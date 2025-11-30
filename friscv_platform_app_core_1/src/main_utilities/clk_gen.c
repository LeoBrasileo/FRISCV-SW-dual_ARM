#include "main_utilities.h"

void cpu_clk_up(void) {
    u32 clk_cpu = 1;
    XGpio_DiscreteWrite(&axi_gpio_clk_gen, 1, clk_cpu);
}

void cpu_clk_down(void) {
    u32 clk_cpu = 0;
    XGpio_DiscreteWrite(&axi_gpio_clk_gen, 1, clk_cpu);
}

void mem_clk_up(void) {
    u32 clk_mem = 1;
    XGpio_DiscreteWrite(&axi_gpio_clk_gen, 2, clk_mem);
}

void mem_clk_down(void) {
    u32 clk_mem = 0;
    XGpio_DiscreteWrite(&axi_gpio_clk_gen, 2, clk_mem);
}


u32 clk_compute_delay_us(float freq_khz) {
    // period in microseconds
    float period_us = 1000.0f / freq_khz;

    // half period
    float half_period_us = period_us / 2.0f;

    // round to nearest integer
    return (u32)(half_period_us + 0.5f);
}
