  #include "utf8_file.h"

  #include <asm-generic/errno-base.h>
  #include <stdio.h>  // delete
  #include <errno.h>
  #include <fcntl.h>
  #include <stddef.h>
  #include <stdlib.h>
  #include <unistd.h>

  size_t encode_utf8(unsigned c, unsigned char* buffer) {
    unsigned cur_cntr = 0;
    unsigned mask[5] = {0xC0, 0xE0, 0xF0, 0xF8, 0xFC};
    if (c <= 0x0000007F) {  // 1 byte
      buffer[0] = (unsigned char)c;
      return 1;
    } else {
      if (c <= 0x000007FF) {  // 2 bytes
        cur_cntr = 1;
      } else if (c <= 0x0000FFFF) {  // 3 bytes
        cur_cntr = 2;
      } else if (c <= 0x001FFFFF) {  // 4 bytes
        cur_cntr = 3;
      } else if (c <= 0x03FFFFFF) {  // 5 bytes
        cur_cntr = 4;
      } else if (c <= 0x7FFFFFFF) {  // 6 bytes
        cur_cntr = 5;
      } else {  // more than 6 bytes
        return 0;
      }
      for (unsigned i = 0, delta = cur_cntr * 6; i <= cur_cntr; ++i, delta -= 6) {
        buffer[i] = ((i == 0) ? mask[cur_cntr - 1] : 0x80) |
                    ((c >> delta) & ((i == 0) ? 0xFF : 0x3F));
      }
      return cur_cntr + 1;
    }
  }

  int utf8_write(utf8_file_t* f, const unsigned* str, size_t count) {
    size_t cntr = 0;             // counter how many we read
    unsigned char buf[6] = {};   // buffer for keep a charecter
    size_t res_of_encode = 0;    // variable to keep reuslt of encoding
    long long res_of_write = 0;  // variable to keep result of function whrite
    for (unsigned i = 0; i < count; ++i) {
      res_of_encode = encode_utf8(str[i], buf);
      if (res_of_encode == 0) {
        errno = EILSEQ;
        return -1;
      }
      res_of_write = write(f->fd, buf, res_of_encode);
      if (res_of_write == -1) {
        if (errno == EINTR) {
          continue;
        }
        return -1;
      }
      if (res_of_write == res_of_encode) {
        cntr += res_of_encode;
      } else {
        return -1;  // did not finish reading
      }
    }
    return cntr;
  }

  int utf8_read(utf8_file_t* f, unsigned* res, size_t count) {
    size_t cntr = 0;            // counter how many we read
    unsigned cur_res = 0;       // current charecter
    unsigned cur_cntr = 0;      // current size of charecter
    unsigned char cur = 0;      // current charecter
    long long res_of_read = 0;  // variable to keep result of function read
    unsigned mask[5] = {0x1F, 0x0F, 0x07, 0x03, 0x01};
    while (cntr < count) {
      res_of_read = read(f->fd, &cur, 1);
      if (res_of_read == -1) {
        if (errno == EINTR)
          continue;  // system call was interrupted, let's try again
        return -1;   // read error
      }
      if (res_of_read == 0) {
        break;
      }
      if (cur <= 0x7F) {  // 1 byte
        res[cntr++] = (unsigned)cur;
      } else {
        cur_cntr = 0;
        cur_res = 0;
        f->buffer[0] = cur;
        if ((cur & 0xE0) == 0xC0) {  // 2 bytes
          cur_cntr = 1;
        } else if ((cur & 0xF0) == 0xE0) {  // 3 bytes
          cur_cntr = 2;
        } else if ((cur & 0xF8) == 0xF0) {  // 4 bytes
          cur_cntr = 3;
        } else if ((cur & 0xFC) == 0xF8) {  // 5 bytes
          cur_cntr = 4;
        } else if ((cur & 0xFE) == 0xFC) {  // 6 bytes
          cur_cntr = 5;
        } else {
          return -1;
        }
        for (unsigned i = 1; i <= cur_cntr; ++i) {
          res_of_read = read(f->fd, f->buffer + i, 1);
          if (res_of_read == -1) {
            if (errno == EINTR)
              continue;  // system call was interrupted, let's try again
            return -1;   // read error
          }
          if (res_of_read == 0) {
            return -1;
            // stoped read in middle of charecter
          }
          if ((f->buffer[i] & 0xC0) != 0x80) {
            return -1;
          }
        }
        for (unsigned i = cur_cntr, delta = 0; i <= cur_cntr; --i, delta += 6) {
          cur_res |= ((((unsigned)f->buffer[i]) &
                       (unsigned)((i != 0) ? (0x3F) : (mask[cur_cntr - 1])))
                      << delta);
        }
        res[cntr++] = cur_res;
      }
    }
    return cntr;
  }

  utf8_file_t* utf8_fromfd(int fd) {
    utf8_file_t* f_ptr = (utf8_file_t*)malloc(sizeof(utf8_file_t));
    if (f_ptr == 0) {
      errno = ENOMEM;
      return NULL;
    }
    f_ptr->fd = fd;
    f_ptr->idx = 0;
    return f_ptr;
  }
