from services import TaxisService


class UI:
  def __init__(self):
    self.__service = TaxisService(self.get_length())

  
  def get_length(self):
    n = int(input("How many taxis should we have? "))
    while n < 1 or n > 10:
      print("The number of taxis is invalid. Please try again")
      n = int(input("How many taxis should we have? "))
    return n

  def print_taxis(self):
    self.__service.sort_taxis()
    for ex_taxi in self.__service.get_taxis():
      taxi_str = "Taxi ID: " + str(ex_taxi.id) + " X: " + str(ex_taxi.x) + " Y: " + str(ex_taxi.y) + " Fare: " + str(ex_taxi.fare)
      print (taxi_str)

  def print_ui(self):
    self.__service.generate_random_taxis()
    while True:
      print ("1. Add manualy a ride")
      print ("2. Simualte a ride")
      print ("3. Display the situation of taxis")
      option = input("Choose your option: ")

      if option == "1":
        start_x = int(input("What is the x coordinate of the start point? "))
        start_y = int(input("What is the y coordinate of the start point? "))
        if not self.__service.validate_coordinate(start_x, start_y):
          print ("Invalid coordinates. Please Try again")
          continue
        end_x = int(input("What is the x coordinate of the end point? "))
        end_y = int(input("What is the y coordinate of the end point? "))

        if not self.__service.validate_coordinate(end_x, end_y):
          print ("Invalid coordinates. Please Try again")
          continue
          
        self.__service.ride(start_x, start_y, end_x, end_y)
        self.print_taxis()
      
      elif option == "2":
        start_x, start_y, end_x, end_y = self.__service.simulate_ride()
        print("The ride was from point(" + str(start_x) + ", " + str(start_y) + ") to point(" + str(end_x) + ", " + str(end_y) + ")")
        self.print_taxis()

      else: 
        print("Invalid option. Please try again")
      
        
      