/*** Macros to fixup some things that the parser does not understand ***/


/* Use this in the source to cast an integer what to a pointer in the same 
 * home area as host. Use this guarded by BEFOREBOX  */
#ifdef BEFOREBOX
#define CASTTOPOINTER(btyp, host, what) \
      (((btyp *)(host)) + (((S32)(what) - (S32)(host)) / ((S32)sizeof(btyp)))) 
#else
#define CASTTOPOINTER(btyp, host, what) ((btyp *)(what))
#endif

#if !defined(__NODE) && !defined(MANUALBOX)
  #define __SAFE
  #define __INDEX
  #define __TAGGED
  #define __FSEQ
  #define __SEQ
  #define __WILD
  #define __SIZED
  #define __RWSTRING
  #define __ROSTRING
  #define __NULLTERM
  #define __SEQN
  #define __FSEQN
  #define __SAFEUNION
  #define __WILDT
  #define __FSEQT
  #define __SEQT
  #define __FSEQNT
  #define __SEQNT
  #define __INDEXT
  #define __NODE
  #define __HEAPIFY
  #define __DUMMYDEFN
  #define __BOXMODEL(fname)
  #define __NOBOX(block) { block }
#else
  #define __WILD   __attribute__((wild))
  #define __SAFE   __attribute__((safe))
  #define __TAGGED __attribute__((tagged))
  #define __INDEX  __attribute__((index))
  #define __SIZED  __attribute__((sized))
  #define __SEQ    __attribute__((seq))
  #define __FSEQ   __attribute__((fseq))
  #define __SEQN   __attribute__((seqn))
  #define __FSEQN  __attribute__((fseqn))
  #define __NULLTERM   __attribute__((nullterm))
  #define __ROSTRING  __attribute__((rostring))
  #define __RWSTRING  __attribute__((string))
  #define __SAFEUNION __attribute__((safeunion))
  #define __INDEXT   __attribute__((indext))
  #define __WILDT   __attribute__((wildt))
  #define __SEQT   __attribute__((seqt))
  #define __SEQNT   __attribute__((seqnt))
  #define __FSEQT   __attribute__((fseqt))
  #define __FSEQNT   __attribute__((fseqnt))
  #define __NODE
  #ifndef DISABLE_HEAPIFY
    #define __HEAPIFY __attribute__((heapify))
  #else
    #define __HEAPIFY
  #endif
  #define __DUMMYDEFN __attribute__((dummydefn))
  #define __BOXMODEL(fname) __attribute__((boxmodel(fname)))
  #define __NOBOX(block)    { __blockattribute__(nobox) block }
#endif

//#if ! defined(MANUALBOX) && ! defined(INFERBOX)
//#define calloc_fseq calloc
//#endif

#if !defined(BEFOREBOX)
  // if some code calls explicit_gc, but we're not boxing, then
  // we won't link safec{debug,}lib.a either; so let's provide
  // a dummy definition of this fn

  /* But we cannot put it here since this will end up being included several 
   * times (once before patching, and one after cabs2cil) */
  //static __inline int explicit_gc() { return 0; }
  #define explicit_gc() ((void)0)
#endif




// Now specify some special pragmas
#ifdef BEFOREBOX
#pragma boxalloc("malloc", nozero, sizein(0))
#pragma boxalloc("alloca", nozero, sizein(0))
#pragma boxalloc("calloc", zero, sizemul(0,1))

#pragma boxprintf("printf", 0)
#pragma boxprintf("fprintf", 1)
#pragma boxprintf("sprintf", 1)
#pragma boxprintf("snprintf", 2)
#pragma boxprintf("syslog", 1)

#pragma boxpoly("memcpy")

#pragma boxexported("main")
#endif


// ideally we could handle this better..
// hack: 'restrict' is a problem with glibc 2.2
#define __restrict
#define restrict


// sm: I think it's a bad idea to try to match signal's declaration since it's
// such an unusual type; and it doesn't use any types that aren't built-in

// gn: disabled this since everythign in BOX mode fails due to redefin.
//#ifdef BEFOREBOX
//  typedef void (*_box_sig_fn)(int);
//  _box_sig_fn signal_model(int signum, _box_sig_fn fn) __BOXMODEL("signal");
//  _box_sig_fn signal_model(int signum, _box_sig_fn fn)
//  {
//    // flow argument to result
//    return fn;
//  }
//#endif // BEFOREBOX


