#include <openssl/sha.h>
#include <stdio.h>

char * sha1_to_hex(unsigned char *sha1)                                                                                                                                   
{
    static char buffer[50];
    static const char hex[] = "0123456789abcdef";
    char *buf = buffer;
    int i;

    for (i = 0; i < 20; i++) {
        unsigned int val = *sha1++;
        *buf++ = hex[val >> 4];
        *buf++ = hex[val & 0xf];
	}
	return buffer;
}


int main(int argc, char** argv){
	unsigned char md[20];

	SHA1("hello", 5, md);
	printf("%s\n", sha1_to_hex(md));
	return 0;
}
