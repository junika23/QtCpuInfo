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

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#if defined( Q_OS_LINUX )
#include "engine/CpuLoaderLinux.h"
#elif defined( Q_OS_MACOS )
#include "engine/CpuLoaderMac.h"
#endif

#define QML_TYPE_PREFIX "cpuinfo", 1, 0

/**
 * @brief registerQmlTypes to register our own or custom QML object type to be used within QML
 */
void registerQmlTypes( )
{
#if defined( Q_OS_LINUX )
    qmlRegisterType< CpuLoaderLinux >( QML_TYPE_PREFIX, "CpuLoader" );
#elif defined( Q_OS_MACOS )
    qmlRegisterType< CpuLoaderMac >( QML_TYPE_PREFIX, "CpuLoader" );
#endif
    qmlRegisterType< TreeModel >( QML_TYPE_PREFIX, "TreeModel" );
}

// -------------------------------------------------------------------------------------------------

int main( int argc, char *argv[ ] )
{
    QGuiApplication app( argc, argv );

    registerQmlTypes( );

    QQmlApplicationEngine engine;
    engine.load( QUrl( QStringLiteral( "qrc:/main.qml" ) ) );

    return app.exec( );
}

// End of file
