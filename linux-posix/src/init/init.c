#include <cmrx/application.h>
#include <stdio.h>
#include <cmrx/sys/syscalls.h>
#include <cmrx/cmrx.h>
#include <cmrx/ipc/notify.h>
#include <cmrx/ipc/mutex.h>
#include <cmrx/ipc/thread.h>
#include <cmrx/ipc/timer.h>
#include <cmrx/ipc/signal.h>
#include <cmrx/sys/irq.h>
#include <assert.h>
#include <stdlib.h>

int init_main(void * arg)
{
    while (1) {
    };
}

OS_APPLICATION_MMIO_RANGE(init, 0, 0);
OS_APPLICATION(init);
OS_THREAD_CREATE(init, init_main, NULL, 64);

