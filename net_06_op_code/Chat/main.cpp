#include "mainwindow.h"
#include <QApplication>

#include "zf_log.h"

static void custom_output_callback(const zf_log_message *msg, void *arg) {
    qDebug( msg->buf, arg );
}

int main(int argc, char *argv[])
{
    const char * LINE = "_______________________________" ;
    ZF_LOGD( "%s", LINE );
    ZF_LOGD( "Hello ..." );
    ZF_LOGD( "%s", LINE );

    zf_log_set_output_v(ZF_LOG_PUT_STD, 0, custom_output_callback);
    zf_log_set_output_level(ZF_LOG_DEBUG);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto result = a.exec();

    ZF_LOGD( "%s", LINE );
    ZF_LOGD( "Good bye!" );
    ZF_LOGD( "%s", LINE );

    return result ;
}
