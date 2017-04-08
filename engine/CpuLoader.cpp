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

#include "CpuLoader.h"


CpuLoader::CpuLoader( QQuickItem* parent )
    : QQuickItem( parent )
{
}

// -------------------------------------------------------------------------------------------------

QVector< CpuLoader::CpuInfo >
CpuLoader::processCpuInfo( const QString& output )
{
    QVector< CpuInfo > cpuInfos;

    // If there's no output, simply return.
    if ( output.isEmpty( ) )
    {
        return cpuInfos;
    }

    // Split the output into list of strings with new line delimiter.
    QStringList entries = output.split( "\n" );

    for( const auto& str : entries )
    {
        // Split again each string with colons delimiter.
        QStringList entry = str.split( ":" );

        if ( entry.size( ) == 2 )
        {
            // Construct our own CpuInfo key value pair object and push it into the vector.
            CpuInfo info( entry[ 0 ].trimmed( ), entry[ 1 ].trimmed( ) );
            cpuInfos.push_back( info );
        }
    }

    return cpuInfos;
}

// End of file
