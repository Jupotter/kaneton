/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/mycure/kane...hitecture/ia32/educational/include/idt.h
 *
 * created       renaud voltz   [fri feb 10 16:36:20 2006]
 * updated       julien quintard   [mon apr 11 13:45:20 2011]
 */

#ifndef ARCHITECTURE_IDT_H
#define ARCHITECTURE_IDT_H      1

/*
 * ---------- macros ----------------------------------------------------------
 */

#define ARCHITECTURE_IDT_SIZE                   256

#define ARCHITECTURE_IDTE_PRESENT               (1LL << 47)
#define ARCHITECTURE_IDTE_PRESENT_FALSE         (0LL << 47)

#define ARCHITECTURE_IDTE_DPL_ALL               ((0LL << 46) |      \
                                                 (0LL << 45))

#define ARCHITECTURE_IDTE_STORAGE               (0LL << 44)

#define ARCHITECTURE_IDTE_TYPE_INT              ((1LL << 43) |      \
                                                 (1LL << 42) |      \
                                                 (1LL << 41) |      \
                                                 (0LL << 40))
#define ARCHITECTURE_IDTE_TYPE_TRAP             ((1LL << 43) |      \
                                                 (1LL << 42) |      \
                                                 (1LL << 41) |      \
                                                 (1LL << 40))

#define ARCHITECTURE_IDTE_INTGATE                                   \
    (ARCHITECTURE_IDTE_PRESENT |                                    \
     ARCHITECTURE_IDTE_DPL_ALL |                                    \
     ARCHITECTURE_IDTE_STORAGE |                                    \
     ARCHITECTURE_IDTE_TYPE_INT) >> 32

/*
 * these macros define the base entry and the number of entries for the
 * several types of gate: IRQ, exception, IPI or syscall.
 *
 * note that 200 syscalls could be set up but the kernel limits itself
 * to ten which is enough for a microkernel.
 */

#define ARCHITECTURE_IDT_EXCEPTION_BASE         0
#define ARCHITECTURE_IDT_EXCEPTION_SIZE         32

#define ARCHITECTURE_IDT_IRQ_BASE               32
#define ARCHITECTURE_IDT_IRQ_SIZE               16

#define ARCHITECTURE_IDT_IPI_BASE               48
#define ARCHITECTURE_IDT_IPI_SIZE               8

#define ARCHITECTURE_IDT_SYSCALL_BASE           56
#define ARCHITECTURE_IDT_SYSCALL_SIZE           10

/*
 * these macro define some of the exception handler sources.
 */

#define ARCHITECTURE_IDT_EXCEPTION_DE                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 0
#define ARCHITECTURE_IDT_EXCEPTION_DB                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 1
#define ARCHITECTURE_IDT_EXCEPTION_BP                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 3
#define ARCHITECTURE_IDT_EXCEPTION_OF                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 4
#define ARCHITECTURE_IDT_EXCEPTION_BR                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 5
#define ARCHITECTURE_IDT_EXCEPTION_UD                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 6
#define ARCHITECTURE_IDT_EXCEPTION_NM                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 7
#define ARCHITECTURE_IDT_EXCEPTION_DF                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 8
#define ARCHITECTURE_IDT_EXCEPTION_TS                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 10
#define ARCHITECTURE_IDT_EXCEPTION_NP                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 11
#define ARCHITECTURE_IDT_EXCEPTION_SS                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 12
#define ARCHITECTURE_IDT_EXCEPTION_GP                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 13
#define ARCHITECTURE_IDT_EXCEPTION_PF                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 14
#define ARCHITECTURE_IDT_EXCEPTION_MF                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 16
#define ARCHITECTURE_IDT_EXCEPTION_AC                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 17
#define ARCHITECTURE_IDT_EXCEPTION_MC                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 18
#define ARCHITECTURE_IDT_EXCEPTION_XM                                   \
  ARCHITECTURE_IDT_EXCEPTION_BASE + 19

/*
 * these macro define some of the IRQ handler sources.
 */

#define ARCHITECTURE_IDT_IRQ_PIT                                        \
  ARCHITECTURE_IDT_IRQ_BASE + 0
#define ARCHITECTURE_IDT_IRQ_KEYBOARD                                   \
  ARCHITECTURE_IDT_IRQ_BASE + 1
#define ARCHITECTURE_IDT_IRQ_CASCADE                                    \
  ARCHITECTURE_IDT_IRQ_BASE + 2
#define ARCHITECTURE_IDT_IRQ_COM2                                       \
  ARCHITECTURE_IDT_IRQ_BASE + 3
#define ARCHITECTURE_IDT_IRQ_COM1                                       \
  ARCHITECTURE_IDT_IRQ_BASE + 4
#define ARCHITECTURE_IDT_IRQ_FLOPPY                                     \
  ARCHITECTURE_IDT_IRQ_BASE + 6
#define ARCHITECTURE_IDT_IRQ_SPURIOUS                                   \
  ARCHITECTURE_IDT_IRQ_BASE + 7
#define ARCHITECTURE_IDT_IRQ_RTC                                        \
  ARCHITECTURE_IDT_IRQ_BASE + 8
#define ARCHITECTURE_IDT_IRQ_ATA1                                       \
  ARCHITECTURE_IDT_IRQ_BASE + 14
#define ARCHITECTURE_IDT_IRQ_ATA2                                       \
  ARCHITECTURE_IDT_IRQ_BASE + 15

/*
 * ---------- macro functions -------------------------------------------------
 */

#define ARCHITECTURE_IDTE_OFFSET_GET(_idte_)                            \
    (t_paddr)(((_idte_).offset0_15 & 0xffff) |                          \
              (((_idte_).offset16_32 << 16) & 0xffff0000))

/*
 * ---------- dependencies ----------------------------------------------------
 */

#include <core/types.h>

/*
 * ---------- types -----------------------------------------------------------
 */

/*
 * the hardware-represented IDT entry which is composed of a segment number,
 * an offset address and some flags.
 *
 * for more information, please refer to the IA32 hardware documentation.
 */

typedef struct
{
    t_uint16     offset0_15;
    t_uint16     select;
    t_uint16     type;
    t_uint16     offset16_32;
}              __attribute__ ((packed)) at_idte;

/*
 * the IDT descriptor i.e the structure for managing an IDT.
 *
 * this structure contains a pointer to the IDT entries along with the
 * current size i.e number of allocated entries.
 */

typedef struct
{
    at_idte*              table;
    t_uint16              size;
}                         as_idt;

/*
 * this structure represents the IDTR - IDT Register which is the hardware
 * structure locating the current IDT.
 */

typedef struct
{
    t_uint16              size;
    t_paddr               address;
}                       __attribute__ ((packed)) as_idtr;

/*
** ---------- globals ---------------------------------------------------------
*/

as_idt _idt;
at_idte _idte[256];

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *      ../idt.c
 */

/*
 * ../idt.c
 */

t_status    architecture_idt_create_desc(t_uint16 select,
                                         t_uint32 offset,
                                         t_uint16 type,
                                         at_idte* desc);

t_status    architecture_idt_dump(void);

t_status    architecture_idt_build(t_paddr base,
                                   t_psize size,
                                   as_idt* idt);

t_status    architecture_idt_load(as_idt* idt);

t_status    architecture_idt_initialize(void);

t_status    architecture_idt_clear(t_id index);

t_status    architecture_idt_reserve(t_id        index,
                                     t_uint32    handler);

t_status    architecture_idt_clean(void);


/*
 * eop
 */

#endif
