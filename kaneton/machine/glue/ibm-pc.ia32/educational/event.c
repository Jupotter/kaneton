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
    glue_event_notify,
    glue_event_enable,
    glue_event_disable,
    glue_event_reserve,
    glue_event_release,
    glue_event_initialize,
    glue_event_clean
  };

/* BEGIN FIXME[code to complete] */

t_status                glue_event_reserve(i_event*             id,
                                           t_type              type,
                                           u_event_handler     handle,
                                           t_data              data)
{
    o_event*            o;

    if (event_get(*id, &o) != STATUS_OK)
        MACHINE_ESCAPE("unable to retrieve the event")

    if (architucture_idt_clean() != STATUS_OK)
        MACHINE_ESCAPE("this architecture can't be build");

    o->machine.idt.flush = BOOLEAN_FALSE;

    MACHINE_LEAVE();
}

t_status                glue_event_release(i_event             id)
{
}

t_status                glue_event_initialize(void)
{
    if (architecture_idt_initialize() != STATUS_OK)
        MACHINE_ESCAPE("Unable to initialize the GDT");

    MACHINE_LEAVE();
}

t_status                glue_event_clean(void)
{
}
/* END FIXME[code to complete] */

