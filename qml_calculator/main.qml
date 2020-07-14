import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import org.orgname.CalclibWrapper 1.0
import org.orgname.ResultSaver 1.0

Window {
    id: app

    property double accumulator: 0
    property string operation: ""

    function isInOperation() {
        return operation !== ""
    }

    function reset() {
        calcDisplay.reset()
        accumulator = 0
        operation = ""
    }

    function executeMathOperation() {
        if (operation === "+") {
            accumulator = CalclibWrapper.sum(accumulator,
                                             calcDisplay.displayedNumber)
        } else if (operation === "-") {
            accumulator = CalclibWrapper.sub(accumulator,
                                             calcDisplay.displayedNumber)
        } else if (operation === "/") {
            accumulator = CalclibWrapper.div(accumulator,
                                             calcDisplay.displayedNumber)
        } else if (operation === "*") {
            accumulator = CalclibWrapper.mul(accumulator,
                                             calcDisplay.displayedNumber)
        }
        operation = ""
    }

    title: qsTr("Calculator")
    visible: true
    minimumHeight: calcDisplay.height + calcDisplay.anchors.topMargin + keyboard.height
                   + keyboard.anchors.topMargin + keyboard.anchors.bottomMargin
    minimumWidth: keyboard.width + keyboard.anchors.leftMargin + keyboard.anchors.rightMargin
    maximumHeight: minimumHeight
    maximumWidth: minimumWidth

    TextEdit {
        id: calcDisplay

        //        readonly property var validationRegEx: /^(?:-?(?!\.))?(?![0-9]{17,}$|[0-9\.]{18,}$)(?:0(?![0-9]))?([1-9][0-9]*)?(?:^-?[0-9]{1,15}\.|[0-9]\.[0-9]+)?$/
        readonly property int maxDigits: 16

        property string displayedNumberStr: "0"
        property double displayedNumber: 0
        property int scale: 1
        property int precision: 0
        property bool zero: true
        property bool dot: false
        property bool sign: false
        property bool full: false

        function setDisplayedNumberStr(newDisplayedNumberStr) {
            const newDisplayedNumber = Number.parseFloat(newDisplayedNumberStr)
            if (Number.isNaN(newDisplayedNumber))
                throw Error("Invalid new displayed number.")

            sign = newDisplayedNumber < 0 ? true : false
            if (Math.abs(newDisplayedNumber) > Number.MAX_SAFE_INTEGER) {
                displayedNumber = sign ? -Infinity : Infinity
                displayedNumberStr = displayedNumber.toString()
                zero = false
                dot = false
                scale = 16
                precision = 0
                full = true
            } else if (newDisplayedNumber === 0) {
                if (newDisplayedNumberStr.charAt(0) === "-")
                    newDisplayedNumberStr = newDisplayedNumberStr.substring(1)

                const scalePrecision = newDisplayedNumberStr.split(".")
                if (scalePrecision[0].length > 1)
                    newDisplayedNumberStr = "0"

                displayedNumberStr = newDisplayedNumberStr
                displayedNumber = 0
                zero = true
                dot = scalePrecision.length > 1 ? true : false
                scale = scalePrecision[0].length
                precision = dot ? scalePrecision[1].length : 0
                full = scale + precision === maxDigits
            } else if (Math.abs(newDisplayedNumber) < 1e-15) {
                displayedNumberStr = "0"
                displayedNumber = 0
                zero = true
                dot = false
                sign = false
                scale = 1
                precision = 0
                full = false
            } else {
                if(newDisplayedNumberStr.includes("e")) {
                    if(Math.abs(newDisplayedNumber) < 1) {
                        const fixedStr = newDisplayedNumber.toFixed(15);
                        let i = fixedStr.length;
                        while(fixedStr.charAt(i - 1) === "0") i--;
                        newDisplayedNumberStr = fixedStr.slice(0, i);
                    } else {
                        newDisplayedNumberStr = newDisplayedNumber.toString();
                    }
                }
                const scalePrecision = newDisplayedNumberStr.split(".")
                scalePrecision[0] = Number.parseInt(scalePrecision[0],
                                                    10).toString()
                scalePrecision[0] = sign && scalePrecision[0].charAt(
                            0) !== "-" ? "-".concat(
                                             scalePrecision[0]) : scalePrecision[0]
                displayedNumberStr = scalePrecision.length
                        > 1 ? scalePrecision[0].concat(
                                  ".", scalePrecision[1]) : scalePrecision[0]
                displayedNumber = newDisplayedNumber
                zero = false
                dot = scalePrecision.length > 1 ? true : false
                scale = sign ? scalePrecision[0].length - 1 : scalePrecision[0].length
                precision = dot ? scalePrecision[1].length : 0
                full = scale + precision === maxDigits
            }
        }

        function reset() {
            setDisplayedNumberStr("0")
        }

        function appendDigit(digitStr) {
            setDisplayedNumberStr(displayedNumberStr.concat(digitStr))
        }

        function appendDot() {
            setDisplayedNumberStr(displayedNumberStr.concat("."))
        }

        function toggleSign() {
            setDisplayedNumberStr(sign ? displayedNumberStr.substring(
                                             1) : "-".concat(
                                             displayedNumberStr))
        }

        function removeLast() {
            if (Math.abs(displayedNumber) === Infinity)
                setDisplayedNumberStr(
                            (Math.sign(
                                 displayedNumber) * Number.MAX_SAFE_INTEGER).toString(
                                ))
            else
                setDisplayedNumberStr(displayedNumberStr.slice(0, -1))
        }

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.topMargin: 30
        anchors.leftMargin: 30
        anchors.rightMargin: anchors.leftMargin

        verticalAlignment: TextInput.AlignVCenter
        horizontalAlignment: TextInput.AlignRight

        readOnly: true
        wrapMode: Text.NoWrap
        selectByMouse: true
        font.pointSize: 12
        text: displayedNumberStr
    }

    GridLayout {
        id: keyboard

        readonly property var keys: new Map([["7", 7], ["8", 8], ["9", 9], ["/", 10], ["4", 4], ["5", 5], ["6", 6], ["*", 11], ["1", 1], ["2", 2], ["3", 3], ["-", 13], ["0", 0], [".", 18], ["+-", 14], ["+", 12], ["<", 15], ["CE", 16], ["C", 17], ["=", 19]])

        anchors.top: calcDisplay.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        anchors.topMargin: 15
        anchors.bottomMargin: 15
        anchors.margins: 10

        columns: 4
        rows: 5
        Repeater {
            model: Array.from(keyboard.keys.keys())
            RoundButton {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                implicitHeight: 50
                implicitWidth: implicitHeight

                font.pointSize: 12
                text: modelData

                flat: true
                autoRepeat: false
                Component.onCompleted: {
                    const key = modelData
                    const value = keyboard.keys.get(key)
                    if (value === 0) {
                        enabled = Qt.binding(function () {
                            return (calcDisplay.dot || !calcDisplay.zero)
                                    && !calcDisplay.full
                        })
                        onPressed.connect(function () {
                            calcDisplay.appendDigit(key)
                        })
                    } else if (value < 10) {
                        enabled = Qt.binding(function () {
                            return !calcDisplay.full
                        })
                        onPressed.connect(function () {
                            calcDisplay.appendDigit(key)
                        })
                    } else if (value === 18) {
                        enabled = Qt.binding(function () {
                            return !calcDisplay.dot && !calcDisplay.full
                        })
                        onPressed.connect(function () {
                            calcDisplay.appendDot()
                        })
                    } else if (value < 14) {
                        enabled = true
                        onPressed.connect(function () {
                            if (app.isInOperation())
                                app.executeMathOperation()
                            else
                                accumulator = calcDisplay.displayedNumber
                            app.operation = key
                            calcDisplay.reset()
                        })
                    } else if (value < 18) {
                        enabled = Qt.binding(function () {
                            if (key === "+-")
                                return !calcDisplay.zero
                            if (key === "<")
                                return calcDisplay.scale > 1 || calcDisplay.dot
                            if (key === "CE")
                                return app.isInOperation() && !calcDisplay.zero
                            return true
                        })
                        onPressed.connect(function () {
                            if (key === "+-") {
                                calcDisplay.toggleSign()
                            } else if (key === "<") {
                                calcDisplay.removeLast()
                            } else if (key === "CE") {
                                calcDisplay.reset()
                            } else if (key === "C") {
                                app.reset()
                            }
                        })
                    } else if (value === 19) {
                        enabled = Qt.binding(app.isInOperation)
                        onPressed.connect(function () {
                            app.executeMathOperation()
                            calcDisplay.setDisplayedNumberStr(
                                        app.accumulator.toString())
                            app.accumulator = 0
                            ResultSaver.save(calcDisplay.displayedNumber)
                        })
                    }
                }
            }
        }
    }
}
