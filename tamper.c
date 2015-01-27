#include "tamper.h"
#include "mem_ops.h"

inline char* encode64(char* str, unsigned long len) 
{
  const char b64[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz"
                     "0123456789+/";
  char *ret, *chunk;

  chunk = xmalloc(((len + 3) << 2) / 4);
  ret=chunk;

  do {
    if (len >= 3) {
      unsigned long bitwise = (str[0] << 16) | (str[1] << 8) | str[2];

      *(chunk++) = b64[bitwise >> 18];
      *(chunk++) = b64[(bitwise >> 12) & 0x3F];
      *(chunk++) = b64[(bitwise >> 6) & 0x3F];
      *(chunk++) = b64[bitwise & 0x3F];
      len -= 3;
      str += 3;
    } else if (len == 2) {
      unsigned long bitwise = (str[0] << 16) | (str[1] << 8);
      *(chunk++) = b64[bitwise >> 18];
      *(chunk++) = b64[(bitwise >> 12) & 0x3F];
      *(chunk++) = b64[(bitwise >> 6) & 0x3D];
      *(chunk++) = '=';
      len -= 2;
      str += 2;
    } else {
      unsigned long bitwise = (str[0] << 16);;
      *(chunk++) = b64[bitwise >> 18];
      *(chunk++) = b64[(bitwise >> 12) & 0x3F];
      *(chunk++) = '=';
      *(chunk++) = '=';
      len--;
      str++;
    }
  } while(len); 
  
  *chunk=0;
/*
  if(chunk!=NULL)
  {
	free(chunk);
	chunk=NULL;
  }
*/
  return ret;
}

// random case return string, input= tomato output=ToMatO or tOmATo...
char *rand_case(char *str)
{
	char *str_new=xmalloc(sizeof(char)*strlen(str));
	int i=0;
	
	while(*str != '\0')
	{
		
		if(!test_letter( *str ) )
		{
			entropy_clock();
// uppercase or lowercase condition
			if( (rand()%3) != 2)
				*(str_new+i)=*str & ~0x20;
			else
				*(str_new+i)=*str | 0x20;
	
			i++;
		} else {
			*(str_new+i)=*str;
			i++;
		}

	
		str++;	
	}

/*
	if(str_new != NULL)
	{
		free(str_new);
	}
*/
	return str_new;

}

