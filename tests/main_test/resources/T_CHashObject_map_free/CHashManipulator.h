
/*
MIT License

Copyright (c) 2023 CHashManipulator

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef CHashManipulator
#define CHashManipulator

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>




#ifndef cJSON__h

/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/


#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif

#ifdef __WINDOWS__

/* When compiling for windows, we specify a specific calling convention to avoid issues where we are being called from a project with a different default calling convention.  For windows you have 3 define options:

CJSON_HIDE_SYMBOLS - Define this in the case where you don't want to ever dllexport symbols
CJSON_EXPORT_SYMBOLS - Define this on library build when you want to dllexport symbols (default)
CJSON_IMPORT_SYMBOLS - Define this if you want to dllimport symbol

For *nix builds that support visibility attribute, you can define similar behavior by

setting default visibility to hidden by adding
-fvisibility=hidden (for gcc)
or
-xldscope=hidden (for sun cc)
to CFLAGS

then using the CJSON_API_VISIBILITY flag to "export" the same symbols the way CJSON_EXPORT_SYMBOLS does

*/

#define CJSON_CDECL __cdecl
#define CJSON_STDCALL __stdcall

/* export symbols by default, this is necessary for copy pasting the C and header file */
#if !defined(CJSON_HIDE_SYMBOLS) && !defined(CJSON_IMPORT_SYMBOLS) && !defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_EXPORT_SYMBOLS
#endif

#if defined(CJSON_HIDE_SYMBOLS)
#define CJSON_PUBLIC(type)   type CJSON_STDCALL
#elif defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllexport) type CJSON_STDCALL
#elif defined(CJSON_IMPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllimport) type CJSON_STDCALL
#endif
#else /* !__WINDOWS__ */
#define CJSON_CDECL
#define CJSON_STDCALL

#if (defined(__GNUC__) || defined(__SUNPRO_CC) || defined (__SUNPRO_C)) && defined(CJSON_API_VISIBILITY)
#define CJSON_PUBLIC(type)   __attribute__((visibility("default"))) type
#else
#define CJSON_PUBLIC(type) type
#endif
#endif

/* project version */
#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 7
#define CJSON_VERSION_PATCH 16

#include <stddef.h>

/* cJSON Types: */
#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7) /* raw json */

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

/* The cJSON structure: */
typedef struct cJSON
{
    /* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
    struct cJSON *next;
    struct cJSON *prev;
    /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */
    struct cJSON *child;

    /* The type of the item, as above. */
    int type;

    /* The item's string, if type==cJSON_String  and type == cJSON_Raw */
    char *valuestring;
    /* writing to valueint is DEPRECATED, use cJSON_SetNumberValue instead */
    int valueint;
    /* The item's number, if type==cJSON_Number */
    double valuedouble;

    /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
    char *string;
} cJSON;

typedef struct cJSON_Hooks
{
    /* malloc/free are CDECL on Windows regardless of the default calling convention of the compiler, so ensure the hooks allow passing those functions directly. */
    void *(CJSON_CDECL *malloc_fn)(size_t sz);
    void (CJSON_CDECL *free_fn)(void *ptr);
} cJSON_Hooks;

typedef int cJSON_bool;

/* Limits how deeply nested arrays/objects can be before cJSON rejects to parse them.
 * This is to prevent stack overflows. */
#ifndef CJSON_NESTING_LIMIT
#define CJSON_NESTING_LIMIT 1000
#endif

/* returns the version of cJSON as a string */
CJSON_PUBLIC(const char*) cJSON_Version(void);

/* Supply malloc, realloc and free functions to cJSON */
CJSON_PUBLIC(void) cJSON_InitHooks(cJSON_Hooks* hooks);

/* Memory Management: the caller is always responsible to free the results from all variants of cJSON_Parse (with cJSON_Delete) and cJSON_Print (with stdlib free, cJSON_Hooks.free_fn, or cJSON_free as appropriate). The exception is cJSON_PrintPreallocated, where the caller has full responsibility of the buffer. */
/* Supply a block of JSON, and this returns a cJSON object you can interrogate. */
CJSON_PUBLIC(cJSON *) cJSON_Parse(const char *value);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLength(const char *value, size_t buffer_length);
/* ParseWithOpts allows you to require (and check) that the JSON is null terminated, and to retrieve the pointer to the final byte parsed. */
/* If you supply a ptr in return_parse_end and parsing fails, then return_parse_end will contain a pointer to the error so will match cJSON_GetErrorPtr(). */
CJSON_PUBLIC(cJSON *) cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated);

/* Render a cJSON entity to text for transfer/storage. */
CJSON_PUBLIC(char *) cJSON_Print(const cJSON *item);
/* Render a cJSON entity to text for transfer/storage without any formatting. */
CJSON_PUBLIC(char *) cJSON_PrintUnformatted(const cJSON *item);
/* Render a cJSON entity to text using a buffered strategy. prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted */
CJSON_PUBLIC(char *) cJSON_PrintBuffered(const cJSON *item, int prebuffer, cJSON_bool fmt);
/* Render a cJSON entity to text using a buffer already allocated in memory with given length. Returns 1 on success and 0 on failure. */
/* NOTE: cJSON is not always 100% accurate in estimating how much memory it will use, so to be safe allocate 5 bytes more than you actually need */
CJSON_PUBLIC(cJSON_bool) cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format);
/* Delete a cJSON entity and all subentities. */
CJSON_PUBLIC(void) cJSON_Delete(cJSON *item);

/* Returns the number of items in an array (or object). */
CJSON_PUBLIC(int) cJSON_GetArraySize(const cJSON *array);
/* Retrieve item number "index" from array "array". Returns NULL if unsuccessful. */
CJSON_PUBLIC(cJSON *) cJSON_GetArrayItem(const cJSON *array, int index);
/* Get item "string" from object. Case insensitive. */
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON_bool) cJSON_HasObjectItem(const cJSON *object, const char *string);
/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when cJSON_Parse() returns 0. 0 when cJSON_Parse() succeeds. */
CJSON_PUBLIC(const char *) cJSON_GetErrorPtr(void);

/* Check item type and return its value */
CJSON_PUBLIC(char *) cJSON_GetStringValue(const cJSON * const item);
CJSON_PUBLIC(double) cJSON_GetNumberValue(const cJSON * const item);

/* These functions check the type of an item */
CJSON_PUBLIC(cJSON_bool) cJSON_IsInvalid(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsFalse(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsTrue(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsBool(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNull(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNumber(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsString(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsArray(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsObject(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsRaw(const cJSON * const item);

/* These calls create a cJSON item of the appropriate type. */
CJSON_PUBLIC(cJSON *) cJSON_CreateNull(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateTrue(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateFalse(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateBool(cJSON_bool boolean);
CJSON_PUBLIC(cJSON *) cJSON_CreateNumber(double num);
CJSON_PUBLIC(cJSON *) cJSON_CreateString(const char *string);
/* raw json */
CJSON_PUBLIC(cJSON *) cJSON_CreateRaw(const char *raw);
CJSON_PUBLIC(cJSON *) cJSON_CreateArray(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateObject(void);

/* Create a string where valuestring references a string so
 * it will not be freed by cJSON_Delete */
CJSON_PUBLIC(cJSON *) cJSON_CreateStringReference(const char *string);
/* Create an object/array that only references it's elements so
 * they will not be freed by cJSON_Delete */
CJSON_PUBLIC(cJSON *) cJSON_CreateObjectReference(const cJSON *child);
CJSON_PUBLIC(cJSON *) cJSON_CreateArrayReference(const cJSON *child);

/* These utilities create an Array of count items.
 * The parameter count cannot be greater than the number of elements in the number array, otherwise array access will be out of bounds.*/
CJSON_PUBLIC(cJSON *) cJSON_CreateIntArray(const int *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateFloatArray(const float *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateDoubleArray(const double *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateStringArray(const char *const *strings, int count);

/* Append item to the specified array/object. */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
/* Use this when string is definitely const (i.e. a literal, or as good as), and will definitely survive the cJSON object.
 * WARNING: When this function was used, make sure to always check that (item->type & cJSON_StringIsConst) is zero before
 * writing to `item->string` */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item);
/* Append reference to item to the specified array/object. Use this when you want to add an existing cJSON to a new cJSON, but don't want to corrupt your existing cJSON. */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);

/* Remove/Detach items from Arrays/Objects. */
CJSON_PUBLIC(cJSON *) cJSON_DetachItemViaPointer(cJSON *parent, cJSON * const item);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(void) cJSON_DeleteItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObjectCaseSensitive(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string);

/* Update array items. */
CJSON_PUBLIC(cJSON_bool) cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem); /* Shifts pre-existing items to the right. */
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObject(cJSON *object,const char *string,cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object,const char *string,cJSON *newitem);

/* Duplicate a cJSON item */
CJSON_PUBLIC(cJSON *) cJSON_Duplicate(const cJSON *item, cJSON_bool recurse);
/* Duplicate will create a new, identical cJSON item to the one you pass, in new memory that will
 * need to be released. With recurse!=0, it will duplicate any children connected to the item.
 * The item->next and ->prev pointers are always zero on return from Duplicate. */
/* Recursively compare two cJSON items for equality. If either a or b is NULL or invalid, they will be considered unequal.
 * case_sensitive determines if object keys are treated case sensitive (1) or case insensitive (0) */
CJSON_PUBLIC(cJSON_bool) cJSON_Compare(const cJSON * const a, const cJSON * const b, const cJSON_bool case_sensitive);

/* Minify a strings, remove blank characters(such as ' ', '\t', '\r', '\n') from strings.
 * The input pointer json cannot point to a read-only address area, such as a string constant,
 * but should point to a readable and writable address area. */
CJSON_PUBLIC(void) cJSON_Minify(char *json);

/* Helper functions for creating and adding items to an object at the same time.
 * They return the added item or NULL on failure. */
CJSON_PUBLIC(cJSON*) cJSON_AddNullToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddTrueToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddFalseToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddBoolToObject(cJSON * const object, const char * const name, const cJSON_bool boolean);
CJSON_PUBLIC(cJSON*) cJSON_AddNumberToObject(cJSON * const object, const char * const name, const double number);
CJSON_PUBLIC(cJSON*) cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string);
CJSON_PUBLIC(cJSON*) cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw);
CJSON_PUBLIC(cJSON*) cJSON_AddObjectToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddArrayToObject(cJSON * const object, const char * const name);

/* When assigning an integer value, it needs to be propagated to valuedouble too. */
#define cJSON_SetIntValue(object, number) ((object) ? (object)->valueint = (object)->valuedouble = (number) : (number))
/* helper for the cJSON_SetNumberValue macro */
CJSON_PUBLIC(double) cJSON_SetNumberHelper(cJSON *object, double number);
#define cJSON_SetNumberValue(object, number) ((object != NULL) ? cJSON_SetNumberHelper(object, (double)number) : (number))
/* Change the valuestring of a cJSON_String object, only takes effect when type of object is cJSON_String */
CJSON_PUBLIC(char*) cJSON_SetValuestring(cJSON *object, const char *valuestring);

/* If the object is not a boolean type this does nothing and returns cJSON_Invalid else it returns the new type*/
#define cJSON_SetBoolValue(object, boolValue) ( \
    (object != NULL && ((object)->type & (cJSON_False|cJSON_True))) ? \
    (object)->type=((object)->type &(~(cJSON_False|cJSON_True)))|((boolValue)?cJSON_True:cJSON_False) : \
    cJSON_Invalid\
)

/* Macro for iterating over an array or object */
#define cJSON_ArrayForEach(element, array) for(element = (array != NULL) ? (array)->child : NULL; element != NULL; element = element->next)

/* malloc/free objects using the malloc/free functions that have been set with cJSON_InitHooks */
CJSON_PUBLIC(void *) cJSON_malloc(size_t size);
CJSON_PUBLIC(void) cJSON_free(void *object);

#ifdef __cplusplus
}
#endif


#undef cJSON__h
#endif
#ifndef CTEXTENGINE_H


#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>




#define CTextScope(s,t)\
ctext_open(s, t);\
for(int snaunduwwqwetjsdvda = 0; snaunduwwqwetjsdvda < 1; ctext_close(s, t), ++snaunduwwqwetjsdvda)

#define CText$Scope(s,t, ...)\
CTextStack_$open(s,t,__VA_ARGS__);\
for(int snaunduwwqwetjsdvda = 0; snaunduwwqwetjsdvda < 1; ctext_close(s, t), ++snaunduwwqwetjsdvda)



#define CTEXT_BY_OWNESHIP 1
#define CTEXT_BY_COPY 2
#define CTEXT_BY_REFERENCE 3

//
// Created by jurandi on 18-04-2023.
//
#define CTEXT_HTML "html"
#define CTEXT_BODY "body"
#define CTEXT_DIV "div"
#define CTEXT_H1 "h1"
#define CTEXT_H2 "h2"
#define CTEXT_H3 "h3"
#define CTEXT_H4 "h4"
#define CTEXT_H5 "h5"
#define CTEXT_H6 "h6"
#define CTEXT_P "p"
#define CTEXT_SPAN "span"
#define CTEXT_A "a"
#define CTEXT_IMG "img"
#define CTEXT_INPUT "input"
#define CTEXT_BUTTON "button"
#define CTEXT_TABLE "table"
#define CTEXT_TR "tr"
#define CTEXT_TD "td"
#define TH "th"
#define CTEXT_THEAD "thead"
#define CTEXT_TBODY "tbody"
#define CTEXT_TFOOT "tfoot"
#define CTEXT_UL "ul"
#define CTEXT_LI "li"
#define CTEXT_OL "ol"
#define CTEXT_FORM "form"
#define CTEXT_LABEL "label"
#define CTEXT_SELECT "select"
#define CTEXT_OPTION "option"
#define CTEXT_TEXTAREA "textarea"
#define CTEXT_SCRIPT "script"
#define CTEXT_STYLE "style"
#define CTEXT_META "meta"
#define CTEXT_LINK "link"
#define CTEXT_HEAD "head"
#define CTEXT_BASE "base"
#define CTEXT_BR "br"
#define CTEXT_HR "hr"
#define CTEXT_TITLE "title"
#define CTEXT_IFRAME "iframe"
#define CTEXT_NAV "nav"
#define CTEXT_HEADER "header"
#define CTEXT_FOOTER "footer"
#define CTEXT_SECTION "section"
#define CTEXT_ARTICLE "article"
#define CTEXT_ASIDE "aside"
#define CTEXT_DETAILS "details"
#define CTEXT_SUMMARY "summary"
#define CTEXT_DIALOG "dialog"
#define MENU "menu"
#define MENUITEM "menuitem"
#define CTEXT_MAIN "main"
#define CTEXT_CANVAS "canvas"
#define CTEXT_AUDIO "audio"
#define CTEXT_VIDEO "video"
#define CTEXT_SOURCE "source"
#define CTEXT_TRACK "track"
#define CTEXT_EMBED "embed"
#define CTEXT_PARAM "param"








#define CTEXT_LINE_BREAKER "\n"
#define CTEXT_SEPARATOR "   "

#define CTEXT_LONG 1
#define CTEXT_DOUBLE 2
#define CTEXT_BOOL 3
#define CTEXT_STRING 4

typedef struct CTextStack{

    char *rendered_text;
    size_t rendered_text_alocation_size;
    size_t size;

    char *line_breaker;
    char *separator;
    int ident_level;

}CTextStack;

struct CTextStack *newCTextStack(const char *line_breaker, const char *separator);


struct CTextStack *newCTextStack_string(const char *starter);

struct CTextStack *newCTextStack_string_format(const char *format, ...);

struct CTextStack *newCTextStack_string_getting_ownership(const char *starter);

struct CTextStack *newCTextStack_string_empty();


void CTextStack_text(struct CTextStack *self, const char *text);


void private_ctext_text_double_size_if_reachs(struct CTextStack *self);


void CTextStack_segment_text(struct CTextStack *self, const char *text);


void CTextStack_segment(struct CTextStack *self);


void CTextStack_$open(struct CTextStack *self, const char *tag, const char *format, ...);



void CTextStack_only$open(struct CTextStack *self, const char *tag, const char *format, ...);


void CTextStack_auto$close(struct CTextStack *self, const char *tag, const char *format, ...);


void CTextStack_format(struct CTextStack *self, const char *format, ...);


void CTextStack_segment_format(struct CTextStack *self, const char *format, ...);


void ctext_open(struct CTextStack *self, const char *tag);



void ctext_close(struct CTextStack *self, const char *tag);

void CTextStack_represent(struct CTextStack *self);
void CTextStack_free(struct CTextStack *self);


struct CTextStack * CTextStack_clone(struct CTextStack *self);


char * CTextStack_self_transform_in_string_and_self_clear(struct CTextStack *self);

void private_CTextStack_parse_ownership(struct CTextStack *self, struct CTextStack *new_string);


void CTextStack_restart(struct CTextStack *self);


//algorithm methods

struct CTextStack *CTextStack_substr(struct CTextStack *self, long starter, long end);
void CTextStack_self_substr(struct CTextStack *self, long starter, long end);


struct CTextStack *CTextStack_pop(struct CTextStack *self, long starter, long end);
void  CTextStack_self_pop(struct CTextStack *self, long starter, long end);


struct CTextStack *CTextStack_replace(struct CTextStack *self,const char *element, const char *element_to_replace);
void CTextStack_self_replace(struct CTextStack *self,const char *element, const char *element_to_replace);


struct CTextStack *CTextStack_replace_long(struct CTextStack *self,const char *element, long element_to_replace);
void CTextStack_self_replace_long(struct CTextStack *self,const char *element, long element_to_replace);

struct CTextStack *CTextStack_replace_double(struct CTextStack *self,const char *element, double element_to_replace);
void CTextStack_self_replace_double(struct CTextStack *self,const char *element, double element_to_replace);


struct CTextStack *CTextStack_insert_at(struct CTextStack *self,long point, const char *element);
void CTextStack_self_insert_at(struct CTextStack *self,long point, const char *element);


long CTextStack_index_of_char(struct  CTextStack *self, char element);
long CTextStack_index_of(struct  CTextStack *self, const char *element);

bool CTextStack_starts_with(struct  CTextStack *self, const char *element);
bool CTextStack_ends_with(struct  CTextStack *self, const char *element);

bool CTextStack_equal(struct  CTextStack *self,const char *element);

struct CTextStack *CTextStack_trim(struct CTextStack *self);
void CTextStack_self_trim(struct CTextStack *self);

struct CTextStack *CTextStack_lower(struct CTextStack *self);
void CTextStack_self_lower(struct CTextStack *self);

struct CTextStack *CTextStack_captalize(struct CTextStack *self);
void CTextStack_self_captalize(struct CTextStack *self);

struct CTextStack *CTextStack_upper(struct CTextStack *self);
void CTextStack_self_upper(struct CTextStack *self);

int CTextStack_typeof(struct CTextStack *self);

bool CTextStack_is_a_num(struct CTextStack *self);


const char * CTextStack_typeof_in_str(struct CTextStack *self);
bool  CTextStack_parse_to_bool(struct CTextStack *self);
long  CTextStack_parse_to_integer(struct CTextStack *self);
double  CTextStack_parse_to_double(struct CTextStack *self);


struct CTextStack *CTextStack_reverse(struct CTextStack *self);
void CTextStack_self_reverse(struct CTextStack *self);






long private_CText_transform_index(long size, long value);


void private_ctext_generate_formated_text(
    struct CTextStack *stack,
    const char *format,
    va_list argptr
    );



typedef struct CTextArray{

    CTextStack **stacks;
    long size;


}CTextArray;

CTextArray * newCTextArray();


void CTextArray_append(CTextArray *self,CTextStack *element);


void CTextArray_append_string(CTextArray *self,const char *element);

CTextStack * CTextArray_join(CTextArray *self,const char *separator);

CTextArray * CTextArray_split(const char *element,const char *target);

CTextArray * CTextArray_map(CTextArray *self, CTextStack *(caller)(CTextStack* element));

CTextArray * CTextArray_filter(CTextArray *self, bool (caller)(CTextStack* element));

void  CTextArray_foreach(CTextArray *self, void (*caller)(CTextStack* element));

bool CTextArray_includes(CTextArray *self,const char *element);

void  CTextArray_free(CTextArray *self);

void CTextArray_represent(CTextArray *self);





typedef struct CTextStackModule{

    //admnistrative methods
    CTextStack  *(*newStack)(const char *line_breaker, const char *separator);
    CTextStack *(*newStack_string)(const char *starter);
    CTextStack *(*newStack_string_format)(const char *format, ...);

    CTextStack *(*newStack_string_getting_ownership)(const char *starter);
    CTextStack *(*newStack_string_empty)();

    void (*free)(struct CTextStack *self);
    struct CTextStack *(*clone)(struct CTextStack *self);
    void (*represent)(struct CTextStack *self);
    char *(*self_transform_in_string_and_self_clear)(struct CTextStack *self);
    void (*restart)(struct CTextStack *self);

    //render methods
    void (*text)(struct CTextStack *self, const char *element);

    void (*segment_text)(struct CTextStack *self, const char *element);

    void (*format)(struct CTextStack *self, const char *format, ...);

    void (*segment)(struct CTextStack *self);

    void (*segment_format)(struct CTextStack *self, const char *format, ...);

    void (*$open)(struct CTextStack *self, const char *tag, const char *format,...);

    void (*only$open)(struct CTextStack *self, const char *tag, const char *format,...);

    void (*auto$close)(struct CTextStack *self, const char *tag, const char *format,...);

    void (*open)(struct CTextStack *self, const char *tag);

    void (*close)(struct CTextStack *self, const char *tag);


    //algorithm methods
    struct CTextStack * (*substr)(struct CTextStack *self, long starter, long end);
    void  (*self_substr)(struct CTextStack *self, long starter, long end);


    struct CTextStack *(*pop)(struct CTextStack *self, long starter, long end);
    void(*self_pop)(struct CTextStack *self, long starter, long end);



    struct CTextStack *(*insert_at)(struct CTextStack *self,long point, const char *element);
    void (*self_insert_at)(struct CTextStack *self,long point, const char *element);

    struct CTextStack *(*replace)(struct CTextStack *self,const char *element, const char *element_to_replace);
    void (*self_replace)(struct CTextStack *self,const char *element, const char *element_to_replace);


    struct CTextStack *(*replace_long)(struct CTextStack *self,const char *element, long element_to_replace);
    void(*self_replace_long)(struct CTextStack *self,const char *element, long element_to_replace);


    struct CTextStack *(*replace_double)(struct CTextStack *self,const char *element, double element_to_replace);
    void (*self_replace_double)(struct CTextStack *self,const char *element, double element_to_replace);


    struct CTextStack * (*lower)(struct CTextStack *self);
    void(*self_lower)(struct CTextStack *self);

    struct CTextStack * (*upper)(struct CTextStack *self);
    void(*self_upper)(struct CTextStack *self);

    struct CTextStack *(*captalize)(struct CTextStack *self);
    void (*self_captalize)(struct CTextStack *self);

    struct CTextStack * (*reverse)(struct CTextStack *self);
    void(*self_reverse)(struct CTextStack *self);

    struct CTextStack * (*trim)(struct CTextStack *self);
    void(*self_trim)(struct CTextStack *self);

    bool (*starts_with)(struct CTextStack *self, const char *element);
    bool (*ends_with)(struct CTextStack *self, const char *element);

    bool (*equal)(struct  CTextStack *self,const char *element);
    int (*typeof_element)(struct CTextStack *self);
    bool (*is_a_num)(struct CTextStack *self);

    const char * (*typeof_in_str)(struct CTextStack *self);
    bool  (*parse_to_bool)(struct CTextStack *self);
    long  (*parse_to_integer)(struct CTextStack *self);
    double  (*parse_to_double)(struct CTextStack *self);

    long (*index_of)(struct CTextStack *self, const char *element);
    long (*index_of_char)(struct CTextStack *self, char element);
}CTextStackModule;

CTextStackModule newCTextStackModule();


typedef struct CTextArrayModule{
    CTextArray *(*newArray)();
    void (*append)(CTextArray *self,CTextStack *element);
    void (*append_string)(CTextArray *self,const char *element);
    CTextStack * (*join)(CTextArray *self,const char *separator);

    CTextArray * (*map)(CTextArray *self, CTextStack *(caller)(CTextStack* element));
    CTextArray * (*filter)(CTextArray *self, bool (caller)(CTextStack* element));
    void  (*foreach)(CTextArray *self, void (*caller)(CTextStack* element));
    bool (*includes)(CTextArray *self,const char *element);
    void (*represent)(CTextArray *self);
    void (*free)(CTextArray *self);

}CTextArrayModule;

CTextArrayModule newCTextArrayModule();



typedef struct CTextNamespace{

    CTextArrayModule array;
    CTextStackModule stack;

}CTextNamespace;

CTextNamespace newCTextNamespace();


#endif



char *privateCHash_read_file(const char *filename);

int privateCHash_write_file(const char *filename, const char *value);


#define CHASH_END NULL


typedef struct CHash{

    unsigned short private_type;
    unsigned short private_reference_type;

    void *private_error;
    struct CHash *private_father;

    unsigned long private_size;

    //these is the reference system
    union {
        unsigned long private_index;
        char * private_key;
    };
    //these is the values sysstem
    union {
        CTextStack  *private_value_stack;
        double private_value_double;
        bool private_value_bool;
        struct CHash **private_sub_elements;
    };

}CHash;

enum {
    PRIVATE_CHASH_NOT_A_REFERENCE,
    PRIVATE_CHASH_ARRAY_ITEM,
    PRIVATE_CHASH_KEYVAL
};

typedef CHash CHashArray;
typedef CHash CHashObject;
typedef CHash CHashArrayOrObject;
typedef  CHash CHashStringArray;

CHash * privatenewChash_raw();



void CHash_print(CHash *self);

CHashArray * CHash_get_path(CHash *self);


CHash * CHash_copy(CHash *self);

CHash * privateCHash_copy_if_its_an_reference(CHash *self);

void CHash_free(CHash *self);

void CHash_set(CHash *self,CHash *element);

void privateCHash_free_values(CHash *self);

bool CHash_equals(CHash *element1, CHash *element2);

long CHash_get_size(CHash *self);


CHash * privateCHash_get_first_object(CHash *self);

CHash * newCHashNULL();




double  CHash_toNumber(CHash *element);


int CHash_convert_toNumber(CHash *self);

double  CHash_toNumber_converting(CHash *self);


void CHash_set_Number(CHash *self,double  value);


CHash * newCHashNumber(double value);




bool CHash_toBool(CHash *element);

int CHash_convert_toBool(CHash *self);

bool CHash_toBool_converting(CHash *self);


void CHash_set_Bool(CHash *self, bool value);


CHash * newCHashBool(bool value);




char * CHash_toString(CHashArray *element);

CTextStack  *CHashtoStack(CHash *element);

CHash * newCHashStackString(CTextStack *element);

CHash * newCHashString(const char *value);

void CHash_set_String(CHash *self, const char *value);

void CHash_set_Stack(CHash *self,CTextStack *element);




CHashArray  *newCHashArrayEmpty();

long privateCHashArray_convert_index(CHashArray *self, long index);

CHashArray * privatenewCHashArray(void *sentinel, ...);
#define  newCHashArray(...)privatenewCHashArray(NULL,__VA_ARGS__,NULL)


CHashArray * privatenewCHashStringArray(void *sentinel, ...);
#define  newCHashStringArray(...)privatenewCHashStringArray(NULL,__VA_ARGS__,NULL)
void CHashArray_append_any(CHashArray *self, CHash *element);

void CHashArray_append_long(CHashArray *self, long element);
void CHashArray_append_double(CHashArray *self, double element);
void CHashArray_append_bool(CHashArray *self, bool element);
void CHashArray_append_string(CHashArray *self, const char *element);
void CHashArray_append_stack(CHashArray *self, CTextStack *element);



void privateCHashArray_append(CHashArray *self, ...);
#define  CHashArray_append(self,...)privateCHashArray_append(self,__VA_ARGS__,NULL)


void CHashArray_switch(CHashArray *self, long index ,long target_index);

void  CHashArray_set(CHashArrayOrObject *self, long index,CHash *element);
void  CHashArray_set_long(CHashArrayOrObject *self, long index,long value);
void  CHashArray_set_double(CHashArrayOrObject *self, long index,double value);
void  CHashArray_set_bool(CHashArrayOrObject *self, long index,bool value);
void  CHashArray_set_string(CHashArrayOrObject *self, long index,const char *value);
void  CHashArray_set_stack(CHashArrayOrObject *self, long index,CTextStack *value);




void  CHashArray_remove(CHashArrayOrObject *self, long index);

CHash * CHashArray_get(CHashArray *self, long index);

void CHashArray_foreach(CHashArray *self,void  (*callback)(CHash *current));

void CHashArray_foreach_with_args(CHashArray *self,void  (*callback)(CHash *current,va_list args),...);
/*
CHashArray * CHashArray_map(CHashArray *self,CHash* (*callback)(CHash *current));

CHashArray * CHashArray_map_with_args(CHashArray *self,CHash* (*callback)(CHash *current,va_list args),...);
*/

long CHashArray_find(CHashArray *self, CHash *element);


long CHashArray_find_Number(CHashArray *self, double element);

long CHashArray_find_Bool(CHashArray *self, bool  element);

long CHashArray_find_String(CHashArray *self, const char *element);


short CHashArray_get_type(CHashArray *self, long index);



CHashArray * CHashArray_getArray(CHashObject * self, long index);

CHashObject * CHashArray_getObject(CHashObject * self, long index);


double CHashArray_getNumber(CHashArrayOrObject *self, long index);

double CHashArray_getNumber_converting(CHashArrayOrObject *self, long index);

bool CHashArray_getBool(CHashObject * self, long index);

bool CHashArray_getBool_converting(CHashObject * self, long index);

char  * CHashArray_getString(CHashObject * self, long index);

CTextStack  * CHashArray_getStack(CHashObject * self, long index);

#define CHash_for_in(var,array, scope){                                            \
        long private_size = CHash_get_size(array);                                 \
        for(int private_iter = 0; private_iter < private_size; private_iter++){    \
                CHash *var = CHashArray_get(array,private_iter);                   \
                                                                                   \
                if(Chash_errors(var)){                                             \
                    break;                                                         \
                }                                                                  \
                scope                                                              \
        }                                                                          \
    }





CHashObject* privatenewCHashObject(void * sentinel, ...);
#define newCHashObject(...) privatenewCHashObject(NULL,__VA_ARGS__,NULL)

CHashObject  * newCHashObjectEmpty();

void  CHashObject_set_any(CHashObject * self, const char *key, CHash *element);
void  CHashObject_set_long(CHashObject * self, const char *key, long value);
void  CHashObject_set_double(CHashObject * self, const char *key, double value);
void  CHashObject_set_bool(CHashObject * self, const char *key, bool value);
void  CHashObject_set_string(CHashObject * self, const char *key, const char *value);
void  CHashObject_set_Stack(CHashObject * self, const char *key,CTextStack *stack_value);



void  privateCHashObject_set(CHashObject *self , ...);
#define  CHashObject_set_many(self,...)privateCHashObject_set(self,__VA_ARGS__,NULL)

void  CHashObject_set_default(CHashObject * self, const char *key, CHash *element);

void  CHashObject_remove(CHashObject *self, const char *key);

CHash * privateCHashObject_get_by_key_or_null(CHashObject * self, const char *key);

bool CHashObject_exist(CHashObject *self, const char *key);



char * CHashObject_get_key_by_index(CHashObject *self,long index);


char   * CHashObject_get_key_of_element(CHash *self);


short  CHashObject_get_type(CHashObject *self, const char *key);

CHash * CHashObject_get(CHashObject * self, const char *key);


CHashArray * CHashObject_getArray(CHashObject * self, const char *key);

CHashObject * CHashObject_getObject(CHashObject * self, const char *key);


double CHashObject_getNumber(CHashObject * self, const char *key);

double CHashObject_getNumber_converting(CHashObject * self, const char *key);

bool CHashObject_getBool(CHashObject * self, const char *key);

bool CHashObject_getBool_converting(CHashObject * self, const char *key);


char  * CHashObject_getString(CHashObject * self, const char *key);


CTextStack * CHashObject_getStack(CHashObject * self, const char *key);




#define CHASH_NOT_EXIST -1

enum{
    CHASH_NULL,
    CHASH_ARRAY,
    CHASH_OBJECT,
    CHASH_NUMBER,
    CHASH_BOOL,
    CHASH_STRING
};

short CHash_get_type(CHash *self);

const char  *private_Chash_convert_type(long type);




cJSON * privateCHash_dumps_json_object(CHashObject *object);

cJSON * privateCHash_dumps_json_array(CHashArray *object);

cJSON * CHash_dump_to_cJSON(CHash *element);


char * CHash_dump_to_json_string(CHash * element);

int  CHash_dump_to_json_file(CHash *element,const char *filename);

//loaders

CHash  * privateCHash_load_json_object(cJSON *element);

CHash  * privateCHash_load_json_array(cJSON *element);


CHash * CHash_load_from_cJSON(cJSON *element);

CHash * CHash_load_from_json_strimg(const char *element);

CHash * CHash_load_from_json_file(const char *filename);








#define  CHASH_CODE "code"
#define  CHASH_MESSAGE "message"

#define  CHASH_FILE_NOT_FOUND 300
#define  CHASH_NOT_VALID_JSON 301
#define CHASH_ELEMENT_NOT_EXIST 400
#define CHASH_WRONG_TYPE 401
#define  CHASH_NOT_HAVE_KEY 402
#define  CHASH_NOT_ITERABLE 403
#define CHASH_NOT_VALID_INDEX 404
#define  CHASH_ELEMENT_IS_NULL 405
#define  CHASH_LOWER_NUMBER 406
#define  CHASH_INVALID_KEY 406
#define CHASH_LOWER_THAN_MIN 407
#define  CHASH_HIGHER_THAN_MIN 408
#define  CHASH_NOT_IN_VALID_CHARS 409
#define  CHASH_NOT_LONG 410
#define CHASH_NOT_SIZE 411





typedef struct privateCHashError{
    CHash *args;
    int error_code;
    CTextStack * error_mensage;
}privateCHashError;

privateCHashError * privatenewCHashError(CHashObject *args, int error_code, const char *error_menssage);

CTextStack * privateCHashError_create_menssage(CHashObject *args, int error_code, const char *error_mensage);

void CHash_generate_custom_error(CHash  *self, CHashArray *error);

void CHash_generate_custom_error_cleaning_args(CHash  *self, CHashArray *error);


void privateCHashError_free(privateCHashError *self);

bool Chash_errors(CHash *self);

#define CHash_protected(element) if(!Chash_errors(element))

#define CHash_catch(element) if(Chash_errors(element))


void CHash_raise_error(CHash *self,int error_code,const char *error_menssage, CHash *args);

void CHash_raise_error_by_key(CHash *self,const char *key, int error_code,const char *error_menssage, CHash *args);

void CHash_raise_error_by_index(CHash *self,long index, int error_code,const char *error_menssage, CHash *args);


char * CHash_get_error_menssage(CHash *self);


int CHash_get_error_code(CHash *self);

CHash * CHash_get_error_args(CHash *self);


privateCHashError * privateCHashError_get_error(CHash *self);


int private_chash_check_type(CHash *element, unsigned short  expected_type);

int CHash_ensure_Number(CHash *element);
int CHash_ensure_Number_by_key(CHash *object, const char *key);
int CHash_ensure_Number_by_index(CHash *array, long index);

int CHash_ensure_Long(CHash *element);
int CHash_ensure_Long_by_key(CHash *object, const char *key);
int CHash_ensure_Long_by_index(CHash *array, long index);


int CHash_ensure_min_value(CHash *element, double  min);
int CHash_ensure_min_value_by_key(CHash *object, const char *key, double min );
int CHash_ensure_min_value_by_index(CHash *array, long index, double min);


int CHash_ensure_max_value(CHash *element, double  max);
int CHash_ensure_max_value_by_key(CHash *object, const char *key, double  max);
int CHash_ensure_max_value_by_index(CHash *array, long index, double  max);




int CHash_ensure_Bool(CHash *element);
int CHash_ensure_Bool_by_key(CHash *object , const char *key);
int CHash_ensure_Bool_by_index(CHash *array , long index);

int CHash_ensure_String(CHash *element);
int Chash_ensure_only_chars(CHash *element, const char *seq);

int CHash_ensure_String_by_key(CHash *object , const char *key);
int CHash_ensure_String_by_index(CHash *array , long index);

int CHash_ensure_Object(CHash *element);
int CHash_ensure_Object_by_key(CHash *object , const char *key);
int CHash_ensure_Object_by_index(CHash *array , long index);

int CHash_ensure_only_keys(CHashObject *object, CHashStringArray *keys);
int CHash_ensure_only_keys_cleaning_args(CHashObject *object, CHashStringArray *keys);


int CHash_ensure_Array(CHash *element);
int CHash_ensure_Array_by_key(CHash *object , const char *key);
int CHash_ensure_Array_by_index(CHash *array , long index);

int CHash_ensure_all_types(CHash *element, short expected_type);
int CHash_ensure_all_String(CHash *element);
int CHash_ensure_all_Numbers(CHash *element);
int CHash_ensure_all_Bool(CHash *element);


int CHash_ensure_min_size(CHash *iterable,long min);
int CHash_ensure_min_size_by_key(CHash  *object, const char *key,long min);
int CHash_ensure_min_size_by_index(CHash  *array, long index,long  min);

int CHash_ensure_size(CHash *iterable,long size);
int CHash_ensure_size_by_key(CHash  *object, const char *key,long size);
int CHash_ensure_size_by_index(CHash  *array, long index,long  size);

int CHash_ensure_max_size(CHash *iterable,long max);
int CHash_ensure_max_size_by_key(CHash  *object, const char *key,long max);
int CHash_ensure_max_size_by_index(CHash  *array, long index,long  max);





int privateCHash_ensureArrayOrObject(CHash *element);





typedef struct CHashObjectModule{

    CHashObject  * (*newObjectEmpty)();
    void  (*set_any)(CHashObject * self, const char *key, CHash *element);
    void  (*set_long)(CHashObject * self, const char *key, long value);
    void  (*set_double)(CHashObject * self, const char *key, double value);
    void  (*set_bool)(CHashObject * self, const char *key, bool value);
    void  (*set_string)(CHashObject * self, const char *key, const char *value);
    void  (*set_Stack)(CHashObject * self, const char *key,CTextStack *stack_value);


    void  (*set_default)(CHashObject * self, const char *key, CHash *element);

    void  (*remove)(CHashObject *self, const char *key);

    char * (*get_key_by_index)(CHashObject *self,long index);

    char   * (*get_key_of_element)(CHash *self);

    short  (*get_type)(CHashObject *self, const char *key);
    bool (*exist)(CHashObject *self, const char *key);

    CHash * (*get)(CHashObject * self, const char *key);

    CHashArray * (*getArray)(CHashObject * self, const char *key);

    CHashObject * (*getObject)(CHashObject * self, const char *key);

    double (*getNumber)(CHashObject * self, const char *key);
    double (*getNumber_converting)(CHashObject * self, const char *key);

    bool (*getBool)(CHashObject * self, const char *key);
    bool (*getBool_converting)(CHashObject * self, const char *key);

    char  * (*getString)(CHashObject * self, const char *key);
    CTextStack * (*getStack)(CHashObject * self, const char *key);



}CHashObjectModule;

CHashObjectModule newCHashObjectModule();



typedef struct CHashArrayModule{

    CHashArray  *(*newArrayEmpty)();
    void (*append_any)(CHashArray *self, CHash *element);
    void (*append_long)(CHashArray *self, long element);
    void (*append_double)(CHashArray *self, double element);
    void (*append_bool)(CHashArray *self, bool element);
    void (*append_string)(CHashArray *self, const char *element);
    void (*append_stack)(CHashArray *self, CTextStack *element);


    void  (*set)(CHashArrayOrObject *self, long index,CHash *element);
    void  (*set_long)(CHashArrayOrObject *self, long index,long value);
    void  (*set_double)(CHashArrayOrObject *self, long index,double value);
    void  (*set_bool)(CHashArrayOrObject *self, long index,bool value);
    void  (*set_string)(CHashArrayOrObject *self, long index,const char *value);
    void  (*set_stack)(CHashArrayOrObject *self, long index,CTextStack *value);


    void  (*remove)(CHashArrayOrObject *self, long index);
    CHash * (*get)(CHashArrayOrObject *self, long position);
    long (*find)(CHashArray *self, CHash *element);
    long (*find_Number)(CHashArray *self, double element);
    long (*find_Bool)(CHashArray *self, bool  element);
    long (*find_String)(CHashArray *self, const char *element);
    void (*foreach)(CHashArray *self,void  (*callback)(CHash *current));
    void (*foreach_with_args)(CHashArray *self,void  (*callback)(CHash *current,va_list args),...);
    //CHashArray * (*map)(CHashArray *self,CHash* (*callback)(CHash *current));
    //CHashArray * (*map_with_args)(CHashArray *self,CHash* (*callback)(CHash *current,va_list args),...);


    short (*get_type)(CHashArrayOrObject *self, long index);

    CHashArray * (*getArray)(CHashArrayOrObject * self, long index);
    CHashObject * (*getObject)(CHashArrayOrObject * self, long index);

    double (*getNumber)(CHashArrayOrObject * self, long index);
    double (*getNumber_converting)(CHashArrayOrObject *self, long index);

    bool (*getBool)(CHashArrayOrObject * self, long index);
    bool (*getBool_converting)(CHashObject * self, long index);
    char  * (*getString)(CHashArrayOrObject * self, long index);
    CTextStack  * (*getStack)(CHashObject * self, long index);

}CHashArrayModule;

CHashArrayModule newCHashArrayModule();



typedef struct CHashValidatorModule {
    void (*raise_error)(CHash *self,int error_code,const char *error_menssage, CHash *args);

    void (*raise_error_by_key)(CHash *self,const char *key, int error_code,const char *error_menssage, CHash *args);
    void (*raise_error_by_index)(CHash *self,long index, int error_code,const char *error_menssage, CHash *args);
    void (*generate_custom_error)(CHash  *self, CHashArray *error);
    void (*generate_custom_error_cleaning_args)(CHash  *self, CHashArray *error);

    int (*ensure_Number)(CHash *element);
    int (*ensure_Number_by_key)(CHash *object, const char *key);
    int (*ensure_Number_by_index)(CHash *array, long index);

    int (*ensure_Long)(CHash *element);
    int (*ensure_Long_by_key)(CHash *object, const char *key);
    int (*ensure_Long_by_index)(CHash *array, long index);

    int (*ensure_min_value)(CHash *element, double  min);
    int (*ensure_min_value_by_key)(CHash *object, const char *key, double min );
    int (*ensure_min_value_by_index)(CHash *array, long index, double min);


    int (*ensure_max_value)(CHash *element, double  max);
    int (*ensure_max_value_by_key)(CHash *object, const char *key, double  max);
    int (*ensure_max_value_by_index)(CHash *array, long index, double  max);

    int (*ensure_Bool)(CHash *element);
    int (*ensure_Bool_by_key)(CHash *object , const char *key);
    int (*ensure_Bool_by_index)(CHash *array , long index);

    int (*ensure_String)(CHash *element);
    int (*ensure_String_by_key)(CHash *object , const char *key);
    int (*ensure_String_by_index)(CHash *array , long index);
    int (*ensure_only_chars)(CHash *element, const char *seq);

    int (*ensure_Object)(CHash *element);
    int (*ensure_Object_by_key)(CHash *object , const char *key);
    int (*ensure_Object_by_index)(CHash *array , long index);
    int (*ensure_only_keys)(CHashObject *object, CHashStringArray *keys);
    int (*ensure_only_keys_cleaning_args)(CHashObject *object, CHashStringArray *keys);


    int (*ensure_Array)(CHash *element);
    int (*ensure_Array_by_key)(CHash *object , const char *key);
    int (*ensure_Array_by_index)(CHash *array , long index);

    int (*ensure_all_types)(CHash *element, short expected_type);
    int (*ensure_all_String)(CHash *element);
    int (*ensure_all_Numbers)(CHash *element);
    int (*ensure_all_Bool)(CHash *element);


    int (*ensure_min_size)(CHash *iterable,long min);
    int (*ensure_min_size_by_key)(CHash  *object, const char *key,long min);
    int (*ensure_min_size_by_index)(CHash  *array, long index,long  min);

    int (*ensure_size)(CHash *iterable,long size);
    int (*ensure_size_by_key)(CHash  *object, const char *key,long size);
    int (*ensure_size_by_index)(CHash  *array, long index,long  size);


    int (*ensure_max_size)(CHash *iterable,long max);
    int (*ensure_max_size_by_key)(CHash  *object, const char *key,long max);
    int (*ensure_max_size_by_index)(CHash  *array, long index,long  max);


}CHashValidatorModule;

CHashValidatorModule newCHashValidatorModule();




typedef struct CHashNamespace{


    CHash * (*load_from_cJSON)(cJSON *element);
    CHash * (*load_from_json_strimg)(const char *element);
    CHash * (*load_from_json_file)(const char *filename);


    cJSON * (*dump_to_cJSON)(CHash *element);
    char * (*dump_to_json_string)(CHash * element);
    int  (*dump_to_json_file)(CHash *element,const char *filename);
    void (*set)(CHash *self,CHash *element);


    CHash * (*newBool)(bool value);
    bool (*toBool)(CHash *element);
    int (*convert_toBool)(CHash *self);
    bool (*toBool_converting)(CHash *self);

    void (*set_Bool)(CHash *self, bool value);



    CHash * (*newNumber)(double value);
    double  (*toNumber)(CHash *element);
    void (*set_Number)(CHash *self,double  value);
    int (*convert_toNumber)(CHash *self);
    double  (*toNumber_converting)(CHash *self);


    CHash * (*newStackString)(CTextStack *element);
    CTextStack  *(*toStack)(CHash *element);
    void (*set_String)(CHash *self, const char *value);
    void (*set_Stack)(CHash *self,CTextStack *element);


    CHash * (*newString)(const char *value);
    char * (*toString)(CHashArray *element);
    CHash * (*newNULL)();

    void (*print)(CHash *self);
    CHashArray * (*get_path)(CHash *self);
    CHash * (*copy)(CHash *self);

    bool (*errors)(CHash *self);
    char * (*get_error_menssage)(CHash *self);
    int (*get_error_code)(CHash *self);
    CHash * (*get_error_args)(CHash *self);



    bool (*equals)(CHash *element1, CHash *element2);

    long (*get_size)(CHash *self);

    short (*get_type)(CHash *self);


    void (*free)(CHash *self);

    CHashObjectModule  object;
    CHashArrayModule array;
    CHashValidatorModule validator;
}CHashNamespace;

CHashNamespace newCHashNamespace();






#ifndef cJSON__h
#define cJSON__h

/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

/* cJSON */
/* JSON parser in C. */

/* disable warnings about old C89 functions in MSVC */
#if !defined(_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif
#if defined(_MSC_VER)
#pragma warning (push)
/* disable warning about single line comments in system headers */
#pragma warning (disable : 4001)
#endif

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <float.h>

#ifdef ENABLE_LOCALES
#include <locale.h>
#endif

#if defined(_MSC_VER)
#pragma warning (pop)
#endif
#ifdef __GNUC__
#pragma GCC visibility pop
#endif


/* define our own boolean type */
#ifdef true
#undef true
#endif
#define true ((cJSON_bool)1)

#ifdef false
#undef false
#endif
#define false ((cJSON_bool)0)

/* define isnan and isinf for ANSI C, if in C99 or above, isnan and isinf has been defined in math.h */
#ifndef isinf
#define isinf(d) (isnan((d - d)) && !isnan(d))
#endif
#ifndef isnan
#define isnan(d) (d != d)
#endif

#ifndef NAN
#ifdef _WIN32
#define NAN sqrt(-1.0)
#else
#define NAN 0.0/0.0
#endif
#endif

typedef struct {
    const unsigned char *json;
    size_t position;
} error;
static error global_error = { NULL, 0 };

CJSON_PUBLIC(const char *) cJSON_GetErrorPtr(void)
{
    return (const char*) (global_error.json + global_error.position);
}

CJSON_PUBLIC(char *) cJSON_GetStringValue(const cJSON * const item)
{
    if (!cJSON_IsString(item))
    {
        return NULL;
    }

    return item->valuestring;
}

CJSON_PUBLIC(double) cJSON_GetNumberValue(const cJSON * const item)
{
    if (!cJSON_IsNumber(item))
    {
        return (double) NAN;
    }

    return item->valuedouble;
}

/* This is a safeguard to prevent copy-pasters from using incompatible C and header files */
#if (CJSON_VERSION_MAJOR != 1) || (CJSON_VERSION_MINOR != 7) || (CJSON_VERSION_PATCH != 16)
#error cJSON.h and cJSON.c have different versions. Make sure that both have the same.
#endif

CJSON_PUBLIC(const char*) cJSON_Version(void)
{
    static char version[15];
    sprintf(version, "%i.%i.%i", CJSON_VERSION_MAJOR, CJSON_VERSION_MINOR, CJSON_VERSION_PATCH);

    return version;
}

/* Case insensitive string comparison, doesn't consider two NULL pointers equal though */
static int case_insensitive_strcmp(const unsigned char *string1, const unsigned char *string2)
{
    if ((string1 == NULL) || (string2 == NULL))
    {
        return 1;
    }

    if (string1 == string2)
    {
        return 0;
    }

    for(; tolower(*string1) == tolower(*string2); (void)string1++, string2++)
    {
        if (*string1 == '\0')
        {
            return 0;
        }
    }

    return tolower(*string1) - tolower(*string2);
}

typedef struct internal_hooks
{
    void *(CJSON_CDECL *allocate)(size_t size);
    void (CJSON_CDECL *deallocate)(void *pointer);
    void *(CJSON_CDECL *reallocate)(void *pointer, size_t size);
} internal_hooks;

#if defined(_MSC_VER)
/* work around MSVC error C2322: '...' address of dllimport '...' is not static */
static void * CJSON_CDECL internal_malloc(size_t size)
{
    return malloc(size);
}
static void CJSON_CDECL internal_free(void *pointer)
{
    free(pointer);
}
static void * CJSON_CDECL internal_realloc(void *pointer, size_t size)
{
    return realloc(pointer, size);
}
#else
#define internal_malloc malloc
#define internal_free free
#define internal_realloc realloc
#endif

/* strlen of character literals resolved at compile time */
#define static_strlen(string_literal) (sizeof(string_literal) - sizeof(""))

static internal_hooks global_hooks = { internal_malloc, internal_free, internal_realloc };

static unsigned char* cJSON_strdup(const unsigned char* string, const internal_hooks * const hooks)
{
    size_t length = 0;
    unsigned char *copy = NULL;

    if (string == NULL)
    {
        return NULL;
    }

    length = strlen((const char*)string) + sizeof("");
    copy = (unsigned char*)hooks->allocate(length);
    if (copy == NULL)
    {
        return NULL;
    }
    memcpy(copy, string, length);

    return copy;
}

CJSON_PUBLIC(void) cJSON_InitHooks(cJSON_Hooks* hooks)
{
    if (hooks == NULL)
    {
        /* Reset hooks */
        global_hooks.allocate = malloc;
        global_hooks.deallocate = free;
        global_hooks.reallocate = realloc;
        return;
    }

    global_hooks.allocate = malloc;
    if (hooks->malloc_fn != NULL)
    {
        global_hooks.allocate = hooks->malloc_fn;
    }

    global_hooks.deallocate = free;
    if (hooks->free_fn != NULL)
    {
        global_hooks.deallocate = hooks->free_fn;
    }

    /* use realloc only if both free and malloc are used */
    global_hooks.reallocate = NULL;
    if ((global_hooks.allocate == malloc) && (global_hooks.deallocate == free))
    {
        global_hooks.reallocate = realloc;
    }
}

/* Internal constructor. */
static cJSON *cJSON_New_Item(const internal_hooks * const hooks)
{
    cJSON* node = (cJSON*)hooks->allocate(sizeof(cJSON));
    if (node)
    {
        memset(node, '\0', sizeof(cJSON));
    }

    return node;
}

/* Delete a cJSON structure. */
CJSON_PUBLIC(void) cJSON_Delete(cJSON *item)
{
    cJSON *next = NULL;
    while (item != NULL)
    {
        next = item->next;
        if (!(item->type & cJSON_IsReference) && (item->child != NULL))
        {
            cJSON_Delete(item->child);
        }
        if (!(item->type & cJSON_IsReference) && (item->valuestring != NULL))
        {
            global_hooks.deallocate(item->valuestring);
        }
        if (!(item->type & cJSON_StringIsConst) && (item->string != NULL))
        {
            global_hooks.deallocate(item->string);
        }
        global_hooks.deallocate(item);
        item = next;
    }
}

/* get the decimal point character of the current locale */
static unsigned char get_decimal_point(void)
{
#ifdef ENABLE_LOCALES
    struct lconv *lconv = localeconv();
    return (unsigned char) lconv->decimal_point[0];
#else
    return '.';
#endif
}

typedef struct
{
    const unsigned char *content;
    size_t length;
    size_t offset;
    size_t depth; /* How deeply nested (in arrays/objects) is the input at the current offset. */
    internal_hooks hooks;
} parse_buffer;

/* check if the given size is left to read in a given parse buffer (starting with 1) */
#define can_read(buffer, size) ((buffer != NULL) && (((buffer)->offset + size) <= (buffer)->length))
/* check if the buffer can be accessed at the given index (starting with 0) */
#define can_access_at_index(buffer, index) ((buffer != NULL) && (((buffer)->offset + index) < (buffer)->length))
#define cannot_access_at_index(buffer, index) (!can_access_at_index(buffer, index))
/* get a pointer to the buffer at the position */
#define buffer_at_offset(buffer) ((buffer)->content + (buffer)->offset)

/* Parse the input text to generate a number, and populate the result into item. */
static cJSON_bool parse_number(cJSON * const item, parse_buffer * const input_buffer)
{
    double number = 0;
    unsigned char *after_end = NULL;
    unsigned char number_c_string[64];
    unsigned char decimal_point = get_decimal_point();
    size_t i = 0;

    if ((input_buffer == NULL) || (input_buffer->content == NULL))
    {
        return false;
    }

    /* copy the number into a temporary buffer and replace '.' with the decimal point
     * of the current locale (for strtod)
     * This also takes care of '\0' not necessarily being available for marking the end of the input */
    for (i = 0; (i < (sizeof(number_c_string) - 1)) && can_access_at_index(input_buffer, i); i++)
    {
        switch (buffer_at_offset(input_buffer)[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '+':
            case '-':
            case 'e':
            case 'E':
                number_c_string[i] = buffer_at_offset(input_buffer)[i];
                break;

            case '.':
                number_c_string[i] = decimal_point;
                break;

            default:
                goto loop_end;
        }
    }
    loop_end:
    number_c_string[i] = '\0';

    number = strtod((const char*)number_c_string, (char**)&after_end);
    if (number_c_string == after_end)
    {
        return false; /* parse_error */
    }

    item->valuedouble = number;

    /* use saturation in case of overflow */
    if (number >= INT_MAX)
    {
        item->valueint = INT_MAX;
    }
    else if (number <= (double)INT_MIN)
    {
        item->valueint = INT_MIN;
    }
    else
    {
        item->valueint = (int)number;
    }

    item->type = cJSON_Number;

    input_buffer->offset += (size_t)(after_end - number_c_string);
    return true;
}

/* don't ask me, but the original cJSON_SetNumberValue returns an integer or double */
CJSON_PUBLIC(double) cJSON_SetNumberHelper(cJSON *object, double number)
{
    if (number >= INT_MAX)
    {
        object->valueint = INT_MAX;
    }
    else if (number <= (double)INT_MIN)
    {
        object->valueint = INT_MIN;
    }
    else
    {
        object->valueint = (int)number;
    }

    return object->valuedouble = number;
}

CJSON_PUBLIC(char*) cJSON_SetValuestring(cJSON *object, const char *valuestring)
{
    char *copy = NULL;
    /* if object's type is not cJSON_String or is cJSON_IsReference, it should not set valuestring */
    if (!(object->type & cJSON_String) || (object->type & cJSON_IsReference))
    {
        return NULL;
    }
    if (strlen(valuestring) <= strlen(object->valuestring))
    {
        strcpy(object->valuestring, valuestring);
        return object->valuestring;
    }
    copy = (char*) cJSON_strdup((const unsigned char*)valuestring, &global_hooks);
    if (copy == NULL)
    {
        return NULL;
    }
    if (object->valuestring != NULL)
    {
        cJSON_free(object->valuestring);
    }
    object->valuestring = copy;

    return copy;
}

typedef struct
{
    unsigned char *buffer;
    size_t length;
    size_t offset;
    size_t depth; /* current nesting depth (for formatted printing) */
    cJSON_bool noalloc;
    cJSON_bool format; /* is this print a formatted print */
    internal_hooks hooks;
} printbuffer;

/* realloc printbuffer if necessary to have at least "needed" bytes more */
static unsigned char* ensure(printbuffer * const p, size_t needed)
{
    unsigned char *newbuffer = NULL;
    size_t newsize = 0;

    if ((p == NULL) || (p->buffer == NULL))
    {
        return NULL;
    }

    if ((p->length > 0) && (p->offset >= p->length))
    {
        /* make sure that offset is valid */
        return NULL;
    }

    if (needed > INT_MAX)
    {
        /* sizes bigger than INT_MAX are currently not supported */
        return NULL;
    }

    needed += p->offset + 1;
    if (needed <= p->length)
    {
        return p->buffer + p->offset;
    }

    if (p->noalloc) {
        return NULL;
    }

    /* calculate new buffer size */
    if (needed > (INT_MAX / 2))
    {
        /* overflow of int, use INT_MAX if possible */
        if (needed <= INT_MAX)
        {
            newsize = INT_MAX;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        newsize = needed * 2;
    }

    if (p->hooks.reallocate != NULL)
    {
        /* reallocate with realloc if available */
        newbuffer = (unsigned char*)p->hooks.reallocate(p->buffer, newsize);
        if (newbuffer == NULL)
        {
            p->hooks.deallocate(p->buffer);
            p->length = 0;
            p->buffer = NULL;

            return NULL;
        }
    }
    else
    {
        /* otherwise reallocate manually */
        newbuffer = (unsigned char*)p->hooks.allocate(newsize);
        if (!newbuffer)
        {
            p->hooks.deallocate(p->buffer);
            p->length = 0;
            p->buffer = NULL;

            return NULL;
        }

        memcpy(newbuffer, p->buffer, p->offset + 1);
        p->hooks.deallocate(p->buffer);
    }
    p->length = newsize;
    p->buffer = newbuffer;

    return newbuffer + p->offset;
}

/* calculate the new length of the string in a printbuffer and update the offset */
static void update_offset(printbuffer * const buffer)
{
    const unsigned char *buffer_pointer = NULL;
    if ((buffer == NULL) || (buffer->buffer == NULL))
    {
        return;
    }
    buffer_pointer = buffer->buffer + buffer->offset;

    buffer->offset += strlen((const char*)buffer_pointer);
}

/* securely comparison of floating-point variables */
static cJSON_bool compare_double(double a, double b)
{
    double maxVal = fabs(a) > fabs(b) ? fabs(a) : fabs(b);
    return (fabs(a - b) <= maxVal * DBL_EPSILON);
}

/* Render the number nicely from the given item into a string. */
static cJSON_bool print_number(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output_pointer = NULL;
    double d = item->valuedouble;
    int length = 0;
    size_t i = 0;
    unsigned char number_buffer[26] = {0}; /* temporary buffer to print the number into */
    unsigned char decimal_point = get_decimal_point();
    double test = 0.0;

    if (output_buffer == NULL)
    {
        return false;
    }

    /* This checks for NaN and Infinity */
    if (isnan(d) || isinf(d))
    {
        length = sprintf((char*)number_buffer, "null");
    }
    else if(d == (double)item->valueint)
    {
        length = sprintf((char*)number_buffer, "%d", item->valueint);
    }
    else
    {
        /* Try 15 decimal places of precision to avoid nonsignificant nonzero digits */
        length = sprintf((char*)number_buffer, "%1.15g", d);

        /* Check whether the original double can be recovered */
        if ((sscanf((char*)number_buffer, "%lg", &test) != 1) || !compare_double((double)test, d))
        {
            /* If not, print with 17 decimal places of precision */
            length = sprintf((char*)number_buffer, "%1.17g", d);
        }
    }

    /* sprintf failed or buffer overrun occurred */
    if ((length < 0) || (length > (int)(sizeof(number_buffer) - 1)))
    {
        return false;
    }

    /* reserve appropriate space in the output */
    output_pointer = ensure(output_buffer, (size_t)length + sizeof(""));
    if (output_pointer == NULL)
    {
        return false;
    }

    /* copy the printed number to the output and replace locale
     * dependent decimal point with '.' */
    for (i = 0; i < ((size_t)length); i++)
    {
        if (number_buffer[i] == decimal_point)
        {
            output_pointer[i] = '.';
            continue;
        }

        output_pointer[i] = number_buffer[i];
    }
    output_pointer[i] = '\0';

    output_buffer->offset += (size_t)length;

    return true;
}

/* parse 4 digit hexadecimal number */
static unsigned parse_hex4(const unsigned char * const input)
{
    unsigned int h = 0;
    size_t i = 0;

    for (i = 0; i < 4; i++)
    {
        /* parse digit */
        if ((input[i] >= '0') && (input[i] <= '9'))
        {
            h += (unsigned int) input[i] - '0';
        }
        else if ((input[i] >= 'A') && (input[i] <= 'F'))
        {
            h += (unsigned int) 10 + input[i] - 'A';
        }
        else if ((input[i] >= 'a') && (input[i] <= 'f'))
        {
            h += (unsigned int) 10 + input[i] - 'a';
        }
        else /* invalid */
        {
            return 0;
        }

        if (i < 3)
        {
            /* shift left to make place for the next nibble */
            h = h << 4;
        }
    }

    return h;
}

/* converts a UTF-16 literal to UTF-8
 * A literal can be one or two sequences of the form \uXXXX */
static unsigned char utf16_literal_to_utf8(const unsigned char * const input_pointer, const unsigned char * const input_end, unsigned char **output_pointer)
{
    long unsigned int codepoint = 0;
    unsigned int first_code = 0;
    const unsigned char *first_sequence = input_pointer;
    unsigned char utf8_length = 0;
    unsigned char utf8_position = 0;
    unsigned char sequence_length = 0;
    unsigned char first_byte_mark = 0;

    if ((input_end - first_sequence) < 6)
    {
        /* input ends unexpectedly */
        goto fail;
    }

    /* get the first utf16 sequence */
    first_code = parse_hex4(first_sequence + 2);

    /* check that the code is valid */
    if (((first_code >= 0xDC00) && (first_code <= 0xDFFF)))
    {
        goto fail;
    }

    /* UTF16 surrogate pair */
    if ((first_code >= 0xD800) && (first_code <= 0xDBFF))
    {
        const unsigned char *second_sequence = first_sequence + 6;
        unsigned int second_code = 0;
        sequence_length = 12; /* \uXXXX\uXXXX */

        if ((input_end - second_sequence) < 6)
        {
            /* input ends unexpectedly */
            goto fail;
        }

        if ((second_sequence[0] != '\\') || (second_sequence[1] != 'u'))
        {
            /* missing second half of the surrogate pair */
            goto fail;
        }

        /* get the second utf16 sequence */
        second_code = parse_hex4(second_sequence + 2);
        /* check that the code is valid */
        if ((second_code < 0xDC00) || (second_code > 0xDFFF))
        {
            /* invalid second half of the surrogate pair */
            goto fail;
        }


        /* calculate the unicode codepoint from the surrogate pair */
        codepoint = 0x10000 + (((first_code & 0x3FF) << 10) | (second_code & 0x3FF));
    }
    else
    {
        sequence_length = 6; /* \uXXXX */
        codepoint = first_code;
    }

    /* encode as UTF-8
     * takes at maximum 4 bytes to encode:
     * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
    if (codepoint < 0x80)
    {
        /* normal ascii, encoding 0xxxxxxx */
        utf8_length = 1;
    }
    else if (codepoint < 0x800)
    {
        /* two bytes, encoding 110xxxxx 10xxxxxx */
        utf8_length = 2;
        first_byte_mark = 0xC0; /* 11000000 */
    }
    else if (codepoint < 0x10000)
    {
        /* three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx */
        utf8_length = 3;
        first_byte_mark = 0xE0; /* 11100000 */
    }
    else if (codepoint <= 0x10FFFF)
    {
        /* four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx */
        utf8_length = 4;
        first_byte_mark = 0xF0; /* 11110000 */
    }
    else
    {
        /* invalid unicode codepoint */
        goto fail;
    }

    /* encode as utf8 */
    for (utf8_position = (unsigned char)(utf8_length - 1); utf8_position > 0; utf8_position--)
    {
        /* 10xxxxxx */
        (*output_pointer)[utf8_position] = (unsigned char)((codepoint | 0x80) & 0xBF);
        codepoint >>= 6;
    }
    /* encode first byte */
    if (utf8_length > 1)
    {
        (*output_pointer)[0] = (unsigned char)((codepoint | first_byte_mark) & 0xFF);
    }
    else
    {
        (*output_pointer)[0] = (unsigned char)(codepoint & 0x7F);
    }

    *output_pointer += utf8_length;

    return sequence_length;

    fail:
    return 0;
}

/* Parse the input text into an unescaped cinput, and populate item. */
static cJSON_bool parse_string(cJSON * const item, parse_buffer * const input_buffer)
{
    const unsigned char *input_pointer = buffer_at_offset(input_buffer) + 1;
    const unsigned char *input_end = buffer_at_offset(input_buffer) + 1;
    unsigned char *output_pointer = NULL;
    unsigned char *output = NULL;

    /* not a string */
    if (buffer_at_offset(input_buffer)[0] != '\"')
    {
        goto fail;
    }

    {
        /* calculate approximate size of the output (overestimate) */
        size_t allocation_length = 0;
        size_t skipped_bytes = 0;
        while (((size_t)(input_end - input_buffer->content) < input_buffer->length) && (*input_end != '\"'))
        {
            /* is escape sequence */
            if (input_end[0] == '\\')
            {
                if ((size_t)(input_end + 1 - input_buffer->content) >= input_buffer->length)
                {
                    /* prevent buffer overflow when last input character is a backslash */
                    goto fail;
                }
                skipped_bytes++;
                input_end++;
            }
            input_end++;
        }
        if (((size_t)(input_end - input_buffer->content) >= input_buffer->length) || (*input_end != '\"'))
        {
            goto fail; /* string ended unexpectedly */
        }

        /* This is at most how much we need for the output */
        allocation_length = (size_t) (input_end - buffer_at_offset(input_buffer)) - skipped_bytes;
        output = (unsigned char*)input_buffer->hooks.allocate(allocation_length + sizeof(""));
        if (output == NULL)
        {
            goto fail; /* allocation failure */
        }
    }

    output_pointer = output;
    /* loop through the string literal */
    while (input_pointer < input_end)
    {
        if (*input_pointer != '\\')
        {
            *output_pointer++ = *input_pointer++;
        }
            /* escape sequence */
        else
        {
            unsigned char sequence_length = 2;
            if ((input_end - input_pointer) < 1)
            {
                goto fail;
            }

            switch (input_pointer[1])
            {
                case 'b':
                    *output_pointer++ = '\b';
                    break;
                case 'f':
                    *output_pointer++ = '\f';
                    break;
                case 'n':
                    *output_pointer++ = '\n';
                    break;
                case 'r':
                    *output_pointer++ = '\r';
                    break;
                case 't':
                    *output_pointer++ = '\t';
                    break;
                case '\"':
                case '\\':
                case '/':
                    *output_pointer++ = input_pointer[1];
                    break;

                    /* UTF-16 literal */
                case 'u':
                    sequence_length = utf16_literal_to_utf8(input_pointer, input_end, &output_pointer);
                    if (sequence_length == 0)
                    {
                        /* failed to convert UTF16-literal to UTF-8 */
                        goto fail;
                    }
                    break;

                default:
                    goto fail;
            }
            input_pointer += sequence_length;
        }
    }

    /* zero terminate the output */
    *output_pointer = '\0';

    item->type = cJSON_String;
    item->valuestring = (char*)output;

    input_buffer->offset = (size_t) (input_end - input_buffer->content);
    input_buffer->offset++;

    return true;

    fail:
    if (output != NULL)
    {
        input_buffer->hooks.deallocate(output);
    }

    if (input_pointer != NULL)
    {
        input_buffer->offset = (size_t)(input_pointer - input_buffer->content);
    }

    return false;
}

/* Render the cstring provided to an escaped version that can be printed. */
static cJSON_bool print_string_ptr(const unsigned char * const input, printbuffer * const output_buffer)
{
    const unsigned char *input_pointer = NULL;
    unsigned char *output = NULL;
    unsigned char *output_pointer = NULL;
    size_t output_length = 0;
    /* numbers of additional characters needed for escaping */
    size_t escape_characters = 0;

    if (output_buffer == NULL)
    {
        return false;
    }

    /* empty string */
    if (input == NULL)
    {
        output = ensure(output_buffer, sizeof("\"\""));
        if (output == NULL)
        {
            return false;
        }
        strcpy((char*)output, "\"\"");

        return true;
    }

    /* set "flag" to 1 if something needs to be escaped */
    for (input_pointer = input; *input_pointer; input_pointer++)
    {
        switch (*input_pointer)
        {
            case '\"':
            case '\\':
            case '\b':
            case '\f':
            case '\n':
            case '\r':
            case '\t':
                /* one character escape sequence */
                escape_characters++;
                break;
            default:
                if (*input_pointer < 32)
                {
                    /* UTF-16 escape sequence uXXXX */
                    escape_characters += 5;
                }
                break;
        }
    }
    output_length = (size_t)(input_pointer - input) + escape_characters;

    output = ensure(output_buffer, output_length + sizeof("\"\""));
    if (output == NULL)
    {
        return false;
    }

    /* no characters have to be escaped */
    if (escape_characters == 0)
    {
        output[0] = '\"';
        memcpy(output + 1, input, output_length);
        output[output_length + 1] = '\"';
        output[output_length + 2] = '\0';

        return true;
    }

    output[0] = '\"';
    output_pointer = output + 1;
    /* copy the string */
    for (input_pointer = input; *input_pointer != '\0'; (void)input_pointer++, output_pointer++)
    {
        if ((*input_pointer > 31) && (*input_pointer != '\"') && (*input_pointer != '\\'))
        {
            /* normal character, copy */
            *output_pointer = *input_pointer;
        }
        else
        {
            /* character needs to be escaped */
            *output_pointer++ = '\\';
            switch (*input_pointer)
            {
                case '\\':
                    *output_pointer = '\\';
                    break;
                case '\"':
                    *output_pointer = '\"';
                    break;
                case '\b':
                    *output_pointer = 'b';
                    break;
                case '\f':
                    *output_pointer = 'f';
                    break;
                case '\n':
                    *output_pointer = 'n';
                    break;
                case '\r':
                    *output_pointer = 'r';
                    break;
                case '\t':
                    *output_pointer = 't';
                    break;
                default:
                    /* escape and print as unicode codepoint */
                    sprintf((char*)output_pointer, "u%04x", *input_pointer);
                    output_pointer += 4;
                    break;
            }
        }
    }
    output[output_length + 1] = '\"';
    output[output_length + 2] = '\0';

    return true;
}

/* Invoke print_string_ptr (which is useful) on an item. */
static cJSON_bool print_string(const cJSON * const item, printbuffer * const p)
{
    return print_string_ptr((unsigned char*)item->valuestring, p);
}

/* Predeclare these prototypes. */
static cJSON_bool parse_value(cJSON * const item, parse_buffer * const input_buffer);
static cJSON_bool print_value(const cJSON * const item, printbuffer * const output_buffer);
static cJSON_bool parse_array(cJSON * const item, parse_buffer * const input_buffer);
static cJSON_bool print_array(const cJSON * const item, printbuffer * const output_buffer);
static cJSON_bool parse_object(cJSON * const item, parse_buffer * const input_buffer);
static cJSON_bool print_object(const cJSON * const item, printbuffer * const output_buffer);

/* Utility to jump whitespace and cr/lf */
static parse_buffer *buffer_skip_whitespace(parse_buffer * const buffer)
{
    if ((buffer == NULL) || (buffer->content == NULL))
    {
        return NULL;
    }

    if (cannot_access_at_index(buffer, 0))
    {
        return buffer;
    }

    while (can_access_at_index(buffer, 0) && (buffer_at_offset(buffer)[0] <= 32))
    {
        buffer->offset++;
    }

    if (buffer->offset == buffer->length)
    {
        buffer->offset--;
    }

    return buffer;
}

/* skip the UTF-8 BOM (byte order mark) if it is at the beginning of a buffer */
static parse_buffer *skip_utf8_bom(parse_buffer * const buffer)
{
    if ((buffer == NULL) || (buffer->content == NULL) || (buffer->offset != 0))
    {
        return NULL;
    }

    if (can_access_at_index(buffer, 4) && (strncmp((const char*)buffer_at_offset(buffer), "\xEF\xBB\xBF", 3) == 0))
    {
        buffer->offset += 3;
    }

    return buffer;
}

CJSON_PUBLIC(cJSON *) cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated)
{
    size_t buffer_length;

    if (NULL == value)
    {
        return NULL;
    }

    /* Adding null character size due to require_null_terminated. */
    buffer_length = strlen(value) + sizeof("");

    return cJSON_ParseWithLengthOpts(value, buffer_length, return_parse_end, require_null_terminated);
}

/* Parse an object - create a new root, and populate. */
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated)
{
    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
    cJSON *item = NULL;

    /* reset error position */
    global_error.json = NULL;
    global_error.position = 0;

    if (value == NULL || 0 == buffer_length)
    {
        goto fail;
    }

    buffer.content = (const unsigned char*)value;
    buffer.length = buffer_length;
    buffer.offset = 0;
    buffer.hooks = global_hooks;

    item = cJSON_New_Item(&global_hooks);
    if (item == NULL) /* memory fail */
    {
        goto fail;
    }

    if (!parse_value(item, buffer_skip_whitespace(skip_utf8_bom(&buffer))))
    {
        /* parse failure. ep is set. */
        goto fail;
    }

    /* if we require null-terminated JSON without appended garbage, skip and then check for a null terminator */
    if (require_null_terminated)
    {
        buffer_skip_whitespace(&buffer);
        if ((buffer.offset >= buffer.length) || buffer_at_offset(&buffer)[0] != '\0')
        {
            goto fail;
        }
    }
    if (return_parse_end)
    {
        *return_parse_end = (const char*)buffer_at_offset(&buffer);
    }

    return item;

    fail:
    if (item != NULL)
    {
        cJSON_Delete(item);
    }

    if (value != NULL)
    {
        error local_error;
        local_error.json = (const unsigned char*)value;
        local_error.position = 0;

        if (buffer.offset < buffer.length)
        {
            local_error.position = buffer.offset;
        }
        else if (buffer.length > 0)
        {
            local_error.position = buffer.length - 1;
        }

        if (return_parse_end != NULL)
        {
            *return_parse_end = (const char*)local_error.json + local_error.position;
        }

        global_error = local_error;
    }

    return NULL;
}

/* Default options for cJSON_Parse */
CJSON_PUBLIC(cJSON *) cJSON_Parse(const char *value)
{
    return cJSON_ParseWithOpts(value, 0, 0);
}

CJSON_PUBLIC(cJSON *) cJSON_ParseWithLength(const char *value, size_t buffer_length)
{
    return cJSON_ParseWithLengthOpts(value, buffer_length, 0, 0);
}

#define cjson_min(a, b) (((a) < (b)) ? (a) : (b))

static unsigned char *print(const cJSON * const item, cJSON_bool format, const internal_hooks * const hooks)
{
    static const size_t default_buffer_size = 256;
    printbuffer buffer[1];
    unsigned char *printed = NULL;

    memset(buffer, 0, sizeof(buffer));

    /* create buffer */
    buffer->buffer = (unsigned char*) hooks->allocate(default_buffer_size);
    buffer->length = default_buffer_size;
    buffer->format = format;
    buffer->hooks = *hooks;
    if (buffer->buffer == NULL)
    {
        goto fail;
    }

    /* print the value */
    if (!print_value(item, buffer))
    {
        goto fail;
    }
    update_offset(buffer);

    /* check if reallocate is available */
    if (hooks->reallocate != NULL)
    {
        printed = (unsigned char*) hooks->reallocate(buffer->buffer, buffer->offset + 1);
        if (printed == NULL) {
            goto fail;
        }
        buffer->buffer = NULL;
    }
    else /* otherwise copy the JSON over to a new buffer */
    {
        printed = (unsigned char*) hooks->allocate(buffer->offset + 1);
        if (printed == NULL)
        {
            goto fail;
        }
        memcpy(printed, buffer->buffer, cjson_min(buffer->length, buffer->offset + 1));
        printed[buffer->offset] = '\0'; /* just to be sure */

        /* free the buffer */
        hooks->deallocate(buffer->buffer);
    }

    return printed;

    fail:
    if (buffer->buffer != NULL)
    {
        hooks->deallocate(buffer->buffer);
    }

    if (printed != NULL)
    {
        hooks->deallocate(printed);
    }

    return NULL;
}

/* Render a cJSON item/entity/structure to text. */
CJSON_PUBLIC(char *) cJSON_Print(const cJSON *item)
{
    return (char*)print(item, true, &global_hooks);
}

CJSON_PUBLIC(char *) cJSON_PrintUnformatted(const cJSON *item)
{
    return (char*)print(item, false, &global_hooks);
}

CJSON_PUBLIC(char *) cJSON_PrintBuffered(const cJSON *item, int prebuffer, cJSON_bool fmt)
{
    printbuffer p = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };

    if (prebuffer < 0)
    {
        return NULL;
    }

    p.buffer = (unsigned char*)global_hooks.allocate((size_t)prebuffer);
    if (!p.buffer)
    {
        return NULL;
    }

    p.length = (size_t)prebuffer;
    p.offset = 0;
    p.noalloc = false;
    p.format = fmt;
    p.hooks = global_hooks;

    if (!print_value(item, &p))
    {
        global_hooks.deallocate(p.buffer);
        return NULL;
    }

    return (char*)p.buffer;
}

CJSON_PUBLIC(cJSON_bool) cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format)
{
    printbuffer p = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };

    if ((length < 0) || (buffer == NULL))
    {
        return false;
    }

    p.buffer = (unsigned char*)buffer;
    p.length = (size_t)length;
    p.offset = 0;
    p.noalloc = true;
    p.format = format;
    p.hooks = global_hooks;

    return print_value(item, &p);
}

/* Parser core - when encountering text, process appropriately. */
static cJSON_bool parse_value(cJSON * const item, parse_buffer * const input_buffer)
{
    if ((input_buffer == NULL) || (input_buffer->content == NULL))
    {
        return false; /* no input */
    }

    /* parse the different types of values */
    /* null */
    if (can_read(input_buffer, 4) && (strncmp((const char*)buffer_at_offset(input_buffer), "null", 4) == 0))
    {
        item->type = cJSON_NULL;
        input_buffer->offset += 4;
        return true;
    }
    /* false */
    if (can_read(input_buffer, 5) && (strncmp((const char*)buffer_at_offset(input_buffer), "false", 5) == 0))
    {
        item->type = cJSON_False;
        input_buffer->offset += 5;
        return true;
    }
    /* true */
    if (can_read(input_buffer, 4) && (strncmp((const char*)buffer_at_offset(input_buffer), "true", 4) == 0))
    {
        item->type = cJSON_True;
        item->valueint = 1;
        input_buffer->offset += 4;
        return true;
    }
    /* string */
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '\"'))
    {
        return parse_string(item, input_buffer);
    }
    /* number */
    if (can_access_at_index(input_buffer, 0) && ((buffer_at_offset(input_buffer)[0] == '-') || ((buffer_at_offset(input_buffer)[0] >= '0') && (buffer_at_offset(input_buffer)[0] <= '9'))))
    {
        return parse_number(item, input_buffer);
    }
    /* array */
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '['))
    {
        return parse_array(item, input_buffer);
    }
    /* object */
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '{'))
    {
        return parse_object(item, input_buffer);
    }

    return false;
}

/* Render a value to text. */
static cJSON_bool print_value(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output = NULL;

    if ((item == NULL) || (output_buffer == NULL))
    {
        return false;
    }

    switch ((item->type) & 0xFF)
    {
        case cJSON_NULL:
            output = ensure(output_buffer, 5);
            if (output == NULL)
            {
                return false;
            }
            strcpy((char*)output, "null");
            return true;

        case cJSON_False:
            output = ensure(output_buffer, 6);
            if (output == NULL)
            {
                return false;
            }
            strcpy((char*)output, "false");
            return true;

        case cJSON_True:
            output = ensure(output_buffer, 5);
            if (output == NULL)
            {
                return false;
            }
            strcpy((char*)output, "true");
            return true;

        case cJSON_Number:
            return print_number(item, output_buffer);

        case cJSON_Raw:
        {
            size_t raw_length = 0;
            if (item->valuestring == NULL)
            {
                return false;
            }

            raw_length = strlen(item->valuestring) + sizeof("");
            output = ensure(output_buffer, raw_length);
            if (output == NULL)
            {
                return false;
            }
            memcpy(output, item->valuestring, raw_length);
            return true;
        }

        case cJSON_String:
            return print_string(item, output_buffer);

        case cJSON_Array:
            return print_array(item, output_buffer);

        case cJSON_Object:
            return print_object(item, output_buffer);

        default:
            return false;
    }
}

/* Build an array from input text. */
static cJSON_bool parse_array(cJSON * const item, parse_buffer * const input_buffer)
{
    cJSON *head = NULL; /* head of the linked list */
    cJSON *current_item = NULL;

    if (input_buffer->depth >= CJSON_NESTING_LIMIT)
    {
        return false; /* to deeply nested */
    }
    input_buffer->depth++;

    if (buffer_at_offset(input_buffer)[0] != '[')
    {
        /* not an array */
        goto fail;
    }

    input_buffer->offset++;
    buffer_skip_whitespace(input_buffer);
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ']'))
    {
        /* empty array */
        goto success;
    }

    /* check if we skipped to the end of the buffer */
    if (cannot_access_at_index(input_buffer, 0))
    {
        input_buffer->offset--;
        goto fail;
    }

    /* step back to character in front of the first element */
    input_buffer->offset--;
    /* loop through the comma separated array elements */
    do
    {
        /* allocate next item */
        cJSON *new_item = cJSON_New_Item(&(input_buffer->hooks));
        if (new_item == NULL)
        {
            goto fail; /* allocation failure */
        }

        /* attach next item to list */
        if (head == NULL)
        {
            /* start the linked list */
            current_item = head = new_item;
        }
        else
        {
            /* add to the end and advance */
            current_item->next = new_item;
            new_item->prev = current_item;
            current_item = new_item;
        }

        /* parse next value */
        input_buffer->offset++;
        buffer_skip_whitespace(input_buffer);
        if (!parse_value(current_item, input_buffer))
        {
            goto fail; /* failed to parse value */
        }
        buffer_skip_whitespace(input_buffer);
    }
    while (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ','));

    if (cannot_access_at_index(input_buffer, 0) || buffer_at_offset(input_buffer)[0] != ']')
    {
        goto fail; /* expected end of array */
    }

    success:
    input_buffer->depth--;

    if (head != NULL) {
        head->prev = current_item;
    }

    item->type = cJSON_Array;
    item->child = head;

    input_buffer->offset++;

    return true;

    fail:
    if (head != NULL)
    {
        cJSON_Delete(head);
    }

    return false;
}

/* Render an array to text */
static cJSON_bool print_array(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output_pointer = NULL;
    size_t length = 0;
    cJSON *current_element = item->child;

    if (output_buffer == NULL)
    {
        return false;
    }

    /* Compose the output array. */
    /* opening square bracket */
    output_pointer = ensure(output_buffer, 1);
    if (output_pointer == NULL)
    {
        return false;
    }

    *output_pointer = '[';
    output_buffer->offset++;
    output_buffer->depth++;

    while (current_element != NULL)
    {
        if (!print_value(current_element, output_buffer))
        {
            return false;
        }
        update_offset(output_buffer);
        if (current_element->next)
        {
            length = (size_t) (output_buffer->format ? 2 : 1);
            output_pointer = ensure(output_buffer, length + 1);
            if (output_pointer == NULL)
            {
                return false;
            }
            *output_pointer++ = ',';
            if(output_buffer->format)
            {
                *output_pointer++ = ' ';
            }
            *output_pointer = '\0';
            output_buffer->offset += length;
        }
        current_element = current_element->next;
    }

    output_pointer = ensure(output_buffer, 2);
    if (output_pointer == NULL)
    {
        return false;
    }
    *output_pointer++ = ']';
    *output_pointer = '\0';
    output_buffer->depth--;

    return true;
}

/* Build an object from the text. */
static cJSON_bool parse_object(cJSON * const item, parse_buffer * const input_buffer)
{
    cJSON *head = NULL; /* linked list head */
    cJSON *current_item = NULL;

    if (input_buffer->depth >= CJSON_NESTING_LIMIT)
    {
        return false; /* to deeply nested */
    }
    input_buffer->depth++;

    if (cannot_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != '{'))
    {
        goto fail; /* not an object */
    }

    input_buffer->offset++;
    buffer_skip_whitespace(input_buffer);
    if (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == '}'))
    {
        goto success; /* empty object */
    }

    /* check if we skipped to the end of the buffer */
    if (cannot_access_at_index(input_buffer, 0))
    {
        input_buffer->offset--;
        goto fail;
    }

    /* step back to character in front of the first element */
    input_buffer->offset--;
    /* loop through the comma separated array elements */
    do
    {
        /* allocate next item */
        cJSON *new_item = cJSON_New_Item(&(input_buffer->hooks));
        if (new_item == NULL)
        {
            goto fail; /* allocation failure */
        }

        /* attach next item to list */
        if (head == NULL)
        {
            /* start the linked list */
            current_item = head = new_item;
        }
        else
        {
            /* add to the end and advance */
            current_item->next = new_item;
            new_item->prev = current_item;
            current_item = new_item;
        }

        /* parse the name of the child */
        input_buffer->offset++;
        buffer_skip_whitespace(input_buffer);
        if (!parse_string(current_item, input_buffer))
        {
            goto fail; /* failed to parse name */
        }
        buffer_skip_whitespace(input_buffer);

        /* swap valuestring and string, because we parsed the name */
        current_item->string = current_item->valuestring;
        current_item->valuestring = NULL;

        if (cannot_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != ':'))
        {
            goto fail; /* invalid object */
        }

        /* parse the value */
        input_buffer->offset++;
        buffer_skip_whitespace(input_buffer);
        if (!parse_value(current_item, input_buffer))
        {
            goto fail; /* failed to parse value */
        }
        buffer_skip_whitespace(input_buffer);
    }
    while (can_access_at_index(input_buffer, 0) && (buffer_at_offset(input_buffer)[0] == ','));

    if (cannot_access_at_index(input_buffer, 0) || (buffer_at_offset(input_buffer)[0] != '}'))
    {
        goto fail; /* expected end of object */
    }

    success:
    input_buffer->depth--;

    if (head != NULL) {
        head->prev = current_item;
    }

    item->type = cJSON_Object;
    item->child = head;

    input_buffer->offset++;
    return true;

    fail:
    if (head != NULL)
    {
        cJSON_Delete(head);
    }

    return false;
}

/* Render an object to text. */
static cJSON_bool print_object(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output_pointer = NULL;
    size_t length = 0;
    cJSON *current_item = item->child;

    if (output_buffer == NULL)
    {
        return false;
    }

    /* Compose the output: */
    length = (size_t) (output_buffer->format ? 2 : 1); /* fmt: {\n */
    output_pointer = ensure(output_buffer, length + 1);
    if (output_pointer == NULL)
    {
        return false;
    }

    *output_pointer++ = '{';
    output_buffer->depth++;
    if (output_buffer->format)
    {
        *output_pointer++ = '\n';
    }
    output_buffer->offset += length;

    while (current_item)
    {
        if (output_buffer->format)
        {
            size_t i;
            output_pointer = ensure(output_buffer, output_buffer->depth);
            if (output_pointer == NULL)
            {
                return false;
            }
            for (i = 0; i < output_buffer->depth; i++)
            {
                *output_pointer++ = '\t';
            }
            output_buffer->offset += output_buffer->depth;
        }

        /* print key */
        if (!print_string_ptr((unsigned char*)current_item->string, output_buffer))
        {
            return false;
        }
        update_offset(output_buffer);

        length = (size_t) (output_buffer->format ? 2 : 1);
        output_pointer = ensure(output_buffer, length);
        if (output_pointer == NULL)
        {
            return false;
        }
        *output_pointer++ = ':';
        if (output_buffer->format)
        {
            *output_pointer++ = '\t';
        }
        output_buffer->offset += length;

        /* print value */
        if (!print_value(current_item, output_buffer))
        {
            return false;
        }
        update_offset(output_buffer);

        /* print comma if not last */
        length = ((size_t)(output_buffer->format ? 1 : 0) + (size_t)(current_item->next ? 1 : 0));
        output_pointer = ensure(output_buffer, length + 1);
        if (output_pointer == NULL)
        {
            return false;
        }
        if (current_item->next)
        {
            *output_pointer++ = ',';
        }

        if (output_buffer->format)
        {
            *output_pointer++ = '\n';
        }
        *output_pointer = '\0';
        output_buffer->offset += length;

        current_item = current_item->next;
    }

    output_pointer = ensure(output_buffer, output_buffer->format ? (output_buffer->depth + 1) : 2);
    if (output_pointer == NULL)
    {
        return false;
    }
    if (output_buffer->format)
    {
        size_t i;
        for (i = 0; i < (output_buffer->depth - 1); i++)
        {
            *output_pointer++ = '\t';
        }
    }
    *output_pointer++ = '}';
    *output_pointer = '\0';
    output_buffer->depth--;

    return true;
}

/* Get Array size/item / object item. */
CJSON_PUBLIC(int) cJSON_GetArraySize(const cJSON *array)
{
    cJSON *child = NULL;
    size_t size = 0;

    if (array == NULL)
    {
        return 0;
    }

    child = array->child;

    while(child != NULL)
    {
        size++;
        child = child->next;
    }

    /* FIXME: Can overflow here. Cannot be fixed without breaking the API */

    return (int)size;
}

static cJSON* get_array_item(const cJSON *array, size_t index)
{
    cJSON *current_child = NULL;

    if (array == NULL)
    {
        return NULL;
    }

    current_child = array->child;
    while ((current_child != NULL) && (index > 0))
    {
        index--;
        current_child = current_child->next;
    }

    return current_child;
}

CJSON_PUBLIC(cJSON *) cJSON_GetArrayItem(const cJSON *array, int index)
{
    if (index < 0)
    {
        return NULL;
    }

    return get_array_item(array, (size_t)index);
}

static cJSON *get_object_item(const cJSON * const object, const char * const name, const cJSON_bool case_sensitive)
{
    cJSON *current_element = NULL;

    if ((object == NULL) || (name == NULL))
    {
        return NULL;
    }

    current_element = object->child;
    if (case_sensitive)
    {
        while ((current_element != NULL) && (current_element->string != NULL) && (strcmp(name, current_element->string) != 0))
        {
            current_element = current_element->next;
        }
    }
    else
    {
        while ((current_element != NULL) && (case_insensitive_strcmp((const unsigned char*)name, (const unsigned char*)(current_element->string)) != 0))
        {
            current_element = current_element->next;
        }
    }

    if ((current_element == NULL) || (current_element->string == NULL)) {
        return NULL;
    }

    return current_element;
}

CJSON_PUBLIC(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string)
{
    return get_object_item(object, string, false);
}

CJSON_PUBLIC(cJSON *) cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string)
{
    return get_object_item(object, string, true);
}

CJSON_PUBLIC(cJSON_bool) cJSON_HasObjectItem(const cJSON *object, const char *string)
{
    return cJSON_GetObjectItem(object, string) ? 1 : 0;
}

/* Utility for array list handling. */
static void suffix_object(cJSON *prev, cJSON *item)
{
    prev->next = item;
    item->prev = prev;
}

/* Utility for handling references. */
static cJSON *create_reference(const cJSON *item, const internal_hooks * const hooks)
{
    cJSON *reference = NULL;
    if (item == NULL)
    {
        return NULL;
    }

    reference = cJSON_New_Item(hooks);
    if (reference == NULL)
    {
        return NULL;
    }

    memcpy(reference, item, sizeof(cJSON));
    reference->string = NULL;
    reference->type |= cJSON_IsReference;
    reference->next = reference->prev = NULL;
    return reference;
}

static cJSON_bool add_item_to_array(cJSON *array, cJSON *item)
{
    cJSON *child = NULL;

    if ((item == NULL) || (array == NULL) || (array == item))
    {
        return false;
    }

    child = array->child;
    /*
     * To find the last item in array quickly, we use prev in array
     */
    if (child == NULL)
    {
        /* list is empty, start new one */
        array->child = item;
        item->prev = item;
        item->next = NULL;
    }
    else
    {
        /* append to the end */
        if (child->prev)
        {
            suffix_object(child->prev, item);
            array->child->prev = item;
        }
    }

    return true;
}

/* Add item to array/object. */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToArray(cJSON *array, cJSON *item)
{
    return add_item_to_array(array, item);
}

#if defined(__clang__) || (defined(__GNUC__)  && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 5))))
#pragma GCC diagnostic push
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif
/* helper function to cast away const */
static void* cast_away_const(const void* string)
{
    return (void*)string;
}
#if defined(__clang__) || (defined(__GNUC__)  && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 5))))
#pragma GCC diagnostic pop
#endif


static cJSON_bool add_item_to_object(cJSON * const object, const char * const string, cJSON * const item, const internal_hooks * const hooks, const cJSON_bool constant_key)
{
    char *new_key = NULL;
    int new_type = cJSON_Invalid;

    if ((object == NULL) || (string == NULL) || (item == NULL) || (object == item))
    {
        return false;
    }

    if (constant_key)
    {
        new_key = (char*)cast_away_const(string);
        new_type = item->type | cJSON_StringIsConst;
    }
    else
    {
        new_key = (char*)cJSON_strdup((const unsigned char*)string, hooks);
        if (new_key == NULL)
        {
            return false;
        }

        new_type = item->type & ~cJSON_StringIsConst;
    }

    if (!(item->type & cJSON_StringIsConst) && (item->string != NULL))
    {
        hooks->deallocate(item->string);
    }

    item->string = new_key;
    item->type = new_type;

    return add_item_to_array(object, item);
}

CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item)
{
    return add_item_to_object(object, string, item, &global_hooks, false);
}

/* Add an item to an object with constant string as key */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item)
{
    return add_item_to_object(object, string, item, &global_hooks, true);
}

CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item)
{
    if (array == NULL)
    {
        return false;
    }

    return add_item_to_array(array, create_reference(item, &global_hooks));
}

CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item)
{
    if ((object == NULL) || (string == NULL))
    {
        return false;
    }

    return add_item_to_object(object, string, create_reference(item, &global_hooks), &global_hooks, false);
}

CJSON_PUBLIC(cJSON*) cJSON_AddNullToObject(cJSON * const object, const char * const name)
{
    cJSON *null = cJSON_CreateNull();
    if (add_item_to_object(object, name, null, &global_hooks, false))
    {
        return null;
    }

    cJSON_Delete(null);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddTrueToObject(cJSON * const object, const char * const name)
{
    cJSON *true_item = cJSON_CreateTrue();
    if (add_item_to_object(object, name, true_item, &global_hooks, false))
    {
        return true_item;
    }

    cJSON_Delete(true_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddFalseToObject(cJSON * const object, const char * const name)
{
    cJSON *false_item = cJSON_CreateFalse();
    if (add_item_to_object(object, name, false_item, &global_hooks, false))
    {
        return false_item;
    }

    cJSON_Delete(false_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddBoolToObject(cJSON * const object, const char * const name, const cJSON_bool boolean)
{
    cJSON *bool_item = cJSON_CreateBool(boolean);
    if (add_item_to_object(object, name, bool_item, &global_hooks, false))
    {
        return bool_item;
    }

    cJSON_Delete(bool_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddNumberToObject(cJSON * const object, const char * const name, const double number)
{
    cJSON *number_item = cJSON_CreateNumber(number);
    if (add_item_to_object(object, name, number_item, &global_hooks, false))
    {
        return number_item;
    }

    cJSON_Delete(number_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string)
{
    cJSON *string_item = cJSON_CreateString(string);
    if (add_item_to_object(object, name, string_item, &global_hooks, false))
    {
        return string_item;
    }

    cJSON_Delete(string_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw)
{
    cJSON *raw_item = cJSON_CreateRaw(raw);
    if (add_item_to_object(object, name, raw_item, &global_hooks, false))
    {
        return raw_item;
    }

    cJSON_Delete(raw_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddObjectToObject(cJSON * const object, const char * const name)
{
    cJSON *object_item = cJSON_CreateObject();
    if (add_item_to_object(object, name, object_item, &global_hooks, false))
    {
        return object_item;
    }

    cJSON_Delete(object_item);
    return NULL;
}

CJSON_PUBLIC(cJSON*) cJSON_AddArrayToObject(cJSON * const object, const char * const name)
{
    cJSON *array = cJSON_CreateArray();
    if (add_item_to_object(object, name, array, &global_hooks, false))
    {
        return array;
    }

    cJSON_Delete(array);
    return NULL;
}

CJSON_PUBLIC(cJSON *) cJSON_DetachItemViaPointer(cJSON *parent, cJSON * const item)
{
    if ((parent == NULL) || (item == NULL))
    {
        return NULL;
    }

    if (item != parent->child)
    {
        /* not the first element */
        item->prev->next = item->next;
    }
    if (item->next != NULL)
    {
        /* not the last element */
        item->next->prev = item->prev;
    }

    if (item == parent->child)
    {
        /* first element */
        parent->child = item->next;
    }
    else if (item->next == NULL)
    {
        /* last element */
        parent->child->prev = item->prev;
    }

    /* make sure the detached item doesn't point anywhere anymore */
    item->prev = NULL;
    item->next = NULL;

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromArray(cJSON *array, int which)
{
    if (which < 0)
    {
        return NULL;
    }

    return cJSON_DetachItemViaPointer(array, get_array_item(array, (size_t)which));
}

CJSON_PUBLIC(void) cJSON_DeleteItemFromArray(cJSON *array, int which)
{
    cJSON_Delete(cJSON_DetachItemFromArray(array, which));
}

CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObject(cJSON *object, const char *string)
{
    cJSON *to_detach = cJSON_GetObjectItem(object, string);

    return cJSON_DetachItemViaPointer(object, to_detach);
}

CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObjectCaseSensitive(cJSON *object, const char *string)
{
    cJSON *to_detach = cJSON_GetObjectItemCaseSensitive(object, string);

    return cJSON_DetachItemViaPointer(object, to_detach);
}

CJSON_PUBLIC(void) cJSON_DeleteItemFromObject(cJSON *object, const char *string)
{
    cJSON_Delete(cJSON_DetachItemFromObject(object, string));
}

CJSON_PUBLIC(void) cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string)
{
    cJSON_Delete(cJSON_DetachItemFromObjectCaseSensitive(object, string));
}

/* Replace array/object items with new ones. */
CJSON_PUBLIC(cJSON_bool) cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem)
{
    cJSON *after_inserted = NULL;

    if (which < 0)
    {
        return false;
    }

    after_inserted = get_array_item(array, (size_t)which);
    if (after_inserted == NULL)
    {
        return add_item_to_array(array, newitem);
    }

    newitem->next = after_inserted;
    newitem->prev = after_inserted->prev;
    after_inserted->prev = newitem;
    if (after_inserted == array->child)
    {
        array->child = newitem;
    }
    else
    {
        newitem->prev->next = newitem;
    }
    return true;
}

CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement)
{
    if ((parent == NULL) || (parent->child == NULL) || (replacement == NULL) || (item == NULL))
    {
        return false;
    }

    if (replacement == item)
    {
        return true;
    }

    replacement->next = item->next;
    replacement->prev = item->prev;

    if (replacement->next != NULL)
    {
        replacement->next->prev = replacement;
    }
    if (parent->child == item)
    {
        if (parent->child->prev == parent->child)
        {
            replacement->prev = replacement;
        }
        parent->child = replacement;
    }
    else
    {   /*
         * To find the last item in array quickly, we use prev in array.
         * We can't modify the last item's next pointer where this item was the parent's child
         */
        if (replacement->prev != NULL)
        {
            replacement->prev->next = replacement;
        }
        if (replacement->next == NULL)
        {
            parent->child->prev = replacement;
        }
    }

    item->next = NULL;
    item->prev = NULL;
    cJSON_Delete(item);

    return true;
}

CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem)
{
    if (which < 0)
    {
        return false;
    }

    return cJSON_ReplaceItemViaPointer(array, get_array_item(array, (size_t)which), newitem);
}

static cJSON_bool replace_item_in_object(cJSON *object, const char *string, cJSON *replacement, cJSON_bool case_sensitive)
{
    if ((replacement == NULL) || (string == NULL))
    {
        return false;
    }

    /* replace the name in the replacement */
    if (!(replacement->type & cJSON_StringIsConst) && (replacement->string != NULL))
    {
        cJSON_free(replacement->string);
    }
    replacement->string = (char*)cJSON_strdup((const unsigned char*)string, &global_hooks);
    if (replacement->string == NULL)
    {
        return false;
    }

    replacement->type &= ~cJSON_StringIsConst;

    return cJSON_ReplaceItemViaPointer(object, get_object_item(object, string, case_sensitive), replacement);
}

CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem)
{
    return replace_item_in_object(object, string, newitem, false);
}

CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object, const char *string, cJSON *newitem)
{
    return replace_item_in_object(object, string, newitem, true);
}

/* Create basic types: */
CJSON_PUBLIC(cJSON *) cJSON_CreateNull(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_NULL;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateTrue(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_True;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateFalse(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_False;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateBool(cJSON_bool boolean)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = boolean ? cJSON_True : cJSON_False;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateNumber(double num)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_Number;
        item->valuedouble = num;

        /* use saturation in case of overflow */
        if (num >= INT_MAX)
        {
            item->valueint = INT_MAX;
        }
        else if (num <= (double)INT_MIN)
        {
            item->valueint = INT_MIN;
        }
        else
        {
            item->valueint = (int)num;
        }
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateString(const char *string)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_String;
        item->valuestring = (char*)cJSON_strdup((const unsigned char*)string, &global_hooks);
        if(!item->valuestring)
        {
            cJSON_Delete(item);
            return NULL;
        }
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateStringReference(const char *string)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item != NULL)
    {
        item->type = cJSON_String | cJSON_IsReference;
        item->valuestring = (char*)cast_away_const(string);
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateObjectReference(const cJSON *child)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item != NULL) {
        item->type = cJSON_Object | cJSON_IsReference;
        item->child = (cJSON*)cast_away_const(child);
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateArrayReference(const cJSON *child) {
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item != NULL) {
        item->type = cJSON_Array | cJSON_IsReference;
        item->child = (cJSON*)cast_away_const(child);
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateRaw(const char *raw)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = cJSON_Raw;
        item->valuestring = (char*)cJSON_strdup((const unsigned char*)raw, &global_hooks);
        if(!item->valuestring)
        {
            cJSON_Delete(item);
            return NULL;
        }
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateArray(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type=cJSON_Array;
    }

    return item;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateObject(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item)
    {
        item->type = cJSON_Object;
    }

    return item;
}

/* Create Arrays: */
CJSON_PUBLIC(cJSON *) cJSON_CreateIntArray(const int *numbers, int count)
{
    size_t i = 0;
    cJSON *n = NULL;
    cJSON *p = NULL;
    cJSON *a = NULL;

    if ((count < 0) || (numbers == NULL))
    {
        return NULL;
    }

    a = cJSON_CreateArray();

    for(i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber(numbers[i]);
        if (!n)
        {
            cJSON_Delete(a);
            return NULL;
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p, n);
        }
        p = n;
    }

    if (a && a->child) {
        a->child->prev = n;
    }

    return a;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateFloatArray(const float *numbers, int count)
{
    size_t i = 0;
    cJSON *n = NULL;
    cJSON *p = NULL;
    cJSON *a = NULL;

    if ((count < 0) || (numbers == NULL))
    {
        return NULL;
    }

    a = cJSON_CreateArray();

    for(i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber((double)numbers[i]);
        if(!n)
        {
            cJSON_Delete(a);
            return NULL;
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p, n);
        }
        p = n;
    }

    if (a && a->child) {
        a->child->prev = n;
    }

    return a;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateDoubleArray(const double *numbers, int count)
{
    size_t i = 0;
    cJSON *n = NULL;
    cJSON *p = NULL;
    cJSON *a = NULL;

    if ((count < 0) || (numbers == NULL))
    {
        return NULL;
    }

    a = cJSON_CreateArray();

    for(i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber(numbers[i]);
        if(!n)
        {
            cJSON_Delete(a);
            return NULL;
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p, n);
        }
        p = n;
    }

    if (a && a->child) {
        a->child->prev = n;
    }

    return a;
}

CJSON_PUBLIC(cJSON *) cJSON_CreateStringArray(const char *const *strings, int count)
{
    size_t i = 0;
    cJSON *n = NULL;
    cJSON *p = NULL;
    cJSON *a = NULL;

    if ((count < 0) || (strings == NULL))
    {
        return NULL;
    }

    a = cJSON_CreateArray();

    for (i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateString(strings[i]);
        if(!n)
        {
            cJSON_Delete(a);
            return NULL;
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p,n);
        }
        p = n;
    }

    if (a && a->child) {
        a->child->prev = n;
    }

    return a;
}

/* Duplication */
CJSON_PUBLIC(cJSON *) cJSON_Duplicate(const cJSON *item, cJSON_bool recurse)
{
    cJSON *newitem = NULL;
    cJSON *child = NULL;
    cJSON *next = NULL;
    cJSON *newchild = NULL;

    /* Bail on bad ptr */
    if (!item)
    {
        goto fail;
    }
    /* Create new item */
    newitem = cJSON_New_Item(&global_hooks);
    if (!newitem)
    {
        goto fail;
    }
    /* Copy over all vars */
    newitem->type = item->type & (~cJSON_IsReference);
    newitem->valueint = item->valueint;
    newitem->valuedouble = item->valuedouble;
    if (item->valuestring)
    {
        newitem->valuestring = (char*)cJSON_strdup((unsigned char*)item->valuestring, &global_hooks);
        if (!newitem->valuestring)
        {
            goto fail;
        }
    }
    if (item->string)
    {
        newitem->string = (item->type&cJSON_StringIsConst) ? item->string : (char*)cJSON_strdup((unsigned char*)item->string, &global_hooks);
        if (!newitem->string)
        {
            goto fail;
        }
    }
    /* If non-recursive, then we're done! */
    if (!recurse)
    {
        return newitem;
    }
    /* Walk the ->next chain for the child. */
    child = item->child;
    while (child != NULL)
    {
        newchild = cJSON_Duplicate(child, true); /* Duplicate (with recurse) each item in the ->next chain */
        if (!newchild)
        {
            goto fail;
        }
        if (next != NULL)
        {
            /* If newitem->child already set, then crosswire ->prev and ->next and move on */
            next->next = newchild;
            newchild->prev = next;
            next = newchild;
        }
        else
        {
            /* Set newitem->child and move to it */
            newitem->child = newchild;
            next = newchild;
        }
        child = child->next;
    }
    if (newitem && newitem->child)
    {
        newitem->child->prev = newchild;
    }

    return newitem;

    fail:
    if (newitem != NULL)
    {
        cJSON_Delete(newitem);
    }

    return NULL;
}

static void skip_oneline_comment(char **input)
{
    *input += static_strlen("//");

    for (; (*input)[0] != '\0'; ++(*input))
    {
        if ((*input)[0] == '\n') {
            *input += static_strlen("\n");
            return;
        }
    }
}

static void skip_multiline_comment(char **input)
{
    *input += static_strlen("/*");

    for (; (*input)[0] != '\0'; ++(*input))
    {
        if (((*input)[0] == '*') && ((*input)[1] == '/'))
        {
            *input += static_strlen("*/");
            return;
        }
    }
}

static void minify_string(char **input, char **output) {
    (*output)[0] = (*input)[0];
    *input += static_strlen("\"");
    *output += static_strlen("\"");


    for (; (*input)[0] != '\0'; (void)++(*input), ++(*output)) {
        (*output)[0] = (*input)[0];

        if ((*input)[0] == '\"') {
            (*output)[0] = '\"';
            *input += static_strlen("\"");
            *output += static_strlen("\"");
            return;
        } else if (((*input)[0] == '\\') && ((*input)[1] == '\"')) {
            (*output)[1] = (*input)[1];
            *input += static_strlen("\"");
            *output += static_strlen("\"");
        }
    }
}

CJSON_PUBLIC(void) cJSON_Minify(char *json)
{
    char *into = json;

    if (json == NULL)
    {
        return;
    }

    while (json[0] != '\0')
    {
        switch (json[0])
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                json++;
                break;

            case '/':
                if (json[1] == '/')
                {
                    skip_oneline_comment(&json);
                }
                else if (json[1] == '*')
                {
                    skip_multiline_comment(&json);
                } else {
                    json++;
                }
                break;

            case '\"':
                minify_string(&json, (char**)&into);
                break;

            default:
                into[0] = json[0];
                json++;
                into++;
        }
    }

    /* and null-terminate. */
    *into = '\0';
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsInvalid(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Invalid;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsFalse(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_False;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsTrue(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xff) == cJSON_True;
}


CJSON_PUBLIC(cJSON_bool) cJSON_IsBool(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & (cJSON_True | cJSON_False)) != 0;
}
CJSON_PUBLIC(cJSON_bool) cJSON_IsNull(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_NULL;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsNumber(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Number;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsString(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_String;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsArray(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Array;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsObject(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Object;
}

CJSON_PUBLIC(cJSON_bool) cJSON_IsRaw(const cJSON * const item)
{
    if (item == NULL)
    {
        return false;
    }

    return (item->type & 0xFF) == cJSON_Raw;
}

CJSON_PUBLIC(cJSON_bool) cJSON_Compare(const cJSON * const a, const cJSON * const b, const cJSON_bool case_sensitive)
{
    if ((a == NULL) || (b == NULL) || ((a->type & 0xFF) != (b->type & 0xFF)))
    {
        return false;
    }

    /* check if type is valid */
    switch (a->type & 0xFF)
    {
        case cJSON_False:
        case cJSON_True:
        case cJSON_NULL:
        case cJSON_Number:
        case cJSON_String:
        case cJSON_Raw:
        case cJSON_Array:
        case cJSON_Object:
            break;

        default:
            return false;
    }

    /* identical objects are equal */
    if (a == b)
    {
        return true;
    }

    switch (a->type & 0xFF)
    {
        /* in these cases and equal type is enough */
        case cJSON_False:
        case cJSON_True:
        case cJSON_NULL:
            return true;

        case cJSON_Number:
            if (compare_double(a->valuedouble, b->valuedouble))
            {
                return true;
            }
            return false;

        case cJSON_String:
        case cJSON_Raw:
            if ((a->valuestring == NULL) || (b->valuestring == NULL))
            {
                return false;
            }
            if (strcmp(a->valuestring, b->valuestring) == 0)
            {
                return true;
            }

            return false;

        case cJSON_Array:
        {
            cJSON *a_element = a->child;
            cJSON *b_element = b->child;

            for (; (a_element != NULL) && (b_element != NULL);)
            {
                if (!cJSON_Compare(a_element, b_element, case_sensitive))
                {
                    return false;
                }

                a_element = a_element->next;
                b_element = b_element->next;
            }

            /* one of the arrays is longer than the other */
            if (a_element != b_element) {
                return false;
            }

            return true;
        }

        case cJSON_Object:
        {
            cJSON *a_element = NULL;
            cJSON *b_element = NULL;
            cJSON_ArrayForEach(a_element, a)
            {
                /* TODO This has O(n^2) runtime, which is horrible! */
                b_element = get_object_item(b, a_element->string, case_sensitive);
                if (b_element == NULL)
                {
                    return false;
                }

                if (!cJSON_Compare(a_element, b_element, case_sensitive))
                {
                    return false;
                }
            }

            /* doing this twice, once on a and b to prevent true comparison if a subset of b
             * TODO: Do this the proper way, this is just a fix for now */
            cJSON_ArrayForEach(b_element, b)
            {
                a_element = get_object_item(a, b_element->string, case_sensitive);
                if (a_element == NULL)
                {
                    return false;
                }

                if (!cJSON_Compare(b_element, a_element, case_sensitive))
                {
                    return false;
                }
            }

            return true;
        }

        default:
            return false;
    }
}

CJSON_PUBLIC(void *) cJSON_malloc(size_t size)
{
    return global_hooks.allocate(size);
}

CJSON_PUBLIC(void) cJSON_free(void *object)
{
    global_hooks.deallocate(object);
}
#endif
#ifndef CTEXTENGINE_H
#define CTEXTENGINE_H










char * CTextStack_self_transform_in_string_and_self_clear(struct CTextStack *self){
    free(self->line_breaker);
    free(self->separator);
    char *result = self->rendered_text;
    free(self);
    return result;
}

void private_CTextStack_parse_ownership(struct CTextStack *self, struct CTextStack *new_stack){

    free(self->line_breaker);
    free(self->separator);
    free(self->rendered_text);

    self->rendered_text_alocation_size = new_stack->rendered_text_alocation_size;
    self->size = new_stack->size;
    self->ident_level = new_stack->ident_level;


    self->line_breaker = new_stack->line_breaker;
    self->separator = new_stack->separator;
    self->rendered_text = new_stack->rendered_text;
    free(new_stack);

}
void CTextStack_restart(struct CTextStack *self){
    free(self->rendered_text);
    self->rendered_text = (char*)malloc(2);
    strcpy(self->rendered_text,"\0");
    self->rendered_text_alocation_size = 2;
    self->size = 0;
    self->ident_level = 0;
}

void CTextStack_represent(struct CTextStack *self){
    printf("%s\n",self->rendered_text);
}


void CTextStack_free(struct CTextStack *self){
    free(self->line_breaker);
    free(self->separator);
    free(self->rendered_text);
    free(self);
}

struct CTextStack * CTextStack_clone(struct CTextStack *self){
    CTextStack *new_stack = newCTextStack(self->line_breaker,self->separator);
    new_stack->ident_level = self->ident_level;
    CTextStack_text(new_stack,self->rendered_text);
    return new_stack;
}




struct CTextStack * CTextStack_substr(struct CTextStack *self, long starter, long end){

    CTextStack *new_element = newCTextStack(self->line_breaker,self->separator);
    new_element->ident_level = self->ident_level;
    long formated_starter = private_CText_transform_index(self->size, starter);
    long formated_end = private_CText_transform_index(self->size, end);

    if(formated_starter == formated_end){
        CTextStack_format(new_element,"%c",self->rendered_text[formated_starter]);
        return new_element;
    }

    for(long i =formated_starter; i < formated_end; i++){
        CTextStack_format(new_element,"%c",self->rendered_text[i]);
    }

    return new_element;

}

void CTextStack_self_substr(struct CTextStack *self, long starter, long end){
    CTextStack *new_stack = CTextStack_substr(self,starter,end);
    private_CTextStack_parse_ownership(self,new_stack);

}


struct CTextStack *CTextStack_replace(struct CTextStack *self,const char *element, const char *element_to_replace){

    CTextStack *new_element = newCTextStack(self->line_breaker,self->separator);
    new_element->ident_level = self->ident_level;

    long element_size = (long)strlen(element);
    for(long i = 0; i < self->size;i++){
        CTextStack  *possible_ocurrence  = CTextStack_substr(self,i,i+element_size);

        if(strcmp(possible_ocurrence->rendered_text,element)== 0){
            CTextStack_text(new_element,element_to_replace);
            i+=element_size -1;
        }

        else{
            CTextStack_format(new_element,"%c",self->rendered_text[i]);
        }

        CTextStack_free(possible_ocurrence);

    }
    return new_element;
}

void CTextStack_self_replace(struct CTextStack *self,const char *element, const char *element_to_replace){
    CTextStack  *new_stack = CTextStack_replace(self,element,element_to_replace);
    private_CTextStack_parse_ownership(self,new_stack);
}


struct CTextStack *CTextStack_replace_long(struct CTextStack *self,const char *element, long element_to_replace){
    char num_conversion[20] = {0};
    sprintf(num_conversion,"%ld",element_to_replace);
    return CTextStack_replace(self,element,num_conversion);
}


void CTextStack_self_replace_long(struct CTextStack *self,const char *element, long element_to_replace){
    CTextStack  *new_stack = CTextStack_replace_long(self,element,element_to_replace);
    private_CTextStack_parse_ownership(self,new_stack);
}


struct CTextStack *CTextStack_replace_double(struct CTextStack *self,const char *element, double element_to_replace){
    CTextStack  *num_formated = newCTextStack_string_empty();
    CTextStack_format(num_formated,"%f",element_to_replace);
    CTextStack  *result = CTextStack_replace(self,element,num_formated->rendered_text);
    CTextStack_free(num_formated);
    return result;
}


void CTextStack_self_replace_double(struct CTextStack *self,const char *element, double element_to_replace){
    CTextStack  *new_stack = CTextStack_replace_double(self,element,element_to_replace);
    private_CTextStack_parse_ownership(self,new_stack);
}



long CTextStack_index_of(struct  CTextStack *self, const char *element){
    long element_size = (long)strlen(element);
    for(int i = 0; i < self->size; i++){
        CTextStack  *possible_element = CTextStack_substr(self,i,i+element_size);
        if(strcmp(possible_element->rendered_text,element) == 0){
            CTextStack_free(possible_element);
            return i;
        }
        CTextStack_free(possible_element);

    }
    return -1;
}


long CTextStack_index_of_char(struct  CTextStack *self, char element){
    for(int i = 0; i < self->size; i++) {
        if(self->rendered_text[i] == element){
            return i;
        }
    }
    return -1;
}
bool CTextStack_starts_with(struct  CTextStack *self, const char *element){
    long element_size = strlen(element);
    CTextStack  *separated = CTextStack_substr(self,0,element_size);
    if(strcmp(separated->rendered_text,element) == 0){
        CTextStack_free(separated);
        return true;
    }
    CTextStack_free(separated);
    return false;
}

bool CTextStack_ends_with(struct  CTextStack *self, const char *element){
    long element_size = strlen(element);
    CTextStack  *separated = CTextStack_substr(self,self->size -element_size,-1);

    if(strcmp(separated->rendered_text,element) == 0){
        CTextStack_free(separated);
        return true;
    }
    CTextStack_free(separated);
    return false;
}



struct CTextStack *CTextStack_lower(struct CTextStack *self){
    CTextStack *new_element = newCTextStack(self->line_breaker,self->separator);
    new_element->ident_level = self->ident_level;
    for(long i =0; i < self->size; i++){
        char current = self->rendered_text[i];
        CTextStack_format(new_element,"%c",tolower(current));
    }
    return new_element;
}

void CTextStack_self_lower(struct CTextStack *self){
    CTextStack *new_stack = CTextStack_lower(self);
    private_CTextStack_parse_ownership(self,new_stack);
}

struct CTextStack *CTextStack_upper(struct CTextStack *self){
    CTextStack *new_element = newCTextStack(self->line_breaker,self->separator);
    new_element->ident_level = self->ident_level;
    for(long i =0; i < self->size; i++){
        char current = self->rendered_text[i];
        CTextStack_format(new_element,"%c",toupper(current));
    }
    return new_element;
}

struct CTextStack *CTextStack_captalize(struct CTextStack *self){
    CTextStack *new_element = newCTextStack(self->line_breaker,self->separator);
    new_element->ident_level = self->ident_level;
    if(self->size  ==0){
        return  new_element;
    }

    CTextStack_format(new_element,"%c", toupper(self->rendered_text[0]));

    for(long i =1; i < self->size; i++){
        char  last = self->rendered_text[i-1];
        char current = self->rendered_text[i];


        if(last == ' '){
            CTextStack_format(new_element,"%c",toupper(current));
        }
        else{
            CTextStack_format(new_element,"%c", tolower(current));

        }

    }
    return new_element;
}

void CTextStack_self_captalize(struct CTextStack *self){
    CTextStack *new_stack = CTextStack_captalize(self);
    private_CTextStack_parse_ownership(self,new_stack);
}


void CTextStack_self_upper(struct CTextStack *self){
    CTextStack *new_stack = CTextStack_upper(self);
    private_CTextStack_parse_ownership(self,new_stack);
}


struct CTextStack *CTextStack_reverse(struct CTextStack *self){
    CTextStack *new_element = newCTextStack(self->line_breaker,self->separator);
    new_element->ident_level = self->ident_level;
    for(long i = (long)self->size; i >= 0 ; i--){
        CTextStack_format(new_element,"%c",self->rendered_text[i]);
    }
    return new_element;

}

void CTextStack_self_reverse(struct CTextStack *self){
    CTextStack *new_stack = CTextStack_reverse(self);
    private_CTextStack_parse_ownership(self,new_stack);
}



struct CTextStack *CTextStack_pop(struct CTextStack *self, long starter, long end){
    CTextStack *new_element = newCTextStack(self->line_breaker,self->separator);
    new_element->ident_level = self->ident_level;
    long formated_starter = private_CText_transform_index(self->size, starter);
    long formated_end = private_CText_transform_index(self->size, end);

    for(int i =0; i < self->size; i ++){
        if(i >= formated_starter && i <= formated_end){
            continue;
        }
        CTextStack_format(new_element,"%c",self->rendered_text[i]);
    }
    return new_element;
}


void  CTextStack_self_pop(struct CTextStack *self, long starter, long end){
    CTextStack  *new_stack = CTextStack_pop(self, starter, end);
    private_CTextStack_parse_ownership(self,new_stack);
}


struct CTextStack *CTextStack_insert_at(struct CTextStack *self,long point, const char *element){

    CTextStack *new_element = newCTextStack(self->line_breaker,self->separator);
    new_element->ident_level = self->ident_level;

    long converted_point = private_CText_transform_index(self->size, point);
    for(long i = 0; i < converted_point; i++){
        CTextStack_format(new_element,"%c",self->rendered_text[i]);
    }
    CTextStack_text(new_element,element);
    for(long i = converted_point; i < self->size; i++){
        CTextStack_format(new_element,"%c",self->rendered_text[i]);
    }
    return new_element;
}

void CTextStack_self_insert_at(struct CTextStack *self,long point, const char *element){
    CTextStack  *new_stack = CTextStack_insert_at(self, point,element);
    private_CTextStack_parse_ownership(self,new_stack);
}


struct CTextStack *CTextStack_trim(struct CTextStack *self){

    CTextStack  *invalid_elements = newCTextStack_string("\t\r\n ");
    long start_point = 0;
    for(int i = 0; i < self->size; i ++){
        char current_char =self->rendered_text[i];
        long invalid_point = CTextStack_index_of_char(invalid_elements, current_char);
        bool is_invalid = invalid_point != -1;
        if(!is_invalid){
            start_point = i;
            break;
        }
    }
    long end_point = -1;
    for(long i = (long)self->size -1; i >= 0; i--){

        char current_char =self->rendered_text[i];
        long invalid_point = CTextStack_index_of_char(invalid_elements, current_char);
        bool is_invalid = invalid_point != -1;
        if(!is_invalid){
            end_point = i+1;
            break;
        }
    }
    CTextStack_free(invalid_elements);
    return CTextStack_substr(self,start_point,end_point);

}


void CTextStack_self_trim(struct CTextStack *self){
    CTextStack  *new_stack = CTextStack_trim(self);
    private_CTextStack_parse_ownership(self,new_stack);
}

//
// Created by jurandi on 14-06-2023.
//
struct CTextStack * newCTextStack(const char *line_breaker, const char *separator){
    struct CTextStack *self = (struct CTextStack*)malloc(sizeof(struct CTextStack));
    *self = (CTextStack){0};
    self->rendered_text = (char*)malloc(2);
    strcpy(self->rendered_text,"\0");
    self->rendered_text_alocation_size = 2;

    self->line_breaker = strdup(line_breaker);
    self->separator = strdup(separator);


    return self;
}

struct CTextStack *newCTextStack_string(const char *starter){
    CTextStack *self = newCTextStack("","");
    if(starter){
        CTextStack_format(self,"%s", starter);
    }
    return self;
}

struct CTextStack *newCTextStack_string_format(const char *format, ...){
    CTextStack *self = newCTextStack("","");
    va_list  argptr;
    va_start(argptr, format);
    private_ctext_generate_formated_text(self,format,argptr);
    return self;
}

struct CTextStack *newCTextStack_string_getting_ownership(const char *starter){
    CTextStack *self = newCTextStack("","");
    free(self->rendered_text);
    self->rendered_text = (char*)starter;
    self->size = strlen(starter);
    self->rendered_text_alocation_size = self->size;
    return self;
}
struct CTextStack *newCTextStack_string_empty(){
    return  newCTextStack("","");
}


int CTextStack_typeof(struct CTextStack *self){
    if(self->size == 0){
        return CTEXT_STRING;
    }

    if(CTextStack_equal(self,"true") ||CTextStack_equal(self,"false") ){
        return CTEXT_BOOL;
    }

    double data;
    int result = sscanf(self->rendered_text,"%lf",&data);
    if(!result){
        return CTEXT_STRING;
    }
    if(CTextStack_index_of(self,".") == -1){
        return CTEXT_LONG;
    }
    return CTEXT_DOUBLE;


}
bool CTextStack_is_a_num(struct CTextStack *self){
    int type = CTextStack_typeof(self);
    if(type == CTEXT_DOUBLE || type == CTEXT_LONG){
        return true;
    }
    return false;
}


const char * CTextStack_typeof_in_str(struct CTextStack *self){
    int current_type = CTextStack_typeof(self);

    if(current_type == CTEXT_BOOL){
        return "bool";
    }

    else if(current_type == CTEXT_STRING){
        return "string";
    }

    else if(current_type == CTEXT_LONG){
        return "long";
    }

    else if(current_type == CTEXT_DOUBLE){
        return "double";
    }

    else{
        return "invalid";
    }
}

bool  CTextStack_parse_to_bool(struct CTextStack *self){
    if(CTextStack_equal(self,"true")){
        return true;
    }
    return false;
}

long  CTextStack_parse_to_integer(struct CTextStack *self){
    long value;
    int result = sscanf(self->rendered_text,"%ld",&value);
    if(!result){
        return -1;
    }
    return value;
}

double  CTextStack_parse_to_double(struct CTextStack *self){
    double value;
    int result = sscanf(self->rendered_text,"%lf",&value);
    if(!result){
        return -1;
    }
    return value;
}



void private_ctext_text_double_size_if_reachs(struct CTextStack *self){

    while(self->size >= (self->rendered_text_alocation_size - 2)){
        self->rendered_text_alocation_size  =  (self->rendered_text_alocation_size  * 2)+2;
        self->rendered_text = (char*)(realloc(
            self->rendered_text,self->rendered_text_alocation_size
        ));
    }
}

void CTextStack_text(struct CTextStack *self, const char *text){

    if (!text || !text[0]) {
        // Tratar caso de ponteiro nulo ou string vazia
        return;
    }

    size_t text_size = strlen(text);

    self->size += text_size;
    private_ctext_text_double_size_if_reachs(self);

    memcpy(
            self->rendered_text + self->size - text_size,
        text,
        text_size
    );
    self->rendered_text[self->size] = '\0';
}



void CTextStack_segment_text(struct CTextStack *self, const char *text){
    CTextStack_segment(self);
    CTextStack_text(self,text);
}


void CTextStack_format(struct CTextStack *self, const char *format, ...){
    va_list  argptr;
    va_start(argptr, format);
    private_ctext_generate_formated_text(self,format,argptr);
}

void CTextStack_segment_format(struct CTextStack *self, const char *format, ...){
    CTextStack_segment(self);
    va_list  argptr;
    va_start(argptr, format);
    private_ctext_generate_formated_text(self,format,argptr);
}


void CTextStack_segment(struct CTextStack *self){

    CTextStack_text(self,self->line_breaker);

    for(int i=0;i<self->ident_level;i++){
        CTextStack_text(self,self->separator);

    }


}

void CTextStack_$open(struct CTextStack *self, const char *tag, const char *format, ...){
    CTextStack_segment(self);
    CTextStack_format(self, "%c",'<');
    CTextStack_text(self,tag);


    if(format!=NULL){
        CTextStack_format(self, "%c",' ');

        va_list  argptr;
        va_start(argptr, format);
        private_ctext_generate_formated_text(self,format,argptr);
    }
    CTextStack_format(self, "%c",'>');


    self->ident_level += 1;
}



void CTextStack_only$open(struct CTextStack *self, const char *tag, const char *format, ...){
    CTextStack_segment(self);
    CTextStack_format(self, "%c",'<');

    CTextStack_text(self,tag);


    if(format!=NULL){
        CTextStack_format(self, "%c",' ');
        va_list  argptr;
        va_start(argptr, format);
        private_ctext_generate_formated_text(self,format,argptr);
    }
    CTextStack_format(self, "%c",'>');


}

void CTextStack_auto$close(struct CTextStack *self, const char *tag, const char *format, ...){
    CTextStack_segment(self);
    CTextStack_format(self, "%c",'<');

    CTextStack_text(self,tag);


    if(format!=NULL){
        CTextStack_format(self, "%c",' ');

        va_list  argptr;
        va_start(argptr, format);
        private_ctext_generate_formated_text(self,format,argptr);
    }
    CTextStack_text(self,"/>");

}

void ctext_open(struct CTextStack *self, const char *tag){
    if(tag ==  NULL){

        self->ident_level += 1;
        return;
    }
    CTextStack_$open(self, tag, NULL);
}



void ctext_close(struct CTextStack *self, const char *tag){

    if(tag==NULL){
        self->ident_level -= 1;

        return;
    }
    self->ident_level -= 1;
    CTextStack_segment(self);


    CTextStack_text(self,"</");
    CTextStack_text(self,tag);
    CTextStack_format(self, "%c",'>');

}







void private_ctext_generate_formated_text(
        struct CTextStack *stack,const char *format,va_list argptr){
    long  text_size = strlen(format);

    int i;
    for(i =0;i < text_size -1 ;i++){

        char single_test[3] = {format[i],format[i+1],'\0'};
        char double_test[4] = {0};


        if(i < text_size -2){
            strcpy(double_test,single_test);
            double_test[2] = format[i+2];
            double_test[3] = '\0';

        }

        if(strcmp(single_test,"%d") == 0) {
            char result[20] ={0};
            sprintf(result,"%ld", va_arg(argptr,long));
            CTextStack_text(stack,result);
            i+=1;
            continue;
        }

        if(strcmp(single_test,"%f") == 0) {
            char result_text[20]= {0};

            sprintf(result_text,"%lf", va_arg(argptr,double ));

            for(int t = 18; t > 0; t--){
                char current_char = result_text[t];
                if(current_char != '0' && current_char != '\0'){

                    if(current_char == '.'){
                        result_text[t+2]  = '\0';
                    }
                    else{
                        result_text[t+1]  = '\0';
                    }

                    break;
                }
            }
            CTextStack_text(stack,result_text);
            i+=1;
            continue;
        }

        else if(strcmp(single_test,"%c") == 0){
            char result = va_arg(argptr,int);
            char element[2] = {result,'\0'};
            CTextStack_text(stack,element);
            i+=1;
            continue;
        }


        else if(strcmp(single_test,"%b") == 0){
            bool value = va_arg(argptr,int);
            if(value){
                CTextStack_text(stack,"true");
            }else{
                CTextStack_text(stack,"false");
            }
            i+=1;
            continue;
        }

        else if(strcmp(double_test,"%sc") == 0){
            char *value = va_arg(argptr,char*);
            CTextStack_text(stack,value);
            free(value);
            i+=2;
            continue;
        }

        else if(strcmp(single_test,"%s") == 0){
            const char *value = va_arg(argptr,const char*);
            CTextStack_text(stack,value);
            i+=1;
            continue;
        }
        else if(strcmp(double_test,"%tc") == 0){
            struct CTextStack *new_stack = (struct  CTextStack*)va_arg(argptr,void *);
            char *result = CTextStack_self_transform_in_string_and_self_clear(new_stack);
            CTextStack_text(stack,result);
            free(result);
            i+=2;
            continue;
        }

        else if(strcmp(single_test,"%t") == 0){
            struct CTextStack *new_stack = (struct  CTextStack*)va_arg(argptr,void *);
            CTextStack_text(stack,new_stack->rendered_text);
            i+=1;
            continue;
        }

        char element[2] = {format[i],'\0'};
        CTextStack_text(stack,element);

        }



    if(text_size > 0 && text_size> i){
        char element[2] = {format[text_size-1],'\0'};
        CTextStack_text(stack,element);
    }

    va_end(argptr);
}


long private_CText_transform_index(long size , long value){
    long formated_value = value;

    if(formated_value >= size){
        formated_value = size;
    }

    if(formated_value  < 0){
        formated_value = size + (formated_value +1);
    }
    if(formated_value <0){
        formated_value = 0;
    }
    return formated_value;
}


CTextArray * newCTextArray(){
    CTextArray  *self = (CTextArray*) malloc(sizeof (CTextArray));
    self->size = 0;
    self->stacks = (CTextStack**) malloc(0);
    return self;
}

void CTextArray_append(CTextArray *self,CTextStack *element){
    self->stacks =  (CTextStack**) realloc(
            self->stacks,
            (self->size+1)* sizeof (CTextStack*)
            );

    self->stacks[self->size] = element;
    self->size+=1;
}



void CTextArray_append_string(CTextArray *self,const char *element){
    CTextStack *new_element = newCTextStack_string(element);
    CTextArray_append(self,new_element);
}

CTextStack * CTextArray_join(CTextArray *self,const char *separator){
    CTextStack  *result  = newCTextStack_string_empty();
    for(int i = 0; i < self->size; i++){
        if(i < self->size -1){
            CTextStack_format(result,"%t%s",self->stacks[i],separator);
        }
        else{
            CTextStack_format(result,"%t",self->stacks[i]);

        }

    }
    return result;
}

CTextArray *CTextArray_split(const char *element,const char *target){
    CTextArray *self = newCTextArray();
    CTextStack *text = newCTextStack_string(element);
    long target_size = (long)strlen(target);
    CTextStack  *acumulated = newCTextStack_string_empty();

    for(int i = 0; i <text->size; i++){
        CTextStack  *possible_division = CTextStack_substr(text,i,target_size + i);
        if(CTextStack_equal(possible_division,target)){
            CTextArray_append(self,acumulated);
            acumulated = newCTextStack_string_empty();
            CTextStack_free(possible_division);
            continue;
        }
        CTextStack_free(possible_division);

        CTextStack_format(acumulated,"%c",text->rendered_text[i]);
    }

    CTextArray_append(self,acumulated);
    CTextStack_free(text);
    return self;
}

bool CTextStack_equal(struct  CTextStack *self,const char *element){
    return strcmp(self->rendered_text,element) == 0;
}


void  CTextArray_free(CTextArray *self){
    for(int i = 0; i < self->size; i++){
            CTextStack_free(self->stacks[i]);
    }
    free(self->stacks);
    free(self);
}

CTextArray * CTextArray_map(CTextArray *self, CTextStack *(caller)(CTextStack* element)){
    CTextArray *new_array  = newCTextArray();
    for(int i = 0; i < self->size; i++){
        CTextStack *result = caller(self->stacks[i]);
        CTextArray_append(new_array,result);
    }
    return new_array;
}


CTextArray * CTextArray_filter(CTextArray *self, bool (caller)(CTextStack* element)){
    CTextArray *new_array  = newCTextArray();

    for(int i = 0; i < self->size; i++){
        if(caller(self->stacks[i])){

            CTextArray_append(new_array, CTextStack_clone(self->stacks[i]));
        }
    }

    return new_array;
}

void  CTextArray_foreach(CTextArray *self, void (*caller)(CTextStack* element)){
    for(int i = 0; i < self->size; i++){
        caller(self->stacks[i]);
    }
}

bool CTextArray_includes(CTextArray *self,const char *element){
    for(int i = 0 ; i < self->size;i++){
        if(CTextStack_equal(self->stacks[i],element)){
            return true;
        }
    }
    return false;
}


void CTextArray_represent(CTextArray *self){
    for(int i =0; i < self->size; i++){
        CTextStack_represent(self->stacks[i]);
    }
}



CTextStackModule newCTextStackModule(){
    struct CTextStackModule self = {0};
    self.newStack = newCTextStack;
    self.newStack_string = newCTextStack_string;
    self.newStack_string_format = newCTextStack_string_format;
    self.newStack_string_empty = newCTextStack_string_empty;
    self.newStack_string_getting_ownership = newCTextStack_string_getting_ownership;
    self.text = CTextStack_text;
    self.segment_text = CTextStack_segment_text;
    self.format = CTextStack_format;
    self.segment = CTextStack_segment;
    self.segment_format = CTextStack_segment_format;
    self.$open = CTextStack_$open;
    self.only$open =CTextStack_only$open;
    self.auto$close = CTextStack_auto$close;
    self.open = ctext_open;
    self.close = ctext_close;
    self.free =  CTextStack_free;
    self.clone = CTextStack_clone;
    self.represent = CTextStack_represent;
    self.self_transform_in_string_and_self_clear = CTextStack_self_transform_in_string_and_self_clear;
    self.restart = CTextStack_restart;
    self.substr = CTextStack_substr;
    self.self_substr =CTextStack_self_substr;

    self.pop = CTextStack_pop;
    self.self_pop =CTextStack_self_pop;

    self.replace = CTextStack_replace;
    self.self_replace = CTextStack_self_replace;

    self.replace_long = CTextStack_replace_long;
    self.self_replace_long =CTextStack_self_replace_long;


    self.replace_double = CTextStack_replace_double;
    self.self_replace_double =CTextStack_self_replace_double;

    self.insert_at = CTextStack_insert_at;
    self.self_insert_at  = CTextStack_self_insert_at;


    self.index_of = CTextStack_index_of;
    self.index_of_char = CTextStack_index_of_char;

    self.lower = CTextStack_lower;
    self.self_lower = CTextStack_self_lower;

    self.upper = CTextStack_upper;
    self.self_upper = CTextStack_self_upper;

    self.captalize = CTextStack_captalize;
    self.self_captalize = CTextStack_self_captalize;

    self.starts_with = CTextStack_starts_with;
    self.ends_with = CTextStack_ends_with;

    self.equal = CTextStack_equal;
    self.reverse = CTextStack_reverse;
    self.self_reverse = CTextStack_self_reverse;


    self.typeof_element = CTextStack_typeof;
    self.is_a_num = CTextStack_is_a_num;
    self.typeof_in_str = CTextStack_typeof_in_str;
    self.parse_to_bool = CTextStack_parse_to_bool;
    self.parse_to_integer = CTextStack_parse_to_integer;
    self.parse_to_double = CTextStack_parse_to_double;

    self.trim = CTextStack_trim;
    self.self_trim = CTextStack_self_trim;


    return self;
}



CTextArrayModule newCTextArrayModule(){
    CTextArrayModule module = {0};
    module.newArray = newCTextArray;
    module.append = CTextArray_append;
    module.append_string = CTextArray_append_string;
    module.join = CTextArray_join;
    module.map  = CTextArray_map;
    module.filter = CTextArray_filter;
    module.foreach = CTextArray_foreach;
    module.represent = CTextArray_represent;
    module.includes = CTextArray_includes;
    module.free = CTextArray_free;
    return module;
}




CTextNamespace newCTextNamespace(){
    CTextNamespace self  = {0};
    self.stack = newCTextStackModule();
    self.array = newCTextArrayModule();
    return self;
}


#endif






char *privateCHash_read_file(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);


    char *buffer = (char *)malloc(file_size + 1);


    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);
    return buffer;
}

int  privateCHash_write_file(const char *filename, const char *value) {

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        return 1;
    }
    fputs(value, file);

    fclose(file);
    return 0;
}



CHash * privatenewChash_raw(){
    CHash  *self = (CHash*) malloc(sizeof (CHash));
    *self = (CHash){0};
    return self;
}

void CHash_print(CHash *self){
    char * result = CHash_dump_to_json_string(self);
    printf("%s\n",result);
    free(result);
}

CHashArray * CHash_get_path(CHash *self){

    if(self->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE){
        return newCHashArrayEmpty();
    }

    CHashArray  *path = CHash_get_path(self->private_father);

    if(self->private_reference_type == PRIVATE_CHASH_ARRAY_ITEM){
        CHashArray_append(path, newCHashNumber(self->private_index));
    }

    if(self->private_reference_type == PRIVATE_CHASH_KEYVAL){
        CHashArray_append(path, newCHashString(self->private_key));
    }
    return path;

}

bool CHash_equals(CHash *element1, CHash *element2){
    if(!element1  && !element2){
        return true;
    }
    if(element1 && element2){
        char *element1_str = CHash_dump_to_json_string(element1);
        char *element2_str = CHash_dump_to_json_string(element2);

        bool equal = strcmp(element1_str,element2_str) == 0;
        free(element1_str);
        free(element2_str);
        return equal;
    }
    return  false;

}

void privateCHash_free_values(CHash *self){

    if(self->private_type == CHASH_STRING){
        CTextStack_free(self->private_value_stack);
    }

    if(self->private_type == CHASH_OBJECT || self->private_type == CHASH_ARRAY){
        long size = (long)self->private_size;
        for(int i = 0; i < size; i++){
            CHash * current = self->private_sub_elements[i];
            CHash_free(current);
        }
        free(self->private_sub_elements);
    }

}
void CHash_free(CHash *self){
    if(!self){
        return;
    }
    if(self->private_reference_type == PRIVATE_CHASH_KEYVAL){
        free(self->private_key);
    }
    if(self->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE){
        if(self->private_error){
            privateCHashError *error = (privateCHashError*)self->private_error;
            privateCHashError_free(error);
        }
    }

    privateCHash_free_values(self);

    free(self);
}


void CHash_set(CHash *self,CHash *element){
    if(Chash_errors(self)){
        return;
    }
    privateCHash_free_values(self);
    CHash  *target_element = privateCHash_copy_if_its_an_reference(element);

    self->private_type = target_element->private_type;
    self->private_size = target_element->private_size;

    if(self->private_type == CHASH_STRING){
        self->private_value_stack = target_element->private_value_stack;
    }

    if(self->private_type == CHASH_BOOL){
        self->private_value_bool = target_element->private_value_bool;
    }

    if(self->private_type == CHASH_NUMBER){
        self->private_value_double = target_element->private_value_double;
    }

    if(self->private_type == CHASH_OBJECT || self->private_type == CHASH_ARRAY){
        self->private_sub_elements = target_element->private_sub_elements;
        for (int i = 0; i < self->private_size; i++){
            CHash  *current = self->private_sub_elements[i];
            current->private_father = self->private_father;
        }
    }

    free(target_element);

}

long CHash_get_size(CHash *self){
    if(Chash_errors(self)){
       return -1;
    }
    if(self->private_type == CHASH_STRING){
        return (long)self->private_value_stack->size;
    }
    if(self->private_type == CHASH_OBJECT || self->private_type == CHASH_ARRAY){
        return (long)self->private_size;
    }
    CHash_raise_error(self,CHASH_NOT_ITERABLE, "the element at #path# its not an iterable (string,array,object)",NULL);
    return -1;
}


CHash * CHash_copy(CHash *self){
    if(!self){
        return newCHashNULL();
    }

    if(self->private_type == CHASH_STRING){
        return newCHashString(self->private_value_stack->rendered_text);
    }


    if(self->private_type == CHASH_NUMBER){
        return newCHashNumber(self->private_value_double);
    }

    if(self->private_type == CHASH_BOOL){
        return newCHashBool(self->private_value_bool);
    }

    if(self->private_type == CHASH_ARRAY ){
        CHash * new_element  = newCHashArrayEmpty();

        for(long i =0; i < self->private_size; i++){
            CHash * copy = CHash_copy(CHashArray_get(self,i));
            CHashArray_append(new_element, copy);
        }
        return new_element;

    }

    if(self->private_type == CHASH_OBJECT){
        CHash * new_element  = newCHashObjectEmpty();

        for(long  i =0; i < self->private_size; i++){
            CHash  * current = CHashArray_get(self,i);
            CHash *copy = CHash_copy(current);

            CHashObject_set_many(new_element, current->private_key, copy);
        }
        return new_element;
    }


    return newCHashNULL();
}
CHash * privateCHash_copy_if_its_an_reference(CHash *self){
    if(!self){
        return NULL;
    }

    if(self->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE){
        return self;
    }
    return CHash_copy(self);

}
CHash * privateCHash_get_first_object(CHash *self){
    if(self->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE) {
        return self;
    }
    return privateCHash_get_first_object(self->private_father);

}
CHash * newCHashNULL(){
    return privatenewChash_raw();
}




double CHash_toNumber(CHash *element){

    if(CHash_ensure_Number(element)){
        return -1;
    }
    return element->private_value_double;

}
int CHash_convert_toNumber(CHash *self){
    if(Chash_errors(self)){
        return 1;
    }
    if(self->private_type == CHASH_NUMBER){
        return 0;
    }
    if(self->private_type != CHASH_STRING){
        CHash_raise_error(self,
                          CHASH_WRONG_TYPE,
                          "element at #path# is not convertible to number ",
                         newCHashObject(
                                  "expected_type", newCHashString(
                                  private_Chash_convert_type(CHASH_NUMBER)
                                )
                          )
        );
        return 1;
    }

    if(!CTextStack_is_a_num(self->private_value_stack)){
        CHash_raise_error(self,
                          CHASH_WRONG_TYPE,
                          "element at #path# is not convertible to number ",
                         newCHashObject(
                                  "expected_type", newCHashString(
                                  private_Chash_convert_type(CHASH_NUMBER)
                                )
                          )
        );
        return 1;
    }

    double  value = CTextStack_parse_to_double(self->private_value_stack);
    CHash_set_Number(self,value);
    return 0;
}

double  CHash_toNumber_converting(CHash *self){
    if(CHash_convert_toNumber(self)){
        return -1;
    }
    return self->private_value_double;
}


void CHash_set_Number(CHash *self,double  value){
    if(Chash_errors(self)){
        return;
    }

    privateCHash_free_values(self);
    self->private_type = CHASH_NUMBER;
    self->private_value_double = value;

}



CHash * newCHashNumber(double value){
    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_NUMBER;
    self->private_value_double = value;
    return self;
}





bool CHash_toBool(CHash *element){
    if(CHash_ensure_Bool(element)){
        return false;
    }
    return element->private_value_bool;
}

int CHash_convert_toBool(CHash *self){

    if(Chash_errors(self)){
        return 1;
    }

    if(self->private_type == CHASH_BOOL){
        return 0;
    }

    if(self->private_type == CHASH_NUMBER){
        CHash_set_Bool(self,(bool)self->private_value_double);
        return 0;
    }


    if(self->private_type != CHASH_STRING){
        CHash_raise_error(self,
                          CHASH_WRONG_TYPE,
                          "element at #path# is not convertable to number ",
                         newCHashObject(
                                  "expected_type", newCHashString(
                                  private_Chash_convert_type(CHASH_BOOL)
                                )
                          )
        );
        return 1;
    }

    int type  = CTextStack_typeof(self->private_value_stack);

    if(type != CTEXT_BOOL){
        CHash_raise_error(self,
                          CHASH_WRONG_TYPE,
                          "element at #path# is not convertible to bool ",
                        newCHashObject(
                                  "expected_type", newCHashString(
                                  private_Chash_convert_type(CHASH_BOOL)
                                )
                          )
        );
        return 1;
    }

    bool  value = CTextStack_parse_to_bool(self->private_value_stack);
    CHash_set_Bool(self,value);
    return 0;

}

bool CHash_toBool_converting(CHash *self){

    if(CHash_convert_toBool(self)){
        return false;
    }
    return self->private_value_bool;
}


void CHash_set_Bool(CHash *self, bool value){
    if(Chash_errors(self)){
        return;
    }

    privateCHash_free_values(self);
    self->private_type = CHASH_BOOL;
    self->private_value_bool = value;
}


CHash * newCHashBool(bool value){
    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_BOOL;
    self->private_value_bool = value;
    return self;
}









char * CHash_toString(CHashArray *element){
    if(CHash_ensure_String(element)){
        return NULL;
    }

    return element->private_value_stack->rendered_text;
}
void CHash_set_String(CHash *self, const char *value){
    if(Chash_errors(self)){
        return;
    }
    privateCHash_free_values(self);
    self->private_type = CHASH_STRING;
    self->private_value_stack = newCTextStack_string(value);

}
void CHash_set_Stack(CHash *self,CTextStack *element){
    if(Chash_errors(self)){
        return;
    }
    privateCHash_free_values(self);
    self->private_type = CHASH_STRING;
    self->private_value_stack = element;
}

CTextStack  *CHashtoStack(CHash *element){
    if(CHash_ensure_String(element)){
        return NULL;
    }
    if(element->private_type != CHASH_STRING){
        return NULL;
    }
    return element->private_value_stack;
}

CHash * newCHashStackString(CTextStack *element){

    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_STRING;
    self->private_value_stack = element;
    return self;
}

CHash * newCHashString(const char *value){
    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_STRING;
    self->private_value_stack = newCTextStack_string(value);
    return self;
}


CHashArray  *newCHashArrayEmpty(){
    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_ARRAY;
    self->private_sub_elements = (CHash**)malloc(0);
    self->private_size = 0;
    return self;
}

CHashArray * privatenewCHashArray(void *sentinel, ...){
    CHash * self =  newCHashArrayEmpty();

    va_list args;
    va_start(args, sentinel);


    while(true){
        void * current = va_arg(args,void*);
        if(!current){
            break;
        }

        CHash * current_element = (CHash*)current;
        CHashArray_append_any(self, current_element);
    }
    va_end(args);
    return self;
}

CHashArray * privatenewCHashStringArray(void *sentinel, ...){
    CHash * self =  newCHashArrayEmpty();

    va_list args;
    va_start(args, sentinel);


    while(true){
        char  * current = va_arg(args,char*);
        if(!current){
            break;
        }
        CHashArray_append_any(self, newCHashString(current));
    }
    va_end(args);
    return self;
}

void CHashArray_append_any(CHashArray *self, CHash *element){

    if(CHash_ensure_Array(self)){
        return ;
    }

    CHash *new_element = privateCHash_copy_if_its_an_reference(element);

    self->private_sub_elements = (CHash**) realloc(
            self->private_sub_elements,
            (self->private_size + 1) * sizeof(CHash**)
    );
    new_element->private_reference_type = PRIVATE_CHASH_ARRAY_ITEM;
    new_element->private_father = self;
    new_element->private_index = self->private_size;
    self->private_sub_elements[self->private_size]= new_element;
    self->private_size+=1;


}

void CHashArray_append_long(CHashArray *self, long element){
    CHashArray_append_any(self, newCHashNumber((double)element));
}
void CHashArray_append_double(CHashArray *self, double element){
    CHashArray_append_any(self, newCHashNumber(element));

}
void CHashArray_append_bool(CHashArray *self, bool element){
    CHashArray_append_any(self, newCHashBool(element));

}
void CHashArray_append_string(CHashArray *self, const char *element){
    CHashArray_append_any(self, newCHashString(element));
}

void CHashArray_append_stack(CHashArray *self, CTextStack *element){
    CHashArray_append_any(self, newCHashStackString(element));
}


void privateCHashArray_append(CHashArray *self, ...){

    if(CHash_ensure_Array(self)){
        return;
    }

    va_list args;
    va_start(args, self);
    while(true){
        void * current = va_arg(args,void*);
        if(!current){
            break;
        }
        CHash * current_element = (CHash*)current;
        CHashArray_append_any(self, current_element);
    }
    va_end(args);

}
void  CHashArray_set(CHashArrayOrObject *self, long index,CHash *element){
    if(privateCHash_ensureArrayOrObject(self)){
        return;
    }
    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return ;
    }

    CHash *new_element = privateCHash_copy_if_its_an_reference(element);

    CHash  *current = self->private_sub_elements[formated_index];
    CHash_free(current);


    self->private_sub_elements[formated_index] = new_element;

}
void  CHashArray_set_long(CHashArrayOrObject *self, long index,long value){
    CHashArray_set(self,index, newCHashNumber((double)value));
}
void  CHashArray_set_double(CHashArrayOrObject *self, long index,double value){
    CHashArray_set(self,index, newCHashNumber(value));

}
void  CHashArray_set_bool(CHashArrayOrObject *self, long index,bool value){
    CHashArray_set(self,index, newCHashBool(value));

}
void  CHashArray_set_string(CHashArrayOrObject *self, long index,const char *value){
    CHashArray_set(self,index, newCHashString(value));
}
void  CHashArray_set_stack(CHashArrayOrObject *self, long index,CTextStack *value){
    CHashArray_set(self,index, newCHashStackString(value));
}


void CHashArray_remove(CHashArrayOrObject *self, long index){

    if(privateCHash_ensureArrayOrObject(self)){
        return;
    }
    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return ;
    }


    CHash  *current = self->private_sub_elements[formated_index];

    CHash_free(current);
    self->private_size-=1;

    for(long i = formated_index; i <  self->private_size;i++){
        self->private_sub_elements[i] = self->private_sub_elements[i + 1];

    }
}
long privateCHashArray_convert_index(CHashArrayOrObject *self, long index){
    long formated_index = index;
    if(index < 0){
        formated_index = (long)self->private_size +index;
    }
    if(formated_index < 0|| formated_index>= self->private_size){
        CHash_raise_error(
                self,
                CHASH_NOT_VALID_INDEX,
                " index: #index# its not valid, at #path#",
                newCHashObject(
                        "index", newCHashNumber(index)
                )
        );
        return -1;
    }
    return formated_index;
}
CHash * CHashArray_get(CHashArrayOrObject *self, long index){
    if(privateCHash_ensureArrayOrObject(self)){
        return NULL;

    }

    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return NULL;
    }

    return self->private_sub_elements[formated_index];
}

long CHashArray_find(CHashArray *self, CHash *element){
    long size = CHash_get_size(self);
    for(long i = 0; i < size; i++){
        CHash *current = CHashArray_get(self,i);
        if(CHash_equals(current,element)){
            return i;
        }
    }
    return -1;
}
long CHashArray_find_Number(CHashArray *self, double element){
    CHash *created = newCHashNumber(element);
    long index = CHashArray_find(self,created);
    CHash_free(created);
    return index;
}

long CHashArray_find_Bool(CHashArray *self, bool  element){
    CHash *created = newCHashBool(element);
    long index = CHashArray_find(self,created);
    CHash_free(created);
    return index;
}

long CHashArray_find_String(CHashArray *self, const char *element){
    CHash *created = newCHashString(element);
    long index = CHashArray_find(self,created);
    CHash_free(created);
    return index;
}



short CHashArray_get_type(CHashArray *self, long index){
    if(privateCHash_ensureArrayOrObject(self)){
        return CHASH_NOT_EXIST;
    }
    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return CHASH_NOT_EXIST;
    }
    CHash  *element = self->private_sub_elements[formated_index];
    return CHash_get_type(element);

}

void CHashArray_switch(CHashArrayOrObject *self, long index ,long target_index){
    if(privateCHash_ensureArrayOrObject(self)){
        return ;
    }
    long formated_index = privateCHashArray_convert_index(self,index);
    if(formated_index == -1){
        return;
    }
    long formated_target_index = privateCHashArray_convert_index(self,target_index);
    if(formated_target_index == -1){
        return;
    }

    CHash *changed = self->private_sub_elements[formated_index];

    self->private_sub_elements[formated_index] =  self->private_sub_elements[target_index];
    self->private_sub_elements[formated_index]->private_index = formated_index;

    self->private_sub_elements[target_index] = changed;
    changed->private_index = target_index;

}
CHashArray * CHashArray_getArray(CHashArrayOrObject * self, long index){
    CHash *element = CHashArray_get(self,index);
    if(CHash_ensure_Array(element)){
        return NULL;
    }
    return  element;
}

CHashObject * CHashArray_getObject(CHashArrayOrObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    if(CHash_ensure_Object(element)){
        return NULL;
    }
    return element;
}



double CHashArray_getNumber(CHashArrayOrObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toNumber(element);
}

double CHashArray_getNumber_converting(CHashArrayOrObject *self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toNumber_converting(element);
}

bool CHashArray_getBool(CHashArrayOrObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toBool(element);

}

bool CHashArray_getBool_converting(CHashObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toBool_converting(element);
}

char  * CHashArray_getString(CHashArrayOrObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHash_toString(element);
}
CTextStack  * CHashArray_getStack(CHashObject * self, long index){
    CHashObject *element = CHashArray_get(self,index);
    return CHashtoStack(element);
}



void CHashArray_foreach(CHashArray *self,void  (*callback)(CHash *current)){
    if(privateCHash_ensureArrayOrObject(self)){
        return;
    }
    long size = CHash_get_size(self);
    for(long i = 0; i < size;i++){

        CHash *current = CHashArray_get(self,i);
        callback(current);
        if(Chash_errors(self)){
            break;
        }
    }
}
void CHashArray_foreach_with_args(CHashArray *self,void  (*callback)(CHash *current,va_list args),...){

    if(privateCHash_ensureArrayOrObject(self)){
        return;
    }
    long size = CHash_get_size(self);

    for(long i = 0; i < size;i++){
        va_list  args;
        va_start(args, callback);
        CHash *current = CHashArray_get(self,i);
        callback(current,args);
        va_end(args);
        if(Chash_errors(self)){
            break;
        }
    }

}
/*
CHashArray * CHashArray_map(CHashArray *self,CHash* (*callback)(CHash *current)){

    if(privateCHash_ensureArrayOrObject(self)){
        return NULL;
    }

    CHashArray  *new_element = newCHashArrayEmpty();

    long size = CHash_get_size(self);
    for(long i = 0; i < size;i++){

        CHash *current = CHashArray_get(self,i);
        CHash *created = callback(current);
        if(Chash_errors(self)){
            CHash_free(new_element);
            CHash_free(created);
            return NULL;
        }
        CHashArray_append_once(new_element,current);
    }
    return  new_element;
}

CHashArray * CHashArray_map_with_args(CHashArray *self,CHash* (*callback)(CHash *current,va_list args),...){

    if(CHash_ensure_Array(self)){
        return NULL;
    }
    CHashArray  *new_element = newCHashArrayEmpty();

    long size = CHash_get_size(self);
    for(long i = 0; i < size;i++){
        va_list  args;
        va_start(args, callback);
        CHash *current = CHashArray_get(self,i);
        CHash *created = callback(current,args);
        va_end(args);
        if(Chash_errors(self)){
            CHash_free(new_element);
            CHash_free(created);
            return NULL;
        }
        CHashArray_append_once(new_element,current);
    }
    return  new_element;
}
*/





CHashObject  * newCHashObjectEmpty(){
    CHash * self =  privatenewChash_raw();
    self->private_type = CHASH_OBJECT;
    self->private_sub_elements = (CHash**)malloc(0);
    self->private_size = 0;
    return self;
}

CHashObject* privatenewCHashObject(void * sentinel, ...){
    CHash * self =  newCHashObjectEmpty();

    va_list args;
    va_start(args, sentinel);

    const int GETTING_KEY = 0;
    const int GETTING_VALUE = 1;


    int state = GETTING_KEY;
    char *key = NULL;

    while(true){
        void * current = va_arg(args,void*);

        if(!current){
            break;
        }

        if(state == GETTING_KEY){
            key = (char*)current;
            state = GETTING_VALUE;
            continue;
        }

        if(state == GETTING_VALUE){
            CHashObject_set_any(self, key, (CHash *) current);
            state = GETTING_KEY;

        }

    }

    va_end(args);

    return self;
}


CHash * privateCHashObject_get_by_key_or_null(CHashObject * self, const char *key){
    if(Chash_errors(self)){
        return NULL;
    }
    for(int i =0;i < self->private_size; i ++){
        CHash * current = self->private_sub_elements[i];
        if(strcmp(current->private_key, key) == 0){
            return current;
        }
    }
    return NULL;
}

bool CHashObject_exist(CHashObject *self, const char *key){
    CHash  *element = privateCHashObject_get_by_key_or_null(self,key);
    if(element){
        return  true;
    }
    return false;
}



char * CHashObject_get_key_by_index(CHashObject *self,long index){
    CHash  *element = CHashArray_get(self,index);
    if(!element){
        return NULL;
    }
    return CHashObject_get_key_of_element(element);
}



char   * CHashObject_get_key_of_element(CHash *self){
    if(Chash_errors(self)){
        return NULL;
    }
    if(self->private_reference_type != PRIVATE_CHASH_KEYVAL){
        CHash_raise_error(self,CHASH_NOT_HAVE_KEY,"element of #path# does not have an key",NULL);
    }
    return self->private_key;
}



void  CHashObject_remove(CHashObject *self, const char *key){
    if(CHash_ensure_Object(self)){
        return ;
    }

    bool found = false;

    for(int i =0;i < self->private_size; i ++){
        CHash * current = self->private_sub_elements[i];
        if(strcmp(current->private_key, key) == 0){
            CHash_free(current);
            found = true;
            self->private_size-=1;
        }

        if(found && i < self->private_size){
            self->private_sub_elements[i] = self->private_sub_elements[i + 1];
        }

    }

}
void  CHashObject_set_any(CHashObject * self, const char *key, CHash *element){
    if(CHash_ensure_Object(self)){
        return ;
    }

    CHash *formated_element = privateCHash_copy_if_its_an_reference(element);

    CHashObject_remove(self, key);

    self->private_sub_elements = (CHash**) realloc(
            self->private_sub_elements,
            (self->private_size + 1) * sizeof(CHash**)
    );

    formated_element->private_reference_type = PRIVATE_CHASH_KEYVAL;
    formated_element->private_father = self;
    formated_element->private_key = strdup(key);
    self->private_sub_elements[self->private_size]= formated_element;
    self->private_size+=1;
}

void  CHashObject_set_long(CHashObject * self, const char *key, long value){
    CHashObject_set_any(self,key, newCHashNumber((double)value));
}

void  CHashObject_set_double(CHashObject * self, const char *key, double value){
    CHashObject_set_any(self,key, newCHashNumber(value));
}

void  CHashObject_set_bool(CHashObject * self, const char *key, bool value){
    CHashObject_set_any(self,key, newCHashBool(value));
}

void  CHashObject_set_string(CHashObject * self, const char *key, const char *value){
    CHashObject_set_any(self,key, newCHashString(value));
}


void  CHashObject_set_Stack(CHashObject * self, const char *key,CTextStack *stack_value){
    CHashObject_set_any(self,key, newCHashStackString(stack_value));
}


void  CHashObject_set_default(CHashObject * self, const char *key, CHash *element){
    if(CHashObject_exist(self,key)){
        if(element->private_reference_type == PRIVATE_CHASH_NOT_A_REFERENCE){
            CHash_free(element);
        }
        return;
    }
    CHashObject_set_any(self, key, element);
}





void  privateCHashObject_set(CHashObject *self , ...){

    if(CHash_ensure_Object(self)){
        return;
    }
    va_list args;

    va_start(args, self);

    const int GETTING_KEY = 0;
    const int GETTING_VALUE = 1;

    int state = GETTING_KEY;

    char *key =NULL;

    while (true){
        void * current = va_arg(args,void*);
        if(!current){
            break;
        }

        if(state == GETTING_KEY){
            key = (char*)current;
            state = GETTING_VALUE;
            continue;
        }

        if(state == GETTING_VALUE){
            CHashObject_set_any(self, key, (CHash *) current);

            state = GETTING_KEY;
        }

    }
    va_end(args);

}
short  CHashObject_get_type(CHashObject *self, const char *key){
    CHash  *element = privateCHashObject_get_by_key_or_null(self,key);
    return CHash_get_type(element);
}


CHash * CHashObject_get(CHashObject * self, const char *key){

    if(CHash_ensure_Object(self)){
        return NULL;
    }

    CHash *element = privateCHashObject_get_by_key_or_null(self, key);

    if(element){
        return  element;
    }


    CHash_raise_error(self,
                      CHASH_ELEMENT_NOT_EXIST,
                      "element of key:#key# at #path# not exist",
                      newCHashObject("key", newCHashString(key))
    );

    return  NULL;
}
CHashArray * CHashObject_getArray(CHashObject * self, const char *key){
    CHashArray  *element = CHashObject_get(self,key);
    if(CHash_ensure_Array(element)){
        return NULL;
    };

    return element;
}

CHashObject * CHashObject_getObject(CHashObject * self, const char *key){

    CHashObject *element = CHashObject_get(self,key);
    if(CHash_ensure_Object(element)){
        return NULL;
    }
    return element;
}



double CHashObject_getNumber(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toNumber(element);
}

double CHashObject_getNumber_converting(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toNumber_converting(element);
}

bool CHashObject_getBool(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toBool(element);
}

bool CHashObject_getBool_converting(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toBool_converting(element);
}

char  * CHashObject_getString(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHash_toString(element);
}

CTextStack * CHashObject_getStack(CHashObject * self, const char *key){
    CHash *element = CHashObject_get(self,key);
    return CHashtoStack(element);
}







short CHash_get_type(CHash *self){
    if(Chash_errors(self)){
        return CHASH_NOT_EXIST;
    }
    return self->private_type;
}

const char  *private_Chash_convert_type(long type){

    if(type == CHASH_NULL){
        return "null";
    }
    if(type == CHASH_STRING){
        return "string";
    }
    if(type == CHASH_ARRAY){
        return "array";
    }

    if(type == CHASH_OBJECT){
        return "object";
    }

    if(type == CHASH_NUMBER){
        return "number";
    }

    if(type == CHASH_BOOL){
        return "bool";
    }

    return "not exist";
}




cJSON * privateCHash_dumps_json_object(CHashObject * object){
    long size = object->private_size;
    cJSON * element = cJSON_CreateObject();
    for(int i = 0; i < size; i++){
        CHashArray *current  = CHashArray_get(object, i);
        cJSON *current_json = CHash_dump_to_cJSON(current);
        cJSON_AddItemToObject(element, current->private_key, current_json);
    }
    return element;
}

cJSON * privateCHash_dumps_json_array(CHashArray * array){
    long size = array->private_size;
    cJSON *element = cJSON_CreateArray();
    for(int i = 0; i < size; i++){
        CHashArray *current  = CHashArray_get(array, i);
        cJSON *current_json = CHash_dump_to_cJSON(current);
        cJSON_AddItemToArray(element,current_json);
    }
    return element;
}


cJSON * CHash_dump_to_cJSON(CHash *element){
    int type = element->private_type;
    if(type == CHASH_OBJECT){
        return privateCHash_dumps_json_object(element);
    }
    if(type == CHASH_ARRAY){
        return privateCHash_dumps_json_array(element);
    }
    if(type == CHASH_STRING){
        char *value  = CHash_toString(element);
        return cJSON_CreateString(value);
    }
    if(type == CHASH_NUMBER){
        return cJSON_CreateNumber(CHash_toNumber(element));
    }

    if(type == CHASH_BOOL){
        return cJSON_CreateBool(CHash_toBool(element));
    }



    return cJSON_CreateNull();

}

char * CHash_dump_to_json_string(CHash * element){
    cJSON * created = CHash_dump_to_cJSON(element);
    char * result  = cJSON_Print(created);
    cJSON_Delete(created);
    return result;
}

int  CHash_dump_to_json_file(CHash *element,const char *filename){
    char *content = CHash_dump_to_json_string(element);
    if(!content){
        return 1;
    }
    privateCHash_write_file(filename,content);
    free(content);
    return 0;

}
CHashArray * privateCHash_load_json_object(cJSON *element){

    int size = cJSON_GetArraySize(element);

    CHashObject *equivalent = newCHashObjectEmpty();

    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(element,i);
        char *key = current->string;
        CHash * value = CHash_load_from_cJSON(current);
        CHashObject_set_any(equivalent, key, value);
    }

    return equivalent;

}

CHash  * privateCHash_load_json_array(cJSON *element){
    int size = cJSON_GetArraySize(element);
    CHashObject *equivalent = newCHashArrayEmpty();
    for(int i = 0; i < size; i++){
        cJSON *current = cJSON_GetArrayItem(element,i);
        CHash * value = CHash_load_from_cJSON(current);
        CHashArray_append_any(equivalent, value);
    }
    return equivalent;
}


CHash * CHash_load_from_cJSON(cJSON *element){

    if(!element){
        return newCHashNULL();
    }

    if(element->type == cJSON_Object){
        return privateCHash_load_json_object(element);
    }

    if(element->type == cJSON_Array){
        return privateCHash_load_json_array(element);
    }
    if(cJSON_IsBool(element)){
        bool value = element->valueint;
        return newCHashBool(value);
    }
    if(element->type == cJSON_String){
        return newCHashString(element->valuestring);
    }

    if(element->type == cJSON_Number){
        return newCHashNumber(element->valuedouble);
    }

    return newCHashNULL();



}

CHash * CHash_load_from_json_strimg(const char *content){
    cJSON *parsed = cJSON_Parse(content);
    if(!parsed){
        CHash *null_element = newCHashNULL();
        CHash_raise_error(null_element,CHASH_NOT_VALID_JSON,
                          "content #content# its not an valid json",
                          newCHashObject("content", newCHashString(content))
        );
        return  null_element;
    }

    CHash *result =CHash_load_from_cJSON(parsed);
    cJSON_Delete(parsed);
    return result;
}

CHash * CHash_load_from_json_file(const char *filename){
    char *content = privateCHash_read_file(filename);
    if(!content){
        CHash *null_element = newCHashNULL();
        CHash_raise_error(null_element,CHASH_FILE_NOT_FOUND,"file at #filepath# not found",
                          newCHashObject("filepath", newCHashString(filename))
        );
        return  null_element;
    }
    CHash *result =  CHash_load_from_json_strimg(content);

    free(content);

    return result;
}








privateCHashError * privatenewCHashError(CHashObject *args, int error_code, const char *error_menssage){
    privateCHashError  *self = (privateCHashError*) malloc(sizeof (privateCHashError));
    self->args = args;
    self->error_code = error_code;
    self->error_mensage =  privateCHashError_create_menssage(args,error_code,error_menssage);

    return self;
}

CTextStack * privateCHashError_create_menssage(CHashObject *args, int error_code, const char *error_mensage){
    CTextStack  * error = newCTextStack_string(error_mensage);

    long args_size = CHash_get_size(args);
    for(int i = 0; i < args_size; i++){
        CHash *current = CHashArray_get(args,i);
        char *key = CHashObject_get_key_of_element(current);
        char *value = CHash_dump_to_json_string(current);
        CTextStack * formated_key = newCTextStack_string_empty();
        CTextStack_format(formated_key,"#%s#",key);
        CTextStack_self_replace(error,formated_key->rendered_text,value);
        CTextStack_free(formated_key);
        free(value);
    }
    return error;
}

void CHash_generate_custom_error(CHash  *self, CHashArray *errors){
    if(!self){
        return;
    }
    if(!Chash_errors(self)){
        return;
    }
    long  size = CHash_get_size(errors);
    long error_code = CHash_get_error_code(self);

    for(int i =0; i < size; i++){
        CHashObject  *current_object = CHashArray_get(errors,i);
        int code = (int)CHashObject_getNumber(current_object,"code");
        char *menssage = CHashObject_getString(current_object,"message");

        if(!Chash_errors(errors) && error_code == code){
          privateCHashError *generated_errror = privateCHashError_get_error(self);

            CTextStack_free(generated_errror->error_mensage);
            generated_errror->error_mensage = privateCHashError_create_menssage(
                    generated_errror->args,
                    code,
                    menssage
                    );
            break;
        }

    }

}

void CHash_generate_custom_error_cleaning_args(CHash  *self, CHashArray *error){
    CHash_generate_custom_error(self,error);
    CHash_free(error);
}

privateCHashError * privateCHashError_get_error(CHash *self){

    CHash  *first =  privateCHash_get_first_object(self);
    if(first->private_error){
        return (privateCHashError*)first->private_error;
    }
    return NULL;
}


bool Chash_errors(CHash *self){

    if(!self){
        return true;
    }

    privateCHashError *error  = privateCHashError_get_error(self);
    if(error){
        return true;
    }
    return false;
}


void CHash_raise_error(CHash *self,int error_code,const char *error_menssage, CHash *args){


    if(Chash_errors(self)){
        CHash_free(args);
        return;
    }

    CHash *formated_args = args;

    if(!args){
        formated_args = newCHashObjectEmpty();
    }
    CHashArray *path = CHash_get_path(self);

    if(CHash_get_size(path) > 0){
        CHash * last = CHashArray_get(path,-1);
        CHashObject_set_default(formated_args,"reference",last);
    }

    CHashObject_set_default(formated_args,  "path",path);
    CHashObject_set_default(formated_args,"value", CHash_copy(self));
    CHashObject_set_default(formated_args,"type",newCHashString(private_Chash_convert_type(self->private_type)));


    privateCHashError *created = privatenewCHashError(
            formated_args,
            error_code,
            error_menssage
    );
    CHash *first = privateCHash_get_first_object(self);
    first->private_error = (void*)created;


}

void CHash_raise_error_by_key(CHash *self,const char *key, int error_code,const char *error_menssage, CHash *args){
    if(Chash_errors(self)){return;}

    CHash *formated_args = args;

    if(!args){
        formated_args = newCHashObjectEmpty();
    }
    CHashArray *path = CHash_get_path(self);
    CHashArray_append_any(path, newCHashString(key));
    CHashObject_set_any(formated_args, "path", path);
    CHash_raise_error(self,error_code,error_menssage,formated_args);
}


void CHash_raise_error_by_index(CHash *self,long index, int error_code,const char *error_menssage, CHash *args){
    if(Chash_errors(self)){return;}

    CHash *formated_args = args;

    if(!args){
        formated_args = newCHashObjectEmpty();
    }
    CHashArray *path = CHash_get_path(self);
    CHashArray_append_any(path, newCHashNumber((double) index));
    CHashObject_set_any(formated_args, "path", path);
    CHash_raise_error(self,error_code,error_menssage,formated_args);
}


void privateCHashError_free(privateCHashError *self){
    CTextStack_free(self->error_mensage);
    CHash_free(self->args);
    free(self);
}

char * CHash_get_error_menssage(CHash *self){
    if(!self){

        return (char*)"element its NULL , (impossíble to get error menssage)\n";
    }

    if(!Chash_errors(self)){
        return NULL;
    }

    privateCHashError  *error = privateCHashError_get_error(self);

    return error->error_mensage->rendered_text;
}

int CHash_get_error_code(CHash *self){

    if(!self){
        return CHASH_ELEMENT_IS_NULL;
    }

    if(!Chash_errors(self)){
        return 0;
    }
    privateCHashError  *error = privateCHashError_get_error(self);
    return error->error_code;
}

CHash * CHash_get_error_args(CHash *self){
    if(!Chash_errors(self)){
        return NULL;
    }
    privateCHashError  *error = privateCHashError_get_error(self);
    return error->args;
}


int private_chash_check_type(CHash *element, unsigned short  expected_type){
    if(Chash_errors(element)){
        return 1;
    }

    if(element->private_type != expected_type){

        CHash_raise_error(element,
                          CHASH_WRONG_TYPE,
                          "element at #path# is #type# instead of #expected_type#  ",
                          newCHashObject(
                                  "expected_type", newCHashString(
                                  private_Chash_convert_type(expected_type)
                                )
                          )
        );
        return 1;
    }
    return 0;
}

int CHash_ensure_Number(CHash *element){
    return private_chash_check_type(element, CHASH_NUMBER);
}
int CHash_ensure_Number_by_key(CHash *object, const char *key){
    CHash *element = CHashObject_get(object,key);
    return CHash_ensure_Number(element);
}
int CHash_ensure_Number_by_index(CHash *array, long index){
    CHash  *element = CHashArray_get(array,index);
    return CHash_ensure_Number(element);
}
int CHash_ensure_Long(CHash *element){
    double value = CHash_toNumber(element);
    if(Chash_errors(element)){
        return 1;
    }

    double rest = value - (double)(long)value;
    if(rest != 0){
        CHash_raise_error(
                element,
                CHASH_NOT_LONG,
                "element at #path# of its an double instead of long",
                NULL
        );
        return 1;
    }

    return  0;
}
int CHash_ensure_Long_by_key(CHash *object, const char *key){
    CHash *element = CHashObject_get(object,key);
    return CHash_ensure_Long(element);
}
int CHash_ensure_Long_by_index(CHash *array, long index){
    CHash  *element = CHashArray_get(array,index);
    return CHash_ensure_Long(element);
}

int CHash_ensure_min_value(CHash *element, double  min){
    double  value = CHash_toNumber(element);
    if(Chash_errors(element)){
        return 1;
    }
    if(value < min){
        CHash_raise_error(
                element,
                CHASH_LOWER_NUMBER,
                "element at #path# of value #value# its lower than #number#",
                newCHashObject("number", newCHashNumber(min))
        );
        return 1;
    }
    return 0;
}
int CHash_ensure_min_value_by_key(CHash *object, const char *key, double min){
    CHash * current = CHashObject_get(object,key);
    return CHash_ensure_min_value(current, min);
}

int CHash_ensure_min_value_by_index(CHash *array, long index, double min){
    CHash *current = CHashArray_get(array,index);
    return CHash_ensure_min_value(current, min);
}



int CHash_ensure_max_value(CHash *element, double  max){
    double  value = CHash_toNumber(element);
    if(Chash_errors(element)){
        return 1;
    }
    if(value > max){
        CHash_raise_error(
                element,
                CHASH_LOWER_NUMBER,
                "element at #path# of value #value# its lower than #number#",
                newCHashObject("number", newCHashNumber(max))
        );
        return 1;
    }
    return 0;
}

int CHash_ensure_max_value_by_key(CHash *object, const char *key, double  max){
    CHash * current = CHashObject_get(object,key);
    return CHash_ensure_max_value(current, max);
}

int CHash_ensure_max_value_by_index(CHash *array, long index, double  max){
    CHash *current = CHashArray_get(array,index);
    return CHash_ensure_max_value(current, max);
}

int CHash_ensure_Bool(CHash *element){
    return private_chash_check_type(element,CHASH_BOOL);

}

int CHash_ensure_Bool_by_key(CHash *object , const char *key){
    CHashObject *current = CHashObject_get(object,key);
    return CHash_ensure_Bool(current);
}

int CHash_ensure_Bool_by_index(CHash *array , long index){
    CHash *current = CHashArray_get(array,index);
    return CHash_ensure_Bool(current);
}

int CHash_ensure_String(CHash *element){
    return private_chash_check_type(element,CHASH_STRING);
}

int Chash_ensure_only_chars(CHash *element, const char *seq){
    if(CHash_ensure_String(element)){
        return 1;
    }
    CTextStack *seq_stack = newCTextStack_string(seq);
    CTextStack *element_stack = CHashtoStack(element);
    for(int i=0; i < element_stack->size; i++){
        char current_char = element_stack->rendered_text[i];
        if(CTextStack_index_of_char(seq_stack,current_char) == -1){
            CTextStack *char_stack = newCTextStack("","");
            CTextStack_format(char_stack,"%c",current_char);
            CHash_raise_error(
                    element,
                    CHASH_NOT_IN_VALID_CHARS,
                    "char :#char# at #path#  its not inside #valid_chars#",
                    newCHashObject(
                            "char", newCHashStackString(char_stack),
                            "valid_chars", newCHashStackString(seq_stack)
                    )
            );
            return 1;

        }
    }
    CTextStack_free(seq_stack);
    return 0;
}
int CHash_ensure_String_by_key(CHash *object , const char *key){
    CHashObject *current = CHashObject_get(object,key);
    return CHash_ensure_String(current);
}

int CHash_ensure_String_by_index(CHash *array , long index){
    CHash *current = CHashArray_get(array,index);
    return CHash_ensure_String(current);
}

int CHash_ensure_Object(CHash *element){
    return private_chash_check_type(element,CHASH_OBJECT);
}


int CHash_ensure_Object_by_key(CHash *object , const char *key){
    CHashObject *current = CHashObject_get(object,key);
    return CHash_ensure_Object(current);
}
int CHash_ensure_Object_by_index(CHash *array , long index){
    CHash *current = CHashArray_get(array,index);
    return CHash_ensure_Object(current);
}

int CHash_ensure_only_keys(CHashObject *object, CHashStringArray *keys){

    if(CHash_ensure_Object(object)){
        return 1;
    }

    long size = CHash_get_size(object);
    for(long i = 0; i < size; i++){
        char *current_key = CHashObject_get_key_by_index(object,i);
        if(CHashArray_find_String(keys, current_key) == -1){
            CHash_raise_error(
                    object,
                    CHASH_INVALID_KEY,
                    "key: #key# at #path#  its not inside #keys#",
                    newCHashObject(
                            "key", newCHashString(current_key),
                            "keys", CHash_copy(keys)
                    )
            );
            return 1;
        }
    }
    return 0;
}
int CHash_ensure_only_keys_cleaning_args(CHashObject *object, CHashStringArray *keys){
    int result = CHash_ensure_only_keys(object,keys);
    CHash_free(keys);
    return result;
}

int CHash_ensure_Array(CHash *element){
    return private_chash_check_type(element,CHASH_ARRAY);
}

int CHash_ensure_Array_by_key(CHash *object , const char *key){
    CHash *current = CHashObject_get(object,key);
    return CHash_ensure_Array(current);
}

int CHash_ensure_Array_by_index(CHash *array , long index){
    CHash *current = CHashArray_get(array,index);
    return CHash_ensure_Array(current);
}

int CHash_ensure_all_types(CHash *element, short expected_type){

    if(privateCHash_ensureArrayOrObject(element)){
        return 1;
    }
    long size = CHash_get_size(element);
    for(long i = 0; i < size; i++){
        CHash  *current = CHashArray_get(element,i);
        if(private_chash_check_type(current,expected_type)){
            return 1;
        }
    }
    return  0;
}

int CHash_ensure_all_String(CHash *element){
    return CHash_ensure_all_types(element,CHASH_STRING);
}
int CHash_ensure_all_Numbers(CHash *element){
    return CHash_ensure_all_types(element,CHASH_NUMBER);
}
int CHash_ensure_all_Bool(CHash *element){
    return CHash_ensure_all_types(element,CHASH_BOOL);
}

int CHash_ensure_min_size(CHash *iterable,long min){
    if(Chash_errors(iterable)){
        return  1;
    }
    long size = CHash_get_size(iterable);
    if(size < min){
        CHash_raise_error(
                iterable,
                CHASH_LOWER_THAN_MIN,
                "the element at #path# its lower than #min# ",
                newCHashObject(
                        "min", newCHashNumber(min)
                )
        );
        return 1;
    }
    return  0;
}

int CHash_ensure_min_size_by_key(CHash  *object, const char *key,long min){
    CHash  *element = CHashObject_get(object,key);
    return CHash_ensure_min_size(element,min);
}

int CHash_ensure_min_size_by_index(CHash  *array, long index,long min){
    CHash *element = CHashArray_get(array,index);
    return CHash_ensure_min_size(element,min);
}


int CHash_ensure_size(CHash *iterable,long size){
    if(Chash_errors(iterable)){
        return  1;
    }
    long iterable_size = CHash_get_size(iterable);
    if(iterable_size != size){
        CHash_raise_error(
                iterable,
                CHASH_NOT_SIZE,
                "the element at #path# has diferent size than #size# ",
                newCHashObject(
                        "size", newCHashNumber(size)
                )
        );
        return 1;
    }
    return  0;
}

int CHash_ensure_size_by_key(CHash  *object, const char *key,long size){
    CHash  *element = CHashObject_get(object,key);
    return CHash_ensure_size(element,size);
}

int CHash_ensure_size_by_index(CHash  *array, long index,long size){
    CHash *element = CHashArray_get(array,index);
    return CHash_ensure_size(element,size);
}

int CHash_ensure_max_size(CHash *iterable,long max){
    if(Chash_errors(iterable)){
        return  1;
    }
    long size = CHash_get_size(iterable);
    if(size > max){

        CHash_raise_error(
                iterable,
                CHASH_HIGHER_THAN_MIN,
                "the element at #path# its higher than #max# ",
                newCHashObject(
                        "max", newCHashNumber(max)
                )
        );

        return 1;
    }
    return  0;
}

int CHash_ensure_max_size_by_key(CHash  *object, const char *key,long max){
    CHash  *element = CHashObject_get(object,key);
    return CHash_ensure_max_size(element,max);
}

int CHash_ensure_max_size_by_index(CHash  *array, long index,long max){
    CHash *element = CHashArray_get(array,index);
    return CHash_ensure_max_size(element,max);
}



int privateCHash_ensureArrayOrObject(CHash *element){
    if(Chash_errors(element)){
        return 1;
    }

    if(element->private_type != CHASH_OBJECT && element->private_type != CHASH_ARRAY){
        CHash_raise_error(element,
                          CHASH_WRONG_TYPE,
                          "element at #path# is #type# instead of array or object  ",
                          NULL
        );
        return 1;
    }
    return 0;

}






CHashObjectModule newCHashObjectModule(){
    CHashObjectModule self = {0};
    self.newObjectEmpty = newCHashObjectEmpty;
    self.set_any = CHashObject_set_any;
    self.set_long = CHashObject_set_long;
    self.set_double = CHashObject_set_double;
    self.set_bool = CHashObject_set_bool;
    self.set_string = CHashObject_set_string;
    self.set_Stack = CHashObject_set_Stack;

    self.set_default = CHashObject_set_default;
    self.remove= CHashObject_remove;

    self.get_key_by_index = CHashObject_get_key_by_index;
    self.get_key_of_element = CHashObject_get_key_of_element;
    self.exist = CHashObject_exist;
    self.get_type = CHashObject_get_type;
    self.get = CHashObject_get;
    self.getArray = CHashObject_getArray;
    self.getObject = CHashObject_getObject;
    self.getBool = CHashObject_getBool;
    self.getBool_converting = CHashObject_getBool_converting;
    self.getNumber = CHashObject_getNumber;
    self.getNumber_converting = CHashObject_getNumber_converting;
    self.getString = CHashObject_getString;
    self.getStack = CHashObject_getStack;

    return self;
}



CHashArrayModule newCHashArrayModule(){
    CHashArrayModule self = {0};
    self.newArrayEmpty = newCHashArrayEmpty;
    self.append_any = CHashArray_append_any;
    self.append_double =CHashArray_append_double;
    self.append_long = CHashArray_append_long;
    self.append_bool = CHashArray_append_bool;
    self.append_string = CHashArray_append_string;
    self.append_stack =CHashArray_append_stack;

    self.set = CHashArray_set;
    self.set_double = CHashArray_set_double;
    self.set_long =CHashArray_set_long;
    self.set_bool =CHashArray_set_bool;
    self.set_string = CHashArray_set_string;
    self.set_stack = CHashArray_set_stack;

    self.remove = CHashArray_remove;
    self.get = CHashArray_get;
    self.foreach = CHashArray_foreach;
    self.foreach_with_args = CHashArray_foreach_with_args;

    //self.map = CHashArray_map;
    //self.map_with_args = CHashArray_map_with_args;

    self.find = CHashArray_find;
    self.find_Number =CHashArray_find_Number;
    self.find_Bool = CHashArray_find_Bool;
    self.find_String = CHashArray_find_String;

    self.get_type = CHashArray_get_type;
    self.getArray = CHashArray_getArray;
    self.getObject = CHashArray_getObject;
    self.getString = CHashArray_getString;
    self.getStack  = CHashArray_getStack;
    self.getNumber = CHashArray_getNumber;
    self.getNumber_converting = CHashArray_getNumber_converting;
    self.getBool = CHashArray_getBool;
    self.getBool_converting = CHashArray_getBool_converting;
    return self;
}



CHashValidatorModule newCHashValidatorModule(){
    CHashValidatorModule self = {0};
    self.raise_error = CHash_raise_error;
    self.raise_error_by_key = CHash_raise_error_by_key;
    self.raise_error_by_index = CHash_raise_error_by_index;
    self.generate_custom_error = CHash_generate_custom_error;
    self.generate_custom_error_cleaning_args = CHash_generate_custom_error_cleaning_args;

    self.ensure_Number = CHash_ensure_Number;
    self.ensure_Number_by_key = CHash_ensure_Number_by_key;
    self.ensure_Number_by_index = CHash_ensure_Number_by_index;

    self.ensure_Long = CHash_ensure_Long;
    self.ensure_Long_by_key = CHash_ensure_Long_by_key;
    self.ensure_Long_by_index = CHash_ensure_Long_by_index;

    self.ensure_min_value = CHash_ensure_min_value;
    self.ensure_min_value_by_key = CHash_ensure_min_value_by_key;
    self.ensure_min_value_by_index = CHash_ensure_min_value_by_index;

    self.ensure_max_value = CHash_ensure_max_value;
    self.ensure_max_value_by_key =CHash_ensure_max_value_by_key;
    self.ensure_max_value_by_index =CHash_ensure_max_value_by_index;



    self.ensure_Bool = CHash_ensure_Bool;
    self.ensure_Bool_by_key = CHash_ensure_Bool_by_key;
    self.ensure_Bool_by_index = CHash_ensure_Bool_by_index;

    self.ensure_String = CHash_ensure_String;
    self.ensure_String_by_key = CHash_ensure_String_by_key;
    self.ensure_String_by_index = CHash_ensure_String_by_index;
    self.ensure_only_chars = Chash_ensure_only_chars;

    self.ensure_Object = CHash_ensure_Object;
    self.ensure_Object_by_key = CHash_ensure_Object_by_key;
    self.ensure_Object_by_index = CHash_ensure_Object_by_index;
    self.ensure_only_keys =CHash_ensure_only_keys;
    self.ensure_only_keys_cleaning_args =CHash_ensure_only_keys_cleaning_args;


    self.ensure_Array = CHash_ensure_Array;
    self.ensure_Array_by_key = CHash_ensure_Array_by_key;
    self.ensure_Array_by_index = CHash_ensure_Array_by_index;

    self.ensure_all_types = CHash_ensure_all_types;
    self.ensure_all_String  = CHash_ensure_all_String;
    self.ensure_all_Bool = CHash_ensure_all_Bool;
    self.ensure_all_Numbers = CHash_ensure_all_Numbers;
    self.ensure_min_size = CHash_ensure_min_size;
    self.ensure_min_size_by_key = CHash_ensure_min_size_by_key;
    self.ensure_min_size_by_index = CHash_ensure_min_size_by_index;

    self.ensure_size = CHash_ensure_size;
    self.ensure_size_by_key= CHash_ensure_size_by_key;
    self.ensure_size_by_index = CHash_ensure_size_by_index;

    self.ensure_max_size = CHash_ensure_max_size;
    self.ensure_max_size_by_key  = CHash_ensure_max_size_by_key;
    self.ensure_max_size_by_index = CHash_ensure_max_size_by_index;

    return self;
}




CHashNamespace newCHashNamespace(){
    CHashNamespace self = {0};

    self.load_from_cJSON = CHash_load_from_cJSON;
    self.load_from_json_strimg  = CHash_load_from_json_strimg;
    self.load_from_json_file = CHash_load_from_json_file;

    self.dump_to_cJSON = CHash_dump_to_cJSON;
    self.dump_to_json_string = CHash_dump_to_json_string;
    self.dump_to_json_file = CHash_dump_to_json_file;

    self.set =CHash_set;

    self.newBool = newCHashBool;
    self.toBool = CHash_toBool;
    self.convert_toBool = CHash_convert_toBool;
    self.toBool_converting = CHash_toBool_converting;

    self.set_Bool = CHash_set_Bool;

    self.newNumber = newCHashNumber;
    self.toNumber = CHash_toNumber;
    self.set_Number = CHash_set_Number;
    self.convert_toNumber =CHash_convert_toNumber;
    self.toNumber_converting  =CHash_toNumber_converting;

    self.newStackString = newCHashStackString;
    self.toStack = CHashtoStack;
    self.set_String = CHash_set_String;
    self.set_Stack = CHash_set_Stack;

    self.newString = newCHashString;
    self.toString = CHash_toString;
    self.newNULL = newCHashNULL;

    self.print = CHash_print;
    self.get_path = CHash_get_path;
    self.copy = CHash_copy;
    self.equals  = CHash_equals;
    self.get_size = CHash_get_size;


    self.errors = Chash_errors;
    self.get_error_code = CHash_get_error_code;
    self.get_error_args = CHash_get_error_args;
    self.get_error_menssage= CHash_get_error_menssage;

    self.get_type = CHash_get_type;

    self.free = CHash_free;

    self.object = newCHashObjectModule();
    self.array = newCHashArrayModule();
    self.validator = newCHashValidatorModule();
    return self;
}



#endif //LibName
