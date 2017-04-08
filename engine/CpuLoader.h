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

#ifndef _CPULOADER_H_
#define _CPULOADER_H_

#include <QQuickItem>
#include <QVector>

class TreeModel;

class CpuLoader : public QQuickItem
{
    Q_OBJECT

public:

    typedef QPair< QString, QString > CpuInfo;

    explicit CpuLoader( QQuickItem* parent = 0 );

public:

    /**
     * Pure virtual methods that needs to be implemented on derived classes.
     */
    Q_INVOKABLE virtual void start( ) = 0;
    Q_INVOKABLE virtual void setAutoRefresh( bool enable ) = 0;
    Q_INVOKABLE virtual TreeModel* treeModel( ) const = 0;

signals:

    void startDone( bool success );
    void numberOfCores( int number );
    void autoRefreshDone( const QString& msg );

protected:

    QVector< CpuInfo > processCpuInfo( const QString& output );
};

#endif // _CPULOADER_H_
