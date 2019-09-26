/*
https://github.com/ARMmbed/mbedtls/tree/development/programs
https://tls.mbed.org/kb/how-to/mbedtls-tutorial
*/
/*So let's assume we have a simple network client that tries to open a connection to an HTTP server an read the default page. That application would probably look something like this:
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>

#define SERVER_PORT 80
#define SERVER_NAME "localhost"
#define GET_REQUEST "GET / HTTP/1.0\r\n\r\n"

int main( void )
{
    int ret, len, server_fd;
    unsigned char buf[1024];
    struct sockaddr_in server_addr;
    struct hostent *server_host;

    /*
     * Start the connection
     */
    printf( "\n  . Connecting to tcp/%s/%4d...", SERVER_NAME,
                                                 SERVER_PORT );
    fflush( stdout );

    if( ( server_host = gethostbyname( SERVER_NAME ) ) == NULL )
    {
        printf( " failed\n  ! gethostbyname failed\n\n");
        goto exit;
    }

    if( ( server_fd = socket( AF_INET, SOCK_STREAM, IPPROTO_IP) ) < 0 )
    {
        printf( " failed\n  ! socket returned %d\n\n", server_fd );
        goto exit;
    }

    memcpy( (void *) &server_addr.sin_addr,
            (void *) server_host->h_addr,
                     server_host->h_length );

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( SERVER_PORT );

    if( ( ret = connect( server_fd, (struct sockaddr *) &server_addr,
                         sizeof( server_addr ) ) ) < 0 )
    {
        printf( " failed\n  ! connect returned %d\n\n", ret );
        goto exit;
    }

    printf( " ok\n" );

    /*
     * Write the GET request
     */
    printf( "  > Write to server:" );
    fflush( stdout );

    len = sprintf( (char *) buf, GET_REQUEST );

    while( ( ret = write( server_fd, buf, len ) ) <= 0 )
    {
        if( ret != 0 )
        {
            printf( " failed\n  ! write returned %d\n\n", ret );
            goto exit;
        }
    }

    len = ret;
    printf( " %d bytes written\n\n%s", len, (char *) buf );

    /*
     * Read the HTTP response
     */
    printf( "  < Read from server:" );
    fflush( stdout );
    do
    {
        len = sizeof( buf ) - 1;
        memset( buf, 0, sizeof( buf ) );
        ret = read( server_fd, buf, len );

        if( ret <= 0 )
        {
            printf( "failed\n  ! ssl_read returned %d\n\n", ret );
            break;
        }

        len = ret;
        printf( " %d bytes read\n\n%s", len, (char *) buf );
    }
    while( 1 );

exit:

    close( server_fd );

#ifdef WIN32
    printf( "  + Press Enter to exit this program.\n" );
    fflush( stdout ); getchar();
#endif

    return( ret );
}

##A simple client application that does nothing more than:

opening a connection on port 80 to a server
write a standard HTTP GET request for the main page
read the result until nothing more is sent
Adding Secure Communication
Adding SSL/TLS to an application requires a number of modifications. The main modifications are setup, 
configuration and teardown of the SSL contexts and structures. Smaller changes are those made to the network functions for connecting to a server, 
reading and writing data.

##Setup
As setup mbed TLS requires a good random number generator and its own SSL context and SSL session store. For random number generation mbed TLS contains the 
CTR_DRBG random number generator, which is used here as well.

The headers required for mbed TLS:
#include "mbedtls/net.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/debug.h"

Creation and initialization of the mbed TLS structures looks as follows:

mbedtls_net_context server_fd;
mbedtls_entropy_context entropy;
mbedtls_ctr_drbg_context ctr_drbg;
mbedtls_ssl_context ssl;
mbedtls_ssl_config conf;

mbedtls_net_init( &server_fd );
mbedtls_ssl_init( &ssl );
mbedtls_ssl_config_init( &conf );
mbedtls_x509_crt_init( &cacert );
mbedtls_ctr_drbg_init( &ctr_drbg );

mbedtls_entropy_init( &entropy );
if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
                           (const unsigned char *) pers,
                           strlen( pers ) ) ) != 0 )
{
    printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret );
    goto exit;
}

##SSL Connection
In a generic TCP/IP client application, the application handles the socket() and connect() calls. mbed TLS 
generally abstracts this inside its Network Layer (net.c). Thus the following code gets simplified.

if( ( server_host = gethostbyname( SERVER_NAME ) ) == NULL )
    goto exit;

if( ( server_fd = socket( AF_INET, SOCK_STREAM, IPPROTO_IP) ) < 0 )
    goto exit;

memcpy( (void *) &server_addr.sin_addr, (void *) server_host->h_addr,
                 server_host->h_length );

server_addr.sin_family = AF_INET;
server_addr.sin_port = htons( SERVER_PORT );

if( ( ret = connect( server_fd, (struct sockaddr *) &server_addr,
                     sizeof( server_addr ) ) ) < 0 )
    goto exit;

Starting the actual connection through mbed TLS is as follows:

if( ( ret = mbedtls_net_connect( &server_fd, SERVER_NAME,
                                     SERVER_PORT, MBEDTLS_NET_PROTO_TCP ) ) != 0 )
{
    printf( " failed\n  ! mbedtls_net_connect returned %d\n\n", ret );
    goto exit;
}

##SSL/TLS Configuration
Now that the low level socket connection is up and running, we should configure the SSL/TLS layer.

First prepare the SSL configuration by setting the endpoint and transport type, and loading reasonnable defaults for security parameters. 
The endpoint determines if the SSL/TLS layer will act as a server (MBEDTLS_SSL_IS_SERVER) or a client (MBEDTLS_SSL_IS_CLIENT). 
The transport type determines if we are using TLS (MBEDTLS_SSL_TRANSPORT_STREAM) or DTLS (MBEDTLS_SSL_TRANSPORT_DATAGRAM).
if( ( ret = mbedtls_ssl_config_defaults( &conf,
                MBEDTLS_SSL_IS_CLIENT,
                MBEDTLS_SSL_TRANSPORT_STREAM,
                MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
{
    mbedtls_printf( " failed\n  ! mbedtls_ssl_config_defaults returned %d\n\n", ret );
    goto exit;
}

The authentication mode determines how strict the certificates that are presented are checked. For this tutorial we are not checking anything. 
Warning: This is not what you want in a full application.

mbedtls_ssl_conf_authmode( &conf, MBEDTLS_SSL_VERIFY_NONE );

The library needs to know which random engine to use and which debug function to use as callback.

mbedtls_ssl_conf_rng( &conf, mbedtls_ctr_drbg_random, &ctr_drbg );
mbedtls_ssl_conf_dbg( &conf, my_debug, stdout );

For the debug function to work we need to add a debug callback called my_debug above our main() function.

static void my_debug( void *ctx, int level,
                      const char *file, int line, const char *str )
{
    ((void) level);
    fprintf( (FILE *) ctx, "%s:%04d: %s", file, line, str );
    fflush(  (FILE *) ctx  );
}

Now that the configuration is ready, we can set up the SSL context to use it.

if( ( ret = mbedtls_ssl_set_hostname( &ssl, "mbed TLS Server 1" ) ) != 0 )
{
    mbedtls_printf( " failed\n  ! mbedtls_ssl_set_hostname returned %d\n\n", ret );
    goto exit;
}

Finally, the SSL context needs to know the input and output functions it needs to use for sending out network traffic.

mbedtls_ssl_set_bio( &ssl, &server_fd, mbedtls_net_send, mbedtls_net_recv, NULL );

##Reading and writing data

After configuring the SSL/TLS layer we should actually write and read through it.

For writing to the network layer:

while( ( ret = write( server_fd, buf, len ) ) <= 0 )

becomes:
while( ( ret = mbedtls_ssl_write( &ssl, buf, len ) ) <= 0 )

For reading from the network layer:

ret = read( server_fd, buf, len );

becomes:

 ret = mbedtls_ssl_read( &ssl, buf, len );

 Note: if mbedtls_ssl_read() or mbedtls_ssl_write() returns an error, the connection must be closed.

 Teardown
At the exit from the application we should close the SSL/TLS connection cleanly and we should also destroy any SSL/TLS related information. Finally, we free the resources allocated

So:

close( server_fd );
becomes:

mbedtls_net_free( &server_fd );
mbedtls_ssl_free( &ssl );
mbedtls_ssl_config_free( &conf );
mbedtls_ctr_drbg_free( &ctr_drbg );
mbedtls_entropy_free( &entropy );
Server authentication
A real application should properly authenticate the server. For this you need a set of trusted CA. How to get or choose this set depends on your use case: 
to connect to a web server, you can use a list provided by a trusted browser vendor; if your client is a device connecting only to a set of servers you control, 
you may want to be your own CA, etc.

Code-wise, here is what you need to do in order to enable verification of the server certificate:

mbedtls_x509_crt cacert;
const char *cafile = "/path/to/trusted-ca-list.pem";

mbedtls_x509_crt_init( &cacert );

if( ( ret = mbedtls_x509_crt_parse_file( &cacert, cafile ) ) != 0 )
{
    mbedtls_printf( " failed\n  !  mbedtls_x509_crt_parse returned -0x%x\n\n", -ret );
    goto exit;
}

mbedtls_ssl_conf_ca_chain( &conf, &cacert, NULL );

// remove the following line
// mbedtls_ssl_conf_authmode( &conf, MBEDTLS_SSL_VERIFY_NONE );
##Conclusion
After changing SERVER_PORT to 443, compiling this application and linking it to the mbed TLS library, we now have an application that can talk basic HTTPS to a web server. The final code is available as ssl_client1.c in the source code of the library or as ssl_client1.c on github.