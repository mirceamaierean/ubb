from tests.tests import TestBoard
from ui.ui import UI, GUI

tests = TestBoard()
tests.testAll()

ui = UI()
gui = GUI()

# ui.run()
gui.run()
