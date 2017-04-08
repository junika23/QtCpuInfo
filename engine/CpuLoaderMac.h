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

#ifndef _CPULOADERMAC_H_
#define _CPULOADERMAC_H_

#include "CpuLoader.h"
#include "model/TreeModel.h"


class CpuLoaderMac : public CpuLoader
{
    Q_OBJECT
    Q_PROPERTY( TreeModel* treeModel READ treeModel NOTIFY modelChanged )

public:

    /**
     * @brief CpuLoaderMac explicit constructor
     * @param parent QQuickItem object
     */
    explicit CpuLoaderMac( QQuickItem* parent = 0 );

public:

    /**
     * Methods that will be called from QtQuick/QML elements
     */
    Q_INVOKABLE virtual void start( );
    Q_INVOKABLE virtual void setAutoRefresh( bool enable );
    Q_INVOKABLE virtual TreeModel* treeModel( ) const;

signals:

    void modelChanged( );

private:

    bool setModelData( const QVector< CpuInfo >& data );
    void setModelChildrenData( TreeModelItem* parent, const QVector< CpuInfo >& data );

private:

    QSharedPointer< TreeModel > mModel;
};

#endif // _CPULOADERMAC_H_
