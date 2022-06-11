/**
 * @file test_leds.c
 * @author Lautaro Vera (lautarovera93@gmail.com)
 * @brief Fichero de test para el framework Ceedling
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdarg.h>
#include "unity.h"
#include "leds.h"
#include "mock_errores.h"

static uint16_t ledsVirtuales;

static void RegistrarError(gravedad_t gravedad, const char *funcion, int linea, const char *mensaje, ...)
{
    char *bufer;
    printf("\n[%d]%s:%d> ", gravedad, funcion, linea);
    va_list va;
    va_start(va, mensaje);
    printf(bufer, mensaje, va);
    va_end(va);
}

void setUp(void)
{
    LedsInit(&ledsVirtuales, RegistrarError);
}

void tearDown(void)
{
}

/* Después de la inicialización todos los LEDs
deben quedar apagados. */
void test_LedsOffAfterCreate(void)
{
    uint16_t ledsVirtuales = 0xFFFF;
    LedsInit(&ledsVirtuales, RegistrarError);
    TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

/* Se puede prender un LED individual. */
void test_TurnOnOneLed(void)
{
    LedTurnOn(5);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, ledsVirtuales);
}

/* Se puede apagar un LED individual. */
void test_TurnOffOneLed(void)
{
    LedTurnOn(5);
    LedTurnOff(5);
    TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

/* Se pueden prender y apagar múltiples LED’s. */
void test_TurnOnAndOffManyLeds(void)
{
    LedTurnOn(5);
    LedTurnOn(11);
    LedTurnOff(3);
    LedTurnOff(11);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, ledsVirtuales);
}

/* Revisar limites de los parametros. */
void test_InvalidUpperLimitTurnOnLed(void)
{
    RegistrarMensaje_Expect(ALERTA, "LedTurnOn", 0, "Número de led inválido");
    RegistrarMensaje_IgnoreArg_linea();
    LedTurnOn(17);
}

/* Se pueden prender todos los LEDs de una vez. */
void test_TurnOnAllLeds(void)
{
    LedTurnOnAll();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}

/* Se pueden apagar todos los LEDs de una vez. */
void test_TurnOffAllLeds(void)
{
    LedTurnOnAll();
    LedTurnOffAll();
    TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

/* Se puede consultar el estado de un LED apagado. */
void test_GetStateLedOff(void)
{
    bool led_state = true;

    LedTurnOnAll();
    LedTurnOff(6);
    (void)LedGetState(6, &led_state);
    TEST_ASSERT_FALSE(led_state);
}

/* Se puede consultar el estado de un LED prendido. */
void test_GetStateLedOn(void)
{
    bool led_state = true;

    LedTurnOn(9);
    (void)LedGetState(9, &led_state);
    TEST_ASSERT_TRUE(led_state);
}

/* Revisar parámetros fuera de los limites. */
void test_OutboundParameterTurnOffLed(void)
{
    bool led_state = true;

    LedTurnOnAll();
    RegistrarMensaje_Expect(ALERTA, "LedTurnOff", 0, "Número de led inválido");
    RegistrarMensaje_IgnoreArg_linea();
    LedTurnOff(25);
}

void test_OutboundParameterGetStateLed(void)
{
    bool led_state = true;
    bool ret_val = true;

    RegistrarMensaje_Expect(ALERTA, "LedGetState", 0, "Número de led inválido");
    RegistrarMensaje_IgnoreArg_linea();
    ret_val = LedGetState(19, &led_state);
    TEST_ASSERT_FALSE(ret_val);
}