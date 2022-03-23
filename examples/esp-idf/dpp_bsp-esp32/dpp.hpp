//.$file${.::dpp.hpp} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: dpp_bsp-esp32.qm
// File:  ${.::dpp.hpp}
//
// This code has been generated by QM 5.1.1 <www.state-machine.com/qm/>.
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
//.$endhead${.::dpp.hpp} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#ifndef DPP_HPP
#define DPP_HPP

enum Signals {
    EAT_SIG = QP::Q_USER_SIG, // published by Table to let a Philosopher eat
    DONE_SIG,       // published by Philosopher when done eating
    PAUSE_SIG,      // published by BSP to pause the application
    SERVE_SIG,      // published by BSP to serve re-start serving forks
    TEST_SIG,       // published by BSP to test the application
    MAX_PUB_SIG,    // the last published signal

    TIMEOUT_SIG,    // timeout used by Time Events
    HUNGRY_SIG,     // posted direclty to Table from hungry Philo
    MAX_SIG         // the last signal
};

// generate declarations all event classes
//.$declare${Events} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//.${Events::TableEvt} .......................................................
class TableEvt : public QP::QEvt {
public:
    uint8_t philoNum;
};
//.$enddecl${Events} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// number of philosophers
enum { N_PHILO = 5 };

// generate declarations of all opaque pointers...
//.$declare${AOs::AO_Philo[N_PHILO]} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
extern QP::QActive * const AO_Philo[N_PHILO];
//.$enddecl${AOs::AO_Philo[N_PHILO]} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//.$declare${AOs::AO_Table} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
extern QP::QActive * const AO_Table;
//.$enddecl${AOs::AO_Table} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#endif // DPP_HPP
