// -------------------------------------------------------------------------------------------------
//
// Copyright (C) Juniarto Saputra (juniarto.wongso@gmail.com). All rights reserved.
//
// This software, including documentation, is protected by copyright controlled by
// the contributor(s). All rights are reserved. Copying, including reproducing, storing,
// adapting or translating, any or all of this material requires the prior written
// consent of the contributor(s).
//
// -------------------------------------------------------------------------------------------------

#include "CpuLoaderLinux.h"
#include <QProcess>
#include <QDebug>
#include <thread>
#include <algorithm>


const QString CPUINFO_COMMAND           = "cat /proc/cpuinfo";
const QString CPUMHZ_COMMAND            = "bash -c \"cat /proc/cpuinfo | grep MHz\"";
const int CPUINFO_COMMAND_TIMEOUT_MS    = 1000;
const int CPUMHZ_COMMAND_TIMEOUT_MS     = 500;
const QString CPU_CORE_INDEX            = "processor";
const QString CPU_CORE_MODEL_NAME       = "model name";
const int PERIODIC_TIMER                = 1000;

// Helper function to find a value based on key starting with a given index.
bool
getValue( const QVector< CpuLoader::CpuInfo >& data, int iter, const QString& key, QString& value )
{
    auto found = std::find_if( data.begin( ) + iter,
                               data.end( ),
                               [ &key ] ( const CpuLoader::CpuInfo& info )
    {
        return ( info.first == key );
    } );

    if ( found != data.end( ) )
    {
        value = found->second;

        return true;
    }

    return false;
}

// -------------------------------------------------------------------------------------------------

CpuLoaderLinux::CpuLoaderLinux( QQuickItem* parent )
    : CpuLoader( parent )
    , mModel( new TreeModel( ) )
    , mTimer( this )
{
    connect( &mTimer, SIGNAL( timeout( ) ), this, SLOT( updateCpuInfo( ) ) );
}

// -------------------------------------------------------------------------------------------------

void
CpuLoaderLinux::start( )
{   
    // On start up, we will get all std output of "cat /proc/cpuinfo".
    QProcess process;

    process.start( CPUINFO_COMMAND );

    if ( !process.waitForFinished( CPUINFO_COMMAND_TIMEOUT_MS ) )
    {
        return;
    }

    // Get raw std output data.
    QString stdOutput = process.readAllStandardOutput( );

    // Process the data and pass it to data model.
    setModelData( processCpuInfo( stdOutput ) );

    // Notify UI that we are done.
    emit startDone( );
}

// -------------------------------------------------------------------------------------------------

void
CpuLoaderLinux::setAutoRefresh( bool enable )
{
    if ( enable )
    {
        // Update CPU info and start the periodic timer.
        updateCpuInfo( );
        mTimer.start( PERIODIC_TIMER );
    }
    else
    {
        // Stop the timer.
        mTimer.stop( );
    }
}

// -------------------------------------------------------------------------------------------------

TreeModel*
CpuLoaderLinux::treeModel( ) const
{
    return mModel.data( );
}

// -------------------------------------------------------------------------------------------------

void
CpuLoaderLinux::setModelData( const QVector< CpuInfo >& data )
{
    if ( !data.isEmpty( ) )
    {
        int i = 0;

        // Notify UI how many CPU core(s) we have.
        emit numberOfCores( std::thread::hardware_concurrency( ) );

        while ( i < data.size( ) )
        {
            CpuInfo info = data[ i ];

            if ( info.first == CPU_CORE_INDEX )
            {
                // For every "processor: x", we create a parent tree entry for the UI.
                QString cpuModel = info.second;

                // Get the CPU brand or model name.
                getValue( data, i, CPU_CORE_MODEL_NAME, cpuModel );

                TreeModelItem* item = mModel->createItem( cpuModel,
                                                          mModel->rowCount( ),
                                                          0 );
                // Set the rest of data as children of tree entry.
                setModelChildernData( item, data, ++i );

                // Add it to the model.
                mModel->addData( item );
            }
        }

        // Notify UI that the model has been changed/updated.
        emit modelChanged( );
    }
}

// -------------------------------------------------------------------------------------------------

void
CpuLoaderLinux::setModelChildernData( TreeModelItem* parent,
                                      const QVector< CpuInfo >& data,
                                      int& index )
{
    while ( index < data.size( ) )
    {
        CpuInfo info = data[ index ];

        // Return on "processor: x" entry since it should be handled as parent tree entry.
        if ( info.first == CPU_CORE_INDEX )
        {
            return;
        }
        else if ( info.first != CPU_CORE_MODEL_NAME )
        {
            TreeModelItem* item = mModel->createItem( info.first + ": " + info.second,
                                                      mModel->rowCount( ),
                                                      parent->mIndex );

            parent->mChildren.append( item );
        }

        index++;
    }
}

// -------------------------------------------------------------------------------------------------

void
CpuLoaderLinux::updateCpuInfo( )
{
    QProcess process;

    // We just need to get "cpu MHz: xxxx.xxx from std output
    process.start( CPUMHZ_COMMAND );

    if ( !process.waitForFinished( CPUMHZ_COMMAND_TIMEOUT_MS ) )
    {
        return;
    }

    QString stdOutput = process.readAllStandardOutput( );
    QStringList data = stdOutput.split( "\n" );

    // Update only some entry on data model side.
    mModel->updateData( data );
}

// End of file
