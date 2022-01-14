#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include "crc.h"

// https://www.youtube.com/watch?v=M9ZwuIv3xz8

#define PNG_SIG_CAP 8
const uint8_t png_sig[] = {137, 80, 78, 71, 13, 10, 26, 10};

void reverse_bytes(void *bytes, size_t buf_cap)
{
   uint8_t *buf = bytes;
   for (size_t i = 0; i < buf_cap / 2; ++i)
   {
      uint8_t t = buf[i];
      buf[i] = buf[buf_cap - i - 1];
      buf[buf_cap - i - 1] = t;
   }
}

#define read_bytes(f, buf, buf_cap) read_bytes_(f, buf, buf_cap, __FILE__, __LINE__)

void read_bytes_(FILE *f, void *buf, size_t buf_cap, const char *source_file, int source_line)
{
   size_t n = fread(buf, buf_cap, 1, f);
   if (n != 1)
   {
      if (ferror(f))
      {
         fprintf(stderr, "%s:%d: ERROR: could not read %zu bytes from file: %s\n",
                        source_file, source_line,
                        buf_cap, strerror(errno));
         exit(3);
      }
      else if (feof(f))
      {
         fprintf(stderr, "%s:%d: ERROR: could not read %zu bytes from file: reached end of file\n",
                        source_file, source_line,
                        buf_cap);
         exit(4);
      }
      else
      {
         assert(0 && "unreachable");
      }
   }
}

void print_bytes(uint8_t *buf, size_t buf_cap)
{
   for (size_t i = 0; i < buf_cap; ++i)
   {
      printf("%u ", buf[i]);
   }

   printf("\n");
}

#define write_bytes(f, buf, buf_cap) write_bytes_(f, buf, buf_cap, __FILE__, __LINE__)

void write_bytes_(FILE *file, void *bytes, size_t buf_cap, const char* source_file, int source_line)
{
   size_t n = fwrite(bytes, buf_cap, 1, file);
   if (n != 1)
   {
      if (ferror(file))
      {
         fprintf(stderr, "%s:%d: ERROR: could write %zu bytes to file: %s\n",
                        source_file, source_line,
                        buf_cap, strerror(errno));
         exit(5);
      }
      else
      {
         assert(0 && "unreachable");
      }
   }
}

void inject_custom_chunk(FILE *file, void *buf, size_t buf_cap,
                        uint8_t chunk_type[4],
                        uint32_t chunk_crc)
{
   uint32_t chunk_sz = buf_cap;
   reverse_bytes(&chunk_sz, sizeof(chunk_sz));
   write_bytes(file, &chunk_sz, sizeof(chunk_sz));
   write_bytes(file, chunk_type, 4);
   write_bytes(file, buf, buf_cap);
   write_bytes(file, &chunk_crc, sizeof(chunk_crc));
}

void usage(FILE *file, char *program)
{
      fprintf(file, "Usage: %s <input.png> <output.png>\n", program);
}

#define CHUNK_BUF_CAP (32 * 1024)
uint8_t chunk_buf[CHUNK_BUF_CAP];

int main(int argc, char **argv)
{
   (void) argc;
   assert(*argv != NULL);
   char *program = *argv++;

   if (*argv == NULL)
   {
      usage(stderr, program);
      fprintf(stderr, "ERROR: no inputfile\n");
      exit(1);
   }

   char *input_filepath = *argv++;

   if (*argv == NULL)
   {
      usage(stderr, program);
      fprintf(stderr, "ERROR: no outputfile\n");
      exit(1);
   }

   char *output_filepath = *argv++;

   printf("Inspected file is %s\n", input_filepath);
   printf("Creating file %s\n", output_filepath);

   FILE *input_file = fopen(input_filepath, "rb");
   if (input_file == NULL)
   {
      fprintf(stderr, "ERROR: could not open file %s: %s\n",
            input_filepath, strerror(errno));
      exit(1);
   }

   FILE *output_file  = fopen(output_filepath, "wb");
   if (output_file == NULL)
   {
      fprintf(stderr, "ERROR: coud not open file %s: %s\n",
                     output_filepath, strerror(errno));
      exit(6);
   }

   uint8_t sig[PNG_SIG_CAP];
   read_bytes(input_file, sig, sizeof(sig));
   write_bytes(output_file, sig, sizeof(sig));

   printf("Signature: ");
   print_bytes(sig, sizeof(sig));
   if (memcmp(sig, png_sig, PNG_SIG_CAP) != 0)
   {
      fprintf(stderr, "ERROR: %s does not appear to be a valid PNG image\n",
                     input_filepath);
      exit(2);
   }

   printf("%s is a valid PNG image\n", input_filepath);

   bool quit = false;
   while (!quit)
   {
      uint32_t chunk_size;
      read_bytes(input_file, &chunk_size, sizeof(chunk_size));
      write_bytes(output_file, &chunk_size, sizeof(chunk_size));
      reverse_bytes(&chunk_size, sizeof(chunk_size));

      uint8_t chunk_type[4];
      read_bytes(input_file, chunk_type, sizeof(chunk_type));
      write_bytes(output_file, chunk_type, sizeof(chunk_type));

      if (*(uint32_t*)chunk_type == 0x444E4549) // IEND
      {
         quit = true;
      }

      size_t n = chunk_size;
      while (n > 0)
      {
         size_t m = n;
         if (m > CHUNK_BUF_CAP)
         {
            m = CHUNK_BUF_CAP;
         }

         read_bytes(input_file, chunk_buf, m);
         write_bytes(output_file, chunk_buf, m);
         n -= m;
      }

      uint32_t chunk_crc;
      read_bytes(input_file, &chunk_crc, sizeof(chunk_crc));
      write_bytes(output_file, &chunk_crc, sizeof(chunk_crc));
      // reverse_bytes(&chunk_crc, sizeof(chunk_crc));

      if (*(uint32_t*)chunk_type == 0x52444849) // IHDR
      {
         char* data = "Hello Everybody !!!";
         uint32_t data_size = strlen(data);

         uint32_t injected_sz = data_size;
         reverse_bytes(&injected_sz, sizeof(injected_sz));
         char* injected_data = data;
         char* injected_type =  "peHu";
         uint32_t injected_crc = crc(injected_data, data_size);

         write_bytes(output_file, &injected_sz, sizeof(injected_sz));
         write_bytes(output_file, injected_type, 4);
         write_bytes(output_file, injected_data, data_size);
         write_bytes(output_file, &injected_crc, sizeof(injected_crc));
         // inject_custom_chunk(
      }

      // print_bytes(chunk_type, sizeof(chunk_type));
      printf("Chunk type: %.*s (0x%08X)\n",
         (int)sizeof(chunk_type), chunk_type,
         *(uint32_t*) chunk_type);
      printf("Chunk size: %d\n", chunk_size);
      printf("Chunk CRC:  0x%08X\n", chunk_crc);
      printf("-----------------------\n");
   }

   fclose(input_file);
   fclose(output_file);
}
