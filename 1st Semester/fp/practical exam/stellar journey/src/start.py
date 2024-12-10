from tests.tests import Test
from ui.ui import UI

def start():
  test = Test()
  test.test_valid_star_position()
  ui = UI()
  ui.play()

start()

