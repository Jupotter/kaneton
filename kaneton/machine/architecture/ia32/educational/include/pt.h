/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/mycure/Down...chitecture/ia32/educational/include/pt.h
 *
 * created       julien quintard   [mon jan 10 09:31:37 2011]
 * updated       julien quintard   [mon apr 11 13:21:04 2011]
 */

#ifndef ARCHITECTURE_PT_H
#define ARCHITECTURE_PT_H       1

/*
 * ---------- macros ----------------------------------------------------------
 */

/*
 * defines the number entries composing a page table.
 */

#define ARCHITECTURE_PT_SIZE            1024

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include <architecture/types.h>

/*
 * ---------- types -----------------------------------------------------------
 */

typedef t_uint32 at_pte;

typedef struct pt
{
    at_pte* table;
}           as_pt;


/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../pt.c
 */

/*
 * ../pt.c
 */

t_status architecture_pt_create_page(t_uint32 addr);


/*
 * eop
 */

#endif
