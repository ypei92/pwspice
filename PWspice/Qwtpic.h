#include <qmainwindow.h>
#include <cstring>
class QwtPlotZoomer;
class QwtPlotPicker;
class QwtPlotPanner;
class Plot;
class QPolygon;

class Qwtpic : public QMainWindow
{
    Q_OBJECT

public:
    //Qwtpic( QWidget *parent = 0 );
    Qwtpic(int type , QWidget *parent = 0 );

private Q_SLOTS:
    void moved( const QPoint & );
    void selected( const QPolygon & );
    void zoom_select(int);

#ifndef QT_NO_PRINTER
#endif

    void exportDocument();
    void enableZoomMode( bool );

private:
    void showInfo( QString text = QString::null );

    Plot *d_plot;

    QwtPlotZoomer *d_zoomer[2];
    QwtPlotPicker *d_picker;
    QwtPlotPanner *d_panner;

    int dealing_type;

};
