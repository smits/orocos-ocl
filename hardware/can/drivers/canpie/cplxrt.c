/***************************************************************************
  tag: Peter Soetens  Mon Jan 10 15:59:16 CET 2005  cplxrt.c 

                        cplxrt.c -  description
                           -------------------
    begin                : Mon January 10 2005
    copyright            : (C) 2005 Peter Soetens
    email                : peter.soetens@mech.kuleuven.ac.be
 
 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/
 
 



#include <linux/module.h>

#include <linux/config.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/smp_lock.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "rtt/can/cplxrt.h"
#include "rtt/can/cpcore.h"
#include <rtai_lxrt.h>
#include <pkgconf/device_drivers_canpie.h>

MODULE_LICENSE("GPL");
//EXPORT_NO_SYMBOLS;

/**
 * The first parameter is the bitmask and denotes what marshalling must
 * happen and if the call is realtime (bit 0), the second parameter is the function
 * to be called.
 */
static struct rt_fun_entry rt_apci_fun[] = {
    [ CP_USER_MESSAGE_READ  ] = { UW1(2,3), CpUserMsgRead },
    [ CP_USER_MESSAGE_WRITE ] = { UR1(2,3), CpUserMsgWrite }, // UR1(2,3)
    [ CP_USER_APP_INIT      ] = { 0, CpUserAppInit },
    [ CP_USER_APP_DE_INIT   ] = { 0, CpUserAppDeInit },
    [ CP_USER_BAUDRATE      ] = { 0, CpUserBaudrate },
    [ CP_USER_FIFO_CLEAR    ] = { 0, CpUserFifoClear },
    [ CP_USER_FILTER_ALL    ] = { 0, CpUserFilterAll },
    [ CP_USER_FILTER_MSG    ] = { 0, CpUserFilterMsg },
    [ CP_USER_INT_FUNCTIONS ] = { 0, CpUserIntFunctions }
};

extern unsigned int cp_recv_int;
extern unsigned int cp_emcy_int;
extern unsigned int cp_trns_int;

#define STACK_SIZE 2000
#define CHANNEL 0
/**
 * Transmit task.
 */
RT_TASK cp_tx_task;
/**
 * Sem that signals a messages should be
 * transmitted (signalled from Send or interrupt)
 */
SEM cp_tx_sem;
/**
 * Receive task.
 */
RT_TASK cp_rx_task;
/**
 * Sem that signals a messages should be
 * received (signalled from Send or interrupt)
 */
SEM cp_rx_sem;

/**
 * The transmit function.
 */
void cp_tx_function(int channel)
{
	while(1)
		{
			rt_sem_wait( &cp_tx_sem );
			CpCoreMsgTransmit(channel);
            //rt_printk(".");
		}
}
		
/**
 * The receive function.
 */
void cp_rx_function(int channel)
{
	while(1)
		{
			rt_sem_wait( &cp_rx_sem );
			CpCoreMsgReceive(channel);
            //rt_printk("-");
		}
}
		


/* init module */
int init_module(void)
{
  if( set_rt_fun_ext_index(rt_apci_fun, ORONUM_CANPIE_LXRT_IDX)) {
    printk("LXRT index %d already in use !\n", ORONUM_CANPIE_LXRT_IDX);
    printk("Recompile canpie with a different index\n");
    return -EACCES;
  }
  cp_recv_int = cp_emcy_int = cp_trns_int = 0;
  rt_task_init(&cp_tx_task, cp_tx_function, CHANNEL, STACK_SIZE, 0, 0, 0);
  rt_sem_init( &cp_tx_sem, 0);
  rt_task_init(&cp_rx_task, cp_rx_function, CHANNEL, STACK_SIZE, 0, 0, 0);
  rt_sem_init( &cp_rx_sem, 0);
  rt_task_resume( &cp_tx_task );
  rt_task_resume( &cp_rx_task );
  printk("CANPie Loaded\n");
  return(0);
}

/*  cleanup module */
void cleanup_module(void)
{
  reset_rt_fun_ext_index(rt_apci_fun, ORONUM_CANPIE_LXRT_IDX);
  rt_task_delete(&cp_tx_task);
  rt_sem_delete(&cp_tx_sem);
  rt_task_delete(&cp_rx_task);
  rt_sem_delete(&cp_rx_sem);
  printk("CANPie Interrupt Statistics : #RECV: %d, #TRNS: %d, #EMCY: %d\n",cp_recv_int, cp_trns_int, cp_emcy_int);
  printk("CANPie Unloaded\n");
}


