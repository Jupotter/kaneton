/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/mycure/kane...chine/architecture/ia32/educational/pd.c
 *
 * created       matthieu bucchianeri   [tue dec 20 19:56:20 2005]
 * updated       julien quintard   [mon apr 11 13:45:04 2011]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file contains functions for managing PDs - Page Directories.
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <kaneton.h>

/*
 * ---------- functions -------------------------------------------------------
 */

t_status architecture_kernel_pd_create_pt(t_uint32 address,
                                          t_uint32 flags)
{
    int i;
    at_pde* target = (at_pde*)ARCHITECTURE_PD_ENTRY(address);

    t_uint32 phys_addr = (t_uint32)malloc(1024 * sizeof (t_uint32));
    module_call(console, message,
            '!', "allocated address: %p\n", phys_addr);
    *target = ARCHITECTURE_PDE(phys_addr,
                               flags | ARCHITECTURE_PD_PRESENT);
    for (i = 0; i < 1024; i++)
    {
        *((t_uint32*)ARCHITECTURE_PT_BASE(address) + i) = 0;
    }

    MACHINE_LEAVE();
}

t_status architecture_kernel_pd_free_pt(t_uint32 address)
{
    at_pde* target = (at_pde*)ARCHITECTURE_PD_ENTRY(address);

    *target = *target & (~ARCHITECTURE_PD_PRESENT);

    module_call(console, message,
            '!', "entering free()\n");
    free((void*)ARCHITECTURE_PD_PADDR(*target));

    MACHINE_LEAVE();
}

/* FIXME[complete if necessary] */
