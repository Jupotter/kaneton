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
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    glue_event_initialize,
    NULL
  };

/* BEGIN FIXME[code to complete] */


t_status                glue_event_release(i_event             id)
{
    MACHINE_LEAVE();
}

t_status                glue_event_initialize(void)
{
    if (architecture_idt_initialize() != STATUS_OK)
        MACHINE_ESCAPE("Unable to initialize the GDT");

    MACHINE_LEAVE();
}

t_status                glue_event_clean(void)
{
    MACHINE_LEAVE();
}
/* END FIXME[code to complete] */

