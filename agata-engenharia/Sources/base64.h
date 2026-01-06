/*
 * base64.h
 *
 *  Created on: 10/09/2023
 *      Author: marcos.butignol
 */

char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length);


unsigned char *base64_decode(const char *data,
                             size_t input_length,
                             size_t *output_length);


void build_decoding_table();

void base64_cleanup();

