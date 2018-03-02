#include <iostream>
#include <assert.h>
#include <cstring>

using namespace std;
char *strcopy1(char* dst,char *src){
    assert(dst);
    assert(src);
    char * ret = dst;
    while((*dst++=*src++)!='\0');
    return ret;
}

char *strcopy2(char* dst,const char *src){
    assert(dst);
    assert(src);
    char * ret = dst;
    size_t len = strlen(src)+1;
    if(dst > src || dst < src+len){//重叠
        dst = dst + len -1;
        src = src + len -1;
        while(len--){
            *dst-- = *src--;
        }
    }else{//不重叠
        while(len--){
            *dst++ = *src++;
        }
    }
    return ret;
    
}

void *memcopy1(void* dst,const void *src,size_t size){
    assert(dst);
    assert(src);
    void * ret = dst;
    const char * psrc = static_cast<const char*>(src) ;
    char * pdst = static_cast<char*>(dst) ;
    if(pdst > psrc || pdst < psrc+size){//重叠
        pdst = pdst + size -1;
        psrc = psrc + size -1;
        while(size--){
            *pdst-- = *psrc--;
        }

    }else{//不重叠
        while(size--){
            *pdst++ = *psrc++;
        }
    }
    return ret;
    
}

char *strcat1(char *dst,const char *src){
    char *ret = dst;
    while(*dst!='\0'){
        ++dst;
    }
    while((*dst++=*src++)!='\0');
    return ret;
    
}

int strcmp(const char*str1,const char*str2){
    while((*str1 == *str2) && *str1!='\0'){
        ++str1;
        ++str2;
    }
    if((*str1) - (*str2)>0){

        return 1;
    }else{
        return 0;
    }
}

int main()
{
    char a[] = "raohui";
    char *p = new char;
    strcopy1(p,a);
    cout << a << endl;
    cout << p << endl;
    char *b = strcat1(p,a);
    cout << b << endl;
    char *pp = new char;  
    memcopy1(pp,b,4);
    cout << pp << endl;
    cout << strcmp(pp,p) << endl;
    
   
    

    return 0;
}

