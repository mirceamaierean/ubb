from pathlib import Path
import sys

path_root = Path(__file__).parents[2]
sys.path.append(str(path_root))

from ui.gui import GUI
from ui.ui import UI

gui = GUI()
gui.run_main_window()
