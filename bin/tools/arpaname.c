/*
 * Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/* $Id: arpaname.c,v 1.2 2009/03/04 02:23:36 marka Exp $ */

#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int
main(int argc, char *argv[]) {
	unsigned char buf[16];
	int i;

	while (argv[1]) {
		if (inet_pton(AF_INET6, argv[1], buf) == 1) {
			for (i = 15; i >= 0; i--)
				fprintf(stdout, "%X.%X.", buf[i] & 0xf,
					(buf[i] >> 4) & 0xf);
			fprintf(stdout, "IP6.ARPA\n");
			argv++;
			continue;
		}
		if (inet_pton(AF_INET, argv[1], buf) == 1) {
			fprintf(stdout, "%u.%u.%u.%u.IN-ADDR.ARPA\n",
				buf[3], buf[2], buf[1], buf[0]);
			argv++;
			continue;
		}
		return (1);
	}
	fflush(stdout);
	return(ferror(stdout));
}