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

#ifndef _TREEMODEL_H_
#define _TREEMODEL_H_

#include <QAbstractListModel>

/**
 * @brief The TreeModelItem class which represents one single entry on UI (listView)
 */
class TreeModelItem
{
public:

    TreeModelItem( const QString& text,
                   unsigned int index,
                   unsigned int parentIndex )
        : mText( text )
        , mIndex( index )
        , mLevel( 0 )
        , mIsOpened( false )
        , mParentIndex( parentIndex )
    {
    }

    void adjustChildrenLevels( )
    {
        foreach ( TreeModelItem* item, mChildren )
        {
            item->mLevel = mLevel + 1;
            item->adjustChildrenLevels( );
        }
    }

    bool hasChildren( ) const
    {
        return !mChildren.empty( );
    }

    QString                 mText;
    int                     mIndex;
    int                     mLevel;
    bool                    mIsOpened;
    int                     mParentIndex;
    QList< TreeModelItem* > mChildren;

};

/**
 * @brief The TreeModel class which represents the whole data model of the UI (listView)
 */
class TreeModel : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit TreeModel( QObject* parent = NULL );

    virtual ~TreeModel( );

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;

    int rowCount( const QModelIndex& parent = QModelIndex( ) ) const;

    int columnCount( const QModelIndex& parent = QModelIndex( ) ) const;

    QHash< int, QByteArray > roleNames( ) const;

    void updateData( const QStringList& data );

public slots:

    void openItem( int numIndex );

    void closeItem( int numIndex );

    void addData( TreeModelItem* item );

    TreeModelItem* createItem( const QString& text,
                               unsigned int index,
                               unsigned int parentIndex );

private:

    void clearData( );

    bool isParentSelected( TreeModelItem* item );

private:

    Q_DISABLE_COPY( TreeModel )

    QList< TreeModelItem* > mItems;

    enum ListMenuItemRoles
    {
        TextRole = Qt::UserRole + 1,
        IndexRole,
        LevelRole,
        IsOpenedRole,
        HasChildrenRole
    };
};

#endif // _TREEMODEL_H_
