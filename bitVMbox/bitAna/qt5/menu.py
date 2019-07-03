from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QApplication, QGridLayout, QLayout, QLineEdit, QCheckBox,
        QSizePolicy, QToolButton, QWidget)
import sys
class MyApp(QWidget):

    def __init__(self):
        super().__init__()
        self.lineArray = []
        self.lineString = ''
        self.initUI()

    def initUI(self):
        mainLayout = QGridLayout()
        self.setLayout(mainLayout)
        self.qle = QLineEdit('Order Please...')
        self.qle.setReadOnly(True)
        self.qle.setAlignment(Qt.AlignRight)
        self.qle.setMaxLength(100)
        self.qle.move(20,20)
        font = self.qle.font()
        font.setPointSize(13)
        self.qle.setFont(font)
        mainLayout.addWidget(self.qle, 0, 0,1, 2)
        test = 10
        self.cb1 = QCheckBox('Jajangmyeon', self)
        #self.cb1.stateChanged.connect(lambda:self.changeTitle(self.cb1))
        self.cb1.stateChanged.connect(self.changeTitle)
        mainLayout.addWidget(self.cb1, 1, 1)
        cb2 = QCheckBox('JJambbong',self)
        cb2.stateChanged.connect(self.changeTitle)
        mainLayout.addWidget(cb2, 2, 1)
        cb3 = QCheckBox('TangShuk',self)
        cb3.stateChanged.connect(self.changeTitle)
        mainLayout.addWidget(cb3, 3, 1)
        
        self.setGeometry(300, 300, 500, 500)
        self.show()

    def changeTitle(self):
        print(2)
        clickedButton = self.sender()
        if clickedButton.isChecked() == True:
            self.setWindowTitle('QCheckBox')
            self.lineArray.append(clickedButton.text())
            print(len(self.lineArray))
            self.ArrayToString()
            self.qle.setText(self.lineString)
        else:
            self.setWindowTitle(' ')
            self.lineArray.remove(clickedButton.text())
            self.ArrayToString()
            self.qle.setText(self.lineString)

    def ArrayToString(self):
        self.lineString = ''
        for i in range(0, len(self.lineArray)):
            if (i) != 0 :
                self.lineString = self.lineString + ','
            self.lineString = self.lineString + self.lineArray[i]
            
        
if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())