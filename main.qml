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

import QtQuick 2.2
import cpuinfo 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.0
import QtQuick.Dialogs 1.1

Item {
    function createQmlObject( objectType, parent, content ) {
        if ( typeof content != "string" ) {
            content = ""
        }

        return Qt.createQmlObject( "import cpuinfo 1.0; " + objectType + "{" + content + "}", parent ? parent : cpuloader, null )
    }

    id: container
    width: 800
    height: 600

    MessageDialog {
        id: dialog
        title: "QtCpuInfo"
        text: ""
        visible: false

        onAccepted: {
            visible: false
        }
    }

    CpuLoader {
        id: cpuLoader
        objectName: "cpuloader"

        onStartDone: {
            if ( success != true ) {
                dialog.text = "Unable to get CPU information!"
                dialog.visible = true
            }
        }

        onAutoRefreshDone: {
            if ( msg.length > 0 ) {
                dialog.text = msg
                dialog.visible = true
            }
        }

        onNumberOfCores: {
            if ( number > 0 ) {
                cpuWindow.title = cpuWindow.title + " with " + number + " core(s):"
            }
        }

        Window {
            objectName: "cpuWindow"
            id: cpuWindow
            width: 800
            height: 600
            title: "Your CPU information"
            color: "#d4d4d4"
            visible: true

            onVisibleChanged: {
                if ( visible == true ) {
                    cpuLoader.start( )
                }
            }

            Rectangle {
                id: rectangleControl
                anchors.fill: parent
                anchors.margins: 5
                color: "#d4d4d4"
                anchors.rightMargin: 5
                anchors.bottomMargin: 5
                anchors.leftMargin: 5
                anchors.topMargin: 5

                Text {
                    id: infoText
                    text: "Please click on each \"+\" icon to see its CPU's core details"
                    width: parent.width
                    height: 30
                    verticalAlignment: Text.AlignVCenter
                    anchors.top: parent.top
                }

                CheckBox {
                    id: autoRefresh
                    checked: false
                    text: "CPU MHz refresh"
                    anchors.right: parent.right
                    anchors.verticalCenter: infoText.verticalCenter

                    onCheckedChanged: {
                        cpuLoader.setAutoRefresh( checked )
                    }
                }

                ListView {
                    id: treeView
                    width: parent.width
                    height: parent.height - 60
                    anchors.top: infoText.bottom
                    anchors.bottom: parent.bottom
                    anchors.margins: 5
                    delegate: treeDelegate
                    model: cpuLoader.treeModel
                    clip: true

                    Component {
                        id: treeDelegate

                        Item {
                            id: wrapper
                            height: 36
                            width: treeView.width

                            Rectangle {
                                height: 1
                                anchors.top: parent.top
                                anchors.left: parent.left
                                anchors.right: parent.right
                                color: "#d0d0d0"
                            }

                            Item {
                                id: levelMarginElement
                                width: level * 32 + 5
                                anchors.left: parent.left
                            }

                            Item {

                                id: nodeOpenElement
                                anchors.left: levelMarginElement.right
                                anchors.verticalCenter: wrapper.verticalCenter
                                height: 24
                                state: "leafNode"

                                Image {
                                    id: triangleOpenImage
                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: {
                                            if ( isOpened ) {
                                                cpuLoader.treeModel.closeItem( index )
                                            }
                                            else {
                                                cpuLoader.treeModel.openItem( index )
                                            }
                                        }
                                    }
                                }

                                states: [
                                    State {
                                        name: "leafNode"
                                        when: !hasChildren
                                        PropertyChanges {
                                            target: nodeOpenElement
                                            visible: false
                                            width: 0
                                        }
                                    },
                                    State {
                                        name: "openedNode"
                                        when: ( hasChildren ) && ( isOpened )
                                        PropertyChanges {
                                            target: nodeOpenElement
                                            visible: true
                                            width: 32
                                        }
                                        PropertyChanges {
                                            target: triangleOpenImage
                                            source: "resources/minus.png"
                                        }
                                    },
                                    State {
                                        name: "closedNode"
                                        when: ( hasChildren ) && ( !isOpened )
                                        PropertyChanges {
                                            target: nodeOpenElement
                                            visible: true
                                            width: 32
                                        }
                                        PropertyChanges {
                                            target: triangleOpenImage
                                            source: "resources/plus.png"
                                        }
                                    }
                                ]
                            }

                            Text {
                                id: textElement
                                text: name
                                verticalAlignment: "AlignVCenter"
                                anchors.left: nodeOpenElement.right
                                anchors.top: parent.top
                                anchors.bottom: parent.bottom
                                anchors.right: parent.right
                            }

                            Image {
                                id: imageCpu
                                source: "resources/cpu.png"
                                visible: {
                                    if ( hasChildren ) {
                                        visible = true
                                    }
                                    else {
                                        visible = false
                                    }
                                }

                                anchors.right: parent.right
                                anchors.margins: 5
                                width: 24
                                height: 24
                                verticalAlignment: "AlignVCenter"
                            }
                        }
                    }
                }
            }
        }
    }
}

