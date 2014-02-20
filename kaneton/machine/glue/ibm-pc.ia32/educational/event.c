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

d_event			glue_event_dispatch =
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

t_status                glue_event_show(i_event                id,
                                        mt_margin              margin)
{

}

t_status                glue_event_dump(void)
{
}

t_status                glue_event_notify(i_event              id)
{
}

t_status                glue_event_enable(void)
{
}

t_status                glue_event_disable(void)
{
}

t_status                glue_event_reserve(i_event             id,
                                           t_type              type,
                                           u_event_handler     handle,
                                           t_data              data)
{

}

t_status                glue_event_release(i_event             id)
{
}

t_status                glue_event_initialize(void)
{
}

t_status                glue_event_clean(void)
{
}
/* END FIXME[code to complete] */

