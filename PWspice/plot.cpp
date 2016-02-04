#include <qwt_math.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_text.h>
#include <qwt_plot_canvas.h>
#include <qmath.h>
#include "complexnumber.h"
#include "plot.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace  std;


#if QT_VERSION < 0x040601
#define qExp(x) ::exp(x)
#define qAtan2(y, x) ::atan2(y, x)
#endif
double* Plot::logSpace( double *array, int size, double xmin, double xmax )
{
    if ( ( xmin <= 0.0 ) || ( xmax <= 0.0 ) || ( size <= 0 ) )
        return array;

    const int imax = size - 1;

    array[0] = xmin;
    array[imax] = xmax;

    const double lxmin = log( xmin );
    const double lxmax = log( xmax );
    const double lstep = ( lxmax - lxmin ) / double( imax );

    for ( int i = 1; i < imax; i++ )
        array[i] = qExp( lxmin + double( i ) * lstep );

    return array;
}
double* Plot::linearSpace(double *array, int size, double xmin, double xmax )
{
    if ( ( xmin < 0.0 ) || ( xmax < 0.0 ) || ( size <= 0 ) )
        return array;

    printf("%f  %f" , xmin , xmax);
    const int imax = size - 1;
    const double lstep = ( xmax - xmin ) / double( imax );

    for( int i = 0 ; i < size ;++i) array[i] = xmin + i*lstep;

    //for(int i = 0 ; i < size ; ++i)
        //cout << "xvalue" << array[i] << endl;
    return array;
}

Plot::Plot(QWidget *parent,  int t):QwtPlot( parent )
{
    int i , j;

    if( t == 1)
    {
        ifstream fin("dc_result.txt");

        fin >> type;
        fin >> object;
        fin >> para[0] >>  para[1] >>  para[2];
        fin >> data_store_length >> data_store_height;
        //cout << "type" << type<<endl;
        //cout << DC_object << ' ' <<DC_para[0] << ' ' <<DC_para[1] << ' ' <<  DC_para[2]<<endl;
        //cout << data_store_length <<' ' << data_store_height << endl;

        data_store = new double*[data_store_height];
        name_store = new char*[data_store_height];
        for( i = 0 ; i < data_store_height ; ++i)
        {
            data_store[i] = new double[data_store_length];
            name_store[i] = new char[64];
        }

        for( i = 0 ; i < data_store_height ; ++i)fin >> name_store[i];
        for( i = 0 ; i < data_store_length ; ++i)
        {
            for( j = 0 ; j < data_store_height ; ++j) fin >> data_store[j][i];
        }
        fin.close();

        if(object[0] == 'V' || object[0] == 'V')strcat(object , " (V)");
        if(object[0] == 'i' || object[0] == 'I')strcat(object , " (A)");
    }
    else if(t == 2)
    {
        ifstream fin("tran_result.txt");

        fin >> type;
        strcpy(object , "T (s)");
        //fin >> object;
        fin >> para[2] >>  para[1];para[0] = 0;
        fin >> data_store_length >> data_store_height;

        data_store = new double*[data_store_height];
        name_store = new char*[data_store_height];
        for( i = 0 ; i < data_store_height ; ++i)
        {
            data_store[i] = new double[data_store_length];
            name_store[i] = new char[64];
        }

        for( i = 0 ; i < data_store_height ; ++i)fin >> name_store[i];
        for( i = 0 ; i < data_store_length ; ++i)
        {
            for( j = 0 ; j < data_store_height ; ++j) fin >> data_store[j][i];
        }

        fin.close();
    }
    else if( t == 3)
    {
    ifstream fin("ac_result.txt");

        fin >> type;
        fin >> object;
        fin >> para[0] >>  para[1] >>  para[2];
        fin >> data_store_length >> data_store_height;
        data_ac_store = new complex<double>*[data_store_height];
        name_store = new char*[data_store_height];
        for( i = 0 ; i < data_store_height ; ++i)
        {
            data_ac_store[i] = new complex<double>[data_store_length];
            name_store[i] = new char[64];
        }

        for( i = 0 ; i < data_store_height ; ++i)fin >> name_store[i];
        for( i = 0 ; i < data_store_length ; ++i)
        {
            for( j = 0 ; j < data_store_height ; ++j) fin >> data_ac_store[j][i];
        }
        strcat(object , " (Hz)");
        fin.close();
    }



    setAutoReplot( false );

    //if(type == 1)

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setBorderRadius( 10 );

    setCanvas( canvas );
    setCanvasBackground( QColor( "MidnightBlue" ) );

    // grid
    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableXMin( true );
    grid->setMajorPen( Qt::white, 0, Qt::DotLine );
    grid->setMinorPen( Qt::gray, 0 , Qt::DotLine );
    grid->attach( this );

    // axes
    enableAxis( QwtPlot::yRight );
    setAxisTitle( QwtPlot::xBottom, object );

    setAxisMaxMajor( QwtPlot::xBottom, 6 );
    setAxisMaxMinor( QwtPlot::xBottom, 9 );
    if( type != 3) setAxisScaleEngine( QwtPlot::xBottom , new QwtLinearScaleEngine);
    else setAxisScaleEngine( QwtPlot::xBottom , new QwtLogScaleEngine);

    // curves
    d_curve1 = new QwtPlotCurve();
    d_curve1->setRenderHint( QwtPlotItem::RenderAntialiased );
    d_curve1->setPen( Qt::yellow );
    d_curve1->setLegendAttribute( QwtPlotCurve::LegendShowLine );
    d_curve1->setYAxis( QwtPlot::yLeft );
    d_curve1->attach( this );

    if(type == 3)
    {
        d_curve2 = new QwtPlotCurve( "Phase" );
        d_curve2->setRenderHint( QwtPlotItem::RenderAntialiased );
        d_curve2->setPen( Qt::cyan );
        d_curve2->setLegendAttribute( QwtPlotCurve::LegendShowLine );
        d_curve2->setYAxis( QwtPlot::yRight );
        d_curve2->attach( this );

        // marker
        d_marker1 = new QwtPlotMarker();
        d_marker1->setValue( 0.0, 0.0 );
        d_marker1->setLineStyle( QwtPlotMarker::VLine );
        d_marker1->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
        d_marker1->setLinePen( Qt::green, 0, Qt::DashDotLine );
        d_marker1->attach( this );

        d_marker2 = new QwtPlotMarker();
        d_marker2->setValue( 0.0, 0.0 );
        d_marker2->setLineStyle( QwtPlotMarker::HLine );
        d_marker2->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
        d_marker2->setLinePen( QColor( 200, 150, 0 ), 0, Qt::DashDotLine );
        d_marker2->setSymbol( new QwtSymbol( QwtSymbol::Diamond,
            QColor( Qt::yellow ), QColor( Qt::green ), QSize( 8, 8 ) ) );
        d_marker2->attach( this );
    }


    setDamp( 0 );

    setAutoReplot( true );
}

void Plot::showData( const double *xvalue, const double *yvalue,int count )
{
    d_curve1->setSamples( xvalue, yvalue , count );
    //printf("count = %d",count);
}

void Plot::showData2( const double *xvalue, const double *amptitude,const double*phase,int count )
{
    d_curve1->setSamples( xvalue, amptitude, count );
    d_curve2->setSamples( xvalue, phase, count );
    //printf("count = %d",count);
}

void Plot::showPeak( double freq, double amplitude )
{
    QString label;
    label.sprintf( "Peak: %.3g dB", amplitude );

    QwtText text( label );
    text.setFont( QFont( "Helvetica", 10, QFont::Bold ) );
    text.setColor( QColor( 200, 150, 0 ) );

    d_marker2->setValue( freq, amplitude );
    d_marker2->setLabel( text );
}

void Plot::show3dB( double freq )
{
    QString label;
    label.sprintf( "-3 dB at f = %.3g Hz", freq );

    QwtText text( label );
    text.setFont( QFont( "Helvetica", 10, QFont::Bold ) );
    text.setColor( Qt::green );

    d_marker1->setValue( freq, 0.0 );
    d_marker1->setLabel( text );
}

void Plot::setDamp( int a )
{
    const bool doReplot = autoReplot();
    setAutoReplot( false );

    int i3 = 1;
    double fmax = 1;
    double amax = -1000.0;
    double min_inter = 100;

    const int ArraySize = data_store_length;

    double *xvalue = new double[ArraySize];
    double *phase = new double[ArraySize];
    double *amplitude = new double[ArraySize];

    char axis_name[128];
    strcpy(axis_name , name_store[a]);

    if(type == 1 || type == 2)
    {
        if( name_store[a][0] == 'i' ||  name_store[a][0] == 'I')strcat(axis_name , "  (A)");
        else strcat(axis_name , "  (V)");
    }
    else
        strcat(axis_name , "  (dB)");

    setAxisTitle( QwtPlot::yLeft, axis_name );

    if(type == 3)
        setAxisTitle( QwtPlot::yRight, "Phase" );
    else
        setAxisTitle( QwtPlot::yRight, "    " );

    // build frequency vector with logarithmic division
    if(type != 3)
    {
        /*for( int i = 0 ; i < ArraySize ; ++ i)
        {
            if( data_store[a][i] > ymax) ymax = data_store[a][i];
            if( data_store[a][i] < ymin) ymin = data_store[a][i];
        }
        setAxisScale(QwtPlot::yLeft, ymin - 1, ymax + 1);*/
        xvalue = linearSpace( xvalue, ArraySize, para[0], para[1] );
        showData( xvalue, data_store[a] , ArraySize );
    }
    else
    {
        xvalue = logSpace( xvalue,ArraySize, para[0], para[1]);
        for ( int i = 0; i < ArraySize; i++ )
        {
            amplitude[i] = 20.0 * log10( qSqrt( real(data_ac_store[a][i]) * real(data_ac_store[a][i]) + imag(data_ac_store[a][i]) * imag(data_ac_store[a][i]) ) );
                phase[i] = qAtan2(imag(data_ac_store[a][i]), real(data_ac_store[a][i]) ) * ( 180.0 / M_PI );

            if(amplitude[i]  < 0.0001 && amplitude[i] > -0.0001) amplitude[i] = 0;
            if(phase[i]  < 0.0001 && phase[i] > -0.0001) phase[i] = 0;

            //if ( ( i3 <= 1 ) && ( amplitude[i] < -3.0 ) )
            //{
            //    cout << amplitude[i] - 3 << endl;
            //    i3 = i;
            //}
            if ( amplitude[i] > amax )
            {
                amax = amplitude[i];
                fmax = xvalue[i];
            }
        }

        double f3;
        for ( int i = 0; i < ArraySize; i++ )
         {
             if( abs( amax - amplitude[i] - 3 ) < min_inter)
             {
                 min_inter = abs( amax - amplitude[i] - 3 );
                 f3 = xvalue[i];
             }
         }


        //double f3 = xvalue[i3] - ( xvalue[i3] - xvalue[i3 - 1] )
        //       / ( amplitude[i3] - amplitude[i3 -1] ) * ( amplitude[i3] + 3 );

        showPeak( fmax, amax );
        show3dB( f3 );
        showData2(xvalue,amplitude,phase,ArraySize);
    }


    setAutoReplot( doReplot );
    delete []xvalue;
    replot();
}
