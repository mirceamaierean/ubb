#
# This module is used to invoke the program's UI and start it. It should not contain a lot of code.
#
import ui
import tests

def start():
  tests.test_all()
  ui.print_ui()

start()