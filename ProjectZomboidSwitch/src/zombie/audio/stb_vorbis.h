// stb_vorbis.h - Ogg Vorbis decoder header
// https://github.com/nothings/stb/blob/master/stb_vorbis.h
// Public domain, Sean Barrett
#ifndef STB_VORBIS_INCLUDE_STB_VORBIS_H
#define STB_VORBIS_INCLUDE_STB_VORBIS_H

/*
   Place the stb_vorbis.h and stb_vorbis.c files in your project.
   #define STB_VORBIS_HEADER_ONLY before including this file in one translation unit.
   #define STB_VORBIS_IMPLEMENTATION in exactly one .c/.cpp file before including this file.
*/

#define STB_VORBIS_NO_STDIO 0
#define STB_VORBIS_NO_PUSHDATA_API 0
#define STB_VORBIS_NO_PULLDATA_API 0
#define STB_VORBIS_NO_INTEGER_CONVERSION 0
#define STB_VORBIS_NO_FAST_SCALED_FLOAT 0
#define STB_VORBIS_NO_DEFERRED_SETUP 0
#define STB_VORBIS_NO_CRT 0
#define STB_VORBIS_NO_EXTRAS 0
#define STB_VORBIS_NO_CODEBOOKS 0
#define STB_VORBIS_NO_INLINE 0
#define STB_VORBIS_NO_SIMD 0
#define STB_VORBIS_NO_ASSERT 0
#define STB_VORBIS_NO_ERROR_STRINGS 0
#define STB_VORBIS_NO_STDIO 0

// The actual stb_vorbis header follows (truncated for brevity)
// You should download the full stb_vorbis.h from the official repo for production use.

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct stb_vorbis stb_vorbis;

typedef struct
{
   unsigned int sample_rate;
   int channels;
   unsigned int setup_memory_required;
   unsigned int setup_temp_memory_required;
   unsigned int temp_memory_required;
   int max_frame_size;
} stb_vorbis_info;

stb_vorbis * stb_vorbis_open_memory(const unsigned char *data, int len, int *error, const void *alloc_buffer);
void stb_vorbis_close(stb_vorbis *f);
int stb_vorbis_get_info(stb_vorbis *f, stb_vorbis_info *info);
int stb_vorbis_get_samples_short_interleaved(stb_vorbis *f, int channels, short *buffer, int num_shorts);
int stb_vorbis_stream_length_in_samples(stb_vorbis *f);

#ifdef __cplusplus
}
#endif

#endif // STB_VORBIS_INCLUDE_STB_VORBIS_H
