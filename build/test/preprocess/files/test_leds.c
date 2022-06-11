#include "build/test/mocks/mock_errores.h"
#include "src/leds.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


static uint16_t ledsVirtuales;



static void RegistrarError(gravedad_t gravedad, const char *funcion, int linea, const char *mensaje, ...)

{

    char *bufer;

    printf("\n[%d]%s:%d> ", gravedad, funcion, linea);

    va_list va;

    

   __builtin_va_start(

   va

   ,

   mensaje

   )

                        ;

    printf(bufer, mensaje, va);

    

   __builtin_va_end(

   va

   )

             ;

}



void setUp(void)

{

    LedsInit(&ledsVirtuales, RegistrarError);

}



void tearDown(void)

{

}







void test_LedsOffAfterCreate(void)

{

    uint16_t ledsVirtuales = 0xFFFF;

    LedsInit(&ledsVirtuales, RegistrarError);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOnOneLed(void)

{

    LedTurnOn(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 4)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(50), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOffOneLed(void)

{

    LedTurnOn(5);

    LedTurnOff(5);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(58), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOnAndOffManyLeds(void)

{

    LedTurnOn(5);

    LedTurnOn(11);

    LedTurnOff(3);

    LedTurnOff(11);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((1 << 4)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_HEX16);

}





void test_InvalidUpperLimitTurnOnLed(void)

{

    RegistrarMensaje_CMockExpect(74, ALERTA, "LedTurnOn", 0, "Nmero de led invlido");

    RegistrarMensaje_CMockIgnoreArg_linea(75);

    LedTurnOn(17);

}





void test_TurnOnAllLeds(void)

{

    LedTurnOnAll();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(83), UNITY_DISPLAY_STYLE_HEX16);

}





void test_TurnOffAllLeds(void)

{

    LedTurnOnAll();

    LedTurnOffAll();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((ledsVirtuales)), (

   ((void *)0)

   ), (UNITY_UINT)(91), UNITY_DISPLAY_STYLE_HEX16);

}





void test_GetStateLedOff(void)

{

    

   _Bool 

        led_state = 

                    1

                        ;



    LedTurnOnAll();

    LedTurnOff(6);

    (void)LedGetState(6, &led_state);

    do {if (!(led_state)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(102)));}} while(0);

}





void test_GetStateLedOn(void)

{

    

   _Bool 

        led_state = 

                    1

                        ;



    LedTurnOn(9);

    (void)LedGetState(9, &led_state);

    do {if ((led_state)) {} else {UnityFail( ((" Expected TRUE Was FALSE")), (UNITY_UINT)((UNITY_UINT)(112)));}} while(0);

}





void test_OutboundParameterTurnOffLed(void)

{

    

   _Bool 

        led_state = 

                    1

                        ;



    LedTurnOnAll();

    RegistrarMensaje_CMockExpect(121, ALERTA, "LedTurnOff", 0, "Nmero de led invlido");

    RegistrarMensaje_CMockIgnoreArg_linea(122);

    LedTurnOff(25);

}



void test_OutboundParameterGetStateLed(void)

{

    

   _Bool 

        led_state = 

                    1

                        ;

    

   _Bool 

        ret_val = 

                  1

                      ;



    RegistrarMensaje_CMockExpect(131, ALERTA, "LedGetState", 0, "Nmero de led invlido");

    RegistrarMensaje_CMockIgnoreArg_linea(132);

    ret_val = LedGetState(19, &led_state);

    do {if (!(ret_val)) {} else {UnityFail( ((" Expected FALSE Was TRUE")), (UNITY_UINT)((UNITY_UINT)(134)));}} while(0);

}
