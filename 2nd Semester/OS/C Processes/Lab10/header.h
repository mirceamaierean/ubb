#ifndef HEADER_H_
#define HEADER_H_

char *myfifo1 = "./myfifo1";
char *myfifo2 = "./myfifo2";
char *myfifo3 = "./myfifo3";

void unlink_fifos()
{
  unlink(myfifo1);
  unlink(myfifo2);
  unlink(myfifo3);
}

#endif