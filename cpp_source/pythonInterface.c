/*
 * export.c
 *
 *  Created on: Nov 24, 2015
 *      Author: tim
 */

#include <basicOps.cuh>

// We cannot call templated code from C, so we wrap the template in a C compatible call here if necessary.
void estimateQuantiles_fp32(float *A, float *code, float offset, int n){ estimateQuantiles<float>(A, code, offset, n); }
void estimateQuantiles_fp16(half *A, float *code, float offset, int n){ estimateQuantiles<half>(A, code, offset, n); }

void adam32bit(float *g, float *p,
               float* state1, float* state2,
               const float beta1, const float beta2, const float eps, const float weight_decay,
               const int step, const float lr, const int n){ optimizer_32bit_2State<float, 0>(g, p, state1, state2, beta1, beta2, eps, weight_decay, step, lr, n); }

extern "C"
{
	void cestimate_quantiles_fp32(float *A, float *code, float offset, int n){ estimateQuantiles_fp32(A, code, offset, n); }
	void cestimate_quantiles_fp16(half *A, float *code, float offset, int n){ estimateQuantiles_fp16(A, code, offset, n); }
	void cquantize(float *code, float *A, unsigned char *out, int n){ quantize(code, A, out, n); }
	void cdequantize(float *code, unsigned char *A, float *out, int n){ dequantize(code, A, out, n); }
	void cadam32bit(float *g, float *p,
								 float* state1, float* state2,
								 const float beta1, const float beta2, const float eps, const float weight_decay,
								 const int step, const float lr, const int n){ adam32bit(g, p, state1, state2, beta1, beta2, eps, weight_decay, step, lr, n); }
}

