/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/mycure/Down...chitecture/ia32/educational/include/pd.h
 *
 * created       julien quintard   [mon jan 10 09:05:19 2011]
 * updated       julien quintard   [mon apr 11 13:20:03 2011]
 */

#ifndef ARCHITECTURE_PD_H
#define ARCHITECTURE_PD_H       1

/*
 * ---------- macros ----------------------------------------------------------
 */

#define ARCHITECTURE_PD_SIZE            1024

/*
 * this value defines the page directory entry which acts as the mirror
 * entry i.e the entry referencing the page directory itself.
 */

#define ARCHITECTURE_PD_MIRROR          1023

#define ARCHITECTURE_PD_USER            (1<<2)
#define ARCHITECTURE_PD_SUPERVISOR      (0<<2)

#define ARCHITECTURE_PD_RW              (1<<1)
#define ARCHITECTURE_PD_RO              (0<<1)

#define ARCHITECTURE_PD_PRESENT         (1<<0)

#define ARCHITECTURE_PD_OTHER           (0b000000 << 3)

#define ARCHITECTURE_PDE(_ADDR_, _BITS_)                                     \
    (((_ADDR_) & 0xFF00)|((_BITS_) & 0x00FF))

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include <architecture/types.h>

/*
 * ---------- types -----------------------------------------------------------
 */

typedef t_uint32 at_pde;

typedef struct pd
{
    at_pde* table;
}           as_pd;

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../pd.c
 */

/*
 * ../pd.c
 */


/*
 * eop
 */

#endif
