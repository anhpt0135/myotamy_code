/*
* Reference this page at the decription section
*https://www.youtube.com/watch?v=pl8ZtVfsUNA&t=711s
Download MQTT:https://github.com/eclipse/paho.mqtt.embedded-c
Download mbedtls: https://tls.mbed.org/download
*/
#include "mqtts.h"

void TimerInit(Timer* timer)
{
	timer->end_time = (struct timeval){0, 0};
}

char TimerIsExpired(Timer* timer)
{
	struct timeval now, res;
	gettimeofday(&now, NULL);
	timersub(&timer->end_time, &now, &res);
	return res.tv_sec < 0 || (res.tv_sec == 0 && res.tv_usec <= 0);
}


void TimerCountdownMS(Timer* timer, unsigned int timeout)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	struct timeval interval = {timeout / 1000, (timeout % 1000) * 1000};
	timeradd(&now, &interval, &timer->end_time);
}


void TimerCountdown(Timer* timer, unsigned int timeout)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	struct timeval interval = {timeout, 0};
	timeradd(&now, &interval, &timer->end_time);
}


int TimerLeftMS(Timer* timer)
{
	struct timeval now, res;
	gettimeofday(&now, NULL);
	timersub(&timer->end_time, &now, &res);
	//printf("left %d ms\n", (res.tv_sec < 0) ? 0 : res.tv_sec * 1000 + res.tv_usec / 1000);
	return (res.tv_sec < 0) ? 0 : res.tv_sec * 1000 + res.tv_usec / 1000;
}

int mqtts_read(Network* n, unsigned char* buffer, int len, int timeout_ms){
	(void)timeout_ms;
	return mbedtls_ssl_read(&n->ssl, buffer, len);

}
int mqtts_write(Network* n, unsigned char* buffer, int len, int timeout_ms){
	(void)timeout_ms;
	return mbedtls_ssl_write(&n->ssl, buffer, len);
}

void Tls_sessionInit(Network* n){

	n->mqttread = mqtts_read;
	n->mqttwrite = mqtts_write;

	mbedtls_net_init( &n->server_fd );
    mbedtls_ssl_init( &n->ssl );
    mbedtls_ssl_config_init( &n->conf );
    mbedtls_x509_crt_init( &n->cacert );
    mbedtls_ctr_drbg_init( &n->ctr_drbg );
    //mbedtls_printf( "\n  . Seeding the random number generator..." );
    //fflush( stdout );
    mbedtls_entropy_init( &n->entropy );

    /*
     * 0. Initialize certificates
     */
    //mbedtls_printf( "  . Loading the CA root certificate ..." );
    //fflush( stdout );

    mbedtls_x509_crt_parse( &n->cacert, (const unsigned char *) mbedtls_test_cas_pem,
                          mbedtls_test_cas_pem_len );

}

static void my_debug( void *ctx, int level,
                      const char *file, int line,
                      const char *str ){
    ((void) level);

    //mbedtls_fprintf( (FILE *) ctx, "%s:%04d: %s", file, line, str );
    //fflush(  (FILE *) ctx  );
}

int NetworkConnect(Network* n, char* SERVER_NAME, char * SERVER_PORT){
	int flags = 0;
	int ret = 0;
	    /*
     * 1. Start the connection
     */
    //mbedtls_printf( "  . Connecting to tcp/%s/%s...", SERVER_NAME, SERVER_PORT );
    //fflush( stdout );

    if( ( ret = mbedtls_net_connect( &n->server_fd, SERVER_NAME,
                                         SERVER_PORT, MBEDTLS_NET_PROTO_TCP ) ) != 0 )
    {
        //mbedtls_printf( " failed\n  ! mbedtls_net_connect returned %d\n\n", ret );
        goto exit;
    }

    //mbedtls_printf( " ok\n" );

    /*
     * 2. Setup stuff
     */
    //mbedtls_printf( "  . Setting up the SSL/TLS structure..." );
    //fflush( stdout );

    if( ( ret = mbedtls_ssl_config_defaults( &n->conf,
                    MBEDTLS_SSL_IS_CLIENT,
                    MBEDTLS_SSL_TRANSPORT_STREAM,
                    MBEDTLS_SSL_PRESET_DEFAULT ) ) != 0 )
    {
        //mbedtls_printf( " failed\n  ! mbedtls_ssl_config_defaults returned %d\n\n", ret );
        goto exit;
    }

    //mbedtls_printf( " ok\n" );

    /* OPTIONAL is not optimal for security,
     * but makes interop easier in this simplified example */
    mbedtls_ssl_conf_authmode( &n->conf, MBEDTLS_SSL_VERIFY_OPTIONAL );
    mbedtls_ssl_conf_ca_chain( &n->conf, &n->cacert, NULL );
    mbedtls_ssl_conf_rng( &n->conf, mbedtls_ctr_drbg_random, &n->ctr_drbg );
    mbedtls_ssl_conf_dbg( &n->conf, my_debug, stdout );

    if( ( ret = mbedtls_ssl_setup( &n->ssl, &n->conf ) ) != 0 )
    {
        //mbedtls_printf( " failed\n  ! mbedtls_ssl_setup returned %d\n\n", ret );
        goto exit;
    }

    if( ( ret = mbedtls_ssl_set_hostname( &n->ssl, SERVER_NAME ) ) != 0 )
    {
        //mbedtls_printf( " failed\n  ! mbedtls_ssl_set_hostname returned %d\n\n", ret );
        goto exit;
    }

    mbedtls_ssl_set_bio( &n->ssl, &n->server_fd, mbedtls_net_send, mbedtls_net_recv, NULL );

    /*
     * 4. Handshake
     */
    //mbedtls_printf( "  . Performing the SSL/TLS handshake..." );
    fflush( stdout );

    while( ( ret = mbedtls_ssl_handshake( &n->ssl ) ) != 0 )
    {
        if( ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE )
        {
            //mbedtls_printf( " failed\n  ! mbedtls_ssl_handshake returned -0x%x\n\n", -ret );
            goto exit;
        }
    }

    //mbedtls_printf( " ok\n" );

    /*
     * 5. Verify the server certificate
     */
    //mbedtls_printf( "  . Verifying peer X.509 certificate..." );

    /* In real life, we probably want to bail out when ret != 0 */
    if( ( flags = mbedtls_ssl_get_verify_result( &n->ssl ) ) != 0 )
    {
        char vrfy_buf[512];

        //mbedtls_printf( " failed\n" );

        mbedtls_x509_crt_verify_info( vrfy_buf, sizeof( vrfy_buf ), "  ! ", flags );

       // mbedtls_printf( "%s\n", vrfy_buf );
    }
    else
        //mbedtls_printf( " ok\n" );
    return 0;
exit:
	mbedtls_net_free( &n->server_fd );
    mbedtls_x509_crt_free( &n->cacert );
    mbedtls_ssl_free( &n->ssl );
    mbedtls_ssl_config_free( &n->conf );
    mbedtls_ctr_drbg_free( &n->ctr_drbg );
    mbedtls_entropy_free( &n->entropy );
    return -1;
}
void NetworkDisconnect(Network* n){

}