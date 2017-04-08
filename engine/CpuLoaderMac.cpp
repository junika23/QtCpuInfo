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

#include "CpuLoaderMac.h"
#include <QProcess>
#include <QDebug>
#include <algorithm>


const QString CPUINFO_COMMAND           = "sysctl -a | grep machdep.cpu";
const int CPUINFO_COMMAND_TIMEOUT_MS    = 1000;
const QString CPU_CORE_COUNT            = "machdep.cpu.core_count";
const QString CPU_BRAND                 = "machdep.cpu.brand_string";

// Helper function to find a value based on key starting.
bool
getValue( const QVector< CpuLoader::CpuInfo >& data, const QString& key, QString& value )
{
    auto found = std::find_if( data.begin( ),
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

CpuLoaderMac::CpuLoaderMac( QQuickItem* parent )
    : CpuLoader( parent )
    , mModel( new TreeModel( ) )
{
}

// -------------------------------------------------------------------------------------------------

void
CpuLoaderMac::start( )
{   
    // On start up, we will get all std output of "sysctl -a | grep machdep.cpu".
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
CpuLoaderMac::setAutoRefresh( bool enable )
{
    Q_UNUSED( enable );

    // Notify UI that we don't support CPU MHz auto refresh in Mac OS.
    emit autoRefreshDone( "Not supported in Mac OS platform!" );
}

// -------------------------------------------------------------------------------------------------

TreeModel*
CpuLoaderMac::treeModel( ) const
{
    return mModel.data( );
}

// -------------------------------------------------------------------------------------------------

void
CpuLoaderMac::setModelData( const QVector< CpuInfo >& data )
{
    if ( !data.isEmpty( ) )
    {
        QString cpuBrand;
        QString coreNumberStr;
        int cpuCoreNumber = 0;

        // Get the CPU brand or model.
        getValue( data, CPU_BRAND, cpuBrand );

        // We proceed the data only if we know how many CPU core we have.
        if ( getValue( data, CPU_CORE_COUNT, coreNumberStr ) )
        {
            cpuCoreNumber = coreNumberStr.toInt( );

            // Notify UI how many CPU core(s) we have.
            emit numberOfCores( cpuCoreNumber );

            for ( int i = 0; i < cpuCoreNumber; i++ )
            {
                // For each core, we create a parent tree entry.
                TreeModelItem* item = mModel->createItem( cpuBrand, i, 0 );
                setModelChildrenData( item, data );

                mModel->addData( item );
            }

            emit modelChanged( );
        }
    }
}

// -------------------------------------------------------------------------------------------------

void
CpuLoaderMac::setModelChildrenData( TreeModelItem* parent, const QVector< CpuInfo >& data )
{
    for ( int i = 0; i < data.size( ); i++ )
    {
        CpuInfo info = data[ i ];

        // We don't need CPU brand and core number anymore since it will be handled by parent tree.
        if ( info.first == CPU_BRAND || info.first == CPU_CORE_COUNT )
        {
            continue;
        }

        TreeModelItem* item = mModel->createItem( info.first + ": " + info.second,
                                                  i,
                                                  parent->mIndex );

        parent->mChildren.append( item );
    }
}

// -------------------------------------------------------------------------------------------------
