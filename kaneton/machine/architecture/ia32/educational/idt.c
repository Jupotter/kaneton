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
 * ---------- externs ---------------------------------------------------------
 */

/*
 * ---------- functions -------------------------------------------------------
 */

t_status    architecture_idt_create_desc(t_uint16 select,
                                         t_uint32 offset,
                                         t_uint16 type,
                                         at_idte* desc)
{
    desc->offset0_15 = (offset & 0xffff);
    desc->offset16_32 = (offset & 0xffff0000) >> 16;
    desc->select = select;
    desc->type = type;

    MACHINE_LEAVE();
}


t_status    architecture_idt_dump(void)
{
    int i;
    module_call(console, message,
            '#', "IDT: table(0x%08x) size(%u)\n",
            _idt.table,
            _idt.size);

    for (i = 0; i < _idt.size; i++)
    {
        t_uint16        select;
        t_paddr         offset;
        t_uint16        type;

//        if (!(((t_uint64)(_idt.table[i].type) << 32)
//                    & ARCHITECTURE_IDTE_PRESENT))
//            continue;

        offset = ARCHITECTURE_IDTE_OFFSET_GET(_idt.table[i]);
        select = _idt.table[i].select;
        type   = _idt.table[i].type;

        module_call(console, message,
                '#', "  %u: offset(0x%08x) selector(0x%04x) "
                "type(0x%04x)\n",
                i, offset, select, type);
    }

    MACHINE_LEAVE();
}
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

t_status    architecture_idt_build(t_paddr base,
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
    idt->size = size;

    /*
    ** 3)
    */

    memset(idt->table, 0x0, idt->size * sizeof (at_idte));

    MACHINE_LEAVE();
}

t_status    architecture_idt_load(as_idt* idt)
{
    as_idtr idtr;

    if (NULL == idt)
        MACHINE_ESCAPE("The 'idt' argument is null");

    idtr.address = (t_paddr)idt->table;
    idtr.size = idt->size * sizeof (at_idte);

    ARCHITECTURE_LIDT(idtr);

    MACHINE_LEAVE();
}

t_status    architecture_idt_initialize(void)
{
    int i;

    if (STATUS_OK != architecture_idt_build((t_paddr)_idte, 255, &_idt))
        MACHINE_ESCAPE("Unable to build the IDT");

    if(STATUS_OK != architecture_idt_load(&_idt))
        MACHINE_ESCAPE("Unable to load the IDT in the processor");

    for (i = 0; i < ARCHITECTURE_IDT_SIZE; i++)
        architecture_idt_create_desc(0x08,
                (t_uint32)architecture_handler_default,
                ARCHITECTURE_IDTE_INTGATE,
                &(_idt.table[i]));

    architecture_idt_create_desc(0x08,
            (t_uint32)architecture_handler_clock,
            ARCHITECTURE_IDTE_INTGATE,
            &(_idt.table[32]));

    architecture_idt_create_desc(0x08,
            (t_uint32)architecture_handler_keyboard,
            ARCHITECTURE_IDTE_INTGATE,
            &(_idt.table[33]));

    asm("sti"::);

    MACHINE_LEAVE();
}

t_status    architecture_idt_clear(t_id index)
{
    if (index >= ARCHITECTURE_IDT_SIZE)
        MACHINE_ESCAPE("Index out of bound");

    _idt.table[index].type &= (ARCHITECTURE_IDTE_PRESENT_FALSE >> 32);

    MACHINE_LEAVE();
}

t_status    architecture_idt_reserve(t_id        index,
                                     t_uint32    handler)
{
    if (index >= ARCHITECTURE_IDT_SIZE)
        MACHINE_ESCAPE("Index out of bound");

    architecture_idt_create_desc(0x08,
            handler,
            ARCHITECTURE_IDTE_INTGATE,
            &(_idt.table[index]));

    MACHINE_LEAVE();
}

t_status    architecture_idt_clean(void)
{
    free(_idt.table);
    _idt.table = NULL;
    _idt.size = 0;
    MACHINE_LEAVE();
}
