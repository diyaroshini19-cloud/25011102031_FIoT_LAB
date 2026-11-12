#include "main.h"
#include <string.h>
#include <stdint.h>

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
void Error_Handler(void);

static void debug_text(const char *s)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)s, (uint16_t)strlen(s), HAL_MAX_DELAY);
}

static void issue_command(const char *cmd, uint32_t timeout)
{
    uint8_t response[512] = {0};
    uint16_t length = 0;
    debug_text("\r\n> ");
    debug_text(cmd);
    HAL_UART_Transmit(&huart1, (uint8_t *)cmd, (uint16_t)strlen(cmd), 2000);
    HAL_UARTEx_ReceiveToIdle(&huart1, response, sizeof(response), &length, timeout);
    if (length) HAL_UART_Transmit(&huart2, response, length, 5000);
    else debug_text("(no response before timeout)\r\n");
}

int main(void)
{
    uint8_t byte;
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    debug_text("CAT10 TASK10B: ESP8266 AT command interface\r\n");
    issue_command("AT\r\n", 3000);
    issue_command("AT+GMR\r\n", 5000);
    issue_command("AT+CWMODE?\r\n", 3000);
    issue_command("AT+CWLAP\r\n", 30000);
    issue_command("AT+CIFSR\r\n", 5000);
    debug_text("Interactive bridge ready: type AT commands in the USART2 terminal.\r\n");

    while (1)
    {
        if (HAL_UART_Receive(&huart2, &byte, 1, 5) == HAL_OK)
            HAL_UART_Transmit(&huart1, &byte, 1, 100);
        if (HAL_UART_Receive(&huart1, &byte, 1, 5) == HAL_OK)
            HAL_UART_Transmit(&huart2, &byte, 1, 100);
    }
}
