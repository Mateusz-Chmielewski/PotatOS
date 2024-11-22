#define IRQ_COUNT 82

typedef void (*fn_ptr)(void);

// https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#page=374
// vector table contains 13+82 pointers to functions (interrupt handlers)
// 13 system interrupts
// 82 periphal interrupts
typedef struct
{
  unsigned int *initial_sp_value;
  fn_ptr reset;
  fn_ptr nmi;
  fn_ptr hard_fault;
  fn_ptr mem_manage;
  fn_ptr bus_fault;
  fn_ptr usage_fault;
  fn_ptr reserved_x001C[4];
  fn_ptr sv_call;
  fn_ptr debug_monitor;
  fn_ptr reserved_x0034;
  fn_ptr pend_sv;
  fn_ptr systick;
  fn_ptr irq[IRQ_COUNT];
} vector_table_t;

// isr - interrupt service routine
// defining interrupt handlers as weak functions
// https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf#page=375

void blocking_handler(void);

void null_handler(void);

// system interrupts
void _reset(void);
void nmi_handler(void);
void hard_fault_handler(void);
void sv_call_handler(void);
void pend_sv_handler(void);
void sys_tick_handler(void);

// peripheral interrupts
void wwdg_isr(void);
void pvd_isr(void);
void tamp_stamp_isr(void);
void rtc_wkup_isr(void);
void flash_isr(void);
void rcc_isr(void);
void exti0_isr(void);
void exti1_isr(void);
void exti2_isr(void);
void exti3_isr(void);
void exti4_isr(void);
void dma1_stream0_isr(void);
void dma1_stream1_isr(void);
void dma1_stream2_isr(void);
void dma1_stream3_isr(void);
void dma1_stream4_isr(void);
void dma1_stream5_isr(void);
void dma1_stream6_isr(void);
void adc_isr(void);
void can1_tx_isr(void);
void can1_rx0_isr(void);
void can1_rx1_isr(void);
void can1_sce_isr(void);
void exti9_5_isr(void);
void tim1_brk__tim9_isr(void);
void tim1_up__tim10_isr(void);
void tim1_trg_com_tim11_isr(void);
void tim1_cc_isr(void);
void tim2_isr(void);
void tim3_isr(void);
void tim4_isr(void);
void i2c1_ev_isr(void);
void i2c1_er_isr(void);
void i2c2_ev_isr(void);
void i2c2_er_isr(void);
void spi1_isr(void);
void spi2_isr(void);
void usart1_isr(void);
void usart2_isr(void);
void usart3_isr(void);
void exti15_10_isr(void);
void rtc_alarm_isr(void);
void otg_fs_wkup_isr(void);
void tim8_brk_tim12_isr(void);
void tim8_up_tim13_isr(void);
void tim8_trg_com_tim14_isr(void);
void tim8_cc_isr(void);
void dma1_stream7_isr(void);
void fsmc_isr(void);
void sdio_isr(void);
void tim5_isr(void);
void spi3_isr(void);
void uart4_isr(void);
void uart5_isr(void);
void tim6_dac_isr(void);
void tim7_isr(void);
void dma2_stream0_isr(void);
void dma2_stream1_isr(void);
void dma2_stream2_isr(void);
void dma2_stream3_isr(void);
void dma2_stream4_isr(void);
void eth_isr(void);
void eth_wkup_isr(void);
void can2_tx_isr(void);
void can2_rx0_isr(void);
void can2_rx1_isr(void);
void can2_sce_isr(void);
void otg_fs_isr(void);
void dma2_stream5_isr(void);
void dma2_stream6_isr(void);
void dma2_stream7_isr(void);
void usart6_isr(void);
void i2c3_ev_isr(void);
void i2c3_er_isr(void);
void otg_hs_ep1_out_isr(void);
void otg_hs_ep1_in_isr(void);
void otg_hs_wkup_isr(void);
void otg_hs_isr(void);
void dcmi_isr(void);
void cryp_isr(void);
void hash_rng_isr(void);
void fpu_isr(void);

#define NVIC_WWDG_IRQ 0
#define NVIC_PVD_IRQ 1
#define NVIC_TAMPER_IRQ 2
#define NVIC_RTC_IRQ 3
#define NVIC_FLASH_IRQ 4
#define NVIC_RCC_IRQ 5
#define NVIC_EXTI0_IRQ 6
#define NVIC_EXTI1_IRQ 7
#define NVIC_EXTI2_IRQ 8
#define NVIC_EXTI3_IRQ 9
#define NVIC_EXTI4_IRQ 10
#define NVIC_DMA1_CHANNEL1_IRQ 11
#define NVIC_DMA1_CHANNEL2_IRQ 12
#define NVIC_DMA1_CHANNEL3_IRQ 13
#define NVIC_DMA1_CHANNEL4_IRQ 14
#define NVIC_DMA1_CHANNEL5_IRQ 15
#define NVIC_DMA1_CHANNEL6_IRQ 16
#define NVIC_DMA1_CHANNEL7_IRQ 17
#define NVIC_ADC1_2_IRQ 18
#define NVIC_USB_HP_CAN_TX_IRQ 19
#define NVIC_USB_LP_CAN_RX0_IRQ 20
#define NVIC_CAN_RX1_IRQ 21
#define NVIC_CAN_SCE_IRQ 22
#define NVIC_EXTI9_5_IRQ 23
#define NVIC_TIM1_BRK_IRQ 24
#define NVIC_TIM1_UP_IRQ 25
#define NVIC_TIM1_TRG_COM_IRQ 26
#define NVIC_TIM1_CC_IRQ 27
#define NVIC_TIM2_IRQ 28
#define NVIC_TIM3_IRQ 29
#define NVIC_TIM4_IRQ 30
#define NVIC_I2C1_EV_IRQ 31
#define NVIC_I2C1_ER_IRQ 32
#define NVIC_I2C2_EV_IRQ 33
#define NVIC_I2C2_ER_IRQ 34
#define NVIC_SPI1_IRQ 35
#define NVIC_SPI2_IRQ 36
#define NVIC_USART1_IRQ 37
#define NVIC_USART2_IRQ 38
#define NVIC_USART3_IRQ 39
#define NVIC_EXTI15_10_IRQ 40
#define NVIC_RTC_ALARM_IRQ 41
#define NVIC_USB_WKUP_IRQ 42
#define NVIC_TIM8_BRK_IRQ 43
#define NVIC_TIM8_UP_IRQ 44
#define NVIC_TIM8_TRG_COM_IRQ 45
#define NVIC_TIM8_CC_IRQ 46
#define NVIC_ADC3_IRQ 47
#define NVIC_FSMC_IRQ 48
#define NVIC_SDIO_IRQ 49
#define NVIC_TIM5_IRQ 50
#define NVIC_SPI3_IRQ 51
#define NVIC_UART4_IRQ 52
#define NVIC_UART5_IRQ 53
#define NVIC_TIM6_IRQ 54
#define NVIC_TIM7_IRQ 55
#define NVIC_DMA2_CHANNEL1_IRQ 56
#define NVIC_DMA2_CHANNEL2_IRQ 57
#define NVIC_DMA2_CHANNEL3_IRQ 58
#define NVIC_DMA2_CHANNEL4_5_IRQ 59
#define NVIC_DMA2_CHANNEL5_IRQ 60
#define NVIC_ETH_IRQ 61
#define NVIC_ETH_WKUP_IRQ 62
#define NVIC_CAN2_TX_IRQ 63
#define NVIC_CAN2_RX0_IRQ 64
#define NVIC_CAN2_RX1_IRQ 65
#define NVIC_CAN2_SCE_IRQ 66
#define NVIC_OTG_FS_IRQ 67
#define NVIC_DMA2_CHANNEL6_IRQ 68
#define NVIC_DMA2_CHANNEL7_IRQ 69
#define NVIC_USART6_IRQ 70
#define NVIC_I2C3_EV_IRQ 72
#define NVIC_I2C3_ER_IRQ 73
#define NVIC_OTG_HS_EP1_OUT_IRQ 74
#define NVIC_OTG_HS_EP1_IN_IRQ 75
#define NVIC_OTG_HS_WKUP_IRQ 76
#define NVIC_OTG_HS_IRQ 77
#define NVIC_DCMI_IRQ 78
#define NVIC_CRYP_IRQ 79
#define NVIC_HASH_RNG_IRQ 80
#define NVIC_FPU_IRQ 81

// used to initalize irq handlers
#define IRQ_HANDLERS                                \
  [NVIC_WWDG_IRQ] = wwdg_isr,                       \
  [NVIC_PVD_IRQ] = pvd_isr,                         \
  [NVIC_TAMPER_IRQ] = tamp_stamp_isr,               \
  [NVIC_RTC_IRQ] = rtc_wkup_isr,                    \
  [NVIC_FLASH_IRQ] = flash_isr,                     \
  [NVIC_RCC_IRQ] = rcc_isr,                         \
  [NVIC_EXTI0_IRQ] = exti0_isr,                     \
  [NVIC_EXTI1_IRQ] = exti1_isr,                     \
  [NVIC_EXTI2_IRQ] = exti2_isr,                     \
  [NVIC_EXTI3_IRQ] = exti3_isr,                     \
  [NVIC_EXTI4_IRQ] = exti4_isr,                     \
  [NVIC_DMA1_CHANNEL1_IRQ] = dma1_stream0_isr,      \
  [NVIC_DMA1_CHANNEL2_IRQ] = dma1_stream1_isr,      \
  [NVIC_DMA1_CHANNEL3_IRQ] = dma1_stream2_isr,      \
  [NVIC_DMA1_CHANNEL4_IRQ] = dma1_stream3_isr,      \
  [NVIC_DMA1_CHANNEL5_IRQ] = dma1_stream4_isr,      \
  [NVIC_DMA1_CHANNEL6_IRQ] = dma1_stream5_isr,      \
  [NVIC_DMA1_CHANNEL7_IRQ] = dma1_stream6_isr,      \
  [NVIC_ADC1_2_IRQ] = adc_isr,                      \
  [NVIC_USB_HP_CAN_TX_IRQ] = can1_tx_isr,           \
  [NVIC_USB_LP_CAN_RX0_IRQ] = can1_rx0_isr,         \
  [NVIC_CAN_RX1_IRQ] = can1_rx1_isr,                \
  [NVIC_CAN_SCE_IRQ] = can1_sce_isr,                \
  [NVIC_EXTI9_5_IRQ] = exti9_5_isr,                 \
  [NVIC_TIM1_BRK_IRQ] = tim1_brk__tim9_isr,         \
  [NVIC_TIM1_UP_IRQ] = tim1_up__tim10_isr,          \
  [NVIC_TIM1_TRG_COM_IRQ] = tim1_trg_com_tim11_isr, \
  [NVIC_TIM1_CC_IRQ] = tim1_cc_isr,                 \
  [NVIC_TIM2_IRQ] = tim2_isr,                       \
  [NVIC_TIM3_IRQ] = tim3_isr,                       \
  [NVIC_TIM4_IRQ] = tim4_isr,                       \
  [NVIC_I2C1_EV_IRQ] = i2c1_ev_isr,                 \
  [NVIC_I2C1_ER_IRQ] = i2c1_er_isr,                 \
  [NVIC_I2C2_EV_IRQ] = i2c2_ev_isr,                 \
  [NVIC_I2C2_ER_IRQ] = i2c2_er_isr,                 \
  [NVIC_SPI1_IRQ] = spi1_isr,                       \
  [NVIC_SPI2_IRQ] = spi2_isr,                       \
  [NVIC_USART1_IRQ] = usart1_isr,                   \
  [NVIC_USART2_IRQ] = usart2_isr,                   \
  [NVIC_USART3_IRQ] = usart3_isr,                   \
  [NVIC_EXTI15_10_IRQ] = exti15_10_isr,             \
  [NVIC_RTC_ALARM_IRQ] = rtc_alarm_isr,             \
  [NVIC_USB_WKUP_IRQ] = otg_fs_wkup_isr,            \
  [NVIC_TIM8_BRK_IRQ] = tim8_brk_tim12_isr,         \
  [NVIC_TIM8_UP_IRQ] = tim8_up_tim13_isr,           \
  [NVIC_TIM8_TRG_COM_IRQ] = tim8_trg_com_tim14_isr, \
  [NVIC_TIM8_CC_IRQ] = tim8_cc_isr,                 \
  [NVIC_ADC3_IRQ] = adc_isr,                        \
  [NVIC_FSMC_IRQ] = fsmc_isr,                       \
  [NVIC_SDIO_IRQ] = sdio_isr,                       \
  [NVIC_TIM5_IRQ] = tim5_isr,                       \
  [NVIC_SPI3_IRQ] = spi3_isr,                       \
  [NVIC_UART4_IRQ] = uart4_isr,                     \
  [NVIC_UART5_IRQ] = uart5_isr,                     \
  [NVIC_TIM6_IRQ] = tim6_dac_isr,                   \
  [NVIC_TIM7_IRQ] = tim7_isr,                       \
  [NVIC_DMA2_CHANNEL1_IRQ] = dma2_stream0_isr,      \
  [NVIC_DMA2_CHANNEL2_IRQ] = dma2_stream1_isr,      \
  [NVIC_DMA2_CHANNEL3_IRQ] = dma2_stream2_isr,      \
  [NVIC_DMA2_CHANNEL4_5_IRQ] = dma2_stream3_isr,    \
  [NVIC_DMA2_CHANNEL5_IRQ] = dma2_stream4_isr,      \
  [NVIC_ETH_IRQ] = eth_isr,                         \
  [NVIC_ETH_WKUP_IRQ] = eth_wkup_isr,               \
  [NVIC_CAN2_TX_IRQ] = can2_tx_isr,                 \
  [NVIC_CAN2_RX0_IRQ] = can2_rx0_isr,               \
  [NVIC_CAN2_RX1_IRQ] = can2_rx1_isr,               \
  [NVIC_CAN2_SCE_IRQ] = can2_sce_isr,               \
  [NVIC_OTG_FS_IRQ] = otg_fs_isr,                   \
  [NVIC_DMA2_CHANNEL6_IRQ] = dma2_stream5_isr,      \
  [NVIC_DMA2_CHANNEL7_IRQ] = dma2_stream6_isr,      \
  [NVIC_USART6_IRQ] = usart6_isr,                   \
  [NVIC_I2C3_EV_IRQ] = i2c3_ev_isr,                 \
  [NVIC_I2C3_ER_IRQ] = i2c3_er_isr,                 \
  [NVIC_OTG_HS_EP1_OUT_IRQ] = otg_hs_ep1_out_isr,   \
  [NVIC_OTG_HS_EP1_IN_IRQ] = otg_hs_ep1_in_isr,     \
  [NVIC_OTG_HS_WKUP_IRQ] = otg_hs_wkup_isr,         \
  [NVIC_OTG_HS_IRQ] = otg_hs_isr,                   \
  [NVIC_DCMI_IRQ] = dcmi_isr,                       \
  [NVIC_CRYP_IRQ] = cryp_isr,                       \
  [NVIC_HASH_RNG_IRQ] = hash_rng_isr,               \
  [NVIC_FPU_IRQ] = fpu_isr
