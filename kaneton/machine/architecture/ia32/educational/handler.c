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

void architecture_handler_default(i_event id, t_data data)
{
    module_call(console, message,
            '+', "Interrupt: 0x%x\n",
            id);
}

void architecture_handler_keyboard(i_event id, t_data data)
{
    module_call(console, message,
            '+', "keyboard\n");
    platform_pic_acknowledge(1);
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

t_status architecture_handler_setup(void)
{
    int i;
    for (i = 0; i < 256; i++)
        _event_handler_array[i] = architecture_handler_default;

    MACHINE_LEAVE();
}

t_status architecture_handler_reserve(i_event id,
                                      t_event_routine handler)
{
    if (id >= ARCHITECTURE_HANDLER_SIZE)
        MACHINE_ESCAPE("Index out of bound: %i", id);

    _event_handler_array[id] = handler;

    MACHINE_LEAVE();
}

t_status architecture_handler_release(i_event id)
{
    if (id >= ARCHITECTURE_HANDLER_SIZE)
        MACHINE_ESCAPE("Index out of bound");

    _event_handler_array[id] = architecture_handler_default;

    MACHINE_LEAVE();
}



