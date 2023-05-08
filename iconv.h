/* iconv.h
 *
 * This header is based on the similarly minimal "include/iconv.h" from musl
 * libc, version 1.2.3. It was very slightly adapted by Philip McGrath to suit
 * a standalone iconv implementation.
 *
 * The following details are excerpted from the COPYRIGHT file in the musl
 * libc v1.2.3 distribution:
 *
 * --8<------------------cut here-------------------start---------------->8---
 *
 * ----------------------------------------------------------------------
 * Copyright © 2005-2020 Rich Felker, et al.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ----------------------------------------------------------------------
 *
 * Authors/contributors include:
 *
 * A. Wilcox
 * Ada Worcester
 * Alex Dowad
 * Alex Suykov
 * Alexander Monakov
 * Andre McCurdy
 * Andrew Kelley
 * Anthony G. Basile
 * Aric Belsito
 * Arvid Picciani
 * Bartosz Brachaczek
 * Benjamin Peterson
 * Bobby Bingham
 * Boris Brezillon
 * Brent Cook
 * Chris Spiegel
 * Clément Vasseur
 * Daniel Micay
 * Daniel Sabogal
 * Daurnimator
 * David Carlier
 * David Edelsohn
 * Denys Vlasenko
 * Dmitry Ivanov
 * Dmitry V. Levin
 * Drew DeVault
 * Emil Renner Berthing
 * Fangrui Song
 * Felix Fietkau
 * Felix Janda
 * Gianluca Anzolin
 * Hauke Mehrtens
 * He X
 * Hiltjo Posthuma
 * Isaac Dunham
 * Jaydeep Patil
 * Jens Gustedt
 * Jeremy Huntwork
 * Jo-Philipp Wich
 * Joakim Sindholt
 * John Spencer
 * Julien Ramseier
 * Justin Cormack
 * Kaarle Ritvanen
 * Khem Raj
 * Kylie McClain
 * Leah Neukirchen
 * Luca Barbato
 * Luka Perkov
 * M Farkas-Dyck (Strake)
 * Mahesh Bodapati
 * Markus Wichmann
 * Masanori Ogino
 * Michael Clark
 * Michael Forney
 * Mikhail Kremnyov
 * Natanael Copa
 * Nicholas J. Kain
 * orc
 * Pascal Cuoq
 * Patrick Oppenlander
 * Petr Hosek
 * Petr Skocik
 * Pierre Carrier
 * Reini Urban
 * Rich Felker
 * Richard Pennington
 * Ryan Fairfax
 * Samuel Holland
 * Segev Finer
 * Shiz
 * sin
 * Solar Designer
 * Stefan Kristiansson
 * Stefan O'Rear
 * Szabolcs Nagy
 * Timo Teräs
 * Trutz Behn
 * Valentin Ochs
 * Will Dietz
 * William Haddon
 * William Pitcock
 *
 * ...
 *
 * All other files which have no copyright comments are original works
 * produced specifically for use as part of this library, written either
 * by Rich Felker, the main author of the library, or by one or more
 * contibutors listed above. Details on authorship of individual files
 * can be found in the git version control history of the project. The
 * omission of copyright and license comments in each file is in the
 * interest of source tree size.
 *
 * [In the next paragraph, "*" is written "@" to avoid closing this comment.]
 *
 * In addition, permission is hereby granted for all public header files
 * (include/@ and arch/@/bits/@) and crt files intended to be linked into
 * applications (crt/@, ldso/dlstart.c, and arch/@/crt_arch.h) to omit
 * the copyright notice and permission notice otherwise required by the
 * license, and to use these files without any requirement of
 * attribution. These files include substantial contributions from:
 *
 * Bobby Bingham
 * John Spencer
 * Nicholas J. Kain
 * Rich Felker
 * Richard Pennington
 * Stefan Kristiansson
 * Szabolcs Nagy
 *
 * all of whom have explicitly granted such permission.
 *
 * This file previously contained text expressing a belief that most of
 * the files covered by the above exception were sufficiently trivial not
 * to be subject to copyright, resulting in confusion over whether it
 * negated the permissions granted in the license. In the spirit of
 * permissive licensing, and of not having licensing issues being an
 * obstacle to adoption, that text has been removed.
 *
 * --8<------------------cut here-------------------end------------------>8---
 *
 * In the musl libc v1.2.3 distribution, "include/iconv.h" was one of the
 * aforementioned "files which have no copyright comments", in addition to
 * being a public header file.
 *
 * To the extent that copyright subsists in any of the modifications to this
 * file, permission is hereby granted to use the modifications under the same
 * terms as the musl libc v1.2.3 original.
 *
 */

#ifndef _ICONV_H
#define _ICONV_H

#ifdef __cplusplus
extern "C" {
#endif

/* need size_t (header defined by C89). */
#include <stddef.h>

typedef void *iconv_t;

iconv_t iconv_open(const char *tocode, const char *fromcode);
size_t iconv(iconv_t cd,
             char **restrict inbuf,
             size_t *restrict inbytesleft,
             char **restrict outbuf,
             size_t *restrict outbytesleft);
int iconv_close(iconv_t cd);

#ifdef __cplusplus
}
#endif

#endif
