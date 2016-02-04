#ifndef _PLOT_H_
#define _PLOT_H_

#include <qwt_plot.h>
#include <complex>
using namespace  std;

class QwtPlotCurve;
class QwtPlotMarker;

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent , int type);
    int type;
    double** data_store;
    char object[64];
    double para[3];
    int data_store_length;
    char **name_store;
    int data_store_height;

    complex <double> **data_ac_store;
public Q_SLOTS:
    void setDamp( int a);
private:
    void showData( const double *xvalue, const double *yvalue, int count );
    void showData2( const double *xvalue, const double *amptitude,const double*phase,int count );
    void showPeak( double freq, double amplitude );
    void show3dB( double freq );
    double*  logSpace( double *array, int size, double xmin, double xmax );
    double* linearSpace(double *array, int size, double xmin, double xmax );

    QwtPlotCurve *d_curve1;

    QwtPlotCurve *d_curve2;

    QwtPlotMarker *d_marker1;
    QwtPlotMarker *d_marker2;
};

#endif
