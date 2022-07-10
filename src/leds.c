/**
 * @file leds.c
 * @author Lautaro Vera (lautarovera93@gmail.com)
 * @brief Archivo fuente del driver Leds
 * 
 * El driver controla hasta 16 leds de una dirección GPIO pasada
 * como parámetro a la función de inicialización.
 * También permite la inyección de dependencia de una función de errores.
 * 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include "leds.h"

#define MAX_NUM_LEDS 16
#define MIN_NUM_LEDS 1
#define LED_TO_BIT_OFFSET 1
#define BITS_MASK 1
#define LEDS_ALL_OFF 0x0000
#define LEDS_ALL_ON 0xFFFF

#define ASSERT_VALID_LED(led) \
    ({bool retval = true; \
    if ((led) < MIN_NUM_LEDS || (led) > MAX_NUM_LEDS) \
    { \
        Alerta("Número de led inválido"); \
        retval = false; \
    }; \
    retval;})

static uint16_t *puerto;
static registro_errores_t RegistroErrores;

static uint16_t LedToMask(uint8_t led)
{
    return (BITS_MASK << (led - LED_TO_BIT_OFFSET));
}

void LedsInit(uint16_t *direccion, registro_errores_t registro_errores)
{
    puerto = direccion;
    RegistroErrores = registro_errores;
    *puerto = LEDS_ALL_OFF;
}

void LedTurnOn(uint8_t led)
{
    if (ASSERT_VALID_LED(led))
    {
        *puerto |= LedToMask(led);
    }
}

void LedTurnOff(uint8_t led)
{
    if (ASSERT_VALID_LED(led))
    {
        *puerto &= ~LedToMask(led);
    }
}

void LedTurnOnAll(void)
{
    *puerto = LEDS_ALL_ON;
}

void LedTurnOffAll(void)
{
    *puerto = LEDS_ALL_OFF;
}

bool LedGetState(uint8_t led, bool *led_state)
{
    bool ret_val = false;

    if (ASSERT_VALID_LED(led))
    {
        *led_state = (*puerto & LedToMask(led)) ? true : false;
        ret_val = true;
    }

    return ret_val;
}