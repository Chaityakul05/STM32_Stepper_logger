# 🌀 Stepper Motor + HC-SR04 Sensor + USART Logger (Bare-Metal STM32)

This project demonstrates the integration of a **stepper motor**, an **HC-SR04 ultrasonic sensor**, and **USART logging** using **bare-metal C** on the STM32F103C8T6 (Blue Pill). It logs real-time distance measurements while moving the motor step-by-step.

---

---

## 🔧 Requirements

- **STM32F103C8T6 (Blue Pill)**
- **28BYJ-48 stepper motor + ULN2003 driver**
- **HC-SR04 ultrasonic sensor**
- **USB to TTL UART adapter** (for serial logging)
- `arm-none-eabi-gcc`, `st-flash`, or `OpenOCD` (toolchain)

---

## 📌 File Descriptions

### `base.h`
- Defines peripheral base addresses and register offsets used by other files.

---

### `gpio.h` / `gpio.c`
Minimal GPIO control using register-level access.

**Functions:**
- `GPIO_Init(GPIO_e base, uint8_t pin, GPIO_Mode mode, GPIO_State state)`
- `GPIO_Write(...)`
- `GPIO_Read(...)`
- `GPIO_Delay(uint32_t cycles)`
- `GPIO_deInit(...)`

**Example:**
```c
GPIO_Config_t* pin = GPIO_Init(GPIO_A, 5, OUTPUT, GPIO_RESET);
GPIO_Write(pin, GPIO_SET);

---

### `usart.c` / `usart.h`
Low-level USART2 logging for data communication via UART.

```yaml
Provides:
  - USART initialization at custom baudrate.
  - Send/receive single characters.
  - `printf`-style logging.

Functions:
  - usart2_init()
  - usart2_write(uint8_t data)
  - usart2_read()
  - usart_set_baudrate(uint32_t peripheral_clock, uint32_t baudrate)
  - usart2_printf(const char* fmt, ...)

Example:
  usart2_init();
  usart2_printf("System started!\n");


Provides:
  - Initialization and deinitialization of sensor pins.
  - Echo time measurement.
  - Distance calculation in centimeters.

Functions:
  - HC_SR04_Config_t* HC_SR04_Init(GPIO_e base, uint8_t trigger_pin, uint8_t echo_pin)
  - uint32_t measureEchoTime(HC_SR04_Config_t* config)
  - float getDistanceCm(HC_SR04_Config_t* config)
  - void HC_SR04_deInit(HC_SR04_Config_t* config)

Example:
  HC_SR04_Config_t* sensor = HC_SR04_Init(GPIO_A, 8, 9);
  float dist = getDistanceCm(sensor);
  HC_SR04_deInit(sensor);



