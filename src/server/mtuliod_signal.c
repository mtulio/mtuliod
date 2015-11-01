/*
 * mtuliod_signals.c
 *
 *  Created on: 1 de nov de 2015
 *      Author: mtulio
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <mtuliod.h>
#include <mtd_stdout.h>

extern void mtuliod_end(void);

/**********************************************************/
/* Signal handlers from this daemon. */

/* SIGHUP handler. */
static void mtuliod_sighup (void)
{
  /* Read config file */
  mtd_stdout_print(" # SYSTEM Signal caught: SIGHUP - Read config signal\n");
  /* Try to return to normal operation. */
}

/* SIGINT handler. */
static void mtuliod_sigint (void)
{
  mtd_stdout_print(" # SYSTEM Signal caught: SIGINT - terminate signal\n");

  mtuliod_end ();
  exit(0);
}

/* SIGUSR1 handler. */
static void mtuliod_sigusr1 (void)
{
  mtd_stdout_print(" # SYSTEM Signal caught: SIGUSR1 - Custom user signal\n");
}

//signal_init (array_size(ripd_signals), ripd_signals);
void mtuliod_signal_init ( int sigc, struct mtuliod_signal_t signals[] )
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
		  sprintf(str_log, "# Can't catch %d signal\n", sig->signal);
		  mtd_stdout_print(str_log);
	  }

	  i++;
	}
}


void mtuliod_signal_main(void)
{
	static struct mtuliod_signal_t mtuliod_signals[] =
	{
	  {
	    .signal = SIGHUP,
	    .handler = &mtuliod_sighup,
	  },
	  {
	    .signal = SIGUSR1,
	    .handler = &mtuliod_sigusr1,
	  },
	  {
	    .signal = SIGINT,
	    .handler = &mtuliod_sigint,
	  },
	  {
	    .signal = SIGTERM,
	    .handler = &mtuliod_sigint,
	  },
	};

	mtuliod_signal_init (array_size(mtuliod_signals), mtuliod_signals);
}

