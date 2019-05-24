#include "mainwindow.h"
#include <QApplication>

#include <zf_log.h>

static void custom_output_callback(const zf_log_message *msg, void *arg) {
    qDebug( msg->buf, arg );
}

int main(int argc, char *argv[])
{
    const char * LINE = "_______________________________" ;
    ZF_LOGI( "%s", LINE );
    ZF_LOGI( "Hello ..." );
    ZF_LOGI( "%s", LINE );

    zf_log_set_output_v(ZF_LOG_PUT_STD, 0, custom_output_callback);
    zf_log_set_output_level(ZF_LOG_DEBUG);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto result = a.exec();

    ZF_LOGI( "%s", LINE );
    ZF_LOGI( "Good bye!" );
    ZF_LOGI( "%s", LINE );

    return result ;
}
