import sys
from PyQt5.QtCore import QCoreApplication
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QToolTip, QMainWindow, QAction, qApp
from PyQt5.QtGui import QFont
from PyQt5.QtGui import QIcon
class MyApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    def initUI(self):
        self.statusBar().showMessage('Ready')   #하단 상태바 메시지 출력
        #항목 생성, 하단 상태바 작업
        exitAction = QAction(QIcon('exit.png'), 'Exit', self)
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit application')
        exitAction.triggered.connect(qApp.quit)
        self.statusBar()
        #메뉴바 생성
        menubar = self.menuBar()
        menubar.setNativeMenuBar(False)
        menubar.setStatusTip('menubar now')
        fileMenu = menubar.addMenu('&File')
        fileMenu.setStatusTip('file menu')
        fileMenu.addAction(exitAction)  #메뉴에 항목 넣기

        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(exitAction)
        QToolTip.setFont(QFont('SansSerif', 10))
        #self.setToolTip('This is a <b>QWidget</b> widget')
        btn = QPushButton('Button', self)
        btn.setToolTip('This is a <b>QPushButton</b> widget')
        btn.move(50, 100)
        btn.resize(btn.sizeHint())
        btn2 = QPushButton('Quit', self)
        btn2.move(200, 100)
        btn2.resize(btn.sizeHint())
        btn2.clicked.connect(QCoreApplication.instance().quit)
        self.setWindowTitle('Quit Button')
        self.setGeometry(300, 300, 300, 200)
        self.show()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())