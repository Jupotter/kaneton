/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/mycure/kane...cture/ia32/educational/include/handler.h
 *
 * created       renaud voltz   [fri feb 17 16:48:22 2006]
 * updated       julien quintard   [mon apr 11 13:45:51 2011]
 */

#ifndef ARCHITECTURE_HANDLER_H
#define ARCHITECTURE_HANDLER_H	1

/*
** ---------- dependencies ----------------------------------------------------
*/

// #include <core/event.h>

/*
 * ---------- macros ----------------------------------------------------------
 */

/*
 * this macro represents the number of handlers the system must set up,
 * for the exceptions, IRQs, IPIs and syscalls.
 */

#define ARCHITECTURE_HANDLER_SIZE	ARCHITECTURE_IDT_EXCEPTION_SIZE + \
					ARCHITECTURE_IDT_IRQ_SIZE +	  \
					ARCHITECTURE_IDT_IPI_SIZE +	  \
					ARCHITECTURE_IDT_SYSCALL_SIZE

/*
 * this macro defines the size of a thread's pile i.e the stack used whenever
 * a privilege change occurs.
 */

#define ARCHITECTURE_HANDLER_PILE_SIZE	___kaneton$pagesz

/*
 * this macro defines the size of the KIS - Kernel Interrupt Stack. this is
 * the stack which is used, within the kernel environment, for treating
 * interrupts.
 */

#define ARCHITECTURE_HANDLER_KIS_SIZE	2 * ___kaneton$pagesz

/*
** ---------- types -----------------------------------------------------------
*/

typedef void (*t_event_handler)(i_event,
                                t_data);

/*
** ---------- globals ---------------------------------------------------------
*/

t_event_handler _event_handler_array[256];

/*
 * ---------- prototypes ------------------------------------------------------
 *
 *	../handler.c
 */

/*
 * ../handler.c
 */

void architecture_handler_default(i_event id, t_data data);

void architecture_handler_keyboard(i_event id, t_data data);

t_status architecture_handler_setup(void);

t_status architecture_handler_reserve(i_event id,
                                      t_event_handler handler);

t_status architecture_handler_release(i_event id);


/*
 * eop
 */

#endif
