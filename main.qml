import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.1
import Controller 1.0

Item {
    id: controllerRoot
    
    property real aspectRatio: width/height
    property bool applicationActive: {
        if(Qt.platform.os === "android" || Qt.platform.os === "ios") {
            if(Qt.application.state === Qt.ApplicationActive) {
                return true
            } else {
                return false
            }
        } else {
            return true
        }
    }
    
    width: 1080
    height: 1080

    focus: true
    
    Component.onCompleted: {
        console.log("Controller started.")
        console.log("Platform: " + Qt.platform.os)
    }

    function addObstacle(x, y) {
        var size = 100;
        x -= size*0.5;
        y -= size*0.5;
        var newObject = Qt.createQmlObject('import QtQuick 2.4; Rectangle {color: "red"; x:'+x+'; y:'+y+'; width: '+size+'; height: '+size+'; radius: width*0.5;}',
             controllerRoot, "dynamicSnippet1");
        x = 2*(x / controllerRoot.width) - 1.0
        y = 2*(y / controllerRoot.height) - 1.0
        controller.addObstacle(Qt.vector2d(x,y));
    }

    MouseArea {
        width: parent.width
        height: parent.height
        hoverEnabled: true

        onMouseXChanged: {
            controller.mouseMoved(mouse);
        }

        onMouseYChanged: {
            controller.mouseMoved(mouse);
        }

        onClicked: {
            addObstacle(mouse.x, mouse.y)
        }
    }
    
    Controller {
        id: controller
        anchors.fill: parent
        running: true

        function mouseMoved(mouse) {
            var mouseX = mouse.x
            var mouseY = mouse.y
            mouseX = mouseX / controllerRoot.width
            mouseY = mouseY / controllerRoot.height
            mouseX = mouseX*2.0 - 1.0
            mouseY = mouseY*2.0 - 1.0
            setMousePosition(Qt.vector2d(mouseX, mouseY));
        }
        
        Timer {
            id: timer
            property real lastTime: Date.now()
            property real lastSampleTime: Date.now()
            running: controller.running && controllerRoot.applicationActive
            repeat: true
            interval: 1
            onTriggered: {
                if(!controller.previousStepCompleted) {
                    return
                }
                
                var currentTime = Date.now()
                var dt = currentTime - lastTime
                dt /= 1000
                controller.step(dt)
                
                var sampleTimeDifference = (currentTime - lastSampleTime)/1000
                lastTime = currentTime
            }
        }
    }
    
    Keys.onPressed: {
        if(event.key === Qt.Key_Space) {
            controller.createBird();
        }
    }
}

