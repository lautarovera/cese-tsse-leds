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

#define LED_TO_BIT_OFFSET 1
#define BITS_MASK 1
#define LEDS_ALL_OFF 0x0000
#define LEDS_ALL_ON 0xFFFF

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
    if (led > 16)
    {
        Alerta("Número de led inválido");
    }
    else
    {
        *puerto |= LedToMask(led);
    }
}

void LedTurnOff(uint8_t led)
{
    if (led > 16)
    {
        Alerta("Número de led inválido");
    }
    else
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

void LedGetState(uint8_t led, bool *led_state)
{
    if (led > 16)
    {
        Alerta("Número de led inválido");
        led_state = NULL;
    }
    else
    {
        *led_state = (*puerto & LedToMask(led)) ? true : false;
    }
}