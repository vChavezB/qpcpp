//============================================================================
// QP/C++ Real-Time Embedded Framework (RTEF)
// Copyright (C) 2005 Quantum Leaps, LLC. All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-QL-commercial
//
// This software is dual-licensed under the terms of the open source GNU
// General Public License version 3 (or any later version), or alternatively,
// under the terms of one of the closed source Quantum Leaps commercial
// licenses.
//
// The terms of the open source GNU General Public License version 3
// can be found at: <www.gnu.org/licenses/gpl-3.0>
//
// The terms of the closed source Quantum Leaps commercial licenses
// can be found at: <www.state-machine.com/licensing>
//
// Redistributions in source code must retain this top-level comment block.
// Plagiarizing this software to sidestep the license obligations is illegal.
//
// Contact information:
// <www.state-machine.com>
// <info@state-machine.com>
//============================================================================
//! @date Last updated on: 2022-08-06
//! @version Last updated for: @ref qpcpp_7_0_1
//!
//! @file
//! @brief QF/C++ port to Zephyr RTOS kernel, all supported compilers

#ifndef QF_PORT_HPP
#define QF_PORT_HPP

// event queue and thread types
#define QF_EQUEUE_TYPE       struct k_msgq
#define QF_THREAD_TYPE       struct k_thread

// The maximum number of active objects in the application, NOTE1
#define QF_MAX_ACTIVE        (CONFIG_NUM_PREEMPT_PRIORITIES - 1U)

// The number of system clock tick rates
#define QF_MAX_TICK_RATE     2U

// QF critical section entry/exit for Zephyr, see NOTE1/
#define QF_CRIT_STAT_TYPE    k_spinlock_key_t
#define QF_CRIT_ENTRY(key_)  ((key_) = k_spin_lock(&QP::QF::spinlock))
#define QF_CRIT_EXIT(key_)   (k_spin_unlock(&QP::QF::spinlock, (key_)))

#include <zephyr.h>      // Zephyr API
#include "qep_port.hpp"  // QEP port
#include "qequeue.hpp"   // used for event deferral
#include "qmpool.hpp"    // this QP port uses the native QF memory pool
#include "qf.hpp"        // QF platform-independent public interface

namespace QP {
namespace QF {

// Zephyr spinlock for QF critical section
extern struct k_spinlock spinlock;

} // namespace QF
} // namespace QP

//============================================================================
// interface used only inside QF, but not in applications
//
#ifdef QP_IMPL

    // QF-specific scheduler locking (global lock in Zephyr, NOTE2)
    #define QF_SCHED_STAT_
    #define QF_SCHED_LOCK_(dummy) (k_sched_lock())
    #define QF_SCHED_UNLOCK_()    (k_sched_unlock())

    // native QF event pool operations...
    #define QF_EPOOL_TYPE_  QMPool
    #define QF_EPOOL_INIT_(p_, poolSto_, poolSize_, evtSize_) \
        (p_).init((poolSto_), (poolSize_), (evtSize_))
    #define QF_EPOOL_EVENT_SIZE_(p_)  ((p_).getBlockSize())
    #define QF_EPOOL_GET_(p_, e_, m_, qs_id_) \
        ((e_) = static_cast<QEvt *>((p_).get((m_), (qs_id_))))
    #define QF_EPOOL_PUT_(p_, e_, qs_id_) ((p_).put((e_), (qs_id_)))

#endif // ifdef QP_IMPL

//============================================================================
// NOTE1:
// This QP port to Zephyr assumes that Active Objects will use only the
// preemptive Zephyr priorities [0..(CONFIG_NUM_PREEMPT_PRIORITIES - 1U)].
// In this priority numbering, the QP AO priority QF_MAX_ACTIVE (highest)
// maps to Zephyr priority 0 (highest). The QP AO priority 1 (lowest) maps
// to Zephyr priority (CONFIG_NUM_PREEMPT_PRIORITIES - 2U).
//
// NOTE2:
// Zephyr does not support selective scheduler locking up to a given
// priority ceiling. Therefore, this port uses global Zephyr scheduler lock.
//

#endif // QF_PORT_HPP
