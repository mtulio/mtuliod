/*
 * mtuliod_signals.c
 *
 *  Created on: 1 de nov de 2015
 *      Author: mtulio
 */

/*
See 'mtuliod_signal.md'
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <mtuliod.h>
#include <mtd_stdout.h>

extern void mtuliod_end(void);

/**********************************************************/
/* Signal handlers from process. */

/* │SIGHUP      │  T        │  1 │ Hangup.                                            │  */
static void mtuliod_SIGHUP (void)
{
  /* Read config file */
  mtd_stdout_print(" # SYSTEM signal caught: SIGHUP - Hang up (Read config)\n");
  /* Try to return to normal operation. */
}

/* │SIGINT      │  T        │  2 │ Terminal interrupt signal.                         │  */
static void mtuliod_SIGINT (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGINT - Terminal interrupt signal.\n");

  mtuliod_end ();
  exit(0);
}

/* │SIGQUIT     │  A        │  3 │ Terminal quit signal.                              │  */
static void mtuliod_SIGQUIT (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGQUIT - Terminal quit signal. \n");

  mtuliod_end ();
  exit(0);
}

/* │SIGILL      │  A        │  4 │ Illegal instruction.                               │  */
static void mtuliod_SIGILL (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGILL - Illegal instruction. \n");
}

/* │SIGTRAP     │  A        │  5 │ Trace/breakpoint trap.                             │  */
static void mtuliod_SIGTRAP (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGTRAP - Trace/breakpoint trap. \n");
}

/* │SIGABRT     │  A        │  6 │ Process abort signal.                              │  */
static void mtuliod_SIGABRT (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGABRT - Process abort signal. \n");
}

/* │SIGBUS      │  A        │  7 │ Access to an undefined portion of a memory object. │  */
static void mtuliod_SIGBUS (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGBUS - Access to an undefined portion of a memory object. \n");
}

/* │SIGFPE      │  A        │  8 │ Erroneous arithmetic operation.                    │  */
static void mtuliod_SIGFPE (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGFPE - Erroneous arithmetic operation. \n");
}

/* │SIGUSR1     │  T        │ 10 │ User-defined signal 1.                             │  */
static void mtuliod_SIGUSR1 (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGUSR1 - User-defined signal 1. \n");
}

/* │SIGSEGV     │  A        │ 11 │ Invalid memory reference.                          │  */
static void mtuliod_SIGSEGV (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGSEGV - Invalid memory reference. \n");
}

/* │SIGUSR2     │  T        │ 12 │ User-defined signal 2.                             │ */
static void mtuliod_SIGUSR2 (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGUSR2 - User-defined signal 2.  \n");
}

/* │SIGPIPE     │  T        │ 13 │ Write on a pipe with no one to read it.            │  */
static void mtuliod_SIGPIPE (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGPIPE - Write on a pipe with no one to read it. \n");
}

/* │SIGALRM     │  T        │ 14 │ Alarm clock.                                       │  */
static void mtuliod_SIGALRM (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGALRM - Alarm clock. \n");
}

/* │SIGTERM     │  T        │ 15 │ Termination signal.                                │  */
static void mtuliod_SIGTERM (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGTERM - Termination signal.  \n");

  mtuliod_end ();
  exit(0);
}

/* │SIGCHLD     │  I        │ 17 │ Child process terminated, stopped, or continued.                │ */
static void mtuliod_SIGCHLD (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGCHLD - Child process terminated, stopped, or continued.  \n");
}

/* │SIGCONT     │  C        │ 18 │ Continue executing, if stopped.                    │  */
static void mtuliod_SIGCONT (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGCONT - Continue executing, if stopped.  \n");
}

/* │SIGSTOP     │  S        │ 19 │ Stop executing (cannot be caught or ignored).      │  */
/*static void mtuliod_SIGSTOP (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGSTOP - Stop executing (cannot be caught or ignored).  \n");
}*/

/* │SIGTSTP     │  S        │ 20 │ Terminal stop signal.                              │  */
static void mtuliod_SIGTSTP (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGTSTP - Terminal stop signal.  \n");
}

/* │SIGTTIN     │  S        │ 21 │ Background process attempting read.                │  */
static void mtuliod_SIGTTIN (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGTTIN - Background process attempting read. \n");
}

/* │SIGTTOU     │  S        │ 22 │ Background process attempting write.               │  */
static void mtuliod_SIGTTOU (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGTTOU - Background process attempting write.  \n");
}

/* │SIGURG      │  I        │ 23 │ High bandwidth data is available at a socket.      │  */
static void mtuliod_SIGURG (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGURG - High bandwidth data is available at a socket.  \n");
}

/* │SIGXCPU     │  A        │ 24 │ CPU time limit exceeded.                           │  */
static void mtuliod_SIGXCPU (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGXCPU - CPU time limit exceeded.  \n");
}

/* │SIGXFSZ     │  A        │ 25 │ File size limit exceeded.                          │ */
static void mtuliod_SIGXFSZ (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGXFSZ - File size limit exceeded.  \n");
}

/* │SIGVTALRM   │  T        │ 26 │ Virtual timer expired.                             │ */
static void mtuliod_SIGVTALRM (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGVTALRM - Virtual timer expired..  \n");
}

/* │SIGPROF     │  T        │ 27 │ Profiling timer expired.                           │ */
static void mtuliod_SIGPROF (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGPROF - Profiling timer expired.   \n");
}

/* │SIGWINCH    │           │ 28 │ Window size change                        │  -   │ */
static void mtuliod_SIGWINCH (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGWINCH - Window size change  \n");
}

/* │SIGIO       │           │ 29 │ File descriptor is ready to perform input or output.  │  */
static void mtuliod_SIGIO (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGIO - File descriptor is ready to perform input or output..  \n");
}

/* │SIGPWR      │           │ 30 │ Power failure - Unusual Hardware Events           │ */
static void mtuliod_SIGPWR (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGPWR - Power failure - Unusual Hardware Events  \n");
}

/* │SIGSYS      │  A        │ 31 │ Bad system call.                                   │  */
static void mtuliod_SIGSYS (void)
{
  mtd_stdout_print(" # SYSTEM signal caught: SIGSYS - Bad system call.  \n");
}

/**********************************************************/
/* Initialize all signals */
void mtuliod_signal_handleAll ( int sigc, struct mtuliod_signal_t signals[] )
{
	int i = 0;
	struct mtuliod_signal_t *sig;
	char str_log[MAX_BUFF_SIZE];
	bzero(str_log, sizeof(str_log));


	/* Initialize all handles available in vector */
	while (i < sigc)
	{
	  sig = &signals[i];

	  if (signal(sig->signal, (void *)sig->handler) == SIG_ERR) {
		  sprintf(str_log, " # WARN - Can't catch signal: %d \n", sig->signal);
		  mtd_stdout_print(str_log);
	  }

	  i++;
	}
}

/* Declare all signals and install it */
void mtuliod_signal_init (void)
{
	static struct mtuliod_signal_t mtuliod_signals[] =
	{
	  { .signal = SIGHUP,  .handler = &mtuliod_SIGHUP,  },
	  { .signal = SIGINT, .handler = &mtuliod_SIGINT, },
	  { .signal = SIGQUIT,  .handler = &mtuliod_SIGQUIT,  },
	  { .signal = SIGILL, .handler = &mtuliod_SIGILL,  },
	  { .signal = SIGTRAP, .handler = &mtuliod_SIGTRAP,  },
	  { .signal = SIGABRT, .handler = &mtuliod_SIGABRT,  },
	  { .signal = SIGBUS, .handler = &mtuliod_SIGBUS,  },
	  { .signal = SIGFPE, .handler = &mtuliod_SIGFPE,  },
	  { .signal = SIGUSR1, .handler = &mtuliod_SIGUSR1,  },
	  { .signal = SIGSEGV, .handler = &mtuliod_SIGSEGV,  },
	  { .signal = SIGUSR2, .handler = &mtuliod_SIGUSR2,  },
	  { .signal = SIGPIPE, .handler = &mtuliod_SIGPIPE,  },
	  { .signal = SIGALRM, .handler = &mtuliod_SIGALRM,  },
	  { .signal = SIGTERM, .handler = &mtuliod_SIGTERM,  },
	  { .signal = SIGCHLD, .handler = &mtuliod_SIGCHLD,  },
	  { .signal = SIGCONT, .handler = &mtuliod_SIGCONT,  },
	  /*{ .signal = SIGSTOP, .handler = &mtuliod_SIGSTOP,  },*/
	  { .signal = SIGTSTP, .handler = &mtuliod_SIGTSTP,  },
	  { .signal = SIGTTIN, .handler = &mtuliod_SIGTTIN,  },
	  { .signal = SIGTTOU, .handler = &mtuliod_SIGTTOU,  },
	  { .signal = SIGURG, .handler = &mtuliod_SIGURG,  },
	  { .signal = SIGXCPU, .handler = &mtuliod_SIGXCPU,  },
	  { .signal = SIGXFSZ, .handler = &mtuliod_SIGXFSZ,  },
	  { .signal = SIGVTALRM, .handler = &mtuliod_SIGVTALRM,  },
	  { .signal = SIGPROF, .handler = &mtuliod_SIGPROF,  },
	  { .signal = SIGWINCH, .handler = &mtuliod_SIGWINCH,  },
	  { .signal = SIGIO, .handler = &mtuliod_SIGIO,  },
	  { .signal = SIGPWR, .handler = &mtuliod_SIGPWR,  },
	  { .signal = SIGSYS, .handler = &mtuliod_SIGSYS,  },
	};

	mtuliod_signal_handleAll (array_size(mtuliod_signals), mtuliod_signals);
}

/*
 	 LINUX SIGNALS - STUDY CASE

# See linux command 'man linux.h'

┌────────────┬───────────┬────┬────────────────────────────────────────────────────┬──────┐
│ Signal     │ Default   │ ID │          Description                               │ Used │
│            │ Action    │    │                                                    │      │
├────────────┼───────────┼────┼────────────────────────────────────────────────────┼──────┤
│SIGHUP      │  T        │  1 │ Hangup.                                            │  Y   │
│SIGINT      │  T        │  2 │ Terminal interrupt signal.                         │  Y   │
│SIGQUIT     │  A        │  3 │ Terminal quit signal.                              │  Y   │
│SIGILL      │  A        │  4 │ Illegal instruction.                               │  Y   │
│SIGTRAP     │  A        │  5 │ Trace/breakpoint trap.                             │  Y   │
│SIGABRT     │  A        │  6 │ Process abort signal.                              │  Y   │
│SIGBUS      │  A        │  7 │ Access to an undefined portion of a memory object. │  Y   │
│SIGFPE      │  A        │  8 │ Erroneous arithmetic operation.                    │  Y   │
│SIGKILL     │  T        │  9 │ Kill (cannot be caught or ignored).                │  N   │
│SIGUSR1     │  T        │ 10 │ User-defined signal 1.                             │  Y   │
│SIGSEGV     │  A        │ 11 │ Invalid memory reference.                          │  Y   │
│SIGUSR2     │  T        │ 12 │ User-defined signal 2.                             │  Y   │
│SIGPIPE     │  T        │ 13 │ Write on a pipe with no one to read it.            │  Y   │
│SIGALRM     │  T        │ 14 │ Alarm clock.                                       │  Y   │
│SIGTERM     │  T        │ 15 │ Termination signal.                                │  Y   │
│SIGSTKFLT   │           │ 16 │ <TODO: Check and fill out>                         │  -   │
│SIGCHLD     │  I        │ 17 │ Child process terminated, stopped,                 │  Y   │
│            │           │    │ or continued.                                      │      │
│SIGCONT     │  C        │ 18 │ Continue executing, if stopped.                    │  Y   │
│SIGSTOP     │  S        │ 19 │ Stop executing (cannot be caught or ignored).      │  N   │
│SIGTSTP     │  S        │ 20 │ Terminal stop signal.                              │  Y   │
│SIGTTIN     │  S        │ 21 │ Background process attempting read.                │  Y   │
│SIGTTOU     │  S        │ 22 │ Background process attempting write.               │  Y   │
│SIGURG      │  I        │ 23 │ High bandwidth data is available at a socket.      │  Y   │
│SIGXCPU     │  A        │ 24 │ CPU time limit exceeded.                           │  Y   │
│SIGXFSZ     │  A        │ 25 │ File size limit exceeded.                          │  Y   │
│SIGVTALRM   │  T        │ 26 │ Virtual timer expired.                             │  Y   │
│SIGPROF     │  T        │ 27 │ Profiling timer expired.                           │  Y   │
│SIGWINCH    │           │ 28 │ Window size change.                                │  Y   │
│SIGIO       │           │ 29 │ File descriptor is ready to perform input/output.  │  Y   │
│SIGPWR      │           │ 30 │ Power failure - Unusual Hardware Events            │  Y   │
│SIGSYS      │  A        │ 31 │ Bad system call.                                   │  Y   │
│SIGRTMIN    │           │ 34 │ <TODO: Check and fill out>                         │  -   │
│SIGRTMIN+15 │           │ 49 │ <TODO: Check and fill out>                         │  -   │
│SIGRTMAX-14 │           │ 50 │ <TODO: Check and fill out>                         │  -   │
│SIGRTMAX-2  │           │ 62 │ <TODO: Check and fill out>                         │  -   │
│SIGPOLL     │  T        │ -- │ Pollable event.                                    │      │
│            │           │    │                                                    │      │
└────────────┴───────────┴────┴────────────────────────────────────────────────────┴──────┘

The default actions are as follows:
* T     Abnormal termination of the process.
* A     Abnormal termination of the process with additional actions.
* I     Ignore the signal.
* S     Stop the process.
* C     Continue the process, if it is stopped; otherwise, ignore the signal.

$ kill -l
 1) SIGHUP
 2) SIGINT
 3) SIGQUIT
 4) SIGILL
 5) SIGTRAP
 6) SIGABRT
 7) SIGBUS
 8) SIGFPE
 9) SIGKILL
10) SIGUSR1
11) SIGSEGV
12) SIGUSR2
13) SIGPIPE
14) SIGALRM
15) SIGTERM
16) SIGSTKFLT
17) SIGCHLD
18) SIGCONT
19) SIGSTOP
20) SIGTSTP
21) SIGTTIN
22) SIGTTOU
23) SIGURG
24) SIGXCPU
25) SIGXFSZ
26) SIGVTALRM
27) SIGPROF
28) SIGWINCH
29) SIGIO
30) SIGPWR
31) SIGSYS
34) SIGRTMIN
35) SIGRTMIN+1
36) SIGRTMIN+2
37) SIGRTMIN+3
38) SIGRTMIN+4
39) SIGRTMIN+5
40) SIGRTMIN+6
41) SIGRTMIN+7
42) SIGRTMIN+8
43) SIGRTMIN+9
44) SIGRTMIN+10
45) SIGRTMIN+11
46) SIGRTMIN+12
47) SIGRTMIN+13
48) SIGRTMIN+14
49) SIGRTMIN+15
50) SIGRTMAX-14
51) SIGRTMAX-13
52) SIGRTMAX-12
53) SIGRTMAX-11
54) SIGRTMAX-10
55) SIGRTMAX-9
56) SIGRTMAX-8
57) SIGRTMAX-7
58) SIGRTMAX-6
59) SIGRTMAX-5
60) SIGRTMAX-4
61) SIGRTMAX-3
62) SIGRTMAX-2

*/
