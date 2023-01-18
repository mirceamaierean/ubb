from src.repository.repository_exception import RepositoryException


class Repository:
  def __init__(self):
    self._data = {}

  def check_if_present(self, id: int):
    if id in self._data:
      raise RepositoryException("This instance is already in the repository")

  def check_if_not_present(self, id: int):
    if id not in self._data:
      raise RepositoryException("This instance is not in the respository")

  def get_element_by_id(self, id: int):
    return self._data[id]

  def add(self, obj):
    self.check_if_present(obj.id)
    self._data[obj.id] = obj
  
  def remove(self, id: int):
    self.check_if_not_present(id)
    del self._data[id]

  def update(self, obj):
    self.check_if_not_present(obj.id)
    self._data[obj.id] = obj

  def search_after_id(self, id: int):
    list_of_instances = []
    
    id = str(id)
    
    for obj in self._data.values():
      obj_id = str(obj.id)
      if id in obj_id:
        list_of_instances.append(obj)
    
    return list_of_instances

  def search_after_name(self, name: str):
    list_of_instances = []
    
    name = name.lower()
    
    for obj in self._data.values():
      obj_name = obj.name.lower()
      if name in obj_name:
        list_of_instances.append(obj)
    
    return list_of_instances

  def get_all(self):
    return list(self._data.values())

  def get_all_ids(self):
    return list(self._data.keys())

  def delete_all(self):
    self._data.clear()