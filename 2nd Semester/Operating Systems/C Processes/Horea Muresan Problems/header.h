#ifndef HEADER_H_
#define HEADER_H_

char *myfifo1 = "./myfifo1";
char *myfifo2 = "./myfifo2";

void unlink_fifo()
{
  unlink(myfifo1);
  unlink(myfifo2);
}

#endif