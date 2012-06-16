//
//  main.cpp
//  toturial


// based on the great toturial here http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html




#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define STDIN (0)  // file descriptor for standard input



struct addrinfoDefintion {
    int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
    int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
    int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
    int              ai_protocol;  // use 0 for "any"
    size_t           ai_addrlen;   // size of ai_addr in bytes
    struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
    char            *ai_canonname; // full canonical hostname
    
    struct addrinfo *ai_next;      // linked list, next node
};

struct sockaddrExample {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
}; 

// (IPv4 only--see struct sockaddr_in6 for IPv6)
struct sockaddr_inExample {
    short int          sin_family;  // Address family, AF_INET
    unsigned short int sin_port;    // Port number must be in Network Byte Order (by using htons()!)
    struct in_addr     sin_addr;    // Internet address
    unsigned char      sin_zero[8]; // Same size as struct sockaddr should be set to all zeros with the function memset()
};
struct in_addrExample {
    uint32_t s_addr; // that's a 32-bit int (4 bytes)
};

// can store an ipv4 and ipv6 address at the same time. 
struct sockaddr_storageExample {
    sa_family_t  ss_family;     // address family
    
    // all this is padding, implementation specific, ignore it:
    char      __ss_pad1[_SS_PAD1SIZE];
    int64_t   __ss_align;
    char      __ss_pad2[_SS_PAD2SIZE];
/*What's important is that you can see the address family in the ss_family 
 field—check this to see if it's AF_INET or AF_INET6 (for IPv4 or IPv6). 
 Then you can cast it to a struct sockaddr_in or struct sockaddr_in6 if you wanna.*/

    
};

using namespace std;
int main(int argc, const char * argv[])
{
//    struct sockaddr_in sa; // IPv4
//    struct sockaddr_in6 sa6; // IPv6
//    
//    inet_pton(AF_INET, "192.0.2.1", &(sa.sin_addr)); // IPv4 So check to make sure the result is greater than 0 before using!
//    inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6
//    
//    
//    // IPv4:    
//    char ip4[INET_ADDRSTRLEN];  // space to hold the IPv4 string
//    struct sockaddr_in sa_1;      // pretend this is loaded with something
//    inet_ntop(AF_INET, &(sa_1.sin_addr), ip4, INET_ADDRSTRLEN);
//    printf("The IPv4 address is: %s\n", ip4);
//    
//    
//    // IPv6:
//    char ip6[INET6_ADDRSTRLEN]; // space to hold the IPv6 string
//    struct sockaddr_in6 sa6_1;    // pretend this is loaded with something
//    inet_ntop(AF_INET6, &(sa6_1.sin6_addr), ip6, INET6_ADDRSTRLEN);
//    printf("The address is: %s\n", ip6);
//    
//    
//    ///sadsad 
//    cout << "the sizeof struct in6_addr = " << sizeof(struct in6_addr) << " bytes" << endl;

    
    
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;
    
    if ((status = getaddrinfo("www.google.co.il", NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }
    
    printf("IP addresses for %s:\n\n", argv[1]);
    
    for(p = res;p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;
        
        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        
        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);
    }
    
    freeaddrinfo(res); // free the linked list
    

    
    
    /////// next binding example 
    
    int sockfd;

    // first, load up address structs with getaddrinfo():
    
    memset(&hints, 0, sizeof hints);
    memset(&res, 0, sizeof res);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
    
    getaddrinfo(NULL, "3490", &hints, &res);
    
    // make a socket:
    
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    // bind it to the port we passed in to getaddrinfo():
    
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    
    cout << sockfd << " "  << res->ai_addr<< endl;
    
    
    /* an important snippest of code which enables you recycle ports easily */
    
    int yes=1;
    //char yes='1'; // Solaris people use this
    
    // lose the pesky "Address already in use" error message
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    
    
    // connecting example
    
    // first, load up address structs with getaddrinfo():
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    getaddrinfo("www.google.com", "80", &hints, &res);
    
    // make a socket:
    
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    // connect!
    
    int retval = connect(sockfd, res->ai_addr, res->ai_addrlen);
    cout << retval << endl;
    close(sockfd);
    ////////////////////
    
    // select() toturial
    
    //int select(int numfds, fd_set *readfds, fd_set *writefds,
    //           fd_set *exceptfds, struct timeval *timeout); 
    
    /*
     
     
     FD_SET(int fd, fd_set *set);   Add fd to the set.
     
     FD_CLR(int fd, fd_set *set);  Remove fd from the set.
     
     FD_ISSET(int fd, fd_set *set);     Return true if fd is in the set.
     
     FD_ZERO(fd_set *set);     Clear all entries from the set.
     
     */
    
    
    struct timeval tv;
    fd_set readfds;
    
    tv.tv_sec = 2;
    tv.tv_usec = 500000;
    
    FD_ZERO(&readfds);
    FD_SET(STDIN, &readfds);
    
    // don't care about writefds and exceptfds:
    select(STDIN+1, &readfds, NULL, NULL, &tv);
    
    if (FD_ISSET(STDIN, &readfds))
        printf("A key was pressed!\n");
    else
        printf("Timed out.\n");
    
    
    
    
    return 0;
}


/// sending all the buffer

int sendall(int s, char *buf, int *len)
{
    int total = 0;        // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;
    
    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }
    
    *len = total; // return number actually sent here
    
    return n==-1?-1:0; // return -1 on failure, 0 on success
} 

