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

extern t_uint32    _idt_exception_wrapper[ARCHITECTURE_IDT_SIZE];

/*
** ---------- wrapper generation ----------------------------------------------
*/

__asm__("                                                               \
.irp id, 0,1,2,3,4,5,6,7,9,15,                                          \
    16,18,19,20,21,22,23,24,25,26,27,28,29,30,31                      \n\
                                                                      \n\
idt_exception_wrapper_\\id:                                           \n\
    pusha                                                             \n\
    push %ss                                                          \n\
    push %ds                                                          \n\
    push %es                                                          \n\
    push %fs                                                          \n\
    push %gs                                                          \n\
                                                                      \n\
    pushl $0                                                          \n\
    pushl $\\id                                                       \n\
    leal _event_handler_array, %edi                                   \n\
    mov $\\id, %eax                                                   \n\
    shl $2, %eax                                                      \n\
    call *(%edi, %eax)                                                \n\
    addl $4, %esp                                                     \n\
    addl $4, %esp                                                     \n\
                                                                      \n\
    pop %gs                                                           \n\
    pop %fs                                                           \n\
    pop %es                                                           \n\
    pop %ds                                                           \n\
    pop %ss                                                           \n\
    popa                                                              \n\
    iret                                                              \n\
                                                                      \n\
.endr                                                                 \n\
                                                                      \n\
.irp id, 10,11,12,13,14,17                                            \n\
idt_exception_wrapper_\\id:                                           \n\
                                                                      \n\
    pusha                                                             \n\
    push %ss                                                          \n\
    push %ds                                                          \n\
    push %es                                                          \n\
    push %fs                                                          \n\
    push %gs                                                          \n\
                                                                      \n\
    pushl %eax                                                        \n\
    pushl $\\id                                                       \n\
    leal _event_handler_array, %edi                                   \n\
    mov $\\id, %eax                                                   \n\
    shl $2, %eax                                                      \n\
    call *(%edi, %eax)                                                \n\
    addl $4, %esp                                                     \n\
    addl $4, %esp                                                     \n\
                                                                      \n\
    pop %gs                                                           \n\
    pop %fs                                                           \n\
    pop %es                                                           \n\
    pop %ds                                                           \n\
    pop %ss                                                           \n\
    popa                                                              \n\
    iret                                                              \n\
                                                                      \n\
.endr                                                                 \n\
                                                                      \n\
.irp id, 8                                                            \n\
idt_exception_wrapper_\\id:                                           \n\
    1: hlt                                                            \n\
    jmp 1b                                                            \n\
.endr                                                                 \n\
                                                                      \n\
.irp id 32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47               \n\
                                                                      \n\
idt_exception_wrapper_\\id:                                           \n\
    pusha                                                             \n\
    push %ss                                                          \n\
    push %ds                                                          \n\
    push %es                                                          \n\
    push %fs                                                          \n\
    push %gs                                                          \n\
                                                                      \n\
    movb $0x20, %al                                                   \n\
    outb %al, $0x20                                                   \n\
                                                                      \n\
    pushl $0                                                          \n\
    pushl $\\id                                                       \n\
    leal _event_handler_array, %edi                                   \n\
    mov $\\id, %eax                                                   \n\
    shl $2, %eax                                                      \n\
    call *(%edi, %eax)                                                \n\
    addl $4, %esp                                                     \n\
    addl $4, %esp                                                     \n\
                                                                      \n\
    pop %gs                                                           \n\
    pop %fs                                                           \n\
    pop %es                                                           \n\
    pop %ds                                                           \n\
    pop %ss                                                           \n\
    popa                                                              \n\
    iret                                                              \n\
                                                                      \n\
.endr                                                                 \n\
                                                                      \n\
.irp id, 48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66     \n\
                                                                      \n\
idt_exception_wrapper_\\id:                                           \n\
    pusha                                                             \n\
    push %ss                                                          \n\
    push %ds                                                          \n\
    push %es                                                          \n\
    push %fs                                                          \n\
    push %gs                                                          \n\
                                                                      \n\
    pushl $0                                                          \n\
    pushl $\\id                                                       \n\
    leal _event_handler_array, %edi                                   \n\
    mov $\\id, %eax                                                   \n\
    shl $2, %eax                                                      \n\
    call *(%edi, %eax)                                                \n\
    addl $4, %esp                                                     \n\
    addl $4, %esp                                                     \n\
                                                                      \n\
    pop %gs                                                           \n\
    pop %fs                                                           \n\
    pop %es                                                           \n\
    pop %ds                                                           \n\
    pop %ss                                                           \n\
    popa                                                              \n\
    iret                                                              \n\
                                                                      \n\
.endr                                                                 \n\
                                                                      \n\
_idt_exception_wrapper:                                               \n\
.irp id, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,                         \
    16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31                   \n\
.long (idt_exception_wrapper_\\id)                                    \n\
    .endr                                                             \n\
                                                                      \n\
.irp id 32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47               \n\
.long (idt_exception_wrapper_\\id)                                    \n\
    .endr                                                               \
                                                                      \n\
.irp id, 48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66     \n\
.long (idt_exception_wrapper_\\id)                                    \n\
    .endr                                                               \
       ");

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

    if (size > (ARCHITECTURE_IDT_SIZE))
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

    if (STATUS_OK != architecture_idt_build((t_paddr)_idte,
                ARCHITECTURE_IDT_SIZE, &_idt))
        MACHINE_ESCAPE("Unable to build the IDT");

    if(STATUS_OK != architecture_idt_load(&_idt))
        MACHINE_ESCAPE("Unable to load the IDT in the processor");

    for (i = 0; i < ARCHITECTURE_IDT_SIZE; i++)
        architecture_idt_create_desc(0x08,
                _idt_exception_wrapper[i],
                ARCHITECTURE_IDTE_INTGATE,
                &(_idt.table[i]));

    MACHINE_LEAVE();
}


t_status    architecture_idt_clean(void)
{
    free(_idt.table);
    _idt.table = NULL;
    _idt.size = 0;
    MACHINE_LEAVE();
}
