/* src/getdata.h.  Generated from getdata.h.in2 by configure.  */
/* Copyright (C) 2002-2005 C. Barth Netterfield
 * Copyright (C) 2003-2005 Theodore Kisner
 * Copyright (C) 2005-2017 D. V. Wiebe
 *
 ***************************************************************************
 *
 * This file is part of the GetData project.
 *
 * GetData is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * GetData is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with GetData; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

/* GETDATA.H -- GetData Library public API definition
 * --------------------------------------------------
 *
 * Several preprocessor symbols may be defined before including this file to
 * modify its use:
 *
 * - defining GD_NO_LEGACY_API will prevent the Legacy API declarations in
 *   getdata_legacy.h from being declared.  If the Legacy API was omitted from
 *   the library when it was built, this symbol does nothing.
 *
 * - defining GD_C89_API will prevent declarations herein from using the C99
 *   keyword `_Complex'.  Affected declarations will instead use a two-element
 *   array of doubles in place of the complex types.  It also changes the
 *   gd_entry_t object as described in the gd_entry(3) manual page.  This
 *   symbol permits including these declarations using a non-C99 conforming
 *   compiler.
 *
 * - defining GD_64BIT_API will expose the declaration of versions of funtions
 *   using an explicitly 64-bit off_t type, regardless of the actual size of
 *   off_t itself.  These functions have "64" appended to their name (e.g.
 *   gd_getdata64()).  It will also define the gd_off64_t type, which is used in
 *   these exposed definitions as a replacement for off_t.  This symbol is
 *   automatically defined if _LARGEFILE64_SOURCE has been defined before
 *   including this file, and may also be defined on certain platforms where
 *   off_t is 64-bits.
 *
 * API DOCUMENTATION
 * -----------------
 *
 * The GetData APIs which are declared in this file are documented in section 3
 * of the Unix manual.  You should be able to access it using the standard
 * man(1) command, e.g.:
 *
 *   man gd_getdata
 *
 * or equivalent.
 */

#ifndef GETDATA_H
#define GETDATA_H

#ifdef __cplusplus
extern "C" {
#endif

/* The most recent standards version supported by this library */
#define GD_DIRFILE_STANDARDS_VERSION 10

#include <math.h>
#include <sys/types.h>

/* If this symbol is defined here, the C99-API is not present in the library */
/* #undef GD_NO_C99_API */

#if defined(GD_NO_C99_API) && ! defined(GD_C89_API)
# define GD_C89_API
#endif

/* MSVC build system defines GD_C89_API */
#if defined(GD_C89_API)
# define GD_NO_C99_API
#endif

/* define function attributes */
#if defined __GNUC__ && defined __GNUC_MINOR__
#  define gd_gnu_enough ((__GNUC__ * 100 + __GNUC_MINOR__) >= 303)
#else
#  define gd_gnu_enough 0
#endif

#ifdef __attribute_deprecated__
# define gd_deprecated __attribute_deprecated__
#elif gd_gnu_enough
# define gd_deprecated __attribute__ ((__deprecated__))
#else
# define gd_deprecated /**/
#endif

#ifdef __THROW
# define gd_nothrow __THROW
#elif !defined __cplusplus && gd_gnu_enough
# define gd_nothrow __attribute__ ((__nothrow__))
#else
# define gd_nothrow /**/
#endif

/* ICC complains that it ignores the __nonnull__ attribute */
#ifdef __INTEL_COMPILER
# define gd_nonnull(...) /**/
#elif gd_gnu_enough
# define gd_nonnull(...) __attribute__ ((__nonnull__ __VA_ARGS__))
#else
# define gd_nonnull(...) /**/
#endif

/* formerly, this was the maximum length of a format file line.  We keep it
 * around for legacy reasons.  (The actual maximum length of a format file
 * line is the maximum value of ssize_t, i.e. 2**(n-1)-1 on a n-bit system.)
 */
#define GD_MAX_LINE_LENGTH  4096

/* error codes */
#define GD_E_OK               (  0) /* this MUST be zero */
#define GD_E_FORMAT           ( -1)
#define GD_E_CREAT            ( -2)
#define GD_E_BAD_CODE         ( -3)
#define GD_E_BAD_TYPE         ( -4)
#define GD_E_IO               ( -5)
#define GD_E_INTERNAL_ERROR   ( -6)
#define GD_E_ALLOC            ( -7)
#define GD_E_RANGE            ( -8)
#define GD_E_LUT              ( -9)
#define GD_E_RECURSE_LEVEL    (-10)
#define GD_E_BAD_DIRFILE      (-11)
#define GD_E_BAD_FIELD_TYPE   (-12)
#define GD_E_ACCMODE          (-13)
#define GD_E_UNSUPPORTED      (-14)
#define GD_E_UNKNOWN_ENCODING (-15)
#define GD_E_BAD_ENTRY        (-16)
#define GD_E_DUPLICATE        (-17)
#define GD_E_DIMENSION        (-18)
#define GD_E_BAD_INDEX        (-19)
#define GD_E_BAD_SCALAR       (-20)
#define GD_E_BAD_REFERENCE    (-21)
#define GD_E_PROTECTED        (-22)
#define GD_E_DELETE           (-23)
#define GD_E_ARGUMENT         (-24)
#define GD_E_CALLBACK         (-25)
#define GD_E_EXISTS           (-26)
#define GD_E_UNCLEAN_DB       (-27)
#define GD_E_DOMAIN           (-28)
#define GD_E_BOUNDS           (-29)
#define GD_E_LINE_TOO_LONG    (-30)

#define GD_N_ERROR_CODES      31 /* including GD_E_OK and unused codes */

/* Deprecated error codes */
#define GD_E_BAD_REPR         GD_E_BAD_CODE /* Deprecated in 0.9 */
#define GD_E_OPEN_LINFILE     GD_E_LUT      /* Deprecated in 0.9 */
#define GD_E_FLUSH            GD_E_IO       /* Deprecated in 0.9 */
#define GD_E_OPEN             GD_E_IO       /* Deprecated in 0.9 */
#define GD_E_OPEN_FRAGMENT    GD_E_IO       /* Deprecated in 0.9 */
#define GD_E_OPEN_INCLUDE     GD_E_IO       /* Deprecated in 0.9 */
#define GD_E_RAW_IO           GD_E_IO       /* Deprecated in 0.9 */
#define GD_E_TRUNC            GD_E_IO       /* Deprecated in 0.9 */

/* the maximum number of input vectors in a LINCOM */
#define GD_MAX_LINCOM 3

/* the following MUST be at most one less than twice GD_MAX_LINCOM */
#define GD_MAX_POLYORD (GD_MAX_LINCOM * 2 - 1)

/* syntax suberrors */
#define GD_E_FORMAT_BAD_SPF    1
#define GD_E_FORMAT_N_FIELDS   2
#define GD_E_FORMAT_N_TOK      3
#define GD_E_FORMAT_NUMBITS    4
#define GD_E_FORMAT_BITNUM     5
#define GD_E_FORMAT_BITSIZE    6
#define GD_E_FORMAT_CHARACTER  7
#define GD_E_FORMAT_BAD_LINE   8
#define GD_E_FORMAT_RES_NAME   9
#define GD_E_FORMAT_ENDIAN    10
#define GD_E_FORMAT_BAD_TYPE  11
#define GD_E_FORMAT_BAD_NAME  12
#define GD_E_FORMAT_UNTERM    13
#define GD_E_FORMAT_METARAW   14
#define GD_E_FORMAT_NO_FIELD  15
#define GD_E_FORMAT_DUPLICATE 16
#define GD_E_FORMAT_LOCATION  17
#define GD_E_FORMAT_PROTECT   18
#define GD_E_FORMAT_LITERAL   19
#define GD_E_FORMAT_WINDOP    20
#define GD_E_FORMAT_META_META 21
#define GD_E_FORMAT_ALIAS     22
#define GD_E_FORMAT_MPLEXVAL  23

/* parser callback return values */
#define GD_SYNTAX_ABORT    0
#define GD_SYNTAX_RESCAN   1
#define GD_SYNTAX_IGNORE   2
#define GD_SYNTAX_CONTINUE 3

/* Protection levels */
#define GD_PROTECT_NONE   00
#define GD_PROTECT_FORMAT 01
#define GD_PROTECT_DATA   02
#define GD_PROTECT_ALL    ( GD_PROTECT_DATA | GD_PROTECT_FORMAT )

/* Standards specifiers */
#define GD_VERSION_CURRENT  (-1)
#define GD_VERSION_LATEST   (-2)
#define GD_VERSION_EARLIEST (-3)

/* this MUST be one less than the lowest allowed fragment index */
#define GD_ALL_FRAGMENTS (-1)

#define GD_SCALAR_ENTRY_BIT  0x10
#define GD_SPECIAL_ENTRY_BIT 0x20
/* field types */
typedef enum {
  GD_NO_ENTRY       = 0x00,
  GD_RAW_ENTRY      = 0x01,
  GD_LINCOM_ENTRY   = 0x02,
  GD_LINTERP_ENTRY  = 0x03,
  GD_BIT_ENTRY      = 0x04,
  GD_MULTIPLY_ENTRY = 0x05,
  GD_PHASE_ENTRY    = 0x06,
  GD_INDEX_ENTRY    = 0x07,
  GD_POLYNOM_ENTRY  = 0x08,
  GD_SBIT_ENTRY     = 0x09,
  GD_DIVIDE_ENTRY   = 0x0A,
  GD_RECIP_ENTRY    = 0x0B,
  GD_WINDOW_ENTRY   = 0x0C,
  GD_MPLEX_ENTRY    = 0x0D,
  GD_INDIR_ENTRY    = 0x0E,
  GD_SINDIR_ENTRY   = 0x0F,
  GD_CONST_ENTRY    = GD_SCALAR_ENTRY_BIT | 0x00,
  GD_STRING_ENTRY   = GD_SCALAR_ENTRY_BIT | 0x01,
  GD_CARRAY_ENTRY   = GD_SCALAR_ENTRY_BIT | 0x02,
  GD_SARRAY_ENTRY   = GD_SCALAR_ENTRY_BIT | 0x03,

  /* not a real entry type, but it's convenient to put this here */
  GD_ALIAS_ENTRY    =   -1
} gd_entype_t;

/* GD_NO_ENTRY and GD_ALIAS_ENTRY are not part of this count */
#define GD_N_ENTYPES 19

/* Special types for gd_nentries(3) and gd_entry_list(3) */
#define GD_ALL_ENTRIES    0
#define GD_VECTOR_ENTRIES (GD_SPECIAL_ENTRY_BIT | 0x01)
#define GD_SCALAR_ENTRIES (GD_SPECIAL_ENTRY_BIT | 0x02)
#define GD_ALIAS_ENTRIES  GD_ALIAS_ENTRY

/* gd_nentries(3), gd_entry_list(3) and gd_match_entries(3) flags */
#define GD_ENTRIES_HIDDEN  0x01
#define GD_ENTRIES_NOALIAS 0x02

/* additional gd_match_entries(3) flags */
#define GD_REGEX_PCRE       0x04
#define GD_REGEX_EXTENDED   0x08
#define GD_REGEX_ICASE      0x10
#define GD_REGEX_CASELESS   GD_REGEX_ICASE /* synonym */
/* The rest of these are ignored if GD_REGEX_PCRE is not also set */
#define GD_REGEX_JAVASCRIPT 0x20
#define GD_REGEX_UNICODE    0x40

/* the current location of the I/O pointer */
#define GD_HERE  (-1)

/* MPLEX lookback defines */
#define GD_DEFAULT_LOOKBACK 10
#define GD_LOOKBACK_ALL (-1)

/* C data types */
#if ! defined GD_C89_API
# include <inttypes.h>
# define gd_int64_t int64_t
# define gd_uint64_t uint64_t
# define GD_DCOMPLEXM(v) double _Complex v
# define GD_DCOMPLEXP(v) double _Complex *v
#else
# define gd_int64_t long int
# define gd_uint64_t unsigned long int
# define GD_DCOMPLEXM(v) double v[2]
# define GD_DCOMPLEXP(v) double *v
#endif

typedef gd_int64_t gd_shift_t; /* Deprecated in 0.10 */

/* Data types -- No valid type may set 0x40 */
#define GD_SIZE8     0x001
#define GD_SIZE16    0x002
#define GD_SIZE32    0x004
#define GD_SIZE64    0x008
#define GD_SIZE128   0x010
#define GD_SIZE(x)   ((x) & 0x01f)

#define GD_SIGNED    0x020
#define GD_IEEE754   0x080
#define GD_COMPLEX   0x100
#define GD_CHAR      0x200

typedef enum {
  GD_NULL       = 0,
  GD_UNKNOWN    = 0xfa0,  /* GD_SIZE(GD_UNKNOWN) MUST evaluate to zero */
  GD_UINT8      = GD_SIZE8,
  GD_INT8       = GD_SIZE8   | GD_SIGNED,
  GD_UINT16     = GD_SIZE16,
  GD_INT16      = GD_SIZE16  | GD_SIGNED,
  GD_UINT32     = GD_SIZE32,
  GD_INT32      = GD_SIZE32  | GD_SIGNED,
  GD_UINT64     = GD_SIZE64,
  GD_INT64      = GD_SIZE64  | GD_SIGNED,
  GD_FLOAT32    = GD_SIZE32  | GD_IEEE754,
  GD_FLOAT64    = GD_SIZE64  | GD_IEEE754,
  GD_COMPLEX64  = GD_SIZE64  | GD_COMPLEX,
  GD_COMPLEX128 = GD_SIZE128 | GD_COMPLEX,
  GD_STRING     = GD_CHAR | (sizeof(char*))
} gd_type_t;


/* Window operations */
typedef enum {
  GD_WINDOP_UNK,
  GD_WINDOP_EQ,
  GD_WINDOP_GE,
  GD_WINDOP_GT,
  GD_WINDOP_LE,
  GD_WINDOP_LT,
  GD_WINDOP_NE,
  GD_WINDOP_SET,
  GD_WINDOP_CLR
} gd_windop_t;

struct gd_private_entry_;

typedef union {
  gd_int64_t i;
  gd_uint64_t u;
  double r;
} gd_triplet_t;

/* Entry object flags */
#define GD_EN_COMPSCAL 0x1 /* entry has complex scalar parameters */
#define GD_EN_CALC     0x2 /* scalar field codes have been resolved */
#define GD_EN_HIDDEN   0x4 /* entry is hidden */

/* ANSI C does not permit anonymous structs/unions */
#ifdef GD_C89_API
# define GD_ANON(x) x
#else
# define GD_ANON(x)
#endif
/* Unified entry struct */
struct gd_unified_entry_ {
  char *field;
  gd_entype_t field_type;
  char *in_fields[GD_MAX_LINCOM];
  char *scalar[GD_MAX_POLYORD + 1];
  int scalar_ind[GD_MAX_POLYORD + 1];
  int fragment_index;
  unsigned flags;
  union {
    struct { /* RAW */
      unsigned int spf;
      gd_type_t data_type;
    } GD_ANON(raw);
    struct { /* LINCOM */
      int n_fields;
      double m[GD_MAX_LINCOM];
      GD_DCOMPLEXM(cm[GD_MAX_LINCOM]);
      double b[GD_MAX_LINCOM];
      GD_DCOMPLEXM(cb[GD_MAX_LINCOM]);
    } GD_ANON(lincom);
    struct { /* BIT and SBIT */
      int bitnum;
      int numbits;
    } GD_ANON(bit);
    struct { /* POLYNOM */
      int poly_ord;
      double a[GD_MAX_POLYORD + 1];
      GD_DCOMPLEXM(ca[GD_MAX_POLYORD + 1]);
    } GD_ANON(polynom);
    struct { /* RECIP */
      double dividend;
      GD_DCOMPLEXM(cdividend);
    } GD_ANON(recip);
    struct { /* LINTERP */
      char *table;
    } GD_ANON(linterp);
    struct { /* PHASE */
      gd_int64_t shift;
    } GD_ANON(phase);
    struct { /* WINDOW */
      gd_windop_t windop;
      gd_triplet_t threshold;
    } GD_ANON(window);
    struct { /* MPLEX */
      int count_val;
      int period;
    } GD_ANON(mplex);
    struct { /* CONST */
      gd_type_t const_type;
      size_t array_len;
    } GD_ANON(scalar);
  } GD_ANON(u);

  struct gd_private_entry_ *e;
};

typedef struct gd_unified_entry_ gd_entry_t;

/* The dirfile object */
typedef struct gd_dirfile_ DIRFILE;

/* Parser callback objects */
struct gd_callback_data_ {
  const DIRFILE *dirfile;
  int suberror;
  int linenum;
  const char *filename;
  char *line;
  size_t buflen;
};

/* the carray list object */
struct gd_carray_data_ {
  size_t n;
  void *d;
};

typedef struct gd_carray_data_ gd_carray_t;

typedef struct gd_callback_data_ gd_parser_data_t;

typedef int (*gd_parser_callback_t)(gd_parser_data_t*, void*);


/* dirfile_flags --- 0xF0000000 are reserved */
#define GD_ACCMODE        0x00000001 /* mask */
#define GD_RDONLY         0x00000000 /* open read only */
#define GD_RDWR           0x00000001 /* open read/write */

#define GD_FORCE_ENDIAN   0x00000002 /* override endianness */
#define GD_BIG_ENDIAN     0x00000004 /* assume big-endian raw data */
#define GD_LITTLE_ENDIAN  0x00000008 /* assume litte-endian raw data */
#define GD_CREAT          0x00000010 /* create dirfile if it doesn't exist */
#define GD_EXCL           0x00000020 /* force creation: fail on existence */
#define GD_TRUNC          0x00000040 /* truncate dirfile (scary!) */
#define GD_PEDANTIC       0x00000080 /* be pedantic */
#define GD_FORCE_ENCODING 0x00000100 /* override encoding scheme */
#define GD_VERBOSE        0x00000200 /* be verbose */
#define GD_IGNORE_DUPS    0x00000400 /* ignore duplicate fields */
#define GD_IGNORE_REFS    0x00000800 /* ignore REFERENCE directives --
                                        dirfile_include only */
#define GD_PRETTY_PRINT   0x00001000 /* make a nicer looking format file */

#if (defined __arm__ && !(defined __VFP_FP__ || defined __MAVERICK__))
# define GD_ARM_ENDIAN     0x00000000 /* ARM-endian doubles */
# define GD_NOT_ARM_ENDIAN 0x00002000 /* "normal"-endian doubles */
#else
# define GD_ARM_ENDIAN     0x00002000 /* ARM-endian doubles */
# define GD_NOT_ARM_ENDIAN 0x00000000 /* "normal"-endian doubles */
#endif

#define GD_PERMISSIVE     0x00004000 /* be permissive */
#define GD_TRUNCSUB       0x00008000 /* truncate subdirectories */

#define GD_ENCODING       0x0F000000 /* mask */
#define GD_AUTO_ENCODED   0x00000000 /* Encoding scheme unknown */
#define GD_UNENCODED      0x01000000 /* Data are not encoded */
#define GD_TEXT_ENCODED   0x02000000 /* Data are text encoded */
#define GD_SLIM_ENCODED   0x03000000 /* Data are slimlib encoded */
#define GD_GZIP_ENCODED   0x04000000 /* Data are gzip encoded */
#define GD_BZIP2_ENCODED  0x05000000 /* Data are bzip2 encoded */
#define GD_LZMA_ENCODED   0x06000000 /* Data are xz encoded */
#define GD_SIE_ENCODED    0x07000000 /* Data are sample index encoded */
#define GD_ZZIP_ENCODED   0x08000000 /* Data are zzip encoded */
#define GD_ZZSLIM_ENCODED 0x09000000 /* Data are zzslim encoded */
#define GD_FLAC_ENCODED   0x0A000000 /* Data are flac encoded */
#define GD_ENC_UNSUPPORTED GD_ENCODING /* Encoding unsupported */

/* delete flags */
#define GD_DEL_META  0x1
#define GD_DEL_DATA  0x2
#define GD_DEL_DEREF 0x4
#define GD_DEL_FORCE 0x8

/* move/rename flags */
#define GD_REN_DATA   0x1
#define GD_REN_UPDB   0x2
#define GD_REN_DANGLE 0x4
#define GD_REN_FORCE  0x8

/* seek flags */
#define GD_SEEK_SET   0x0
#define GD_SEEK_CUR   0x1
#define GD_SEEK_END   0x2
#define GD_SEEK_WRITE 0x4

/* desync flags */
#define GD_DESYNC_PATHCHECK 0x1
#define GD_DESYNC_REOPEN    0x2

/* open_limit special values */
#define GD_OLIMIT_NONE    0
#define GD_OLIMIT_CURRENT (-1)
#define GD_OLIMIT_COUNT   (-2)

void gd_alloc_funcs(void *(*malloc_func)(size_t),
    void (*free_func)(void*)) gd_nothrow;

extern int gd_add_alias(DIRFILE *dirfile, const char *alias_name,
    const char *target_code, int fragment_index) gd_nothrow
gd_nonnull ((1,2,3));

extern int gd_add_bit(DIRFILE *dirfile, const char *field_code,
    const char *in_field, int bitnum, int numbits, int fragment_index)
gd_nothrow gd_nonnull ((1,2,3));

extern int gd_add_clincom(DIRFILE *dirfile, const char *field_code,
    int n_fields, const char **in_fields, const GD_DCOMPLEXP(cm),
    const GD_DCOMPLEXP(cb), int fragment_index) gd_nothrow
gd_nonnull ((1,2,4,5,6));

extern int gd_add_carray(DIRFILE *dirfile, const char *field_code,
    gd_type_t const_type, size_t array_len, gd_type_t data_type,
    const void *values, int fragment_index) gd_nothrow gd_nonnull((1,2,6));

extern int gd_add_const(DIRFILE *dirfile, const char *field_code,
    gd_type_t const_type, gd_type_t data_type, const void *value,
    int fragment_index) gd_nothrow gd_nonnull ((1,2,5));

extern int gd_add_cpolynom(DIRFILE *dirfile, const char *field_code,
    int poly_ord, const char *in_field, const GD_DCOMPLEXP(ca),
    int fragment_index) gd_nothrow gd_nonnull ((1,2,4));

/* The native gd_add_crecip cannot be used in C89 mode */
#if ! defined GD_C89_API
extern int gd_add_crecip(DIRFILE *dirfile, const char *field_code,
    const char *in_field, _Complex double cdividend, int fragment_index)
gd_nothrow gd_nonnull ((1,2,3));
#else
#define gd_add_crecip gd_add_crecip89
#endif

extern int gd_add_crecip89(DIRFILE *dirfile, const char *field_code,
    const char *in_field, const double cdividend[2], int fragment_index)
gd_nothrow gd_nonnull ((1,2,3));

extern int gd_add_divide(DIRFILE *dirfile, const char *field_code,
    const char *in_field1, const char *in_field2, int fragment_index)
gd_nothrow gd_nonnull ((1,2,3,4));

extern int gd_add_indir(DIRFILE *dirfile, const char *field_code,
    const char *in_field1, const char *in_field2, int fragment_index) gd_nothrow
gd_nonnull ((1,2,3,4));

extern int gd_add_lincom(DIRFILE *dirfile, const char *field_code, int n_fields,
    const char **in_fields, const double *m, const double *b,
    int fragment_index) gd_nothrow gd_nonnull ((1,2,4,5,6));

extern int gd_add_linterp(DIRFILE *dirfile, const char *field_code,
    const char *in_field, const char *table, int fragment_index) gd_nothrow
gd_nonnull ((1,2,3,4));

extern int gd_add_mplex(DIRFILE *dirfile, const char *field_code,
    const char *in_field, const char *count_field, int count_val, int period,
    int fragment_index) gd_nothrow gd_nonnull ((1,2,3,4));

extern int gd_add_multiply(DIRFILE *dirfile, const char *field_code,
    const char *in_field1, const char *in_field2, int fragment_index)
gd_nothrow gd_nonnull ((1,2,3,4));

extern int gd_add_phase(DIRFILE *dirfile, const char *field_code,
    const char *in_field, gd_int64_t shift, int fragment_index) gd_nothrow
gd_nonnull ((1,2,3));

extern int gd_add_polynom(DIRFILE *dirfile, const char *field_code,
    int poly_ord, const char *in_field, const double *a, int fragment_index)
gd_nothrow gd_nonnull ((1,2,4));

extern int gd_add_recip(DIRFILE *dirfile, const char *field_code,
    const char *in_field, double dividend, int fragment_index) gd_nothrow
gd_nonnull ((1,2,3));

extern int gd_add_sarray(DIRFILE *dirfile, const char *field_code,
    size_t array_len, const char **values, int fragment_index) gd_nothrow
gd_nonnull ((1,2,4));

extern int gd_add_sbit(DIRFILE *dirfile, const char *field_code,
    const char *in_field, int bitnum, int numbits,
    int fragment_index) gd_nothrow gd_nonnull ((1,2,3));

extern int gd_add_sindir(DIRFILE *dirfile, const char *field_code,
    const char *in_field1, const char *in_field2, int fragment_index)
gd_nothrow gd_nonnull ((1,2,3,4));

extern int gd_add_string(DIRFILE *dirfile, const char *field_code,
    const char *value, int fragment_index) gd_nothrow gd_nonnull((1,2,3));

extern int gd_add_window(DIRFILE *dirfile, const char *field_code,
    const char *in_field, const char *check_field, gd_windop_t windop,
    gd_triplet_t threshold, int fragment_index) gd_nothrow
gd_nonnull ((1,2,3,4));

extern const char *gd_alias_target(DIRFILE *dirfile,
    const char *field_code) gd_nothrow gd_nonnull ((1,2));

extern const char **gd_aliases(DIRFILE *dirfile,
    const char *field_code) gd_nothrow gd_nonnull ((1,2));

extern int gd_alter_affixes(DIRFILE *dirfile, int index, const char *prefix,
        const char *suffix) gd_nothrow gd_nonnull ((1));

extern int gd_alter_bit(DIRFILE *dirfile, const char *field_code,
    const char *in_field, int bitnum, int numbits) gd_nothrow
gd_nonnull((1,2));

extern int gd_alter_carray(DIRFILE *dirfile, const char *field_code,
    gd_type_t const_type, size_t array_len) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_clincom(DIRFILE *dirfile, const char *field_code,
    int n_fields, const char **in_fields, const GD_DCOMPLEXP(m),
    const GD_DCOMPLEXP(b)) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_const(DIRFILE *dirfile, const char *field_code,
    gd_type_t const_type) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_cpolynom(DIRFILE *dirfile, const char *field_code,
    int poly_ord, const char *in_field, const GD_DCOMPLEXP(a)) gd_nothrow
gd_nonnull((1,2));

#if ! defined GD_C89_API
extern int gd_alter_crecip(DIRFILE *dirfile, const char *field_code,
    const char *in_field, _Complex double cdividend) gd_nothrow
gd_nonnull((1,2));
#else
#define gd_alter_crecip gd_alter_crecip89
#endif

extern int gd_alter_crecip89(DIRFILE *dirfile, const char *field_code,
    const char *in_field, const double cdividend[2]) gd_nothrow
gd_nonnull((1,2));

extern int gd_alter_divide(DIRFILE *dirfile, const char *field_code,
    const char *in_field1, const char *in_field2) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_indir(DIRFILE *dirfile, const char *field_code,
    const char *in_field1, const char *in_field2) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_lincom(DIRFILE *dirfile, const char *field_code,
    int n_fields, const char **in_fields, const double *m, const double *b)
gd_nothrow gd_nonnull((1,2));

extern int gd_alter_mplex(DIRFILE *dirfile, const char *field_code,
    const char *in_field, const char *count_field, int count_val,
    int period) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_multiply(DIRFILE *dirfile, const char *field_code,
    const char *in_field1, const char *in_field2) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_phase(DIRFILE *dirfile, const char *field_code,
    const char *in_field, gd_int64_t shift) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_polynom(DIRFILE *dirfile, const char *field_code,
    int poly_ord, const char *in_field, const double *a) gd_nothrow
gd_nonnull((1,2));

extern int gd_alter_recip(DIRFILE *dirfile, const char *field_code,
    const char *in_field, double cdividend) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_sarray(DIRFILE *dirfile, const char *field_code,
    size_t array_len) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_sbit(DIRFILE *dirfile, const char *field_code,
    const char *in_field, int bitnum, int numbits) gd_nothrow
gd_nonnull((1,2));

extern int gd_alter_sindir(DIRFILE *dirfile, const char *field_code,
    const char *in_field1, const char *in_field2) gd_nothrow gd_nonnull((1,2));

extern int gd_alter_window(DIRFILE *dirfile, const char *field_code,
    const char *in_field, const char *check_field, gd_windop_t windop,
    gd_triplet_t threshold) gd_nothrow gd_nonnull((1,2));

extern size_t gd_array_len(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull((1,2));

/* Deprecated in GetData-0.9.  Use gd_array_len() instead */
extern size_t gd_carray_len(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull((1,2)) gd_deprecated;

extern int gd_get_carray(DIRFILE *dirfile, const char *field_code,
    gd_type_t return_type, void *data_out) gd_nothrow gd_nonnull((1,2));

extern int gd_get_carray_slice(DIRFILE *dirfile, const char *field_code,
    unsigned long start, size_t n, gd_type_t return_type, void *data_out)
gd_nothrow gd_nonnull((1,2));

extern int gd_put_carray(DIRFILE *dirfile, const char *field_code,
  gd_type_t data_type, const void *data_in) gd_nothrow gd_nonnull((1,2,4));

extern int gd_put_carray_slice(DIRFILE *dirfile, const char *field_code,
    unsigned long first, size_t n, gd_type_t data_type, const void *data_in)
gd_nothrow gd_nonnull((1,2,6));

extern int gd_get_constant(DIRFILE *dirfile, const char *field_code,
    gd_type_t return_type, void *data) gd_nothrow gd_nonnull ((1, 2));

extern int gd_put_constant(DIRFILE *dirfile, const char *field_code,
    gd_type_t data_type, const void *data) gd_nothrow gd_nonnull ((1, 2, 4));

extern const void *gd_constants(DIRFILE *dirfile,
    gd_type_t return_type) gd_nothrow gd_nonnull ((1));

extern const gd_carray_t *gd_carrays(DIRFILE *dirfile,
    gd_type_t return_type) gd_nothrow gd_nonnull ((1));

extern unsigned long int gd_encoding(DIRFILE *dirfile,
    int fragment) gd_nothrow gd_nonnull ((1));

extern int gd_encoding_support(unsigned long encoding) gd_nothrow;

extern unsigned long int gd_endianness(DIRFILE *dirfile,
    int fragment) gd_nothrow gd_nonnull((1));

extern int gd_entry(DIRFILE *dirfile, const char *field_code,
    gd_entry_t *entry) gd_nothrow gd_nonnull ((1, 2));

extern const char **gd_entry_list(DIRFILE *dirfile, const char *parent,
    int type, unsigned int flags) gd_nothrow gd_nonnull ((1));

extern gd_entype_t gd_entry_type(DIRFILE *dirfile,
    const char *field_code) gd_nothrow gd_nonnull ((1));

extern int gd_error(const DIRFILE *dirfile) gd_nothrow gd_nonnull ((1));

extern int gd_error_count(DIRFILE *dirfile) gd_nothrow gd_nonnull ((1));

extern char *gd_error_string(const DIRFILE *dirfile, char *buffer,
    size_t buflen) gd_nothrow gd_nonnull ((1));

extern const char **gd_field_list(DIRFILE *dirfile) gd_nothrow gd_nonnull ((1));

extern const char **gd_field_list_by_type(DIRFILE *dirfile,
    gd_entype_t type) gd_nothrow gd_nonnull ((1));

extern unsigned long gd_flags(DIRFILE *D, unsigned long set,
    unsigned long resest) gd_nothrow gd_nonnull ((1));

extern int gd_fragment_affixes(DIRFILE *dirfile, int index, char **prefix,
    char **suffix) gd_nothrow gd_nonnull ((1,3,4));

extern int gd_fragment_index(DIRFILE *dirfile,
    const char *field_code) gd_nothrow gd_nonnull ((1));

extern const char *gd_fragmentname(DIRFILE *dirfile,
    int index) gd_nothrow gd_nonnull ((1));

extern const char *gd_fragment_namespace(DIRFILE *D, int index,
    const char *ns) gd_nothrow;

extern gd_entry_t *gd_free_entry_strings(gd_entry_t *entry) gd_nothrow;

extern int gd_hidden(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull ((1,2));

extern int gd_hide(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull ((1,2));

extern DIRFILE *gd_invalid_dirfile(void) gd_nothrow;

extern char *gd_linterp_tablename(DIRFILE *D, const char *field_code) gd_nothrow
gd_nonnull ((1, 2));

extern int gd_madd(DIRFILE *dirfile, const gd_entry_t *entry,
    const char *parent) gd_nothrow gd_nonnull ((1,2,3));

extern int gd_madd_alias(DIRFILE *dirfile, const char *parent,
    const char *alias_name, const char *target_code) gd_nothrow
gd_nonnull ((1,2,3,4));

extern int gd_madd_bit(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field, int bitnum,
    int numbits) gd_nothrow gd_nonnull ((1,2,3,4));

extern int gd_madd_carray(DIRFILE *dirfile, const char *parent,
    const char *field_code, gd_type_t const_type, size_t array_len,
    gd_type_t data_type, const void *values) gd_nothrow gd_nonnull((1,2,3,7));

extern int gd_madd_clincom(DIRFILE *dirfile, const char *parent,
    const char *field_code, int n_fields, const char **in_fields,
    const GD_DCOMPLEXP(cm), const GD_DCOMPLEXP(cb)) gd_nothrow
gd_nonnull((1,2,3,5,6,7));

extern int gd_madd_const(DIRFILE *dirfile, const char *parent,
    const char *field_code, gd_type_t const_type, gd_type_t data_type,
    const void *value) gd_nothrow gd_nonnull ((1,2,3,6));

extern int gd_madd_cpolynom(DIRFILE *dirfile, const char *parent,
    const char *field_code, int poly_ord, const char *in_field,
    const GD_DCOMPLEXP(ca)) gd_nothrow gd_nonnull ((1,2,3,5));

#if ! defined GD_C89_API
extern int gd_madd_crecip(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field, _Complex double cdividend)
gd_nothrow gd_nonnull ((1,2,3,4));
#else
#define gd_madd_crecip gd_madd_crecip89
#endif

extern int gd_madd_crecip89(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field, const double cdividend[2])
gd_nothrow gd_nonnull ((1,2,3,4));

extern int gd_madd_divide(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field1, const char *in_field2)
gd_nothrow gd_nonnull ((1,2,3,4,5));

extern int gd_madd_indir(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field1, const char *in_field2)
gd_nothrow gd_nonnull ((1,2,3,4,5));

extern int gd_madd_lincom(DIRFILE *dirfile, const char *parent,
    const char *field_code, int n_fields, const char **in_fields,
    const double *m, const double *b) gd_nothrow gd_nonnull((1,2,3,5,6,7));

extern int gd_madd_linterp(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field, const char *table)
gd_nothrow gd_nonnull ((1,2,3,4,5));

extern int gd_madd_mplex(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field, const char *count_field,
    int count_val, int period) gd_nothrow
gd_nonnull ((1,2,3,4,5));

extern int gd_madd_multiply(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field1, const char *in_field2)
gd_nothrow gd_nonnull ((1,2,3,4,5));

extern int gd_madd_phase(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field, gd_int64_t shift)
gd_nothrow gd_nonnull ((1,2,3,4));

extern int gd_madd_polynom(DIRFILE *dirfile, const char *parent,
    const char *field_code, int poly_ord, const char *in_field, const double *a)
gd_nothrow gd_nonnull ((1,2,3,5));

extern int gd_madd_recip(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field, double dividend) gd_nothrow
gd_nonnull ((1,2,3,4));

extern int gd_madd_sarray(DIRFILE *dirfile, const char *parent,
    const char *field_code, size_t array_len, const char **values) gd_nothrow
gd_nonnull ((1,2,3,5));

extern int gd_madd_sbit(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field, int bitnum,
    int numbits) gd_nothrow gd_nonnull ((1,2,3,4));

extern int gd_madd_sindir(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field1, const char *in_field2)
gd_nothrow gd_nonnull ((1,2,3,4,5));

extern int gd_madd_spec(DIRFILE *dirfile, const char *line,
    const char *parent) gd_nothrow gd_nonnull ((1,2,3));

extern int gd_madd_string(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *value) gd_nothrow
gd_nonnull ((1,2,3,4));

extern int gd_madd_window(DIRFILE *dirfile, const char *parent,
    const char *field_code, const char *in_field, const char *check_field,
    gd_windop_t windop, gd_triplet_t threshold) gd_nothrow
gd_nonnull ((1,2,3,4,5));

extern unsigned int gd_match_entries(DIRFILE *D, const char *regex,
    int fragment, int type, unsigned int flags, const char ***list) gd_nothrow
gd_nonnull ((1));

extern int gd_dirfile_standards(DIRFILE *dirfile, int vers) gd_nothrow
gd_nonnull ((1));

extern const void *gd_mconstants(DIRFILE *dirfile, const char *parent,
    gd_type_t return_type) gd_nothrow gd_nonnull((1,2));

extern const gd_carray_t *gd_mcarrays(DIRFILE *dirfile, const char *parent,
    gd_type_t return_type) gd_nothrow;

extern const char **gd_mfield_list(DIRFILE *dirfile,
    const char *parent) gd_nothrow gd_nonnull((1,2));

extern const char **gd_mfield_list_by_type(DIRFILE *dirfile,
    const char *parent, gd_entype_t type) gd_nothrow gd_nonnull((1,2));

extern void gd_mplex_lookback(DIRFILE *dirfile, int lookback) gd_nothrow
gd_nonnull((1));

extern const char ***gd_msarrays(DIRFILE *dirfile,
    const char *parent) gd_nothrow gd_nonnull ((1,2));

extern const char **gd_mstrings(DIRFILE *dirfile, const char *parent) gd_nothrow
gd_nonnull((1,2));

extern const char **gd_mvector_list(DIRFILE *dirfile,
    const char *parent) gd_nothrow gd_nonnull((1,2));

extern const char *gd_dirfilename(DIRFILE *dirfile) gd_nothrow gd_nonnull ((1));

extern unsigned int gd_naliases(DIRFILE *dirfile,
    const char *field_code) gd_nothrow gd_nonnull ((1,2));

extern gd_type_t gd_native_type(DIRFILE *dirfile,
    const char *field_code) gd_nothrow gd_nonnull ((1,2));

extern unsigned int gd_nentries(DIRFILE *D, const char *parent, int type,
    unsigned int flags) gd_nothrow gd_nonnull ((1));

extern unsigned int gd_nfields(DIRFILE *dirfile) gd_nothrow gd_nonnull ((1));

extern unsigned int gd_nfields_by_type(DIRFILE *dirfile,
    gd_entype_t type) gd_nothrow gd_nonnull ((1));

extern int gd_nfragments(DIRFILE *dirfile) gd_nothrow gd_nonnull((1));

extern unsigned int gd_nmfields(DIRFILE *dirfile, const char *parent) gd_nothrow
gd_nonnull((1,2));

extern unsigned int gd_nmfields_by_type(DIRFILE *dirfile, const char *parent,
    gd_entype_t type) gd_nothrow gd_nonnull((1,2));

extern unsigned int gd_nmvectors(DIRFILE *dirfile,
    const char *parent) gd_nothrow gd_nonnull((1,2));

extern unsigned int gd_nvectors(DIRFILE *dirfile) gd_nothrow gd_nonnull ((1));

extern int gd_parent_fragment(DIRFILE *dirfile, int fragment_index) gd_nothrow
gd_nonnull ((1));

extern void gd_parser_callback(DIRFILE *dirfile, gd_parser_callback_t sehandler,
    void*) gd_nothrow gd_nonnull ((1));

extern int gd_alter_protection(DIRFILE *dirfile, int protection_level,
    int fragment_index) gd_nothrow gd_nonnull ((1));

extern int gd_protection(DIRFILE *dirfile, int fragment_index) gd_nothrow
gd_nonnull ((1));

extern char *gd_raw_filename(DIRFILE *dirfile,
    const char *field_code) gd_nothrow gd_nonnull ((1, 2));

extern const char *gd_reference(DIRFILE *dirfile,
    const char *field_code) gd_nothrow gd_nonnull ((1));

extern int gd_get_sarray(DIRFILE *dirfile, const char *field_code,
    const char **data_out) gd_nothrow gd_nonnull((1,2));

extern int gd_get_sarray_slice(DIRFILE *dirfile, const char *field_code,
    unsigned long start, size_t n, const char **data_out) gd_nothrow
gd_nonnull((1,2));

extern int gd_put_sarray(DIRFILE *dirfile, const char *field_code,
    const char **data_in) gd_nothrow gd_nonnull((1,2,3));

extern int gd_put_sarray_slice(DIRFILE *dirfile, const char *field_code,
    unsigned long first, size_t n, const char **data_in) gd_nothrow
gd_nonnull((1,2,5));

extern unsigned int gd_spf(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull ((1, 2));

extern size_t gd_get_string(DIRFILE *dirfile, const char *field_code,
    size_t len, char *data) gd_nothrow gd_nonnull ((1, 2));

extern int gd_put_string(DIRFILE *dirfile, const char *field_code,
    const char *data) gd_nothrow gd_nonnull ((1, 2, 3));

const char ***gd_sarrays(DIRFILE *dirfile) gd_nothrow gd_nonnull ((1));

extern const char **gd_strings(DIRFILE *dirfile) gd_nothrow gd_nonnull ((1));

extern char *gd_strtok(DIRFILE *D, const char *string) gd_nothrow
gd_nonnull ((1));

extern int gd_unhide(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull ((1,2));

extern int gd_validate(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull((1,2));

extern int gd_verbose_prefix(DIRFILE *D, const char *prefix) gd_nothrow
gd_nonnull ((1));

extern const char **gd_vector_list(DIRFILE *dirfile) gd_nothrow gd_nonnull((1));

/* The following functions contain calls to I/O functions, making them
 * cancellation points.  As a result we cannot mark them with gd_nothrow.
 */
extern int gd_add(DIRFILE *dirfile, const gd_entry_t *entry) gd_nonnull((1,2));

extern int gd_add_raw(DIRFILE *dirfile, const char *field_code,
    gd_type_t data_type, unsigned int spf,
    int fragment_index) gd_nonnull((1,2));

extern int gd_add_spec(DIRFILE *dirfile, const char *line,
    int fragment_index) gd_nonnull ((1,2));

extern int gd_alter_encoding(DIRFILE *dirfile, unsigned long int encoding,
    int fragment, int recode) gd_nonnull ((1));

extern int gd_alter_endianness(DIRFILE *dirfile, unsigned long int byte_sex,
    int fragment, int recode) gd_nonnull ((1));

extern int gd_alter_entry(DIRFILE *dirfile, const char *field_code,
    const gd_entry_t *entry, int recode) gd_nonnull ((1,2));

extern int gd_alter_linterp(DIRFILE *dirfile, const char *field_code,
    const char *in_field, const char *table, int recode) gd_nonnull ((1,2));

extern int gd_alter_raw(DIRFILE *dirfile, const char *field_code,
    gd_type_t data_type, unsigned int spf, int recode) gd_nonnull ((1,2));

extern int gd_alter_spec(DIRFILE *dirfile, const char *line,
    int recode) gd_nonnull ((1,2));

extern DIRFILE *gd_cbopen(const char *dirfilename, unsigned long int flags,
    gd_parser_callback_t sehandler, void *extra) gd_nonnull ((1));

extern int gd_close(DIRFILE *dirfile);

extern int gd_delete(DIRFILE *dirfile, const char *field_code,
    unsigned int flags) gd_nonnull ((1,2));

extern int gd_desync(DIRFILE *dirfile, unsigned int flags);

extern int gd_discard(DIRFILE *dirfile);

extern int gd_flush(DIRFILE *dirfile, const char *field_code) gd_nonnull ((1));

extern int gd_include(DIRFILE *dirfile, const char *file, int fragment_index,
    unsigned long int flags) gd_nonnull ((1,2));

extern int gd_include_affix(DIRFILE *dirfile, const char *file,
    int fragment_index, const char *prefix, const char *suffix,
    unsigned long int flags) gd_nonnull ((1,2));

extern int gd_include_ns(DIRFILE *D, const char *file, int fragment_index,
    const char *ns, unsigned long flags) gd_nonnull ((1,2));

extern double gd_framenum(DIRFILE *dirfile, const char *field_code,
    double value) gd_nonnull ((1,2));

extern int gd_malter_spec(DIRFILE *dirfile, const char *line,
    const char *parent, int recode) gd_nonnull ((1,2,3));

extern int gd_metaflush(DIRFILE *dirfile) gd_nonnull ((1));

extern int gd_move(DIRFILE *dirfile, const char *field_code, int new_fragment,
    unsigned flags) gd_nonnull ((1,2));

extern DIRFILE *gd_open(const char *dirfilename,
    unsigned long int flags) gd_nonnull ((1));

extern long gd_open_limit(DIRFILE *dirfile, long new_limit) gd_nonnull ((1));

extern int gd_raw_close(DIRFILE *dirfile,
    const char *field_code) gd_nonnull ((1));

extern int gd_rename(DIRFILE *dirfile, const char *old_code,
    const char *new_name, unsigned flags) gd_nonnull ((1,2,3));

extern int gd_rewrite_fragment(DIRFILE *dirfile, int fragment) gd_nonnull ((1));

extern int gd_sync(DIRFILE *dirfile, const char *field_code) gd_nonnull ((1));

extern int gd_uninclude(DIRFILE *dirfile, int fragment_index,
    int del) gd_nonnull ((1));

#if defined _FILE_OFFSET_BITS && _FILE_OFFSET_BITS == 64

/* Expose the 64-bit API */
#ifndef GD_64BIT_API
#define GD_64BIT_API
#endif

/* Force the use of the 64-bit API */
#define gd_alter_frameoffset gd_alter_frameoffset64
#define gd_getdata gd_getdata64
#define gd_putdata gd_putdata64
#define gd_framenum_subset gd_framenum_subset64
#define gd_frameoffset gd_frameoffset64
#define gd_nframes gd_nframes64
#define gd_bof gd_bof64
#define gd_eof gd_eof64
#define gd_seek gd_seek64
#define gd_tell gd_tell64

#else

/* the following functions are _FILE_OFFSET_BITS sensitive.  */
extern int gd_alter_frameoffset(DIRFILE *dirfile, off_t offset, int fragment,
    int recode) gd_nonnull ((1));

extern size_t gd_getdata(DIRFILE *dirfile, const char *field_code,
    off_t first_frame, off_t first_sample, size_t num_frames,
    size_t num_samples, gd_type_t return_type, void *data) gd_nonnull ((1, 2));

extern size_t gd_putdata(DIRFILE *dirfile, const char *field_code,
    off_t first_frame, off_t first_sample, size_t num_frames,
    size_t num_samples, gd_type_t data_type, const void *data)
gd_nonnull ((1, 2));

extern double gd_framenum_subset(DIRFILE *dirfile, const char *field_code,
    double value, off_t field_start, off_t field_end) gd_nonnull ((1,2));

extern off_t gd_frameoffset(DIRFILE *dirfile, int fragment) gd_nothrow
gd_nonnull ((1));

extern off_t gd_nframes(DIRFILE *dirfile) gd_nonnull ((1));

extern off_t gd_bof(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull ((1,2));

extern off_t gd_eof(DIRFILE *dirfile, const char *field_code)
gd_nonnull ((1,2));

extern off_t gd_seek(DIRFILE *dirfile, const char *field_code, off_t frame_num,
    off_t sample_num, int whence) gd_nonnull ((1,2));

extern off_t gd_tell(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull ((1,2));

#endif 

#ifdef _LARGEFILE64_SOURCE
#ifndef GD_64BIT_API
#define GD_64BIT_API
#endif
#endif

/* This is the explicitly 64-bit API */
#ifdef GD_64BIT_API
#ifdef __off64_t_defined
typedef __off64_t gd_off64_t;
#elif (defined _FILE_OFFSET_BITS && _FILE_OFFSET_BITS == 64)
typedef off_t gd_off64_t;
#else
typedef gd_int64_t gd_off64_t;
#endif

extern int gd_alter_frameoffset64(DIRFILE *dirfile, gd_off64_t offset,
    int fragment, int recode) gd_nonnull ((1));

extern size_t gd_getdata64(DIRFILE *dirfile, const char *field_code,
    gd_off64_t first_frame, gd_off64_t first_samp, size_t num_frames,
    size_t num_samp, gd_type_t return_type, void *data) gd_nonnull ((1, 2));

extern size_t gd_putdata64(DIRFILE *dirfile, const char *field_code,
    gd_off64_t first_frame, gd_off64_t first_sample, size_t num_frames,
    size_t num_samples, gd_type_t data_type, const void *data)
gd_nonnull ((1, 2));

extern gd_off64_t gd_frameoffset64(DIRFILE *dirfile,
    int fragment) gd_nonnull((1));

extern double gd_framenum_subset64(DIRFILE *dirfile, const char *field_code,
    double value, gd_off64_t field_start,
    gd_off64_t field_end) gd_nonnull ((1,2));

extern gd_off64_t gd_nframes64(DIRFILE *dirfile) gd_nonnull ((1));

extern gd_off64_t gd_bof64(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull ((1,2));

extern gd_off64_t gd_eof64(DIRFILE *dirfile, const char *field_code)
gd_nonnull ((1,2));

extern gd_off64_t gd_seek64(DIRFILE *dirfile, const char *field_code,
    gd_off64_t frame_num, gd_off64_t sample_num, int whence) gd_nonnull ((1,2));

extern gd_off64_t gd_tell64(DIRFILE *dirfile, const char *field_code) gd_nothrow
gd_nonnull ((1,2));
#endif


#ifdef __cplusplus
}
#endif

/* If this symbol is defined here, the legacy API is present in the library */
/* #undef GD_LEGACY_API */

/* The caller can disable the legacy API by defining GD_NO_LEGACY_API
 * before including getdata.h
 */
#ifndef GD_NO_LEGACY_API
/* include the legacy api, if present */
#  ifdef GD_LEGACY_API
#    include <getdata_legacy.h>
#  endif
#endif

/* Library version information */
#define GD_GETDATA_VERSION "0.11.0"

/* This is (major * 10000) + (minor * 100) + revision */
#define GD_GETDATA_INT_VERSION 1100

/* If this symbol is defined here, the library lacks POSIX regex support */
/* #undef GD_NO_REGEX */

/* If this symbol is defined here, the library lacks PCRE regex support */
/* #undef GD_NO_PCRE */

#endif
