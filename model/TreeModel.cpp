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


#include "TreeModel.h"

const QString CPU_MHZ = "cpu MHz";

TreeModel::TreeModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

// -------------------------------------------------------------------------------------------------

TreeModel::~TreeModel( )
{
    // Release data.
    clearData( );
}

// -------------------------------------------------------------------------------------------------

QVariant
TreeModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid( ) )
    {
        return QVariant( );
    }

    if ( index.row() > ( mItems.size( ) - 1 ) )
    {
        return QVariant( );
    }

    // Get the current list item to be updated.
    TreeModelItem *item = mItems.at( index.row( ) );

    switch ( role )
    {
        case Qt :: DisplayRole :
        case TextRole :
            return QVariant::fromValue( item->mText );
        case IndexRole:
            return QVariant::fromValue( item->mIndex );
        case LevelRole :
            return QVariant::fromValue( item->mLevel );
        case IsOpenedRole:
            return QVariant::fromValue( item->mIsOpened );
        case HasChildrenRole:
            return QVariant::fromValue( item->hasChildren( ) );
        default:
            return QVariant( );
    }
}

// -------------------------------------------------------------------------------------------------

int
TreeModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    return mItems.size( );
}

// -------------------------------------------------------------------------------------------------

int
TreeModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED( parent )
    // We have no other column, only a single column.
    return 1;
}

// -------------------------------------------------------------------------------------------------

QHash< int, QByteArray >
TreeModel::roleNames( ) const
{
    // Register roles for easy access within QML objects.
    QHash< int,  QByteArray > Roles = QAbstractListModel::roleNames( );
    Roles.insert( TextRole,  QByteArray( "name" ) );
    Roles.insert( IndexRole,  QByteArray( "index" ) );
    Roles.insert( LevelRole,  QByteArray( "level" ) );
    Roles.insert( IsOpenedRole,  QByteArray( "isOpened" ) );
    Roles.insert( HasChildrenRole,  QByteArray( "hasChildren" ) );

    return Roles;
}

// -------------------------------------------------------------------------------------------------

void
TreeModel::updateData( const QStringList& data )
{
    // We just need to iterate one level of items which are currently displayed.
    for ( int i = 0; i < mItems.count( ); i++ )
    {
        TreeModelItem* item = mItems[ i ];

        // Check whether the current UI entry contains "cpu MHz".
        if ( item->mText.contains( CPU_MHZ ) )
        {
            int parentIndex = item->mParentIndex;

            if ( parentIndex < data.size( ) )
            {
                QStringList tmp = data[ parentIndex ].split( ":" );

                if ( tmp.size( ) == 2 )
                {
                    // Modify the entry.
                    QString val = tmp[ 1 ];
                    item->mText = CPU_MHZ + ": " + val;

                    // Notify UI element to refresh only updated entry, nothing else,
                    // because if we render everything again, it's expensive and unecessary.
                    QModelIndex modelIndex = index( item->mIndex );
                    emit dataChanged( modelIndex, modelIndex, { TextRole } );
                }
            }
        }
    }
}

// -------------------------------------------------------------------------------------------------

void
TreeModel::openItem( int numIndex )
{
    if ( numIndex > ( mItems.size( ) - 1 ) )
    {
        return;
    }

    if ( mItems[ numIndex ]->mIsOpened )
    {
        return;
    }

    // Expand a parent tree is just to add new entries from its children.
    QModelIndex modelIndex = index( numIndex );
    mItems[ numIndex ]->mIsOpened = true;

    emit dataChanged( modelIndex, modelIndex );
    int i = numIndex + 1 ;

    // UI should be notified first that we are going to add new entries on run time.
    beginInsertRows( QModelIndex( ), i, i + mItems[ numIndex ]->mChildren.size( ) - 1 );

    // Insert new entries which are the children of current to be expanded parent entry.
    foreach ( TreeModelItem *item , mItems[ numIndex ]->mChildren )
    {
        mItems.insert( i++, item );
    }

    // We need to align all indexes.
    for ( int i = 0; i < mItems.size( ); i++ )
    {
        mItems[ i ]->mIndex = i;
    }

    // Notify UI that we are done.
    endInsertRows( );
}

// -------------------------------------------------------------------------------------------------

void
TreeModel::closeItem( int numIndex )
{
    if ( numIndex > ( mItems.size( ) - 1 ) )
    {
        return;
    }

    if ( !mItems[ numIndex ]->mIsOpened )
    {
        return;
    }

    // Collapse a parent tree is just to remove its children from the UI model.
    // The real children data is stil exists within parent tree entry.
    QModelIndex modelIndex = index( numIndex );
    mItems[ numIndex ]->mIsOpened = false;

    emit dataChanged( modelIndex, modelIndex );
    int i = numIndex + 1;

    for ( ; i < mItems.size( ) && ( mItems[ i ]->mLevel > mItems[ numIndex ]->mLevel ); ++i )
    {
    }
    --i;

    // UI should be notified first that we are going to remove entries on run time.
    beginRemoveRows( QModelIndex( ), numIndex + 1, i );

    // Removal.
    while ( i > numIndex )
    {
        mItems[ i ]->mIsOpened = false;
        mItems.removeAt( i-- );
    }

    // We need to align all indexes.
    for ( int i = 0; i < mItems.size( ); i++ )
    {
        mItems[ i ]->mIndex = i;
    }

    // Notify UI that we are done.
    endRemoveRows( );
}

// -------------------------------------------------------------------------------------------------

void
TreeModel::addData( TreeModelItem *item )
{
    // Initial adding parent tree entries.
    beginInsertRows( QModelIndex( ), mItems.size( ), mItems.size( ) );
    item->adjustChildrenLevels( );
    item->mIndex = mItems.size( );
    mItems.append( item );
    endInsertRows( );
}

// -------------------------------------------------------------------------------------------------

TreeModelItem*
TreeModel::createItem( const QString& text,
                       unsigned int index,
                       unsigned int parentIndex )
{
    return new TreeModelItem( text, index, parentIndex );
}

// -------------------------------------------------------------------------------------------------

void
TreeModel::clearData( )
{
    // Destory and clear the list.
    qDeleteAll( mItems.begin( ), mItems.end( ) );
    mItems.clear( );
}

// End of file
