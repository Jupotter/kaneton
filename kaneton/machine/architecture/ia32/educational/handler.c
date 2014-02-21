/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/mycure/kane.../architecture/ia32/educational/handler.c
 *
 * created       renaud voltz   [thu feb 23 10:49:43 2006]
 * updated       julien quintard   [mon apr 11 13:44:48 2011]
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <kaneton.h>

/*
 * ---------- functions -------------------------------------------------------
 */

void architecture_handler_default(void)
{
    __asm__("pusha");

    module_call(console, message,
            '+', "Interrupt\n");

    __asm__("popa; leave; iret");
}

void architecture_handler_keyboard(void)
{
    __asm__("pusha");

    module_call(console, message,
            '+', "keyboard\n");

    __asm__("popa; leave; iret");
}

void architecture_handler_clock(void)
{
    __asm__("pusha");

    static int tic = 0;
    static int sec = 0;
    tic++;
    if (tic % 100 == 0) {
        sec++;
        tic = 0;
        module_call(console, message,
                '+', "clock\n");
    }

    __asm__("popa; leave; iret");
}
