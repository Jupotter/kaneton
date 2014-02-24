/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/mycure/kane...ine/glue/ibm-pc.ia32/educational/event.c
 *
 * created       renaud voltz   [mon feb 13 01:05:52 2006]
 * updated       julien quintard   [sat feb  5 12:30:16 2011]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file implements the event manager's glue.
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <kaneton.h>

/*
 * ---------- globals ---------------------------------------------------------
 */

/*
 * the event dispatcher.
 */

d_event                 glue_event_dispatch =
{
    glue_event_show,
    glue_event_dump,
    NULL,
    glue_event_enable,
    glue_event_disable,
    glue_event_reserve,
    glue_event_release,
    glue_event_initialize,
    NULL
};

t_status glue_event_dump(void)
{
    architecture_idt_dump();

    MACHINE_LEAVE();
}

/* BEGIN FIXME[code to complete] */

t_status                glue_event_show(i_event                id,
        mt_margin              margin)
{
//    o_event*            o;

    //    if (event_get(id, &o) != STATUS_OK)
    //        MACHINE_ESCAPE("unable to retrieve the event object");

    module_call(console, message,
            '#',
            MODULE_CONSOLE_MARGIN_FORMAT
            " machine:\n",
            MODULE_CONSOLE_MARGIN_VALUE(margin));

    MACHINE_LEAVE();
}

t_status                glue_event_enable(void)
{
    ARCHITECTURE_STI();
    __asm__("int $32");

    MACHINE_LEAVE();
}

t_status                glue_event_disable(void)
{
    ARCHITECTURE_CLI();

    MACHINE_LEAVE();
}

t_status                glue_event_reserve(i_event             id,
        t_type              type,
        u_event_handler     handle,
        t_data              data)
{
    o_event*            o;

    if (event_get(id, &o) != STATUS_OK)
        MACHINE_ESCAPE("unable to retrieve the event");

    if (architecture_handler_reserve(id, handle.routine) != STATUS_OK)
        MACHINE_ESCAPE("Unable to install the handler");

    MACHINE_LEAVE();
}

t_status                glue_event_release(i_event  id)
{
    if (architecture_handler_release(id) != STATUS_OK)
        MACHINE_ESCAPE("Unable to release the handler");
    MACHINE_LEAVE();
}

t_status                glue_event_initialize(void)
{
    int i;
    if (architecture_idt_initialize() != STATUS_OK)
        MACHINE_ESCAPE("Unable to initialize the IDT");

    if (architecture_handler_setup() != STATUS_OK)
        MACHINE_ESCAPE("Unable to setup the handlers");

    if (platform_pic_initialize()!= STATUS_OK)
        MACHINE_ESCAPE("Unable to initialize the PIC");
    for (i = 0; i < 8; i++)
        if (platform_pic_enable(i) != STATUS_OK)
            MACHINE_ESCAPE("Unable to initialize the PIC");

    MACHINE_LEAVE();
}

/* END FIXME[code to complete] */

