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

#ifndef _CPULOADERLINUX_H_
#define _CPULOADERLINUX_H_

#include "CpuLoader.h"
#include "model/TreeModel.h"

#include <QTimer>

class CpuLoaderLinux : public CpuLoader
{
    Q_OBJECT
    Q_PROPERTY( TreeModel* treeModel READ treeModel NOTIFY modelChanged )

public:

    /**
     * @brief CpuLoaderLinux explicit constructor
     * @param parent QQuickItem object
     */
    explicit CpuLoaderLinux( QQuickItem* parent = 0 );

public:

   /**
    * Methods that will be called from QtQuick/QML elements
    */
    Q_INVOKABLE virtual void start( );
    Q_INVOKABLE virtual void setAutoRefresh( bool enable );
    Q_INVOKABLE virtual TreeModel* treeModel( ) const;

signals:

    void modelChanged( );

protected Q_SLOTS:

    void updateCpuInfo( );

private:

    bool setModelData( const QVector< CpuInfo >& data );
    void setModelChildernData( TreeModelItem* parent, const QVector<CpuInfo> &data, int& index );

private:

    QSharedPointer< TreeModel > mModel;
    QTimer mTimer;
};

#endif // _CPULOADERLINUX_H_
