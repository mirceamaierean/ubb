import unittest
from domain import taxi

from services import TaxisService

class TestTaxis(unittest.TestCase):
  def test_taxi_ride(self):
    # We will have 3 taxis, that we will add manually, in order to test which taxi will be taken
    taxis_service = TaxisService(3) 
    # The taxis
    taxis_service.add_taxi(taxi(1, 10, 10, 0))
    taxis_service.add_taxi(taxi(2, 50, 50, 0))
    taxis_service.add_taxi(taxi(3, 100, 100, 0))

    # We will ride from (40, 40) to (90, 90)
    taxis_service.ride(40, 40, 90, 90) 

    # The second taxi should be chosen, having the ID 2. Since it was the one that performed the ride, when we return the list of sorted taxis, we will have it as the first one
    taxis = taxis_service.sort_taxis()
    self.assertEqual(taxis[0].id, 2)
    self.assertEqual(taxis[0].fare, 100)
    self.assertEqual(taxis[0].x, 90)
    self.assertEqual(taxis[0].y, 90)
    