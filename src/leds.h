/**
 * @file leds.h
 * @author Lautaro Vera (lautarovera93@gmail.com)
 * @brief Cabecera del driver Leds
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include <stdbool.h>
#include "errores.h"

/**
 * @brief Configura la biblioteca y apaga todos los leds
 * 
 * @param direccion Dirección del puerto GPIO que controla los leds
 */
void LedsInit(uint16_t *direccion, registro_errores_t registro_errores);

/**
 * @brief Prende un led
 * 
 * @param led Número de led a prender (1 a 16)
 */
void LedTurnOn(uint8_t led);

/**
 * @brief Apaga un led
 * 
 * @param led Número de led a apagar (1 a 16)
 */
void LedTurnOff(uint8_t led);

/**
 * @brief Prende todos los leds (1 a 16)
 * 
 */
void LedTurnOnAll(void);

/**
 * @brief Apaga todos los leds (1 a 16)
 * 
 */
void LedTurnOffAll(void);

/**
 * @brief Retorna por parámetro el estado del led
 * 
 * @param led Número de led (1 a 16)
 * @param led_state Estado del led ('true' prendido, 'false' apagado)
 * @return true Si el número de led es válido
 * @return false Si el número de led es inválido
 */
bool LedGetState(uint8_t led, bool *led_state);

#endif