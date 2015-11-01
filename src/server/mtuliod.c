/*
 * mtuliod.c
 *
 *  Created on: 18 de out de 2015
 *      Author: mtulio
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include <getopt.h>

#include <mtuliod.h>
#include <mtd_lib.h>
#include <mtd_stdout.h>
#include <mtuliod_server.h>
#include <mtuliod_signal.h>
#include <mtd_server_config.h>

/* Global config */
mtd_srv_cfg_t *mtd_config;

/* Global options */
mtd_options_t *mtd_opts;

/* Global return control */
short int ret = -1;

/**********************************************************/
/*
 *  Initialize main configuration reading from file and
 *  setting up structures.
 *
 * */
int mtuliod_initConfig(void)
{
	//int ret = -1;

	/* Server config file */
	if (!mtd_config) {
		mtd_config = (mtd_srv_cfg_t *)malloc(sizeof(mtd_srv_cfg_t));
		memset (mtd_config, 0, sizeof(mtd_srv_cfg_t));
	}

	if (!mtd_opts) {
		mtd_opts = (mtd_options_t *)malloc(sizeof(mtd_options_t));
		memset (mtd_opts, 0, sizeof(mtd_options_t));
	}


	/* Might to be read from command line */
	if (mtd_lib_fileExist("/etc/mtuliod/mtuliod.conf") == RET_OK) {
		sprintf(mtd_config->config_file, "/etc/mtuliod/mtuliod.conf");

	} else if (mtd_lib_fileExist("mtuliod.conf") == RET_OK) {
		sprintf(mtd_config->config_file, "mtuliod.conf");

	} else if (mtd_lib_fileExist("conf/mtuliod.conf") == RET_OK) {
		sprintf(mtd_config->config_file, "conf/mtuliod.conf");

	} else {
		mtd_stdout_print("#% ERROR - Configuration file was not found\n");
		return (-1);

	}

	sprintf(mtd_config->log_file, "mtuliod.log");
	mtd_opts->log = FLAG_ENABLED;

	mtd_stdout_print("\t*** Starting MTULIOd Server *** \n");

	/* Load configuration file  */
	ret = mtd_srv_config_main(mtd_config);
	if (ret != 0) {
		mtd_stdout_print("#% ERROR - opening config file\n");
		return ret;
	}

	return 0;
}

/* Clean config / free structs */
void mtuliod_end(void)
{
	//mtd_stdout_print("#>> Cleaning server config <<#\n");

	/* Free structures */
	if (mtd_config)
		free (mtd_config);

	if (mtd_opts)
		free (mtd_opts);

}

/****************************/
/* options using getopt. */
static struct option longopts[] =
{
  { "daemon",      no_argument,       NULL, 'd'},
  { "config_file", required_argument, NULL, 'f'},
  { "pid_file",    required_argument, NULL, 'i'},
  { "help",        no_argument,       NULL, 'h'},
  { "version",     no_argument,       NULL, 'v'},
  { 0 }
};

/* Help information display. */
static void mtuliod_mainUsage (int status)
{
      printf ("Usage : %s [OPTION...]\n\
Daemon which manages MTuliod.\n\n\
-d, --daemon       Runs in daemon mode\n\
-f, --config_file  Set configuration file name\n\
-i, --pid_file     Set process identifier file name\n\
-v, --version      Print program version\n\
-h, --help         Display this help and exit\n\
\n\
Report bugs to 'git@mtulio.eng.br'\n");

  exit (status);
}

/*
* Main function - might to be change when daemon function will be created.
* @param argc number of arguments in argv vector
* @param argv vector with arguments sent by command line
* @return a int to OS with status of execution program, zero is success
*/
int main(int argc , char *argv[])
{

	int arg_daemon_mode = 0;
	char arg_file_config[MAX_BUFF_SIZE];
	char arg_file_pid[MAX_BUFF_SIZE];
	bzero(arg_file_config, strlen(arg_file_config));
	bzero(arg_file_pid, strlen(arg_file_pid));


  /* Command line option parse. */
  while (1) {
    int opt;
    opt = getopt_long (argc, argv, "df:i:h:v", longopts, 0);
    if (opt == EOF)
    	break;

    switch (opt)
	{
	  case 0:
		break;
      case 'd':
        arg_daemon_mode = 1;
        break;
	  case 'f':
		/*TODO: get argument string */
//		*arg_file_config = optarg;
		strncpy(optarg, arg_file_config, strlen(optarg));
		break;
	  case 'i':
	    /*TODO: get argument string */
//		*arg_file_pid = optarg;
		strncpy(optarg, arg_file_pid, strlen(optarg));
		printf("ARGS: arg_file_pid[%s]\n",  optarg);
		break;
	  case 'v':
		printf("0.1\n");
		exit (0);
		break;
	  case 'h':
		mtuliod_mainUsage (0);
		break;
	  default:
		mtuliod_mainUsage (1);
	    break;
	  }
	}

  /* Show args */
//  printf("ARGS: arg_daemon_mode[%d], arg_file_config[%s], arg_file_pid[%s]\n",
//		  arg_daemon_mode,
//		  arg_file_config,
//		  arg_file_pid);

	/* Create a daemon */
	if (arg_daemon_mode == 1) {
		ret = mtd_lib_daemon_init (1, 1);
		if ( (ret) < 0 ) {
			printf(" '%s': Starting daemon ... ERROR ", "mtuliod");
			mtd_stdout_msg(ret);
		} else {
			printf(" '%s': Starting daemon ... PID %d \n", "mtuliod", ret);
		}
	}

	/* Init main config file */
	if ( (ret = mtuliod_initConfig()) != 0 )
		goto GT_EXIT;

	/* Init System Signals */
	mtuliod_signal_init ();


	/* Start TCP server */
	if ( (ret = mtd_srv_main(mtd_config)) != 0 )
		mtd_stdout_print("#% ERROR - starting TCP server\n");



	/* END */
	GT_EXIT:

	/* Free structures */
	mtuliod_end();

	exit (ret);
}
