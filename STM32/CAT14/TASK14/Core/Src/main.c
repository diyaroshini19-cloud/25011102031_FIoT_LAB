/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ESPLib.h"
#include "bme280.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart1;
I2C_HandleTypeDef hi2c1;
static struct bme280_dev sensor;
static struct bme280_data reading;
static struct bme280_settings settings;
static uint8_t bme_address = BME280_I2C_ADDR_PRIM;
static void SystemClock_Config(void); static void MX_GPIO_Init(void); static void MX_USART1_UART_Init(void); static void MX_I2C1_Init(void);
static int8_t bme_read(uint8_t reg,uint8_t *data,uint32_t len,void *ctx){uint8_t a=*(uint8_t*)ctx;return HAL_I2C_Mem_Read(&hi2c1,(uint16_t)(a<<1),reg,I2C_MEMADD_SIZE_8BIT,data,(uint16_t)len,100)==HAL_OK?BME280_OK:BME280_E_COMM_FAIL;}
static int8_t bme_write(uint8_t reg,const uint8_t *data,uint32_t len,void *ctx){uint8_t a=*(uint8_t*)ctx;return HAL_I2C_Mem_Write(&hi2c1,(uint16_t)(a<<1),reg,I2C_MEMADD_SIZE_8BIT,(uint8_t*)data,(uint16_t)len,100)==HAL_OK?BME280_OK:BME280_E_COMM_FAIL;}
static void bme_delay(uint32_t us,void *ctx){(void)ctx;HAL_Delay((us+999U)/1000U);}
static int sensor_init(void){sensor.intf_ptr=&bme_address;sensor.intf=BME280_I2C_INTF;sensor.read=bme_read;sensor.write=bme_write;sensor.delay_us=bme_delay;if(bme280_init(&sensor)!=BME280_OK)return 0;settings.osr_h=BME280_OVERSAMPLING_1X;settings.osr_p=BME280_OVERSAMPLING_1X;settings.osr_t=BME280_OVERSAMPLING_1X;settings.filter=BME280_FILTER_COEFF_OFF;if(bme280_set_sensor_settings(BME280_SEL_OSR_PRESS|BME280_SEL_OSR_TEMP|BME280_SEL_OSR_HUM|BME280_SEL_FILTER,&settings,&sensor)!=BME280_OK)return 0;return bme280_set_sensor_mode(BME280_POWERMODE_NORMAL,&sensor)==BME280_OK;}
int main(void){HAL_Init();SystemClock_Config();MX_GPIO_Init();MX_USART1_UART_Init();MX_I2C1_Init();if(!sensor_init())Error_Handler();ESP8266_Init(StationMode,huart1);
/* Configure locally before flashing. Values are intentionally not embedded in the repository. */
ESP8266_wifiConnect("YOUR_WIFI_SSID","YOUR_WIFI_PASSWORD");ESP8266_portConnect("TCP","broker.emqx.io","1883");
MQTT_InitTypeDef_t mqtt={0};mqtt.clientID="STM32_BME280_CAT14";mqtt.username=NULL;mqtt.password=NULL;mqtt.keepAlive=60;mqtt.connectFlag=CleanSession;MQTT_connectBroker(&mqtt);MQTT_subscribeTopic("IOT",QoS0);
uint32_t previous=0;char json[128];for(;;){if(HAL_GetTick()-previous>=1000U){previous=HAL_GetTick();if(bme280_get_sensor_data(BME280_ALL,&reading,&sensor)==BME280_OK){long t=(long)reading.temperature;long p=(long)(reading.pressure/25600U);long h=(long)((reading.humidity*100U)/1024U);int n=snprintf(json,sizeof(json),"{\"temperature_centi_c\":%ld,\"pressure_hpa\":%ld,\"humidity_centi_pct\":%ld}",t,p,h);if(n>0&&(size_t)n<sizeof(json))MQTT_publishTopic("stm32/test/data",json,QoS0);}}char topic[64],message[64];MQTTDataHandler(topic,message);}}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* Configure voltage scaling */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    /* Configure HSI and PLL */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;

    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /* Configure CPU, AHB and APB clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

static void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

static void MX_I2C1_Init(void){hi2c1.Instance=I2C1;hi2c1.Init.ClockSpeed=100000;hi2c1.Init.DutyCycle=I2C_DUTYCYCLE_2;hi2c1.Init.OwnAddress1=0;hi2c1.Init.AddressingMode=I2C_ADDRESSINGMODE_7BIT;hi2c1.Init.DualAddressMode=I2C_DUALADDRESS_DISABLE;hi2c1.Init.OwnAddress2=0;hi2c1.Init.GeneralCallMode=I2C_GENERALCALL_DISABLE;hi2c1.Init.NoStretchMode=I2C_NOSTRETCH_DISABLE;if(HAL_I2C_Init(&hi2c1)!=HAL_OK)Error_Handler();}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
