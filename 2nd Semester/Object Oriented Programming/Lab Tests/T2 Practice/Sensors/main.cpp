#include <iostream>
#include "ui.h"

int main()
{
  // Sensor *tm = new TemperatureSensor("Prod1", 10, 20);
  // tm->addRecording(20);
  // tm->addRecording(30);
  // tm->addRecording(40);
  // std::cout << tm->toString() << '\n';

  // Sensor *hm = new HumiditySensor("Prod2");
  // hm->addRecording(50);
  // hm->addRecording(60);
  // hm->addRecording(70);
  // std::cout << hm->toString() << '\n';

  // Sensor *sm = new SmokeSensor("Prod3");
  // sm->addRecording(80);
  // sm->addRecording(90);
  // sm->addRecording(100);
  // std::cout << sm->toString() << '\n';
  UI ui = UI();
  ui.runApp();
  return 0;
}