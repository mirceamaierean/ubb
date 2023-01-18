from repository.BinaryFileRepository import BinaryFileRepository
from repository.DBRepository import DBRepository
from repository.JSONRepository import JSONRepository
from repository.MemoryRepository import MemoryRepository
from repository.TextFileRepository import TextFileRepository
from tests.tests import Test
from ui.ui import UI
from jproperties import Properties

def test_all_reporsitories():
  memo_repo_test = MemoryRepository()
  text_repo_test = TextFileRepository("students_test.txt")
  bin_repo_test = BinaryFileRepository("students_test.bin")
  json_repo_test = JSONRepository("students_test.json")

  tests_memory_repository = Test(memo_repo_test)
  tests_memory_repository.test_all()

  tests_memory_repository = Test(text_repo_test)
  tests_memory_repository.test_all()

  tests_memory_repository = Test(bin_repo_test)
  tests_memory_repository.test_all()

  tests_memory_repository = Test(json_repo_test)
  tests_memory_repository.test_all()

def get_repo_from_properties():
  configs = Properties()
  with open('settings.properties', 'rb') as config_file:
      configs.load(config_file)

  repo_string = configs.get("REPO").data
  repo = ""

  if repo_string == "Memory":
    repo = MemoryRepository()
    
  elif repo_string == "Text":
    repo = TextFileRepository()

  elif repo_string == "Binary":
    repo = BinaryFileRepository()

  elif repo_string == "JSON":
    repo = JSONRepository()

  elif repo_string == "DB":
    repo = DBRepository()

  return repo

test_all_reporsitories()

ui = UI(get_repo_from_properties())
ui.print_ui()