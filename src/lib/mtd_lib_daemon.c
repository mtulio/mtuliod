/*
 * mtd_lib_daemon.c
 *
 *  Created on: 1 de nov de 2015
 *      Author: mtulio
 */

#include <unistd.h>	/*Daemon function */
#include <errno.h> /* errno */
#include <fcntl.h> /* O_RDWR */
#include <sys/stat.h> /* umask */

#include <mtuliod.h>

/**********************************************************/
/* DAEMON (Disk and Execution Monitor).
 * Create a daemon from myself. ;)
 * nochdir set to 0 to change daemon home to / (root)
 * If noclose is zero, daemon() redirects standard input,
 * 	standard output and standard error to /dev/null; otherwise,
 * 	no changes are made to these file descriptors.
 * If nochdir is zero, daemon() changes the calling process's
 * 	current working directory to the root directory ("/"); otherwise,
 * 	the current working directory is left unchanged.
 *
 * return -1 to fork() failed
 * return -2 to setsid() failed
 * see man daemon();
 * */
int mtd_lib_daemon_init (int nochdir, int noclose)
{
  pid_t pid;

  pid = fork ();

  /* In case of fork is error. */
  if (pid < 0)
	  return RET_ERR_DM01;

  /* In case of this is parent process. Can exit here */
  if (pid != 0)
	  return RET_OK;

  /* Become session leader and get pid. */
  pid = setsid();

  if (pid == -1)
	  return RET_ERR_DM02;

  /* Change directory to root. */
  if (! nochdir)
    chdir ("/");

  /* File descriptor close. */
  if (! noclose)
    {
      int fd;

      fd = open ("/dev/null", O_RDWR, 0);
      if (fd != -1)
	{
	  dup2 (fd, STDIN_FILENO);
	  dup2 (fd, STDOUT_FILENO);
	  dup2 (fd, STDERR_FILENO);
	  if (fd > 2)
	    close (fd);
	}
    }

  umask (0027);

  return 0;
}

