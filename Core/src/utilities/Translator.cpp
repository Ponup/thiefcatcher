#include "Translator.h"

#include <string.h>
#include <stdlib.h>
#include <libintl.h>

// @see http://www.gnu.org/software/gettext/FAQ.html#windows_howto

#if defined _WIN32
# include <windows.h>
#else
#define HAVE_SETENV 1
#endif

int my_setenv (const char * name, const char * value) {
#if defined _WIN32
  /* On Woe32, each process has two copies of the environment variables,
     one managed by the OS and one managed by the C library. We set
     the value in both locations, so that other software that looks in
     one place or the other is guaranteed to see the value. Even if it's
     a bit slow. See also
     <http://article.gmane.org/gmane.comp.gnu.mingw.user/8272>
     <http://article.gmane.org/gmane.comp.gnu.mingw.user/8273>
     <http://www.cygwin.com/ml/cygwin/1999-04/msg00478.html> */
  if (!SetEnvironmentVariableA(name,value))
    return -1; 
#endif
#if defined(HAVE_PUTENV)
  size_t namelen = strlen(name);
  size_t valuelen = (value==NULL ? 0 : strlen(value));

  char* buffer = (char*)malloc(namelen+1+valuelen+1);
  if (!buffer)
    return -1; /* no need to set errno = ENOMEM */
  memcpy(buffer,name,namelen);
  if (value != NULL) {
    buffer[namelen] = '=';
    memcpy(buffer+namelen+1,value,valuelen);
    buffer[namelen+1+valuelen] = 0;
  } else
    buffer[namelen] = 0;
  return putenv(buffer);
#elif defined(HAVE_SETENV)
  return setenv(name,value,1);
#else
  /* Uh oh, neither putenv() nor setenv() ... */
  return -1;
#endif
}

void Translator::init ( const char *localeCode ) {
	setlocale( LC_ALL, "" );
	my_setenv( "LANGUAGE", localeCode );
	my_setenv( "LANG", localeCode );
	bindtextdomain( "messages", "resources/languages" );
	bind_textdomain_codeset( "messages", "utf-8" );
	textdomain( "messages" );
}

string Translator::translate( const char *id )
{
	return gettext( id );
}

