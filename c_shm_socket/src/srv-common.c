/*
 * This file was generated by orbit-idl-2 - DO NOT EDIT!
 */

#include <string.h>
#define ORBIT2_STUBS_API
#define ORBIT_IDL_C_COMMON
#define srv_COMMON
#include "srv.h"

static const CORBA_unsigned_long ORBit_zero_int = 0;

#ifndef ORBIT_IDL_C_IMODULE_srv
void _ORBIT_skel_small_srv_add(POA_srv             *_o_servant, gpointer            _o_retval,gpointer           *_o_args,CORBA_Context       _o_ctx,CORBA_Environment  *_o_ev,
CORBA_double (*_impl_add)(PortableServer_Servant _servant, const CORBA_double i, const CORBA_double j, CORBA_Environment *ev)) {
*(CORBA_double *)_o_retval = _impl_add (_o_servant, *(const CORBA_double *)_o_args[0], *(const CORBA_double *)_o_args[1], _o_ev);
}

#endif
#if ( (TC_IMPL_TC_srv_0 == 's') \
&& (TC_IMPL_TC_srv_1 == 'r') \
&& (TC_IMPL_TC_srv_2 == 'v') \
) && !defined(TC_DEF_TC_srv)
#define TC_DEF_TC_srv 1
#ifdef ORBIT_IDL_C_IMODULE_srv
static
#endif
ORBIT2_MAYBE_CONST struct CORBA_TypeCode_struct TC_srv_struct = {
{&ORBit_TypeCode_epv, ORBIT_REFCOUNT_STATIC},
CORBA_tk_objref,
0,
0,
ORBIT_ALIGNOF_CORBA_POINTER,
0,
0
,
NULL,
CORBA_OBJECT_NIL,
(char *)"srv",
(char *)"IDL:srv:1.0",
NULL,
NULL,
-1,
0,
0, 0
};
#endif

#ifndef ORBIT_IDL_C_IMODULE_srv
CORBA_unsigned_long srv__classid = 0;
#endif

/* Interface type data */

static ORBit_IArg srv_add__arginfo [] = {
	{ TC_CORBA_double,  ORBit_I_ARG_IN | ORBit_I_COMMON_FIXED_SIZE, (char *)"i" },
	{ TC_CORBA_double,  ORBit_I_ARG_IN | ORBit_I_COMMON_FIXED_SIZE, (char *)"j" }
};

#ifdef ORBIT_IDL_C_IMODULE_srv
static
#endif
ORBit_IMethod srv__imethods [] = {
	{
		{ 2, 2, srv_add__arginfo, FALSE },
		{ 0, 0, NULL, FALSE },
		{ 0, 0, NULL, FALSE },
		TC_CORBA_double, (char *)"add", 3,
		0| ORBit_I_COMMON_FIXED_SIZE
}
};

static CORBA_string srv__base_itypes[] = {
(char *)"IDL:omg.org/CORBA/Object:1.0"
};
#ifdef ORBIT_IDL_C_IMODULE_srv
static
#endif
ORBit_IInterface srv__iinterface = {
TC_srv,{1, 1, srv__imethods, FALSE},
{1, 1, srv__base_itypes, FALSE}
};
