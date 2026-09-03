#ifndef FASTALP_C_H
#define FASTALP_C_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Computes maximum possible compressed buffer size in bytes for len f64 values.
 * ---
 * 计算 len 个 f64 浮点数值在最差情况下所需的最大压缩缓冲区字节大小。
 */
size_t fastalp_max_compressed_size_f64(size_t len);

/*
 * Computes maximum possible compressed buffer size in bytes for len f32 values.
 * ---
 * 计算 len 个 f32 浮点数值在最差情况下所需的最大压缩缓冲区字节大小。
 */
size_t fastalp_max_compressed_size_f32(size_t len);

/*
 * Resets cached model parameters for thread-local f64 encoder.
 * ---
 * 重置当前线程局部双精度 (f64) 状态化编码器的已缓存模型参数。
 */
void fastalp_reset_encoder_f64(void);

/*
 * Resets cached model parameters for thread-local f32 encoder.
 * ---
 * 重置当前线程局部单精度 (f32) 状态化编码器的已缓存模型参数。
 */
void fastalp_reset_encoder_f32(void);

/*
 * Compresses an array of f64 floating-point values with dynamic parameter sampling.
 * Returns bytes written, or 0 on error or insufficient capacity.
 * ---
 * 压缩 f64 浮点数组（包含动态模型参数采样探测）。
 * 返回实际写入字节数；出错或容量不足时返回 0。
 */
size_t fastalp_compress_f64(const double* src, size_t len, uint8_t* dst, size_t dst_cap);

/*
 * Compresses an array of f64 values by reusing cached parameters from thread-local encoder.
 * Skips sampling overhead, suitable for high-throughput streaming pipelines.
 * Returns bytes written, or 0 on error or insufficient capacity.
 * ---
 * 复用线程局部编码器已缓存的模型参数压缩 f64 浮点数组。
 * 跳过重复采样开销，直接执行核心编码内核，适用于平稳时序数据的高吞吐流式批量压缩。
 * 返回实际写入字节数；出错或容量不足时返回 0。
 */
size_t fastalp_compress_cached_f64(const double* src, size_t len, uint8_t* dst, size_t dst_cap);

/*
 * Decompresses a byte buffer into an array of f64 floating-point values.
 * Returns number of decompressed f64 values, or 0 on error or insufficient capacity.
 * ---
 * 解压字节缓冲区至 f64 浮点数组。
 * 返回实际解压出的 f64 浮点元素个数；出错或容量不足时返回 0。
 */
size_t fastalp_decompress_f64(const uint8_t* src, size_t src_len, double* dst, size_t dst_cap);

/*
 * Compresses an array of f32 floating-point values with dynamic parameter sampling.
 * Returns bytes written, or 0 on error or insufficient capacity.
 * ---
 * 压缩 f32 浮点数组（包含动态模型参数采样探测）。
 * 返回实际写入字节数；出错或容量不足时返回 0。
 */
size_t fastalp_compress_f32(const float* src, size_t len, uint8_t* dst, size_t dst_cap);

/*
 * Compresses an array of f32 values by reusing cached parameters from thread-local encoder.
 * Skips sampling overhead, suitable for high-throughput streaming pipelines.
 * Returns bytes written, or 0 on error or insufficient capacity.
 * ---
 * 复用线程局部编码器已缓存的模型参数压缩 f32 浮点数组。
 * 跳过重复采样开销，直接执行核心编码内核，适用于平稳时序数据的高吞吐流式批量压缩。
 * 返回实际写入字节数；出错或容量不足时返回 0。
 */
size_t fastalp_compress_cached_f32(const float* src, size_t len, uint8_t* dst, size_t dst_cap);

/*
 * Decompresses a byte buffer into an array of f32 floating-point values.
 * Returns number of decompressed f32 values, or 0 on error or insufficient capacity.
 * ---
 * 解压字节缓冲区至 f32 浮点数组。
 * 返回实际解压出的 f32 浮点元素个数；出错或容量不足时返回 0。
 */
size_t fastalp_decompress_f32(const uint8_t* src, size_t src_len, float* dst, size_t dst_cap);

/*
 * Stateful handle-based API for independent instances (f64).
 * ---
 * 独立实例句柄 API（f64）。
 */
typedef struct FastAlpEncoderF64 FastAlpEncoderF64;
FastAlpEncoderF64* fastalp_encoder_f64_new(void);
void fastalp_encoder_f64_free(FastAlpEncoderF64* enc);
void fastalp_encoder_f64_reset(FastAlpEncoderF64* enc);
size_t fastalp_encoder_f64_compress(FastAlpEncoderF64* enc, const double* src, size_t len, uint8_t* dst, size_t dst_cap);

/*
 * Stateful handle-based API for independent instances (f32).
 * ---
 * 独立实例句柄 API（f32）。
 */
typedef struct FastAlpEncoderF32 FastAlpEncoderF32;
FastAlpEncoderF32* fastalp_encoder_f32_new(void);
void fastalp_encoder_f32_free(FastAlpEncoderF32* enc);
void fastalp_encoder_f32_reset(FastAlpEncoderF32* enc);
size_t fastalp_encoder_f32_compress(FastAlpEncoderF32* enc, const float* src, size_t len, uint8_t* dst, size_t dst_cap);

#ifdef __cplusplus
}
#endif

#endif // FASTALP_C_H
