#include <syslog.h>
#include "zf_log.h"
#include "zf_log.c"

static void custom_output_callback(const zf_log_message *msg, void *arg)
{
	FILE * out = stdout ;
	fprintf( out, msg->buf, arg ); 
	fprintf( out, "\n" );
	fflush( out );
}

int main(int argc, char *argv[]) {
	zf_log_set_output_v(ZF_LOG_PUT_STD, 0, custom_output_callback);
	//zf_log_set_output_level(ZF_LOG_WARN);
	//zf_log_set_output_level(ZF_LOG_INFO);
	zf_log_set_output_level(ZF_LOG_DEBUG);

	ZF_LOGI("A: %i", argc);
	ZF_LOGW("B: %s", "");
	ZF_LOGD("C");
	
	return 0;
}
