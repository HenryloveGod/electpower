/* vi: set sw=4 ts=4:
 *
 * picocom.c
 *
 * simple dumb-terminal program. Helps you manually configure and test
 * stuff like modems, devices w. serial ports etc.
 *
 * by Nick Patavalis (npat@efault.net)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>

#define _GNU_SOURCE
#include <getopt.h>

#include "term.h"

/**********************************************************************/

#define KEY_EXIT    '\x18' /* C-x: exit picocom */
#define KEY_QUIT    '\x11' /* C-q: exit picocom without reseting port */
#define KEY_PULSE   '\x10' /* C-p: pulse DTR */
#define KEY_TOGGLE  '\x14' /* C-t: toggle DTR */
#define KEY_BAUD_UP '\x15' /* C-u: increase baudrate (up) */
#define KEY_BAUD_DN '\x04' /* C-d: decrase baudrate (down) */ 
#define KEY_FLOW    '\x06' /* C-f: change flowcntrl mode */ 
#define KEY_PARITY  '\x19' /* C-y: change parity mode */ 
#define KEY_BITS    '\x02' /* C-b: change number of databits */ 
#define KEY_LECHO   '\x03' /* C-c: toggle local echo */ 
#define KEY_STATUS  '\x16' /* C-v: show program option */
#define KEY_SEND    '\x13' /* C-s: send file */
#define KEY_RECEIVE '\x12' /* C-r: receive file */
#define KEY_BREAK   '\x1c' /* C-\: break */

#define STO STDOUT_FILENO
#define STI STDIN_FILENO



