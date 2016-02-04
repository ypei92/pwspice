#include <qregexp.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qstatusbar.h>
#include <qprinter.h>
#include <qpicture.h>
#include <qpainter.h>
#include <qprintdialog.h>
#include <QComboBox>
#include <qwt_counter.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_renderer.h>
#include <qwt_text.h>
#include <qwt_math.h>
#include "pixmaps.h"
#include "plot.h"
#include "Qwtpic.h"

class Zoomer: public QwtPlotZoomer
{
public:
    Zoomer( int xAxis, int yAxis, QWidget *canvas ):
        QwtPlotZoomer( xAxis, yAxis, canvas )
    {
        setTrackerMode( QwtPicker::AlwaysOff );
        setRubberBand( QwtPicker::NoRubberBand );

        // RightButton: zoom out by 1
        // Ctrl+RightButton: zoom out to full size

        setMousePattern( QwtEventPattern::MouseSelect2,
            Qt::RightButton, Qt::ControlModifier );
        setMousePattern( QwtEventPattern::MouseSelect3,
            Qt::RightButton );
    }
};

//-----------------------------------------------------------------
//
//      bode.cpp -- A demo program featuring QwtPlot and QwtCounter
//
//      This example demonstrates the mapping of different curves
//      to different axes in a QwtPlot widget. It also shows how to
//      display the cursor position and how to implement zooming.
//
//-----------------------------------------------------------------

Qwtpic::Qwtpic(int type , QWidget *parent):
    QMainWindow( parent )
{
    dealing_type = type;

    d_plot = new Plot( this , type);
    const int margin = 5;
    d_plot->setContentsMargins( margin, margin, margin, 0 );

    setContextMenuPolicy( Qt::NoContextMenu );

    d_zoomer[0] = new Zoomer( QwtPlot::xBottom, QwtPlot::yLeft, d_plot->canvas() );
    if( dealing_type == 3) d_zoomer[1] = new Zoomer( QwtPlot::xTop, QwtPlot::yRight, d_plot->canvas() );
    d_panner = new QwtPlotPanner( d_plot->canvas() );

    zoom_select(0);

    d_picker = new QwtPlotPicker( QwtPlot::xBottom, QwtPlot::yLeft,
        QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
        d_plot->canvas() );
    d_picker->setStateMachine( new QwtPickerDragPointMachine() );
    d_picker->setRubberBandPen( QColor( Qt::green ) );
    d_picker->setRubberBand( QwtPicker::CrossRubberBand );
    d_picker->setTrackerPen( QColor( Qt::white ) );

    setCentralWidget( d_plot );

    QToolBar *toolBar = new QToolBar( this );

    QToolButton *btnZoom = new QToolButton( toolBar );
    btnZoom->setText( "Zoom" );
    btnZoom->setIcon( QPixmap( zoom_xpm ) );
    btnZoom->setCheckable( true );
    btnZoom->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnZoom );
    connect( btnZoom, SIGNAL( toggled( bool ) ), SLOT( enableZoomMode( bool ) ) );

    QToolButton *btnExport = new QToolButton( toolBar );
    btnExport->setText( "Export" );
    btnExport->setIcon( QPixmap( print_xpm ) );
    btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnExport );
    connect( btnExport, SIGNAL( clicked() ), SLOT( exportDocument() ) );

    toolBar->addSeparator();

    QWidget *hBox = new QWidget( toolBar );

    QHBoxLayout *layout = new QHBoxLayout( hBox );
    layout->setSpacing( 0 );
    layout->addWidget( new QWidget( hBox ), 10 ); // spacer
    layout->addSpacing( 10 );

    QComboBox *object = new QComboBox( hBox);
    layout->addWidget( new QLabel( "           Object", hBox ), 1 );
    for( int i = 0 ; i < d_plot->data_store_height ; ++i)object->addItem(QWidget::tr( d_plot->name_store[i]));
    layout->addWidget( object , 0);
    ( void )toolBar->addWidget( hBox );

    addToolBar( toolBar );
#ifndef QT_NO_STATUSBAR
    ( void )statusBar();
#endif

    enableZoomMode( false );
    showInfo();
    connect( object , SIGNAL(  activated(int) ),
        this , SLOT( zoom_select(int) ) );
    connect( object , SIGNAL(  currentIndexChanged(int) ),
        d_plot , SLOT( setDamp( int ) ) );

    connect( d_picker, SIGNAL( moved( const QPoint & ) ),
        SLOT( moved( const QPoint & ) ) );
    connect( d_picker, SIGNAL( selected( const QPolygon & ) ),
        SLOT( selected( const QPolygon & ) ) );


}




void Qwtpic::exportDocument()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( d_plot, "bode.pdf" );
}

void Qwtpic::enableZoomMode( bool on )
{
    d_panner->setEnabled( on );

    d_zoomer[0]->setEnabled( on );
    d_zoomer[0]->zoom( 0 );

    if(dealing_type == 3) d_zoomer[1]->setEnabled( on );
    if(dealing_type == 3)  d_zoomer[1]->zoom( 0 );

    d_picker->setEnabled( !on );

    showInfo();
}

void Qwtpic::showInfo( QString text )
{
    if ( text == QString::null )
    {
        if ( d_picker->rubberBand() )
            text = "Cursor Pos: Press left mouse button in plot region";
        else
            text = "Zoom: Press mouse button and drag";
    }

#ifndef QT_NO_STATUSBAR
    statusBar()->showMessage( text );
#endif
}

void Qwtpic::moved( const QPoint &pos )
{
    QString info;

    info.sprintf( "x =%g, yleft =%g,  yright=%g",
        d_plot->invTransform( QwtPlot::xBottom, pos.x() ),
        d_plot->invTransform( QwtPlot::yLeft, pos.y() ),
        d_plot->invTransform( QwtPlot::yRight, pos.y() )
                  );
    showInfo( info );
}

void Qwtpic::selected( const QPolygon & )
{
    showInfo();
}

void Qwtpic::zoom_select(int a)
{
    delete d_zoomer[0];
    if(dealing_type == 3) delete d_zoomer[1];

    delete d_panner;

    d_zoomer[0] = new Zoomer( QwtPlot::xBottom, QwtPlot::yLeft,
        d_plot->canvas() );
    d_zoomer[0]->setRubberBand( QwtPicker::RectRubberBand );
    d_zoomer[0]->setRubberBandPen( QColor( Qt::green ) );
    d_zoomer[0]->setTrackerMode( QwtPicker::ActiveOnly );
    d_zoomer[0]->setTrackerPen( QColor( Qt::white ) );

    if(dealing_type == 3)d_zoomer[1] = new Zoomer( QwtPlot::xTop, QwtPlot::yRight, d_plot->canvas() );

    d_panner = new QwtPlotPanner( d_plot->canvas() );
    d_panner->setMouseButton( Qt::MidButton );

    d_panner->setEnabled( true );

    d_zoomer[0]->setEnabled( false );
    d_zoomer[0]->zoom( 0 );

    if(dealing_type == 3)d_zoomer[1]->setEnabled( false );
    if(dealing_type == 3)d_zoomer[1]->zoom( 0 );

}
