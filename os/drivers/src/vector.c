#include "vector.h"

void blocking_handler(void) {
  while (1) {
  }
}

void null_handler(void) {}

// system interrupts
void _reset(void)
    __attribute__((naked, noreturn, weak, alias("blocking_handler")));
void nmi_handler(void) __attribute__((weak, alias("blocking_handler")));
void hard_fault_handler(void) __attribute__((weak, alias("blocking_handler")));
void mem_manage_handler(void) __attribute__((weak, alias("blocking_handler")));
void bus_fault_handler(void) __attribute__((weak, alias("blocking_handler")));
void usage_fault_handler(void) __attribute__((weak, alias("blocking_handler")));

void sv_call_handler(void) __attribute__((weak, alias("blocking_handler")));
void debug_monitor_handler(void)
    __attribute__((weak, alias("blocking_handler")));
void pend_sv_handler(void) __attribute__((weak, alias("blocking_handler")));
void sys_tick_handler(void) __attribute__((weak, alias("blocking_handler")));

// peripheral interrupts
void wwdg_isr(void) __attribute__((weak, alias("blocking_handler")));
void pvd_isr(void) __attribute__((weak, alias("blocking_handler")));
void tamp_stamp_isr(void) __attribute__((weak, alias("blocking_handler")));
void rtc_wkup_isr(void) __attribute__((weak, alias("blocking_handler")));
void flash_isr(void) __attribute__((weak, alias("blocking_handler")));
void rcc_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti0_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti1_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti2_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti3_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti4_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_stream0_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_stream1_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_stream2_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_stream3_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_stream4_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_stream5_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_stream6_isr(void) __attribute__((weak, alias("blocking_handler")));
void adc_isr(void) __attribute__((weak, alias("blocking_handler")));
void can1_tx_isr(void) __attribute__((weak, alias("blocking_handler")));
void can1_rx0_isr(void) __attribute__((weak, alias("blocking_handler")));
void can1_rx1_isr(void) __attribute__((weak, alias("blocking_handler")));
void can1_sce_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti9_5_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim1_brk__tim9_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim1_up__tim10_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim1_trg_com_tim11_isr(void)
    __attribute__((weak, alias("blocking_handler")));
void tim1_cc_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim2_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim3_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim4_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c1_ev_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c1_er_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c2_ev_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c2_er_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi1_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi2_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart1_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart2_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart3_isr(void) __attribute__((weak, alias("blocking_handler")));
void exti15_10_isr(void) __attribute__((weak, alias("blocking_handler")));
void rtc_alarm_isr(void) __attribute__((weak, alias("blocking_handler")));
void otg_fs_wkup_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim8_brk_tim12_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim8_up_tim13_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim8_trg_com_tim14_isr(void)
    __attribute__((weak, alias("blocking_handler")));
void tim8_cc_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma1_stream7_isr(void) __attribute__((weak, alias("blocking_handler")));
void fsmc_isr(void) __attribute__((weak, alias("blocking_handler")));
void sdio_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim5_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi3_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart4_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart5_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim6_dac_isr(void) __attribute__((weak, alias("blocking_handler")));
void tim7_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_stream0_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_stream1_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_stream2_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_stream3_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_stream4_isr(void) __attribute__((weak, alias("blocking_handler")));
void eth_isr(void) __attribute__((weak, alias("blocking_handler")));
void eth_wkup_isr(void) __attribute__((weak, alias("blocking_handler")));
void can2_tx_isr(void) __attribute__((weak, alias("blocking_handler")));
void can2_rx0_isr(void) __attribute__((weak, alias("blocking_handler")));
void can2_rx1_isr(void) __attribute__((weak, alias("blocking_handler")));
void can2_sce_isr(void) __attribute__((weak, alias("blocking_handler")));
void otg_fs_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_stream5_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_stream6_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma2_stream7_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart6_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c3_ev_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c3_er_isr(void) __attribute__((weak, alias("blocking_handler")));
void otg_hs_ep1_out_isr(void) __attribute__((weak, alias("blocking_handler")));
void otg_hs_ep1_in_isr(void) __attribute__((weak, alias("blocking_handler")));
void otg_hs_wkup_isr(void) __attribute__((weak, alias("blocking_handler")));
void otg_hs_isr(void) __attribute__((weak, alias("blocking_handler")));
void dcmi_isr(void) __attribute__((weak, alias("blocking_handler")));
void cryp_isr(void) __attribute__((weak, alias("blocking_handler")));
void hash_rng_isr(void) __attribute__((weak, alias("blocking_handler")));
void fpu_isr(void) __attribute__((weak, alias("blocking_handler")));
