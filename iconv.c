#include "unicode/utypes.h"   /* Basic ICU data types */
#include "unicode/ucnv.h"     /* C   Converter API    */
#include "unicode/ustring.h"  /* some more string fcns*/
#include "unicode/uchar.h"    /* char names           */
#include "unicode/uloc.h"
#include "unicode/unistr.h"

#ifndef ICUICONV_SET_ERRNO
# include <errno.h>
# define ICUICONV_SET_ERRNO(Expr) { errno = Expr; }
#endif
#ifndef ICUICONV_ENCODING_TO_ICU
# define ICUICONV_ENCODING_TO_ICU(Expr) (Expr)
#endif

#define ICUICONV_BUF_SIZE 4096 /* is this a good size? */

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
    cd->pivotSource = &cd->buf;
    cd->pivotTarget = &cd->buf;
    cd->sourceCnv = ucnv_open(ICUICONV_ENCODING_TO_ICU(fromcode), &errorCode);
    if (U_FAILURE(errorCode)) {
      free(cd);
      ICUICONV_SET_ERRNO(EINVAL); /* is this the right error ? */
      return (iconv_t)(-1);
    } else {
      errorCode = U_ZERO_ERROR;
      cd->targetCnv = ucnv_open(ICUICONV_ENCODING_TO_ICU(tocode), &errorCode);
      if (U_FAILURE(errorCode)) {
        ucnv_close(cd->sourceCnv);
        free(cd);
        ICUICONV_SET_ERRNO(EINVAL); /* is this the right error ? */
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
  if ((NULL == inbuf) || (NULL == *inbuf)) {
    if ((NULL == outbuf) || (NULL == *outbuf)) {
      /* set cd's conversion state to the initial state */
      ucnv_reset(cd->from);
      ucnv_reset(cd->to);
      cd->pivotSource = &cd->buf;
      cd->pivotTarget = &cd->buf;
      abort(); /* FIXME: what to return */
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
      abort(); /* TODO */
    };
  } else {
    /* Main case: inbuf is not NULL and *inbuf is not NULL */
    /* https://unicode-org.github.io/icu-docs/apidoc/dev/icu4c/ucnv_8h.html#a8c2852929b99ca983ccd1f33a203cc2a */
    UBool reset = false;
    UBool flush = false;
    UErrorCode errorCode = U_ZERO_ERROR;
    const char *source = *inbuf;
    char *target = *outbuf;
    
    ucnv_convertEx(cd->targetCnv,
                   cd->sourceCnv,
                   &target,
                   target + *outbytesleft,
                   &source,
                   source + *inbytesleft,
                   cd->buf,
                   &cd->pivotSource,
                   &cd->pivotTarget,
                   cd->buf + ICUICONV_BUF_SIZE,
                   reset,
                   flush,
                   &errorCode);
      
    abort(); /* TODO */
  };
}

/*
This is the typical life cycle of a converter, as shown step-by-step:

    First, open up the converter with a specified name (or alias name).

    UConverter *conv = ucnv_open("shift_jis", &status);

    Target here is the char s[] to write into, and targetSize is how big the target buffer is. Source is the UChars that are being converted.

    int32_t len = ucnv_fromUChars(conv, target, targetSize, source, u_strlen(source), &status);

    Clean up the converter.

    ucnv_close(conv);

Sharing Converters Between Threads

A converter cannot be shared between threads at the same time. However, if it is reset it can be used for unrelated chunks of data. For example, use the same converter for converting data from Unicode to ISO-8859-3, and then reset it. Use the same converter for converting data from ISO-8859-3 back into Unicode.
Converting Large Quantities of Data

If it is necessary to convert a large quantity of data in smaller buffers, use the same converter to convert each buffer. This will make sure any state is preserved from one chunk to the next. Doing this conversion is known as streaming or buffering, and is mentioned Buffered or Streamed section (§) later in this chapter.

Conversion

    The converters always consume the source buffer as far as possible, and advance the source pointer.

    The converters write to the target all converted output as far as possible, and then write any remaining output to the internal services buffer. When the conversion routines are called again, the internal buffer is flushed out and written to the target buffer before proceeding with any further conversion.

    In conversions to Unicode from Multi-byte encodings or conversions from Unicode involving surrogates, if (a) only a partial byte sequence is retrieved from the source buffer, (b) the “flush” parameter is set to “TRUE” and (c) the end of source is reached, then the callback is called with U_TRUNCATED_CHAR_FOUND.

Reset

Converters can be reset explicitly or implicitly. Explicit reset is done by calling:

    ucnv_reset(): Resets the converter to initial state in both directions.

    ucnv_resetToUnicode(): Resets the converter to initial state to Unicode direction.

    ucnv_resetFromUnicode(): Resets the converter to initial state from Unicode direction.

The converters are reset implicitly when the conversion functions are called with the “flush” parameter set to “TRUE” and the source is consumed.
*/
