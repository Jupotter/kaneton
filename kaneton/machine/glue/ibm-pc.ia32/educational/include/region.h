/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/mycure/kane...ibm-pc.ia32/educational/include/region.h
 *
 * created       julien quintard   [wed jun  6 16:22:05 2007]
 * updated       julien quintard   [sun dec 19 13:46:56 2010]
 */

#ifndef GLUE_REGION_H
#define GLUE_REGION_H           1

/*
 * ---------- macro functions -------------------------------------------------
 */

/*
 * this macro-function defines the region dispatcher.
 */

#define         machine_include_region()                                \
  extern d_region       glue_region_dispatch

/*
 * this macro-function dispatches the region calls.
 */

#define         machine_call_region(_function_, _args_...)              \
  (                                                                     \
    {                                                                   \
      t_status _r_ = STATUS_OK;                                         \
                                                                        \
      if (glue_region_dispatch.region_ ## _function_ != NULL)           \
        _r_ = glue_region_dispatch.region_ ## _function_(_args_);       \
                                                                        \
      _r_;                                                              \
    }                                                                   \
  )

/*
 * this macro-function includes data in 'm_region'.
 */

#define         machine_data_m_region()

/*
 * this macro-function includes data in 'o_region'.
 */

#define         machine_data_o_region()

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../region.c
 */

/*
 * ../region.c
 */


/*
 * eop
 */

#endif
