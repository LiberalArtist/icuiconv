#include <stdlib.h>
#include "unicode/utypes.h"   /* Basic ICU data types  */
#include "unicode/ucnv.h"     /* C   Converter API     */
#include "unicode/ustring.h"  /* some more string fcns */
#include "unicode/uchar.h"    /* char names            */
#include "unicode/uloc.h"
#include "unicode/unistr.h"

#ifndef ICUICONV_SET_ERRNO
# include <errno.h>
# define ICUICONV_SET_ERRNO(Expr) { errno = Expr; }
#endif
#ifndef ICUICONV_ENCODING_TO_ICU
# define ICUICONV_ENCODING_TO_ICU(Expr) (Expr)
#endif
#ifndef ICUICONV_BUF_SIZE
# define ICUICONV_BUF_SIZE 4096 /* Is this a good size? */
#endif

typedef struct icuiconv_state {
  UConverter *sourceCnv;
  UConverter *targetCnv;
  UChar *pivotSource; /* pointer info buf */
  UChar *pivotTarget; /* pointer info buf */
  UChar buf[ICUICONV_BUF_SIZE];
} icuiconv_state;

typedef icuiconv_state *iconv_t;



iconv_t iconv_open(const char *tocode, const char *fromcode) {
  UErrorCode errorCode = U_ZERO_ERROR;
  icuiconv_state *cd = (icuiconv_state *)calloc(1, sizeof(icuiconv_state));
  if (NULL == cd) {
    ICUICONV_SET_ERRNO(ENOMEM);
    return (iconv_t)(-1);
  } else {
    cd->pivotSource = &cd->buf[0];
    cd->pivotTarget = &cd->buf[0];
    cd->sourceCnv = ucnv_open(ICUICONV_ENCODING_TO_ICU(fromcode), &errorCode);
    if (U_FAILURE(errorCode)) {
      free(cd);
      ICUICONV_SET_ERRNO(EINVAL); /* Is this the right error ? */
      return (iconv_t)(-1);
    } else {
      errorCode = U_ZERO_ERROR;
      cd->targetCnv = ucnv_open(ICUICONV_ENCODING_TO_ICU(tocode), &errorCode);
      if (U_FAILURE(errorCode)) {
        ucnv_close(cd->sourceCnv);
        free(cd);
        ICUICONV_SET_ERRNO(EINVAL); /* Is this the right error ? */
        return (iconv_t)(-1);
      } else {
        return cd;
      }
    }
  }
};

int iconv_close(iconv_t cd) {
  ucnv_close(cd->sourceCnv);
  ucnv_close(cd->targetCnv);
  free(cd);
  return 0;
};

size_t iconv(iconv_t cd,
             char **restrict inbuf,
             size_t *restrict inbytesleft,
             char **restrict outbuf,
             size_t *restrict outbytesleft) {
  UErrorCode errorCode = U_ZERO_ERROR;
  if ((NULL == inbuf) || (NULL == *inbuf)) {
    if ((NULL == outbuf) || (NULL == *outbuf)) {
      /* Set cd's conversion state to the initial state. */
      ucnv_reset(cd->sourceCnv);
      ucnv_reset(cd->targetCnv);
      cd->pivotSource = &cd->buf[0];
      cd->pivotTarget = &cd->buf[0];
      return 0;
    } else {
      /* outbuf is not NULL and *outbuf is not NULL */
      /* Attempt to set cd’s conversion state to the initial state.
       * Store a corresponding shift sequence at *outbuf.
       * Write at most *outbytesleft bytes, starting at *outbuf.
       * If no more room for this reset sequence,
       * set errno to E2BIG and return (size_t)(−1).
       * Otherwise, increment *outbuf and decrement *outbytesleft
       * by the number of bytes written. (return ???)
       */
      const char *source = "";
      char *target = *outbuf;
      ucnv_convertEx(cd->targetCnv,
                     cd->sourceCnv,
                     &target,
                     target + *outbytesleft,
                     &source,
                     source, /* no inbytesleft */
                     cd->buf,
                     &cd->pivotSource,
                     &cd->pivotTarget,
                     cd->buf + ICUICONV_BUF_SIZE,
                     false, /* reset */
                     true, /* flush */
                     &errorCode);
      *outbytesleft = *outbytesleft - (target - *outbuf);
      *outbuf = target;
      if (U_SUCCESS(errorCode)) {
        return 0;
      } else {
        ICUICONV_SET_ERRNO(U_BUFFER_OVERFLOW_ERROR == errorCode
                           ? E2BIG
                           : EBADMSG); /* ? */
        return -1;
      };
    };
  } else {
    /* Main case: inbuf is not NULL and *inbuf is not NULL */
    /* https://unicode-org.github.io/icu-docs/apidoc/dev/icu4c/ucnv_8h.html#a8c2852929b99ca983ccd1f33a203cc2a */
    char *source = *inbuf;
    char *target = *outbuf;
    size_t ret = 0;
    ucnv_convertEx(cd->targetCnv,
                   cd->sourceCnv,
                   &target,
                   target + *outbytesleft,
                   (const char **) &source, /* TODO: double-check cast */
                   source + *inbytesleft,
                   cd->buf,
                   &cd->pivotSource,
                   &cd->pivotTarget,
                   cd->buf + ICUICONV_BUF_SIZE,
                   false, /* reset */
                   false, /* flush */
                   &errorCode);
    ret = source - *inbuf;
    *inbytesleft = *inbytesleft - (ret);
    *inbuf = source;
    *outbytesleft = *outbytesleft - (target - *outbuf);
    *outbuf = target;
    if (U_SUCCESS(errorCode)) {
      return ret;
    } else {
      if (U_BUFFER_OVERFLOW_ERROR == errorCode) {
        ICUICONV_SET_ERRNO(E2BIG);
      } else {
        /* TODO: distinguish EILSEQ */
        ICUICONV_SET_ERRNO(EINVAL);
      };
      return -1;
    }
  };
}
