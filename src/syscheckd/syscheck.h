/* Copyright (C) 2009 Trend Micro Inc.
 * All right reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */

#ifndef __SYSCHECK_H
#define __SYSCHECK_H

#include "config/syscheck-config.h"
#define MAX_LINE PATH_MAX+256

/* Notify list size */
#define NOTIFY_LIST_SIZE    32

// Number of attributes in the hash table
#define SK_DB_NATTR 9

/* Global config */
extern syscheck_config syscheck;

/** Function Prototypes **/

/* Check the integrity of the files against the saved database */
void run_check(void);

/* Run run_check periodically */
void start_daemon(void) __attribute__((noreturn));

/* Read the XML config */
int Read_Syscheck_Config(const char *cfgfile) __attribute__((nonnull));

/* Create the database */
int create_db(void);

/* Check database for changes */
int run_dbcheck(void);

/* Scan directory */
int read_dir(const char *dir_name, int opts, OSMatch *restriction, whodata_evt *evt);

/* Check the registry for changes */
void os_winreg_check(void);

/* Start real time */
int realtime_start(void);

/* Add a directory to real time monitoring */
int realtime_adddir(const char *dir, int whodata) __attribute__((nonnull(1)));

/* Initializes the whodata scan mode */
int run_whodata_scan(void);

/* Process real time queue */
int realtime_process(void);

/* Process the content of the file changes */
char *seechanges_addfile(const char *filename) __attribute__((nonnull));

/* Generate the whodata csum */
int extract_whodata_sum(whodata_evt *evt, char *wd_sum, int size);

/* Get checksum changes */
int c_read_file(const char *file_name, const char *oldsum, char *newsum) __attribute__((nonnull));

int send_syscheck_msg(const char *msg) __attribute__((nonnull));
int send_rootcheck_msg(const char *msg) __attribute__((nonnull));

const char* get_user(const char *path, int uid);
const char* get_group(int gid);

int realtime_checksumfile(const char *file_name, whodata_evt *evt) __attribute__((nonnull(1)));

#ifndef WIN32
int audit_init(void);
int check_auditd_enabled(void);
int set_auditd_config(void);
int init_auditd_socket(void);
int add_audit_rule(const char *dir);
void * audit_main(int *audit_sock);
#endif

#endif
