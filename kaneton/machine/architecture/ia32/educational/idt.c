/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/mycure/kane...hine/architecture/ia32/educational/idt.c
 *
 * created       renaud voltz   [sun feb 12 02:02:19 2006]
 * updated       julien quintard   [mon apr 11 13:44:56 2011]
 */

/*
 * ---------- information -----------------------------------------------------
 *
 * this file provides functionalities for managing the IDT - Interrupt
 * Descriptor Table.
 *
 * for more information regarding the handlers triggered through the IDT,
 * please have a look at the handler.c file.
 */

/*
 * ---------- includes --------------------------------------------------------
 */

#include <kaneton.h>

/*
 * ---------- functions -------------------------------------------------------
 */

/*
 * this function builds an IDT according to the given parameters.
 *
 * steps:
 *
 * 0) verify the arguments.
 * 1) align the base address if necessary.
 * 2) initialized the idt structure.
 * 3) initialize the table's memory.
 */

t_status    architecture_idt_build (t_paddr base,
                                    t_psize size,
                                    as_idt* idt)
{
    /*
    ** 0)
    */

    if (NULL == idt)
        MACHINE_ESCAPE("The 'idt' argument is null");

    if (size > (ARCHITECTURE_IDT_SIZE * sizeof (at_idte)))
        MACHINE_ESCAPE("the given size is too large as exceeding the IDT's "
                "theoretically maximum capacity");

    /*
    ** 1)
    */

    if (base % sizeof (at_idte))
        base += sizeof (at_idte) - (base % sizeof (at_idte));

    /*
    ** 2)
    */

    idt->table = (at_idte*)base;
    idt->size = size / sizeof (at_idte);

    /*
    ** 3)
    */

    memset(idt->table, 0x0, idt->size * sizeof (at_idte));

    MACHINE_LEAVE();
}
