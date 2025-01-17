/*
    $Id: asm.h 115 2008-04-08 02:55:57Z phf $

    the DASM macro assembler (aka small systems cross assembler)

    Copyright (c) 1988-2002 by Matthew Dillon.
    Copyright (c) 1995 by Olaf "Rhialto" Seibert.
    Copyright (c) 2003-2008 by Andrew Davie.
    Copyright (c) 2008 by Peter H. Froehlich.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

/*
 *  ASM65.H
 *
 *  Structures and definitions
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* tag object files going into dasm executable */
#define SVNTAG(id) static const char _svnid[] = id

#define OlafFreeFormat    0    /* Decide on looks of word if it is opcode */
#define OlafHashFormat    1    /* Decide on # and ^ if it is an opcode */

#if OlafHashFormat && OlafFreeFormat
#error This cannot be!
#endif

/* for -T option [phf] */
typedef enum
{
  SORTMODE_DEFAULT,
  SORTMODE_ALPHA = SORTMODE_DEFAULT,
  SORTMODE_ADDRESS,
  SORTMODE_MAX
} sortmode_t;

/* for -E option [phf] */
typedef enum
{
  ERRORFORMAT_DEFAULT,
  ERRORFORMAT_WOE = ERRORFORMAT_DEFAULT,
  ERRORFORMAT_DILLON,
  ERRORFORMAT_GNU,
  ERRORFORMAT_MAX
} errorformat_t;

#define DAD

#ifdef DAD

enum FORMAT
{
    FORMAT_DEFAULT = 1,
    FORMAT_RAS,
    FORMAT_RAW,
    FORMAT_MAX
};


#define MAX_SYM_LEN 1024

    enum ASM_ERROR_EQUATES
    {
        ERROR_NONE = 0,
        ERROR_COMMAND_LINE,                             /* Check format of command-line */
        ERROR_FILE_ERROR,                               /* Unable to open file */
        ERROR_NOT_RESOLVABLE,                           /* Source is not resolvable */
        ERROR_TOO_MANY_PASSES,                          /* Too many passes - something wrong */

        ERROR_SYNTAX_ERROR,                             /*  0 */
        ERROR_EXPRESSION_TABLE_OVERFLOW,                /*  1 */
        ERROR_UNBALANCED_BRACES,                        /*  2 */
        ERROR_DIVISION_BY_0,                            /*  3 */
        ERROR_UNKNOWN_MNEMONIC,                         /*  4 */
        ERROR_ILLEGAL_ADDRESSING_MODE,                  /*  5 */
        ERROR_ILLEGAL_FORCED_ADDRESSING_MODE,           /*  6 */
        ERROR_NOT_ENOUGH_ARGUMENTS_PASSED_TO_MACRO,     /*  7 */
        ERROR_PREMATURE_EOF,                            /*  8 */
        ERROR_ILLEGAL_CHARACTER,                        /*  9 */
        ERROR_BRANCH_OUT_OF_RANGE,                      /* 10 */
        ERROR_ERR_PSEUDO_OP_ENCOUNTERED,                /* 11 */
        ERROR_ORIGIN_REVERSE_INDEXED,                   /* 12 */
        ERROR_EQU_VALUE_MISMATCH,                       /* 13 */
        ERROR_ADDRESS_MUST_BE_LT_100,                   /* 14 */
        ERROR_ILLEGAL_BIT_SPECIFICATION,                /* 15 */
        ERROR_NOT_ENOUGH_ARGS,                          /* 16 */
        ERROR_LABEL_MISMATCH,                           /* 17 */
        ERROR_VALUE_UNDEFINED,                          /* 18 */
        ERROR_PROCESSOR_NOT_SUPPORTED,                  /* 20 */
        ERROR_REPEAT_NEGATIVE,                          /* 21 */
        ERROR_BADERROR,                                 /* 22 */
        ERROR_ONLY_ONE_PROCESSOR_SUPPORTED,             /* Only allow one type of processor */
        ERROR_BAD_FORMAT,                               /* Bad format specifier */

		/* F8 support... */

        ERROR_VALUE_MUST_BE_1_OR_4,                     /* 25 */
        ERROR_VALUE_MUST_BE_LT_10,                      /* 26 */
        ERROR_VALUE_MUST_BE_LT_8,                       /* 27 */
        ERROR_VALUE_MUST_BE_LT_F,                       /* 28 */
        ERROR_VALUE_MUST_BE_LT_10000,                   /* 29 */
        ERROR_ILLEGAL_OPERAND_COMBINATION,              /* 30 */
	
        ERROR_UNRECOVERABLE,                            /* 31 */	
	
	};

    typedef struct ERRORSTRUCT
    {
        int nErrorType;                                 /* ASM_ERROR_EQUATES value */
        bool bFatal;                                    /* 0 = OK, non-zero = cannot continue compilation */
        const char *sDescription;                             /* Error message */

    } ERROR_DEFINITION;


    enum REASON_CODES
    {
        REASON_MNEMONIC_NOT_RESOLVED = 1 << 0,
        REASON_OBSCURE = 1 << 1,                        /* fix this! */
        REASON_DC_NOT_RESOVED = 1 << 2,
        REASON_DV_NOT_RESOLVED_PROBABLY = 1 << 3,
        REASON_DV_NOT_RESOLVED_COULD = 1 << 4,
        REASON_DS_NOT_RESOLVED = 1 << 5,
        REASON_ALIGN_NOT_RESOLVED = 1 << 6,
        REASON_ALIGN_RELOCATABLE_ORIGIN_NOT_KNOWN = 1 << 7,
        REASON_ALIGN_NORMAL_ORIGIN_NOT_KNOWN = 1 << 8,
        REASON_EQU_NOT_RESOLVED = 1 << 9,
        REASON_EQU_VALUE_MISMATCH = 1 << 10,
        REASON_IF_NOT_RESOLVED = 1 << 11,
        REASON_REPEAT_NOT_RESOLVED = 1 << 12,
        REASON_FORWARD_REFERENCE = 1 << 13,
        REASON_PHASE_ERROR = 1 << 14
    };


#endif

#define MNEMONIC    struct _MNE
#define MACRO       struct _MACRO
#define INCFILE     struct _INCFILE
#define REPLOOP     struct _REPLOOP
#define IFSTACK     struct _IFSTACK
#define SEGMENT     struct _SEGMENT
#define SYMBOL        struct _SYMBOL
#define STRLIST     struct _STRLIST

#define DEFORGFILL  255
#define SHASHSIZE   1024
#define MHASHSIZE   1024
#define SHASHAND    0x03FF
#define MHASHAND    0x03FF
#define ALLOCSIZE   16384
#define MAXMACLEVEL 32
#define TAB        9


	enum ADDRESS_MODES {
		AM_IMP,					/*    implied         */
		AM_IMM8,				/*    immediate 8  bits   */
		AM_IMM16,		        /*    immediate 16 bits   */
		AM_BYTEADR,				/*    address 8 bits        */
		AM_BYTEADRX,			/*    address 16 bits     */
		AM_BYTEADRY,			/*    relative 8 bits     */
		AM_WORDADR,				/*    index x 0 bits        */
		AM_WORDADRX,			/*    index x 8 bits        */
		AM_WORDADRY,			/*    index x 16 bits     */
		AM_REL,					/*    bit inst. special   */
		AM_INDBYTEX,			/*    bit-bra inst. spec. */
		AM_INDBYTEY,			/*    index y 0 bits        */
		AM_INDWORD,				/*    index y 8 bits        */
		AM_0X,					/*    index x 0 bits        */
		AM_0Y,					/*    index y 0 bits        */
		AM_BITMOD,				/*    ind addr 8 bits     */
		AM_BITBRAMOD,			/*    ind addr 16 bits    */

		AM_SYMBOL,
		AM_EXPLIST,
		AM_LONG,
		AM_BSS,

		NUMOC
	};

#define AF_IMP					( 1L << AM_IMP )
#define AF_IMM8					( 1L << AM_IMM8 )
#define AF_IMM16				( 1L << AM_IMM16 )
#define AF_BYTEADR				( 1L << AM_BYTEADR )
#define AF_BYTEADRX				( 1L << AM_BYTEADRX )
#define AF_BYTEADRY				( 1L << AM_BYTEADRY )
#define AF_WORDADR				( 1L << AM_WORDADR )
#define AF_WORDADRX				( 1L << AM_WORDADRX )
#define AF_WORDADRY				( 1L << AM_WORDADRY )
#define AF_REL					( 1L << AM_REL )
#define AF_INDBYTEX				( 1L << AM_INDBYTEX )
#define AF_INDBYTEY				( 1L << AM_INDBYTEY )
#define AF_INDWORD				( 1L << AM_INDWORD )
#define AF_0X					( 1L << AM_0X )
#define AF_0Y					( 1L << AM_0Y )
#define AF_BITMOD				( 1L << AM_BITMOD )
#define AF_BITBRAMOD			( 1L << AM_BITBRAMOD )

#define AM_BYTE					AM_BYTEADR
#define AM_WORD					AM_WORDADR



STRLIST {
    STRLIST *next;
    char    buf[4];
};

#define STRLISTSIZE    sizeof(STRLIST *)

#define MF_IF					0x04
#define MF_MACRO				0x08
#define MF_MASK					0x10    /*  has mask argument (byte)    */
#define MF_REL					0x20    /*  has rel. address (byte)    */
#define MF_IMOD					0x40    /*  instruction byte mod.    */
#define MF_ENDM					0x80    /*  is v_endm            */

MNEMONIC {
    MNEMONIC     *next;        /*    hash        */
    void    (*vect)(char *, MNEMONIC *);    /*  dispatch        */
    const char    *name;        /*    actual name    */
    unsigned char   flags;        /*    special flags    */
    unsigned long   okmask;
    unsigned int opcode[NUMOC];  /*    hex codes, byte or word (>xFF) opcodes    */
};

/* MNEMONIC with all fields 0, used as end-of-table marker. */
#define MNEMONIC_NULL {NULL, NULL, NULL, 0, 0, {0,}}

MACRO {
    MACRO   *next;
    void    (*vect)(char *, MACRO *);
    char    *name;
    unsigned char   flags;
    STRLIST *strlist;
};

#define INF_MACRO   0x01
#define INF_NOLIST  0x02

INCFILE {
    INCFILE *next;  /*      previously pushed context */
    char    *name;  /*      file name            */
    FILE    *fi;    /*      file handle            */
    unsigned long   lineno; /*      line number in file        */
    unsigned char   flags;  /*      flags (macro)         */

    /*    Only if Macro    */

    STRLIST *args;    /*  arguments to macro        */
    STRLIST *strlist;    /*  current string list     */
    unsigned long   saveidx;    /*  save localindex        */
    unsigned long   savedolidx; /*  save localdollarindex   */

};

#define RPF_UNKNOWN 0x01    /*      value unknown     */

REPLOOP {
    REPLOOP *next;  /*      previously pushed context */
    unsigned long   count;  /*      repeat count            */
    unsigned long   seek;   /*      seek to top of repeat     */
    unsigned long   lineno; /*      line number of line before  */
    INCFILE *file;  /*      which include file are we in*/
    unsigned char   flags;
};

#define IFF_UNKNOWN 0x01    /*      value unknown        */
#define IFF_BASE    0x04

IFSTACK {
    IFSTACK *next;  /*      previous IF            */
    INCFILE *file;  /*      which include file are we in*/
    unsigned char   flags;
    unsigned char   xtrue;   /*      1 if true, 0 if false     */
    unsigned char   acctrue;/*      accumulatively true (not incl this one) */
};

#define SF_UNKNOWN  0x01    /*      ORG unknown            */
#define SF_REF        0x04    /*      ORG referenced        */
#define SF_BSS        0x10    /*      uninitialized area (U flag)    */
#define SF_RORG     0x20    /*      relocatable origin active    */

SEGMENT {
    SEGMENT *next;  /*      next segment in segment list    */
    char    *name;  /*      name of segment        */
    unsigned char   flags;  /*      for ORG            */
    unsigned char   rflags; /*      for RORG            */
    unsigned long   org;    /*      current org            */
    unsigned long   rorg;   /*      current rorg            */
    unsigned long   initorg;
    unsigned long   initrorg;
    unsigned char   initflags;
    unsigned char   initrflags;
};

#define SYM_UNKNOWN 0x01    /*      value unknown     */
#define SYM_REF     0x04    /*      referenced        */
#define SYM_STRING  0x08    /*      result is a string    */
#define SYM_SET     0x10    /*      SET instruction used    */
#define SYM_MACRO   0x20    /*      symbol is a macro    */
#define SYM_MASREF  0x40    /*      master reference    */

SYMBOL {
    SYMBOL  *next;    /*  next symbol in hash list        */
    char    *name;    /*  symbol name or string if expr.  */
    char    *string;    /*  if symbol is actually a string  */
    unsigned char   flags;    /*  flags                */
    unsigned char   addrmode;    /*  addressing mode (expressions)   */
    long value; /* current value, never EVER change this to unsigned! */
    unsigned int namelen;    /*  name length             */
};

extern SYMBOL    *SHash[];
extern MNEMONIC    *MHash[];
extern INCFILE    *pIncfile;
extern REPLOOP    *Reploop;
extern SEGMENT    *Seglist;
extern IFSTACK    *Ifstack;

extern SEGMENT    *Csegment;  /*      current segment */
extern char    *Av[];
extern char    Avbuf[];
/*extern unsigned int Adrbytes[];*/
extern unsigned int Cvt[];
extern MNEMONIC    Ops[];
extern unsigned int    Opsize[];
extern int    Mnext;          /*    mnemonic extension    */
extern unsigned int    Mlevel;

extern bool bTrace;
extern bool     Xdebug;
extern unsigned char    MsbOrder;
extern unsigned char    Outputformat;
extern unsigned long    Redo_why;
extern bool NoIceSupport;

extern int Redo;
extern int Redo_eval;

extern unsigned long    Redo_if;
extern unsigned long    Localindex, Lastlocalindex;
extern unsigned long    Localdollarindex, Lastlocaldollarindex;
extern int   F_format;
extern sortmode_t F_sortmode; /* -T option [phf] */
extern errorformat_t F_errorformat; /* -E option [phf] */
extern unsigned char    F_verbose;
extern const char    *F_outfile;
extern char    *F_listfile;
extern char    *F_symfile;
extern char    *F_noicefile;
extern FILE    *FI_listfile;
extern FILE    *FI_temp;
extern FILE    *FI_noicefile;
extern unsigned char    Fisclear;
extern unsigned long    Plab, Pflags;
extern char    Inclevel;
extern char    ListMode;
extern unsigned long    Processor;
extern unsigned long BaseAddress;

/*extern unsigned int _fmode;*/
extern unsigned long  CheckSum;

/* main.c */
/*extern unsigned char Listing;*/
void    findext(char *str);
int    asmerr(int err, bool bAbort, const char *sText);
char   *sftos(long val, int flags);
void    rmnode(void **base, int bytes);
void    addhashtable(MNEMONIC *mne);
void    pushinclude(char *str);
char   *permalloc(int bytes);
char   *zmalloc(int bytes);
char   *ckmalloc(int bytes);
char   *strlower(char *str);

/* symbols.c */
void    setspecial(int value, int flags);
SYMBOL *allocsymbol(void);
SYMBOL *findsymbol(const char *str, int len);
SYMBOL *CreateSymbol( const char *str, int len );
void    FreeSymbolList(SYMBOL *sym);
void    programlabel(void);

/* ops.c */
extern    unsigned char Gen[];
extern    int Glen;
void    v_set(char *str, MNEMONIC *);
void    v_mexit(char *str, MNEMONIC *);
void    closegenerate(void);
void    generate(void);

void v_list(char *, MNEMONIC *);
void v_include(char *, MNEMONIC *);
void v_seg(char *, MNEMONIC *);
void v_dc(char *, MNEMONIC *);
void v_ds(char *, MNEMONIC *);
void v_org(char *, MNEMONIC *);
void v_rorg(char *, MNEMONIC *);
void v_rend(char *, MNEMONIC *);
void v_align(char *, MNEMONIC *);
void v_subroutine(char *, MNEMONIC *);
void v_equ(char *, MNEMONIC *);
void v_eqm(char *, MNEMONIC *);
void v_set(char *, MNEMONIC *);
void v_macro(char *, MNEMONIC *);
void v_endm(char *, MNEMONIC *);
void v_mexit(char *, MNEMONIC *);
void v_ifconst(char *, MNEMONIC *);
void v_ifnconst(char *, MNEMONIC *);
void v_if(char *, MNEMONIC *);
void v_else(char *, MNEMONIC *);
void v_endif(char *, MNEMONIC *);
void v_repeat(char *, MNEMONIC *);
void v_repend(char *, MNEMONIC *);
void v_err(char *, MNEMONIC *);
void v_hex(char *, MNEMONIC *);
void v_trace(char *, MNEMONIC *);
void v_end(char *, MNEMONIC *);
void v_echo(char *, MNEMONIC *);
void v_processor(char *, MNEMONIC *);
void v_incbin(char *, MNEMONIC *);
void v_incdir(char *, MNEMONIC *);
void v_execmac(char *str, MACRO *mac);
void v_mnemonic(char *str, MNEMONIC *mne);

FILE *pfopen(const char *, const char *);


/* exp.c */
SYMBOL *eval(const char *str, int wantmode);





/* end of asm.h */
