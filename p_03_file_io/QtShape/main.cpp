#include "mainwindow.h"
#include <QApplication>

#include "zf_log.h"

static void custom_output_callback(const zf_log_message *msg, void *arg) {
    qDebug( msg->buf, arg );
}

int main(int argc, char *argv[])
{
    qDebug( "Hello" );

    zf_log_set_output_v(ZF_LOG_PUT_STD, 0, custom_output_callback);
    zf_log_set_output_level(ZF_LOG_DEBUG);

    const char * LINE = "___________________________________________________\n" ;
    ZF_LOGI( "%s", LINE );
    ZF_LOGI( "argc = %d", argc );
    ZF_LOGI( "%s", LINE );

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ZF_LOGI( "%s", LINE );
    ZF_LOGI( "Good bye!" );
    ZF_LOGI( "%s", LINE );

    qDebug( "Good bye!" );

    return a.exec();
}
