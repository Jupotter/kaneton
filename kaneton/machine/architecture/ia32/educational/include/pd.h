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

#define ARCHITECTURE_PD_KER_STD                                              \
    (ARCHITECTURE_PD_OTHER                                                   \
    |ARCHITECTURE_PD_SUPERVISOR                                              \
    |ARCHITECTURE_PD_RW                                                      \
    |ARCHITECTURE_PD_PRESENT)

#define ARCHITECTURE_PDE(_ADDR_, _BITS_)                                     \
    (((_ADDR_) & 0xFFFFE00)|((_BITS_) & 0x00000FF))

#define ARCHITECTURE_PD_ENTRY(_NUM_)                                         \
    (((ARCHITECTURE_PD_MIRROR) << 22)                                        \
    |((ARCHITECTURE_PD_MIRROR) << 12)                                        \
    |(((_NUM_) & (0x3FF << 22)) >> 20))

#define ARCHITECTURE_PT_ENTRY(_NUM_)                                         \
    (((ARCHITECTURE_PD_MIRROR) << 22)                                        \
    |(((_NUM_) & (0x3FF << 22)) >> 10)                                       \
    |(((_NUM_) & (0x3FF << 12)) >> 12))

#define ARCHITECTURE_PT_BASE(_NUM_)                                          \
    (((ARCHITECTURE_PD_MIRROR) << 22)                                        \
    |(((_NUM_) & (0x3FF << 22)) >> 10)                                       \
    |(0x000))

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
** --------- globals ----------------------------------------------------------
*/

as_pd _pd;

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../pd.c
 */

/*
 * ../pd.c
 */

t_status architecture_kernel_pd_create_pt(t_uint32 address,
                                          t_uint32 flags);


/*
 * eop
 */

#endif
